#include "RedactorManager.h"

static Console c;
static FileManager fm;
static Subjects subj;


void RedactorManager::QuestionsLoad(HWND main_dialog, HWND list_box, std::wstring path, int qu_quests)
{
	for (int i = 0; i < qu_quests; i++)
		fm.ReadQuestionsToLB(main_dialog, list_box, i, path);
}

int RedactorManager::GetCurrentSubject(HWND combo_box)
{
	return SendMessage(combo_box, CB_GETCURSEL, 0, 0);
}

int RedactorManager::GetCurrentQuestion(HWND list_box)
{
	int cur_point = SendMessage(list_box, LB_GETCURSEL, 0, 0);
	return cur_point;
}

void RedactorManager::SetCurrentQuestion(HWND main_dialog, HWND static_text, int num_of_qu, std::wstring path)
{
	fm.ReadQuestionsToST(main_dialog, static_text, num_of_qu, path);
}

int RedactorManager::GetNumSubj(HWND combo_box, int cur_index)
{
	int quant_subj = SendMessage(combo_box, CB_GETCOUNT, 0, 0);
	for (int i = 0; i < quant_subj; i++)
	{
		if (i == cur_index)
			return cur_index;
	}
}

int RedactorManager::GetNumQuest(HWND list_box, int cur_index)
{
	int quant_quest = SendMessage(list_box, LB_GETCOUNT, 0, 0);
	for (int i = 0; i < quant_quest; i++)
	{
		if (i == cur_index)
			return cur_index;
	}
}

void RedactorManager::LoadQuestionToEQDC(HWND main_dialog, HWND edit_control, int num_of_qu, std::wstring path)
{
	fm.ReadQuestionsToEC(main_dialog, edit_control,  num_of_qu, path);
}

void RedactorManager::LoadAnswersToEQDC(HWND main_dialog, HWND combo_box, int num_of_qu, std::wstring path)
{
	right_anses_load.clear();
	fm.ReadAnswersToEC(main_dialog, combo_box, num_of_qu, path);
	right_anses_load = fm.GetRightAnses();
}

void RedactorManager::LoadQuestionsToCont(HWND main_dialog, std::wstring path, int qu_quest)
{
	cont_quests = fm.GetQuestsCont(main_dialog, path, qu_quest);
}

void RedactorManager::LoadAnswersToCont(HWND main_dialog, std::wstring path, int qu_quest)
{
	cont_anses = fm.GetAnswersCont(main_dialog, path, qu_quest);
}

void RedactorManager::GetEditQuest(HWND edit_control)
{
	edit_quest.clear();
	TCHAR buff_text[512];
	GetWindowText(edit_control, buff_text, 512);
	edit_quest = buff_text;
}

void RedactorManager::DelAnswer(HWND combo_box)
{
    int cur_ans = SendMessage(combo_box, CB_GETCURSEL, 0, 0);
	SendMessage(combo_box, CB_DELETESTRING, cur_ans, 0);
}

void RedactorManager::AddAnswer(HWND combo_box, HWND edit_control)
{
	TCHAR buff_text[512];
	GetWindowText(edit_control, buff_text, 512);
	SendMessage(combo_box, CB_ADDSTRING, 0, (LPARAM)buff_text);
}

void RedactorManager::FillVectorRA(HWND check_box, HWND edit_control)
{
	right_anses_edit.clear();
	int ch_box = SendMessage(check_box, BM_GETCHECK, 0, 0);
	if (ch_box == BST_CHECKED)
	{
		TCHAR buff_text[512];
		std::wstring wbuff_text;
		GetWindowText(edit_control, buff_text, 512);
		wbuff_text = buff_text;
		right_anses_edit.push_back(wbuff_text);
	}
	SetWindowText(edit_control, L"");
}

void RedactorManager::AddDataToConteiners()
{
	for (auto &itr_vrae : right_anses_edit)
	{
		c.wstring_data(itr_vrae);
	}
	int last_key = cont_quests.size();
	cont_quests.insert(std::make_pair(last_key, edit_quest));
	
	for (int i = 0; i < edit_anses.size(); i++)
	{
		for (auto &itr_vrae : right_anses_edit)
		{
			if (itr_vrae == edit_anses[i]) {
				edit_anses[i] = L"*" + edit_anses[i];
			}
			else {
				edit_anses[i] = L" " + edit_anses[i];
			}
		}
		cont_anses.insert(std::make_pair(last_key, edit_anses[i]));
	}
		
	cont_anses.insert(std::make_pair(last_key, L"-------------------------------"));
}

void RedactorManager::GetEditAns(HWND combo_box)
{
	edit_anses.clear();
	TCHAR buff_text[512];
	std::wstring wbuff_text;
	int cnt_anses = SendMessage(combo_box, CB_GETCOUNT, 0, 0);
	for (int i = 0; i < cnt_anses; i++)
	{
		SendMessage(combo_box, CB_GETLBTEXT, i, (LPARAM)buff_text);
		wbuff_text = buff_text;
		edit_anses.push_back(wbuff_text);
	}

}

void RedactorManager::UpdateMaps(int num_quest)
{
	for (auto itr = cont_quests.begin(); itr != cont_quests.end(); itr++)
	{
		if (itr->first == num_quest)
			itr = cont_quests.erase(itr);
		
		cont_quests.insert(std::make_pair(num_quest, edit_quest));
	}
	
	auto itr = cont_anses.find(num_quest);
	cont_anses.erase(itr->first);

	for (int i = 0; i < edit_anses.size(); i++)
	{
		if (edit_anses[i].at(0) != ' ')
		{
			for (auto &itr_vrae : right_anses_edit)
			{
				if (itr_vrae == edit_anses[i]) {
					edit_anses[i] = L"*" + edit_anses[i];
				}
				else {
					edit_anses[i] = L" " + edit_anses[i];
				}
			}	
		}
		else {
			for (auto &itr_vral : right_anses_load)
			{
				if (itr_vral == edit_anses[i])
					edit_anses[i].at(0) = '*';
			}
		}
		cont_anses.insert(std::make_pair(num_quest, edit_anses[i]));
	}
	cont_anses.insert(std::make_pair(num_quest, L"-------------------------------"));
}

void RedactorManager::ReWriteData(HWND main_dialog, std::wstring path, int qu_quest)
{
	fm.ReWriteQuestions(main_dialog, path, cont_quests, cont_anses, qu_quest);
}
