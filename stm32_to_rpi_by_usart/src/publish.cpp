#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "geometry_msgs/Vector3.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "publish");
    ros::NodeHandle n;

    ros::Publisher ex_pub = n.advertise<geometry_msgs::Vector3>("ex", 1000);
    ros::Publisher ev_pub = n.advertise<geometry_msgs::Vector3>("ev", 1000);
    ros::Publisher arm_pub = n.advertise<geometry_msgs::Vector3>("arm", 1000);
    ros::Publisher yaw_pub = n.advertise<std_msgs::Float32>("yaw", 1000);
    ros::Publisher depth_pub = n.advertise<std_msgs::Float32>("depth", 1000);
    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        std_msgs::Float32 temp_depth;
        std_msgs::Float32 temp_yaw;
        geometry_msgs::Vector3 temp_ex;
        geometry_msgs::Vector3 temp_ev;
        geometry_msgs::Vector3 temp_arm;

        temp_depth.data = 0;
        temp_yaw.data = 1;

        temp_ex.x = 2;
        temp_ex.y = 3;
        temp_ex.z = 4;

        temp_ev.x = 5;
        temp_ev.y = 6;
        temp_ev.z = 7;

        temp_arm.x = 8;
        temp_arm.y = 9;
        temp_arm.z = 10;

        ex_pub.publish(temp_ex);
        ev_pub.publish(temp_ev);
        arm_pub.publish(temp_arm);
        yaw_pub.publish(temp_yaw);
        depth_pub.publish(temp_depth);
        ros::spinOnce();
        loop_rate.sleep();
    }
}