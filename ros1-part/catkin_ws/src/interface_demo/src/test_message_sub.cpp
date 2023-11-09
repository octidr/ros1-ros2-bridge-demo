#include "ros/ros.h"
#include "device_msgs/Status.h"

void testerCallback(const device_msgs::Status::ConstPtr& s) {
	ROS_INFO("ROS1 side heard:\nDevice: %s\n,Mode: %d\n,Action: %d Identifier:%s,\nResult: %d\nTimestamp: %s", s->deviceName.c_str(), s->mode, s->action, s->actionIdentifier.c_str(), s->result, s->timeStamp.c_str());
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "test_message_sub");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("interface_tester", 1000, testerCallback);
	ros::spin();
	return 0;
}
