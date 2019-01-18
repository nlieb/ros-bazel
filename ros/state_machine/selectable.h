#pragma once

#include <unistd.h>
#include <sys/eventfd.h>
#include <sys/timerfd.h>
#include <poll.h>

#include <string.h>

#include <vector>
#include <mutex>
#include <thread>


namespace slct {

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


// Convert to pointer if it's a ref: https://stackoverflow.com/a/14466705
template<typename T>
T* ptr(T& obj) { return &obj; }
template<typename T>
T* ptr(T* obj) { return obj; }
template<typename T>
std::shared_ptr<T> ptr(std::shared_ptr<T> obj) { return obj; }

std::pair<std::vector<struct pollfd>, std::vector<int>>
collect_pollfds() {
  return std::make_pair(std::vector<struct pollfd>(), std::vector<int>());
}

template<typename T, typename... Args>
std::pair<
  std::vector<struct pollfd>,
  std::vector<int>>
collect_pollfds(T& first, Args&... rest) {
  std::vector<int> fds = ptr(first)->get_waitfds();

  std::vector<struct pollfd> pollfds;
  std::vector<int> waitable_pollfd_lens{(int)fds.size()};
  for(auto& fd : fds) {
    pollfds.push_back({fd, POLLIN, 0});
  }

  auto rest_pollfds_tuple = collect_pollfds(rest...);
  std::vector<struct pollfd>& rest_pollfds = rest_pollfds_tuple.first;
  std::vector<int>& rest_waitable_pollfd_lens = rest_pollfds_tuple.second;

  // merge
  pollfds.insert(pollfds.end(), rest_pollfds.begin(), rest_pollfds.end());
  waitable_pollfd_lens.insert(waitable_pollfd_lens.end(), rest_waitable_pollfd_lens.begin(), rest_waitable_pollfd_lens.end());

  return std::make_pair(pollfds, waitable_pollfd_lens);
}

int select_(std::vector<struct pollfd>& pollfds, std::vector<int>& waitable_pollfd_lens) {
  uint64_t u = 1;
  poll(&pollfds[0], pollfds.size(), -1);

  int triggered_fd_id = 0;
  for(int i = 0; i < (int)pollfds.size(); ++i) {
    if(pollfds[i].revents) {
      do { read(pollfds[i].fd, &u, sizeof(uint64_t)); } while (errno != EAGAIN);
      triggered_fd_id = i;
      break;
    }
  }

  int sum = 0;
  for(int j = 0; j < (int)waitable_pollfd_lens.size(); ++j) {
    sum += waitable_pollfd_lens[j];
    if (sum > triggered_fd_id)
      return j;
  }
  assert(false);
}

template<typename T, typename... Args>
int select(T& first, Args&... rest) {
  auto pollfds_tuple = collect_pollfds(first, rest...);
  auto& pollfds = pollfds_tuple.first;
  auto& waitable_pollfd_lens = pollfds_tuple.second;

  return select_(pollfds, waitable_pollfd_lens);
}


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


class ServiceCallSelectable :
        public EventSelectable,
        public std::enable_shared_from_this<ServiceCallSelectable> {
public:
    static std::shared_ptr<ServiceCallSelectable> create() {
      return std::shared_ptr<ServiceCallSelectable>(new ServiceCallSelectable());
    }

    ~ServiceCallSelectable() {
      thread_.detach();
    }

    template<class M>
    void call(ros::ServiceClient& client, M& srv) {
      thread_ = std::thread([&client, &srv] (std::weak_ptr<ServiceCallSelectable> wk_parent) {
          bool success = client.call(srv);

          if(auto parent = wk_parent.lock()) {
            // lock to prevent the enclosing ServiceCallSelectable object from
            // being destructed while we mutate its state
            parent->success = success;
            parent->signal_event();
          }
          // else, the enclosing object has been destructed, do nothing
      }, std::weak_ptr<ServiceCallSelectable>(shared_from_this()));
    }
    bool success;

private:
    ServiceCallSelectable() : success(false) {}
    std::thread thread_;
};

}