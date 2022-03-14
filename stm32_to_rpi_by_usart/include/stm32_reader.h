#ifndef stm32_reader_H
#define stm32_reader_H
#include "serial_reader.h"

class stm32_reader:private Serial_reader
{
	float num;
	float convert(int );	
public:
	stm32_reader(const char*,int,int,char);
	~stm32_reader();
	void update();
	float get_num(){return num;}
};

#endif