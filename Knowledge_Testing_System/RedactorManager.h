
#pragma once
#include "includes_libs.h"

class RedactorManager
{
	std::map<int, std::wstring> cont_quests;
	std::multimap<int, std::wstring> cont_anses;
	std::wstring edit_quest;
	std::vector<std::wstring> edit_anses;
	std::vector<std::wstring> right_anses_edit;
	std::vector<std::wstring> right_anses_load;
	
public:
	void QuestionsLoad(HWND main_dialog, HWND list_box, std::wstring path, int qu_quests);
	int GetCurrentSubject(HWND combo_box);
	int GetCurrentQuestion(HWND list_box);
	void SetCurrentQuestion(HWND main_dialog, HWND static_text, int num_of_qu, std::wstring path);
	int GetNumSubj(HWND combo_box, int cur_index);
	int GetNumQuest(HWND list_box, int cur_index);

	void LoadQuestionToEQDC(HWND main_dialog, HWND edit_control, int num_of_qu, std::wstring path);
	void LoadAnswersToEQDC(HWND main_dialog, HWND combo_box,  int num_of_qu, std::wstring path);
	void LoadQuestionsToCont(HWND main_dialog, std::wstring path, int qu_quest);
	void LoadAnswersToCont(HWND main_dialog, std::wstring path, int qu_quest);
	void GetEditQuest(HWND edit_control);
	void DelAnswer(HWND combo_box);
	void AddAnswer(HWND combo_box, HWND edit_control);
	void GetEditAns(HWND combo_box);
	void UpdateMaps(int num_quest);
	void ReWriteData(HWND main_dialog, std::wstring path, int qu_quest);
	void FillVectorRA(HWND check_box, HWND edit_control);
	void AddDataToConteiners();
};

