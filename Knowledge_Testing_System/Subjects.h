#pragma once
#include "includes_libs.h"
class Subjects
{
	int quan_subj;
	std::vector<std::wstring> names_subjs;
	int num_subj;
	int num_quest;
	int quan_quests;

public:
	Subjects();
	Subjects(int num_subj, int num_quest);
	Subjects(const Subjects &copy);
	int GetNumSubj();
	int GetNumQuest();
	int GetQuanSubj();
	void ReadData(HWND main_dialog, HWND combo_box);
	std::wstring SetPath(int num_of_subj);
};

