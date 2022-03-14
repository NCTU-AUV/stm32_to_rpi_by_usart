#ifndef SERIAL_READER_H
#define SERIAL_READER_H

#include <wiringSerial.h>
#include <fstream>
#include <string>
#include <vector>

class Serial_reader
{
private:
	int fd;	//the file descriptor used by wiringPi library
	std::ifstream device;	//the std ifstream object who open the serial port and read data
	int size;	//the size of the data package wished to be read
	char delim;	//the delimiting character

protected:
	char *input;	//the raw input data will be stored here and waited to be converted

public:
	Serial_reader(const char *dev_name, int baud, int sz, char del);
	~Serial_reader();
	void read_data_head();	//read data whose delimiting character is at the front
	void read_data_tail();	//read data whose delimiting character is at the back
	void print();
};

#endif