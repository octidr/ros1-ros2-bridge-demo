#include "ros/ros.h"
#include "device_srvs/GripperControl.h"
#include <cstdlib>

int main(int argc, char**argv)
{
    ros::init(argc, argv, "test_srv_client");
    if (argc != 6)
    {
        ROS_INFO("Usage: test_srv_client <isopen> <range> <force> <speed> <acceleration>");
        return 1;
    }

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<device_srvs::GripperControl>("interface_test_srv");

    device_srvs::GripperControl srv;
    srv.request.isOpen = atoi(argv[1]) > 0 ? true : false;
    srv.request.range = atof(argv[2]);
    srv.request.force = atof(argv[3]);
    srv.request.speed = atof(argv[4]);
    srv.request.acceleration = atof(argv[5]);
    if (client.call(srv))
    {
        ROS_INFO("Sum = %s", srv.response.res ? "true" : "false");
    }
    else
    {
        ROS_INFO("Service call failed");
        return 1;
    }

    return 0;
}
