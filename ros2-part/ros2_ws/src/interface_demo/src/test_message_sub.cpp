#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "device_msgs/msg/status.hpp"
using std::placeholders::_1;


class Ros2Listener : public rclcpp::Node
{
  public:
    Ros2Listener()
    : Node("ros2_listener")
    {
      subscription_ = this->create_subscription<device_msgs::msg::Status>(
      "interface_tester", 1000, std::bind(&Ros2Listener::topic_callback, this, _1));
    }

  private:
    void topic_callback(const device_msgs::msg::Status::SharedPtr s) const
    {
      RCLCPP_INFO(this->get_logger(), "ROS2 side heard:\nDevice: %s\n,Mode: %d\n,Action: %d Identifier:%s,\nResult: %d\nTimestamp: %s", s->device_name.c_str(), s->mode, s->action, s->action_identifier.c_str(), s->result, s->time_stamp.c_str());
    }
    rclcpp::Subscription<device_msgs::msg::MyMsg>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Ros2Listener>());
  rclcpp::shutdown();
  return 0;
}
