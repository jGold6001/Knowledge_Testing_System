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
	void GetCurrentPoint(const HWND list_box);//�������� ������ �������� ������ � ��� ���������� ����� list box 
	void SelectAnswers(const HWND list_box);//��������� �������� �������
	void CleanConteiners();//������� �����������: ans_select � cont_num_ans_sel
	int CalkCounter();//������� ���������� �������� num_of_qu
	void IncrementNumOfQuest();//��������� ������� �������� ��� Next
	void DecrementNumOfQuest();//��������� ������� �������� ��� Prew
	void SetCurSelAns(const HWND list_box);//���������� ���������� ��������
	void ReadTextFile_NEXT(const HWND main_dialog, const HWND edit_control, const HWND list_box);//����������� ������� � ������� ��� �������� NEXT
	void ReadTextFile_PREW(const HWND main_dialog, const HWND edit_control, const HWND list_box);//���������� ������� � ������� ��� �������� PREW
	void DeleteLastPoint(const HWND list_box);//������� ��������� ����� list box ���������� �������� "-"
	void ClearListBox(const HWND list_box);//������� list box �� ���������� �������
	void PrintResults(const HWND main_dialog);//������ ����������	
	bool IfNotAllSelect(const HWND list_box, HWND main_dialog);//������ �� ������� � ����������(��� ����������� �������) ���� �� ��� ������ �������
	int CalkMark(int sum_ans_right, int sum_ans_select);//������� ������
	int CalkSumAnsRight(int cnt_ans_right);//���������� ����� ���� ���������� �������
};

