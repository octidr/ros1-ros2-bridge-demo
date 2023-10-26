#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "ros2_part_interfaces/msg/my_msg.hpp"
using std::placeholders::_1;

class Ros2Listener : public rclcpp::Node
{
  public:
    Ros2Listener()
    : Node("ros2_listener")
    {
      subscription_ = this->create_subscription<ros2_part_interfaces::msg::MyMsg>(
      "tester2", 1000, std::bind(&Ros2Listener::topic_callback, this, _1));
      subscriptionBridge_ = this->create_subscription<ros2_part_interfaces::msg::MyMsg>(
      "tester", 1000, std::bind(&Ros2Listener::topic_callback_b, this, _1));
    }

  private:
    void topic_callback(const ros2_part_interfaces::msg::MyMsg::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "ROS2 side heard: [%s %s %d]", msg->first_name.c_str(), msg->last_name.c_str(), msg->age);
    }
    void topic_callback_b(const ros2_part_interfaces::msg::MyMsg::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "Legacy: ROS2 side heard: [%s %s %d]", msg->first_name.c_str(), msg->last_name.c_str(), msg->age);
    }
    rclcpp::Subscription<ros2_part_interfaces::msg::MyMsg>::SharedPtr subscription_;
    rclcpp::Subscription<ros2_part_interfaces::msg::MyMsg>::SharedPtr subscriptionBridge_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Ros2Listener>());
  rclcpp::shutdown();
  return 0;
}
