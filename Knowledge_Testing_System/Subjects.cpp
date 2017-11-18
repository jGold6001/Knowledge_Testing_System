#include "Subjects.h"

static FileManager fm;
static Console c;

Subjects::Subjects()
{
	quan_subj = 0;
}

Subjects::Subjects(int num_subj, int num_quest)
{
	this->num_subj = num_subj;
	this->num_quest = num_quest;
}

Subjects::Subjects(const Subjects & copy)
{
	this->num_subj = copy.num_subj;
	this->num_quest = copy.num_quest;
}

int Subjects::GetNumSubj()
{
	return num_subj;
}

int Subjects::GetNumQuest()
{
	return num_quest;
}

int Subjects::GetQuanSubj()
{
	return quan_subj;
}




void Subjects::ReadData(HWND main_dialog, HWND combo_box)
{
	quan_subj = fm.ReadSubjects(main_dialog, combo_box);
}

std::wstring Subjects::SetPath(int num_of_subj)
{
	names_subjs = fm.GetContSubjs();
	std::wstring folder_path = L"txt_files/tests/";
	std::wstring subject_path;
	std::wstring txt_path = L".txt";
	std::wstring full_path;

	if (names_subjs.size() == 0)
	{
		subject_path = std::to_wstring(num_of_subj + 1);
		full_path = (folder_path + subject_path + txt_path);
	}
	else {
		for (int i = 0; i < names_subjs.size(); i++)
		{
			if (i == num_of_subj)
			{
				subject_path = std::to_wstring(i + 1);
				full_path = (folder_path + subject_path + txt_path);
			}
		}
	}
	
	return full_path;
}

