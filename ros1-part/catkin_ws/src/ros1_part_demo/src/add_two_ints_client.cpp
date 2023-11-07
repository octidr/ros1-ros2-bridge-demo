#include "ros/ros.h"
#include "ros1_part_demo/AddTwoInts.h"
#include <cstdlib>

int main(int argc, char**argv)
{
    ros::init(argc, argv, "add_two_ints_client");
    if (argc != 3)
    {
        ROS_INFO("Usage: add_two_ints_client X Y");
        return 1;
    }

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<ros1_part_demo::AddTwoInts>("add_two_ints");

    ros1_part_demo::AddTwoInts srv;
    srv.request.a = atoll(argv[1]);
    srv.request.b = atoll(argv[2]);
    if (client.call(srv))
    {
        ROS_INFO("Sum = %ld", (long int) srv.response.sum);
    }
    else
    {
        ROS_INFO("Service call failed");
        return 1;
    }

    return 0;
}
