#include "ros/ros.h"
#include "device_srvs/GripperControl.h"

bool test(device_srvs::GripperControl::Request &req,
	device_srvs::GripperControl::Response &res)
{
    res.res = req.isOpen;
    ROS_INFO("SRV REQUEST: OPEN: %s\n Range: %f\n,Force: %f\n,Speed: %f\n,Acceleration: %f\n\nRESPONSE: %s", req.isOpen ? "true" : "false", req.range, req.force, req.speed, req.acceleration, res.res ? "true" : "false");
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "test_srv_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("interface_test_srv", test);
    ROS_INFO("INTERFACE TEST SRV READY");
    ros::spin();
    return 0;
}
