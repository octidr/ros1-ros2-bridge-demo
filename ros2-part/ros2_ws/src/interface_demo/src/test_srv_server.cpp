#include "rclcpp/rclcpp.hpp"
#include "device_srvs/srv/gripper_control.hpp"

void test(const std::shared_ptr<device_srvs::srv::GripperControl::Request> req, std::shared_ptr<device_srvs::srv::GripperControl::Response> res)
{
	res->res = req->is_open;
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "SRV REQUEST: OPEN: %s\n Range: %f\n,Force: %f\n,Speed: %f\n,Acceleration: %f\n\nRESPONSE: %s", req->is_open ? "true" : "false", req->range, req->force, req->speed, req->acceleration, res->res ? "true" : "false");
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("test_srv_server");

    rclcpp::Service<device_srvs::srv::GripperControl>::SharedPtr service = node->create_service<device_srvs::srv::GripperControl>("interface_test_srv", &test);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "SRV READY: GripperControl");

    rclcpp::spin(node);
    rclcpp::shutdown();
}
