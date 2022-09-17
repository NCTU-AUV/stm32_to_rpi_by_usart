#include <wiringPi.h>
#include <wiringSerial.h>

struct Deliver
{
    float data[11]; //ex ev arm_angle yaw depth
    int serial_port;
    char delim;
    void deliver();    
};

void Deliver::deliver()
{
  int i,j;
  float deliverd_num;

  for(i=0;i<11;i++)
  {
    deliverd_num = data[i];
    char *ch =  ( ( ( char * )( & deliverd_num ) ) );

    for(j=0;j<4;j++)
    {
        serialPutchar (serial_port, *ch) ;
        ch++;
    }
    ROS_INFO("to stm data[%d]: %f\n", i, deliverd_num);
  }
  //ros::Duration(1).sleep();
  delay(8000);
}
