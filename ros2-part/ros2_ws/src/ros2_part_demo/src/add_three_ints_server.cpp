#include "rclcpp/rclcpp.hpp"
#include "ros2_part_interfaces/srv/add_three_ints.hpp"

void add(const std::shared_ptr<ros2_part_interfaces::srv::AddThreeInts::Request> req, std::shared_ptr<ros2_part_interfaces::srv::AddThreeInts::Response> res)
{
    res->sum = req->a + req->b + req->c;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "SRV REQUESTED: %ld + %ld + %ld =  %ld", (long int) req->a, (long int) req->b, (long int) req->c, (long int) res->sum);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_three_ints_server");

    rclcpp::Service<ros2_part_interfaces::srv::AddThreeInts>::SharedPtr service = node->create_service<ros2_part_interfaces::srv::AddThreeInts>("add_three_ints", &add);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "SRV READY: ADD THREE INTS");

    rclcpp::spin(node);
    rclcpp::shutdown();
}
