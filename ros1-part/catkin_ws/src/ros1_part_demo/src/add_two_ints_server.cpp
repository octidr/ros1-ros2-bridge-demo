#include "ros/ros.h"
#include "ros1_part_demo/AddTwoInts.h"

bool add(ros1_part_demo::AddTwoInts::Request &req,
	ros1_part_demo::AddTwoInts::Response &res)
{
    res.sum = req.a + req.b;
    ROS_INFO("SRV REQUEST: SUM %ld + %ld, RESPONSE = %ld", (long int) req.a, (long int) req.b, (long int) res.sum);
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "add_two_ints_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("add_two_ints", add);
    ROS_INFO("ADD TWO INTS SRV READY");
    ros::spin();
    return 0;
}
