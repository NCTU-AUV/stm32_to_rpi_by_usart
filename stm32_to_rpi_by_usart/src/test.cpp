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

  if ((serial_port = serialOpen ("/dev/ttyS0", 9600)) < 0)	/* open serial port */
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)					/* initializes wiringPi setup */
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  while(1)
  {
    fprintf (stdout,"1:\n");
    deliver(); //send data to stm32
    fprintf (stdout,"2:\n");
    if(serialGetchar (serial_port) == '\n')
    {
      fprintf (stdout,"3:\n");
      for(int i=0;i<100;i++)
      {
        receieved_num[i] = receive();
        fprintf (stdout,"received: %f\n", receieved_num[i]);
      }
    }
	}
}


void deliver()
{
  int i,j;
  float deliverd_num;
  char delim = '\n';

  serialPutchar (serial_port, delim) ;

  for(i=0;i<100;i++)
      {
        deliverd_num = 1.0 * i;

        char *ch =  ( ( ( char * )( & deliverd_num ) ) );
        for(j=0;j<4;j++)
        {
          serialPutchar (serial_port, *ch) ;
          ch++;
        }
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