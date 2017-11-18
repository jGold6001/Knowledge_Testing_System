#include "Students.h"

static FileManager fm;
static Console c;

void Students::ReadFile(HWND main_dialog)
{
	fm.WriteStudents(main_dialog, buff_st_name, buff_st_surname, buff_st_group);
}

void Students::GetWindowTextStudents(HWND main_dialog, HWND name, HWND surname, HWND group)
{
	GetWindowText(name, buff_st_name, 20);
	GetWindowText(surname, buff_st_surname, 40);
	GetWindowText(group, buff_st_group, 5);
	std::wstring w_name, w_surname, w_group;
	w_name = buff_st_name;
	w_surname = buff_st_surname;
	w_group = buff_st_group;

	if (w_name.empty())
		MessageBox(main_dialog, L"Заполните все поля", L"Сообщение", MB_ICONWARNING);
	else if (w_surname.empty())
		MessageBox(main_dialog, L"Заполните все поля", L"Сообщение", MB_ICONWARNING);
	else if (w_group.empty())
		MessageBox(main_dialog, L"Заполните все поля", L"Сообщение", MB_ICONWARNING);
}
