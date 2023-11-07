#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "ros2_part_interfaces/msg/my_msg.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class Ros2Demo : public rclcpp::Node
{
  public:
    Ros2Demo()
    : Node("ros2_demo"), count_(0)
    {
      publisher_ = this->create_publisher<ros2_part_interfaces::msg::MyMsg>("tester2", 1000);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&Ros2Demo::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      count_++;
      auto msg = ros2_part_interfaces::msg::MyMsg();
      msg.first_name = first_names[count_%6];
      msg.first_name = last_names[count_%6];
      msg.age = 25 + count_%35;
      RCLCPP_INFO(this->get_logger(), "Publishing %ld: '%s %s %d'", (long int) count_, msg.first_name.c_str(), msg.last_name.c_str(), msg.age);
      publisher_->publish(msg);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<ros2_part_interfaces::msg::MyMsg>::SharedPtr publisher_;
    
    std::string first_names[6] = {"Max", "Johannes", "Alex", "Peter", "Florian", "Thomas"};
    std::string last_names[6] = {"Mueller", "Mustermann", "Schmidt", "Schumacher", "Meier", "Bauer"};
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Ros2Demo>());
  rclcpp::shutdown();
  return 0;
}

