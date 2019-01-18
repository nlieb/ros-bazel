#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "std_srvs/SetBool.h"

#include <sys/eventfd.h>
#include <sys/timerfd.h>
#include <poll.h>

#include <mutex>
#include <thread>
#include <functional>

#include "selectable.h"


class WorldState : public slct::EventSelectable {
public:
    void update_ping() {
      std::lock_guard<std::mutex> guard(m_);
      pings_ += 1;
      signal_event();
    }

    int get_pings() {
      std::lock_guard<std::mutex> guard(m_);
      return pings_;
    }

private:
    std::mutex m_;
    int pings_ = 0;
};


struct StateMachineData {
    StateMachineData() : world_state(new WorldState()) {}
    std::unique_ptr<WorldState> world_state;

    // Publishers (ie callbacks)
    ros::Publisher pong_pub;
    ros::ServiceClient toggle_client;
};


int call_set_bool(slct::Context& ctx, std::shared_ptr<StateMachineData>& sm_data) {
  printf("Sending SetBool service call\n");

  auto service_sel = slct::ServiceCallSelectable::create();
  std_srvs::SetBool set_bool{}; // default false
  service_sel->call(sm_data->toggle_client, set_bool);

  switch (select(ctx, service_sel)) {
    case 0:
      printf("Timeout\n");
      return -1;
    case 1:
      printf("SetBool completed with success=%d message=%s\n",
             service_sel->success,
             set_bool.response.message.c_str());
      return service_sel->success;
  }
  assert(false);
}


int send_bools_until_timeout(slct::Context& ctx, std::shared_ptr<StateMachineData>& sm_data) {
  int bools_sent = 0, res;

  while(true) {
    if((res = call_set_bool(ctx, sm_data)) != -1) {
      printf("Result: %d\n", res);
      bools_sent += res;
    } else {
      return bools_sent;
    }
  }
}


/*[[noreturn]] */void state_machine_thread(std::shared_ptr<StateMachineData> sm_data) {
  slct::Context ctx(10);

  int bools_sent = send_bools_until_timeout(ctx, sm_data);
  printf("Sent %d bools before timing out\n", bools_sent);
}


class StateMachineNode {
public:
    StateMachineNode() : sm_data_(std::make_shared<StateMachineData>()) {}

    void spin() {
      ros::Subscriber sub = nh_.subscribe("ping", 1, &StateMachineNode::ping_cb, this);
      sm_data_->pong_pub = nh_.advertise<std_msgs::Bool>("pong", 1);
      sm_data_->toggle_client = nh_.serviceClient<std_srvs::SetBool>("set_bool");

      auto sm_thread = std::thread(state_machine_thread, sm_data_);
      ros::spin();
    }

private:
    ros::NodeHandle nh_;
    std::shared_ptr<StateMachineData> sm_data_;

    void ping_cb(const std_msgs::Bool::ConstPtr& msg) {
      sm_data_->world_state->update_ping();
    }
};


int main(int argc, char **argv)
{
  ros::init(argc, argv, "state_machine");
  StateMachineNode sm_node;
  sm_node.spin();
  return 0;
}