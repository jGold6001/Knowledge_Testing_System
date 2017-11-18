#include "Questions.h"

static Console c;
static FileManager fm;

Questions::Questions()
{
	num_of_qu = 0;
	path = L"txt_files/tests/1.txt";
}

Questions::Questions(std::wstring path)
{
	this->path = path;
}

Questions::Questions(const Questions &copy)
{
	this->path = copy.path;
}

int Questions::GetNUmberQuest()
{
	return num_of_qu;
}

std::wstring Questions::GetPath()
{
	return path;
}

void Questions::GetCurrentPoint(const HWND list_box)
{
	std::map<int, int>::iterator itr_cnra = cont_quan_ans_right.find(num_of_qu);
	int cur_sel = SendMessage(list_box, LB_GETCURSEL, 0, 0);
	int get_sel_cnt = SendMessage(list_box, LB_GETSELCOUNT, 0, 0);

	if (get_sel_cnt > itr_cnra->second)
		SendMessage(list_box, LB_SETSEL, FALSE, cur_sel);
}

void Questions::SelectAnswers(const HWND list_box)
{
	if (CalkCounter() > 1)
		CleanConteiners();

	int cnt_p = SendMessage(list_box, LB_GETCOUNT, 0, 0);
	TCHAR * Tbuff_selected_ans = new TCHAR[100];
	std::wstring wbuff_selected_ans;
	for (int i = 0; i < cnt_p; i++)
	{
		int get_sel = SendMessage(list_box, LB_GETSEL, i, 0);
		if (get_sel == true)
		{
			SendMessage(list_box, LB_GETTEXT, (WPARAM)i, (LPARAM)Tbuff_selected_ans);
			wbuff_selected_ans = Tbuff_selected_ans;
			ans_select.insert(std::make_pair(num_of_qu, wbuff_selected_ans));
			cont_num_ans_sel.insert(std::make_pair(num_of_qu, i));
		}
	}
}

void Questions::CleanConteiners()
{
	std::multimap<int, std::wstring>::iterator itr_ca = ans_select.find(num_of_qu);
	ans_select.erase(itr_ca->first);

	std::multimap<int, int>::iterator itr_cna = cont_num_ans_sel.find(num_of_qu);
	cont_num_ans_sel.erase(itr_cna->first);
}

int Questions::CalkCounter()
{
	int cnt = 0;
	buff_ans_sel.push_back(num_of_qu);
	for (int i = 0; i < buff_ans_sel.size(); i++)
	{
		if (buff_ans_sel[i] == num_of_qu)
			cnt++;
	}
	return cnt;
}

void Questions::IncrementNumOfQuest()
{
	num_of_qu ++;
}

void Questions::DecrementNumOfQuest()
{
	num_of_qu--;
}

void Questions::SetCurSelAns(const HWND list_box)
{
	std::multimap<int, int>::iterator itr_cna;
	for (itr_cna = cont_num_ans_sel.begin(); itr_cna != cont_num_ans_sel.end(); itr_cna++)
	{
		if (num_of_qu == itr_cna->first)
		{
			SendMessage(list_box, LB_SETSEL, TRUE, itr_cna->second);
		}
	}
}

void Questions::ReadTextFile_NEXT(const HWND main_dialog, const HWND edit_control, const HWND list_box)
{
	fm.ReadQuestionsNEXT(main_dialog, edit_control, list_box, num_of_qu, path);
	DeleteLastPoint(list_box);
	ans_right = fm.GetRightAns();
	cont_quan_ans_right = fm.GetContRA();
}

void Questions::ReadTextFile_PREW(const HWND main_dialog, const HWND edit_control, const HWND list_box)
{
	fm.ReadQuestionsPREW(main_dialog, edit_control, list_box, num_of_qu, path);
	DeleteLastPoint(list_box);
}

void Questions::DeleteLastPoint(const HWND list_box)
{
	int last_point = SendMessage(list_box, LB_GETCOUNT, 0, 0);
	SendMessage(list_box, LB_DELETESTRING, last_point - 1, 0);
}

void Questions::ClearListBox(const HWND list_box)
{
	SendMessage(list_box, LB_RESETCONTENT, 0, 0);
}

void Questions::PrintResults(const HWND main_dialog)
{
	int sum_ans_select = 0, cnt_ans_right = 0;
	std::multimap<int, std::wstring>::iterator itr_ra;
	std::multimap<int, std::wstring>::iterator itr_ca;
	for (itr_ca = ans_select.begin(); itr_ca != ans_select.end(); itr_ca++)
	{
		for (itr_ra = ans_right.begin(); itr_ra != ans_right.end(); itr_ra++)
		{
			if ((itr_ra->first == itr_ca->first) && (itr_ra->second == itr_ca->second))
				sum_ans_select++;
		}
	}
	int sum_ans_right = CalkSumAnsRight(cnt_ans_right);
	int mark = CalkMark(sum_ans_right, sum_ans_select);

	TCHAR MARK[4];
	swprintf_s(MARK, L"%d", mark);

	TCHAR *STUDENT = fm.ReadStudents(main_dialog);
	TCHAR RESALT[100] = L"Ваша оценка - ";
	lstrcat(RESALT, MARK);
	MessageBox(main_dialog, RESALT, STUDENT, MB_ICONINFORMATION);
}

int Questions::CalkMark(int sum_ans_right, int sum_ans_select)
{
	int percent = (100 * sum_ans_select) / sum_ans_right;
	return (12 * percent) / 100;
}

int Questions::CalkSumAnsRight(int cnt_ans_right)
{
	std::map<int, int>::iterator itr_cnra;
	for (itr_cnra = cont_quan_ans_right.begin(); itr_cnra != cont_quan_ans_right.end(); itr_cnra++)
		cnt_ans_right += itr_cnra->second;

	return cnt_ans_right;
}

bool Questions::IfNotAllSelect(const HWND list_box, HWND main_dialog)
{
	std::map<int, int>::iterator itr_cnra = cont_quan_ans_right.find(num_of_qu);
	int get_sel_cnt = SendMessage(list_box, LB_GETSELCOUNT, 0, 0);

	if (get_sel_cnt < itr_cnra->second)
		return false;
	else
		return true;
}
