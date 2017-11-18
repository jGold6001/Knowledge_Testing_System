#include "Console.h"

Console::Console()
{
	
}

Console::~Console()
{
	FreeConsole();
}

void Console::run_console()
{
	AllocConsole();
	out_data.open(L"CONOUT$");
	std::wcout.rdbuf(out_data.rdbuf());
	std::wcout.imbue(std::locale("rus_rus.866"));
}

void Console::wstring_data(const std::wstring & _str)
{
	run_console();
	std::wcout<< _str << std::endl;
}

void Console::char_array_data(const char _str[1024])
{
	run_console();
	std::wcout << _str << std::endl;
}


void Console::char_pointer_data(const char * _str)
{
	run_console();
	std::wcout << _str << std::endl;
}

void Console::char_data(const char character)
{
	run_console();
	std::wcout << character << std::endl;
}

void Console::int_number_data(const int num)
{
	run_console();
	std::wcout << num << std::endl;
}

void Console::double_number_data(const double num)
{
	run_console();
	std::wcout << num << std::endl;
}

