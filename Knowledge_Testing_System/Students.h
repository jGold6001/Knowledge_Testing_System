#pragma once
#include "includes_libs.h"

class Students
{
	TCHAR buff_st_name[20], buff_st_surname[40], buff_st_group[5];
public:
	
	void ReadFile(HWND main_dialog);
	void GetWindowTextStudents(HWND main_dialog, HWND name, HWND surname, HWND group);
};

