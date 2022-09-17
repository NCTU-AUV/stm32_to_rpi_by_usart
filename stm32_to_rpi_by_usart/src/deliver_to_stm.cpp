#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "geometry_msgs/Vector3.h"
#include "deliver_to_stm.h"

Deliver D;

void depth_callback(const std_msgs::Float32::ConstPtr& msg)
{
    D.data[0] = msg->data;
    D.deliver();
}

void yaw_callback(const std_msgs::Float32::ConstPtr& msg)
{
    D.data[1] = msg->data;
    D.deliver();
}

void ex_callback(const geometry_msgs::Vector3::ConstPtr& msg)
{
    D.data[2] = msg->x;
    D.data[3] = msg->y;
    D.data[4] = msg->z;
    D.deliver();
}

void ev_callback(const geometry_msgs::Vector3::ConstPtr& msg)
{
    D.data[5] = msg->x;
    D.data[6] = msg->y;
    D.data[7] = msg->z;
    D.deliver();
}

void arm_callback(const geometry_msgs::Vector3::ConstPtr& msg)
{
    D.data[8] = msg->x;
    D.data[9] = msg->y;
    D.data[10] = msg->z;
    D.deliver();
}

// void temp()
// {
//     for(int i=0;i<26;i++)
//     {
//         serialPutchar (D.serial_port, (i+'A')) ;
//         fprintf(stdout,"%c\n",(i+'A'));
//     }
//     for(int j=26;j<44;j++)
//     {
//         serialPutchar (D.serial_port, (j-26+'a')) ;
//         fprintf(stdout,"%c\n",(j-26+'a'));
//     }
// }

int main(int argc, char **argv)
{
    ros::init(argc, argv, "deliver_to_stm");
    ros::NodeHandle n;

    if ((D.serial_port = serialOpen ("/dev/ttyS0", 115200)) < 0)	/* open serial port */
    {
        fprintf (stderr, "Unable to open serial device !: %s\n", strerror (errno)) ;
        return 1;
    }

    if (wiringPiSetup () == -1)					/* initializes wiringPi setup */
    {
        fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
        return 1;
    }
    D.delim = '\n';
    serialPutchar (D.serial_port, D.delim) ;
    fprintf(stdout,"delim\n");

    // int counter = 1;
    // while(1)
    // {
    //     for(int i=0;i<11;i++)
    //     {
    //         D.data[i] = i*counter;
    //     }
    //     D.deliver();
    //     counter++;
    //     ros::Duration(7).sleep();
    // }

    ros::Subscriber depth_sub = n.subscribe("depth", 1000, depth_callback);
    ros::Subscriber yaw_sub = n.subscribe("yaw", 1000, yaw_callback);
    ros::Subscriber ex_sub = n.subscribe("ex", 1000, ex_callback);
    ros::Subscriber ev_sub = n.subscribe("ev", 1000, ev_callback);
    ros::Subscriber arm_sub = n.subscribe("arm", 1000, arm_callback);
    
    ros::spin();
    return 0;
}