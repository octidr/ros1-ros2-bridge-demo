#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ros1_part_demo/MyMsg.h"

void testerCallback(const ros1_part_demo::MyMsg::ConstPtr& msg) {
	ROS_INFO("ROS1 side heard: [%s %s %d]", msg->first_name.c_str(), msg->last_name.c_str(), msg->age);
}

void testerCallback2(const ros1_part_demo::MyMsg::ConstPtr& msg) {
	ROS_INFO("New: ROS1 side heard: [%s %s %d]", msg->first_name.c_str(), msg->last_name.c_str(), msg->age);
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "ros1_listener");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("tester", 1000, testerCallback);
	ros::Subscriber sub2 = n.subscribe("tester2", 1000, testerCallback2);
	ros::spin();
	return 0;
}
