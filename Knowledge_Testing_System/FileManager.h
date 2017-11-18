#pragma once
#include "includes_libs.h"

class FileManager
{
	std::ifstream fin;
	std::wofstream fout;
	int count_str_file;
	int position_que;
	char buff_text[512];
	int size_buff;
	TCHAR *Tbuff_text;
	std::wstring wbuff_text;
	std::multimap<int, std::wstring> right_ans;
	int cnt_ra, num_ra;
	std::map<int, int>  c_num_ra;
	std::vector<std::wstring> cont_subjs;
	std::map<int, std::wstring> cont_quests;
	std::multimap<int, std::wstring> cont_anses;
	int quant_quests;
	std::vector<std::wstring> right_anses;
	
public:
	FileManager();

	//методы для класса Questions
	std::multimap<int, std::wstring> GetRightAns();
	std::map<int, int> GetContRA();
	std::vector<std::wstring> GetRightAnses();
	int GetQuantQuest(HWND main_dialog, std::wstring path);
	int GetNumRA();
	void ReadQuestionsNEXT(HWND main_dialog, HWND edit_control, HWND list_box, int num_of_qu, std::wstring path);
	void RightAnswers(int num_of_qu);
	void ReadQuestionsPREW(HWND main_dialog, HWND edit_control, HWND list_box, int num_of_qu, std::wstring path);
	void RemoveStars(int num_of_qu);

	//для Subjects
	int ReadSubjects(HWND main_dialog, HWND combo_box);
	std::vector<std::wstring> GetContSubjs();

	//для Students
	void WriteStudents(HWND main_dialog, TCHAR buff_name[], TCHAR buff_surname[], TCHAR buff_group[]);
	TCHAR* ReadStudents(HWND main_dialog);

	//для RedactorManager
	void ReadQuestionsToLB(HWND main_dialog, HWND list_box, int num_of_qu, std::wstring path);
	int GetCntStr();
	void ReadQuestionsToST(HWND main_dialog, HWND static_text, int num_of_qu, std::wstring path);
	void ReadQuestionsToEC(HWND main_dialog, HWND edit_control, int num_of_qu, std::wstring path);
	void ReadAnswersToEC(HWND main_dialog, HWND combo_box, int num_of_qu, std::wstring path);
	std::map<int, std::wstring> GetQuestsCont(HWND main_dialog, std::wstring path, int qu_quest);
	std::multimap<int, std::wstring> GetAnswersCont(HWND main_dialog, std::wstring path, int qu_quest);
	void ReWriteQuestions(HWND main_dialog, std::wstring path, std::map<int, std::wstring> &questions, std::multimap<int , std::wstring> &answers,int qu_quest);
};	

