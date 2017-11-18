#pragma once
#include "includes_libs.h"
struct Console
{
	std::wofstream out_data;

	Console();
	~Console();
	void run_console();
	void wstring_data(const std::wstring &_str);
	void char_array_data(const char _str[1024]);
	void char_pointer_data(const char *_str);
	void char_data(const char character);
	void int_number_data(const int num);
	void double_number_data(const double num);
};

