#include "ros/ros.h"
#include "ros1_part_demo/AddThreeInts.h"
#include <cstdlib>

int main(int argc, char**argv)
{
    ros::init(argc, argv, "add_three_ints_client");
    if (argc != 4)
    {
        ROS_INFO("Usage: add_three_ints_client X Y Z");
        return 1;
    }

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<ros1_part_demo::AddThreeInts>("add_three_ints");

    ros1_part_demo::AddThreeInts srv;
    srv.request.a = atoll(argv[1]);
    srv.request.b = atoll(argv[2]);
    srv.request.c = atoll(argv[3]);
    if (client.call(srv))
    {
        ROS_INFO("Sum (ros2 response) = %ld", (long int) srv.response.sum);
    }
    else
    {
        ROS_INFO("Service call failed");
        return 1;
    }

    return 0;
}
