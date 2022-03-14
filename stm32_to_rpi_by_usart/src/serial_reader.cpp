#include "serial_reader.h"
#include <iostream>

Serial_reader::Serial_reader(const char *dev_name, int buad, int sz, char del)
{
	std::cout << "connecting\n";
	fd = serialOpen(dev_name, buad);
	device.open(dev_name);
	if (!device)
		std::cout << "file open error\n";
	size = sz;
	delim = del;
	input = new char[size];
}

Serial_reader::~Serial_reader()
{
	delete[] input;
}

void Serial_reader::read_data_head()
{
	bool found_header = false;
	while(!found_header)
	{
		device.get(input[0]);
		if (input[0] == delim)
		{
			for (int i = 1; i < size; i++)
				device.get(input[i]);
			input[0] = device.peek();
			if (input[0] == delim)
				found_header = true;
		}
	}
}

void Serial_reader::read_data_tail()
{
	bool found_header = false;
	while(!found_header)
	{
		device.get(input, size, delim);
		if (input[0] == delim)
		{
			for (int i = 1; i < size; i++)
				device.get(input[i]);
		}
		device.get(input[0]);
		if (input[0] == delim)
			found_header = true;
	}
}

void Serial_reader::print()
{
	for (int i = 0; i < size; i++)
		std::cout << (int)input[i] << std::endl;
}