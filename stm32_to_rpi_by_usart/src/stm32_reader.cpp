#include <iostream>
#include "stm32_reader.h"
#include "serial_reader.h"

const int start_of_num = 0;

stm32_reader::stm32_reader(const char* dev_name,int baud,int sz,char del):Serial_reader(dev_name,baud,sz,del)
{
	num = 0;
}

stm32_reader::~stm32_reader()
{
		
}

float stm32_reader::convert(int start_byte)
{
	float f;
	for(int i=0;i<4;i++)
		((char*)&f)[i] = Serial_reader::input[start_byte+i];
	return f;	
}

void  stm32_reader::update()
{
	Serial_reader::read_data_tail();
	num = convert(start_of_num) - 0.0002;
    std::cout<<"stm32_reader.cpp: "<<num<<std::endl;
}	