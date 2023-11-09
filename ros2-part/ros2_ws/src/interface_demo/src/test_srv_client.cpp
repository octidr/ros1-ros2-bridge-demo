#include "rclcpp/rclcpp.hpp"
#include "device_srvs/srv/gripper_control.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  if (argc != 6) {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Usage: test_srv_client <isopen> <range> <force> <speed> <acceleration>");
      return 1;
  }

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("test_srv_client");
  rclcpp::Client<device_srvs::srv::GripperControl>::SharedPtr client =
    node->create_client<device_srvs::srv::GripperControl>("interface_test_srv");

  auto request = std::make_shared<device_srvs::srv::GripperControl::Request>();
  request->isOpen = atoi(argv[1]) > 0 ? true : false;
  request->range = atof(argv[2]);
  request->force = atof(argv[3]);
  request->speed = atof(argv[4]);
  request->acceleration = atof(argv[5]);

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Result = %s", result.get()->res ? "true" : "false";
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service");
  }

  rclcpp::shutdown();
  return 0;
}
