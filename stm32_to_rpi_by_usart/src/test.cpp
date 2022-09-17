#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

int serial_port ;

void deliver();
float receive();

int main ()
{
  float receieved_num[100] ={0.0};

  if ((serial_port = serialOpen ("/dev/ttyS0", 115200)) < 0)	/* open serial port */
  {
    fprintf (stderr, "Unable to open serial device !: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)					/* initializes wiringPi setup */
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  deliver();
  while(1)
  {
  //  deliver(); //send data to stm32
    // if(serialGetchar (serial_port) == '\n')
    // {
    //   fprintf (stdout,"3:\n");
    //   for(int i=0;i<100;i++)
    //   {
    //     receieved_num[i] = receive();
    //     fprintf (stdout,"received: %f\n", receieved_num[i]);
    //   }
    // }

	}
}


void deliver()
{
  int i,j;
  float deliverd_num;
  char delim = '\n';

  serialPutchar (serial_port, delim) ;

  for(i=1;i<29;i++)
      {
        deliverd_num = 1.0*i;

        char *ch =  ( ( ( char * )( & deliverd_num ) ) );
        for(j=0;j<4;j++)
        {
          serialPutchar (serial_port, *ch) ;
          ch++;
        }
        fprintf (stdout,"data: %f\n", deliverd_num);
      }
}


float receive()
{	
	int i;
	float n;
  char *ch = (char *) &n;
	for(i=0;i<4;i++)
		ch[i] = serialGetchar (serial_port); 
	return n;
}