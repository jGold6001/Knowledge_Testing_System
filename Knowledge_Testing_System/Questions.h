#pragma once
#include "includes_libs.h"

class Questions
{
	int num_of_qu;
	std::multimap<int, std::wstring> ans_right;
	std::multimap<int, std::wstring> ans_select;
	std::map<int, int>  cont_quan_ans_right;
	std::multimap<int, int> cont_num_ans_sel;
	std::vector<int> buff_ans_sel;
	std::wstring path;

public:
	Questions();
	Questions(std::wstring path);
	Questions(const Questions &copy);
	int GetNUmberQuest();
	std::wstring GetPath();
	void GetCurrentPoint(const HWND list_box);//получаем индекс текущего пункта и его содержимый текст list box 
	void SelectAnswers(const HWND list_box);//контейнер выбраных ответов
	void CleanConteiners();//очистка контейнеров: ans_select и cont_num_ans_sel
	int CalkCounter();//счетчик повторения значений num_of_qu
	void IncrementNumOfQuest();//инкремент номеров вопросов для Next
	void DecrementNumOfQuest();//декремент номеров вопросов для Prew
	void SetCurSelAns(const HWND list_box);//сохранение выделенных вопросов
	void ReadTextFile_NEXT(const HWND main_dialog, const HWND edit_control, const HWND list_box);//считываение вопроса и ответов для контрола NEXT
	void ReadTextFile_PREW(const HWND main_dialog, const HWND edit_control, const HWND list_box);//считываеие вопроса и ответов для контрола PREW
	void DeleteLastPoint(const HWND list_box);//удаляем последний пункт list box содержимую дефисами "-"
	void ClearListBox(const HWND list_box);//очистка list box от предыдущих записей
	void PrintResults(const HWND main_dialog);//ввывод результата	
	bool IfNotAllSelect(const HWND list_box, HWND main_dialog);//запрет на переход к следующему(или предыдущему вопросу) если не все ответы выбраны
	int CalkMark(int sum_ans_right, int sum_ans_select);//рассчет оценки
	int CalkSumAnsRight(int cnt_ans_right);//вычисление суммы всех правильных ответов
};

