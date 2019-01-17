#pragma once

#include <unistd.h>
#include <sys/eventfd.h>
#include <sys/timerfd.h>
#include <poll.h>

#include <string.h>

#include <vector>
#include <mutex>
#include <thread>


void handle_error(const char *str) {
  fprintf(stderr, "%s: %s", str, strerror(errno));
  exit(EXIT_FAILURE);
}


class Selectable {
public:
    virtual std::vector<int> get_waitfds() = 0;
};


class Context : public Selectable {
public:
    explicit Context(int timeout) :
            timeout_spec_({{0, 0},{timeout, 0}}),
            timerfd_(timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK)),
            cancel_eventfd_(eventfd(0, EFD_NONBLOCK))
    {
      if (cancel_eventfd_ == -1) handle_error("eventfd");
      if (timerfd_ == -1) handle_error("timerfd_create");
      if (timerfd_settime(timerfd_, 0, &timeout_spec_, nullptr) == -1) handle_error("timerfd_settime");
    }
    ~Context() {
      close(timerfd_);
      close(cancel_eventfd_);
    }

    void cancel() {
      std::lock_guard<std::mutex> guard(m_);
      uint64_t u = 1;
      ssize_t s;
      s = write(cancel_eventfd_, &u, sizeof(uint64_t));
      if (s != sizeof(uint64_t)) handle_error("write");
    }

    std::vector<int> get_waitfds() override {
      return {timerfd_, cancel_eventfd_};
    };

private:
    std::mutex m_;
    const struct itimerspec timeout_spec_;
    const int timerfd_;
    const int cancel_eventfd_;
};


class Select {
public:
    explicit Select(std::vector<Selectable*> waitables) {
      int counter = 0;
      for(auto& waitable : waitables) {
        for(auto& waitfd : waitable->get_waitfds()) {
          pollfds.push_back({waitfd, POLLIN, 0});
          counter++;
        }
        waitable_pollfd_poses.push_back(counter);
      }
    }

    int select() {
      uint64_t u = 1;
      poll(&pollfds[0], pollfds.size(), -1);

      int i = 0;
      for(; i < (int)pollfds.size(); ++i) {
        if(pollfds[i].revents) {
          do { read(pollfds[i].fd, &u, sizeof(uint64_t)); } while (errno != EAGAIN);
          break;
        }
      }
      for(int j = 0; j < (int)waitable_pollfd_poses.size(); ++j)
        if(i < (int)waitable_pollfd_poses[j])
          return j;
      return -1;
    }

private:
    std::vector<struct pollfd> pollfds;
    std::vector<int> waitable_pollfd_poses;
};


class EventSelectable : public Selectable {
public:
    EventSelectable() : eventfd_(eventfd(0, EFD_NONBLOCK)) {
      if (eventfd_ == -1) handle_error("eventfd");
    }
    ~EventSelectable() {
      close(eventfd_);
    }

    std::vector<int> get_waitfds() override {
      return {eventfd_};
    }

    void signal_event() {
      uint64_t u = 1;
      ssize_t s;
      s = write(eventfd_, &u, sizeof(uint64_t));
      if (s != sizeof(uint64_t)) handle_error("write");
    }

private:
    const int eventfd_;
};


template<class M>
class ServiceCall : public EventSelectable {
public:
    ServiceCall(ros::ServiceClient& client, M& srv) :
            success(false),
            destruct_mutex_(std::make_shared<std::mutex>()) {

      thread_ = std::thread([this, &client, &srv] (std::weak_ptr<std::mutex> wk_destruct_mutex) {
          bool success = client.call(srv);

          if(auto m = wk_destruct_mutex.lock()) {
            // lock to prevent the enclosing ServiceCall object from
            // being destructed while we mutate its state
            std::lock_guard<std::mutex> guard(*m);
            this->success = success;
            this->signal_event();
          }
          // else, the enclosing object has been destructed, do nothing
      }, std::weak_ptr<std::mutex>(destruct_mutex_));
    }
    ~ServiceCall() {
      std::lock_guard<std::mutex> guard(*destruct_mutex_);
      thread_.detach();
    }

    bool success;

private:
    std::shared_ptr<std::mutex> destruct_mutex_;
    std::thread thread_;
};
