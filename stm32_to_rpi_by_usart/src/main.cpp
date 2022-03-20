#include "stm32_reader.h"
#include "serial_reader.h"
#include "ros/ros.h"
#include <std_msgs/Float32.h>

const int size = 5;
const char delima = 165;

int main(int argc, char **argv)
{
	stm32_reader stm32("/dev/ttyUSB0", 9600, size, delima);

	ros::init(argc, argv, "stm32");
	ros::NodeHandle node;

    std_msgs::Float32 msg;

    ros::Publisher pub = node.advertise<std_msgs::Float32>("num", 1000);
    ros::Rate loop_rate(10);

	while (ros::ok())
	{
		stm32.update();
        msg.data = stm32.get_num();
        pub.publish(msg);
        loop_rate.sleep();
	}
	return 0;
}
