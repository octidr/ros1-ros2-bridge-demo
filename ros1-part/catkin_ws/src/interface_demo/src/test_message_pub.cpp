#include "ros/ros.h"
#include "device_msgs/Status.h"
#include <ctime>
#include <sstream>

int main(int argc, char **argv)
{

  ros::init(argc, argv, "test_message_pub");

  ros::NodeHandle n;

  ros::Publisher tester_pub = n.advertise<device_msgs::Status>("interface_tester", 1000);

  ros::Rate loop_rate(1);

  while (ros::ok())
  {

    device_msgs::Status s;
    s.deviceName = "Test Device";
    s.mode = 1;
    s.action = 2;
    s.actionIdentifier = "Test Action";
    s.result = 0;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    auto str = oss.str();
    s.timeStamp = str;


    ROS_INFO("SENDING message:\nDevice: %s\n,Mode: %d\n,Action: %d Identifier:%s,\nResult: %d\nTimestamp: %s", s.deviceName.c_str(), s.mode, s.action, s.actionIdentifier.c_str(), s.result, s.timeStamp.c_str());

    tester_pub.publish(s);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}
