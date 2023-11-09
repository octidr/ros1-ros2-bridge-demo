#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "device_msgs/msg/status.hpp"
#include <ctime>
#include <sstream>

using namespace std::chrono_literals;
class Ros2Demo : public rclcpp::Node
{
  public:
    Ros2Demo()
    : Node("test_message_pub"), count_(0)
    {
      publisher_ = this->create_publisher<device_msgs::msg::Status>("interface_tester", 1000);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&Ros2Demo::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      count_++;
      auto s= device_msgs::msg::Status();

      s.device_name = "Test Device 2";
      s.mode = 1;
      s.action = 2;
      s.action_identifier = "Test Action";
      s.result = count_%5;
      auto t = std::time(nullptr);
      auto tm = *std::localtime(&t);
      std::ostringstream oss;
      oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
      auto str = oss.str();
      s.time_tamp = str;

      RCLCPP_INFO(this->get_logger(), "SENDING message:\nDevice: %s\n,Mode: %d\n,Action: %d Identifier:%s,\nResult: %d\nTimestamp: %s", s.device_name.c_str(), s.mode, s.action, s.action_identifier.c_str(), s.result, s.time_stamp.c_str());
      publisher_->publish(s);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<device_msgs::msg::Status>::SharedPtr publisher_;

    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Ros2Demo>());
  rclcpp::shutdown();
  return 0;
}
