#include "FileManager.h"

static Console c;
static Questions quest;

FileManager::FileManager()
{
	count_str_file = 0;
	size_buff = 0;
	cnt_ra = 0;
	quant_quests = 0;
	std::locale::global(std::locale("Russian_Russia"));
}

std::multimap<int, std::wstring> FileManager::GetRightAns()
{
	return right_ans;
}

std::map<int, int> FileManager::GetContRA()
{
	return c_num_ra;
}

std::vector<std::wstring> FileManager::GetRightAnses()
{
	return right_anses;
}

int FileManager::GetNumRA()
{
	return num_ra;
}

int FileManager::GetQuantQuest(HWND main_dialog, std::wstring path)
{
	fin.open(path, std::ios_base::in);
	count_str_file = 0;
	if (!fin.is_open())
		MessageBox(main_dialog, L"Файл со списками тестов не найден", TEXT("Ошибка поиска"), MB_ICONWARNING);
	else {
		while (!fin.eof()) {
			fin.getline(buff_text, 512);
			if (buff_text[0] == '/')
			{
				quant_quests = count_str_file / 7;
			}
			count_str_file++;
		}
	}
	fin.close();
	return quant_quests;
}

void FileManager::ReadQuestionsNEXT(HWND main_dialog, HWND edit_control, HWND list_box, int num_of_qu, std::wstring path)
{
	position_que = num_of_qu * 7;

	fin.open(path, std::ios_base::in);
	
	count_str_file = 0;
	if (!fin.is_open())
		MessageBox(main_dialog, L"Файл со списками тестов не найден", TEXT("Ошибка поиска"), MB_ICONWARNING);
	else {
		while (!fin.eof()) {
			fin.getline(buff_text, 512);

			if (count_str_file == position_que) {
				size_buff = strlen(buff_text) + 1;
				Tbuff_text = new TCHAR[size_buff];
				wsprintf(Tbuff_text, L"%S", buff_text);
				SetWindowText(edit_control, Tbuff_text);
			}
			else if (count_str_file > position_que) {
				size_buff = strlen(buff_text) + 1;
				Tbuff_text = new TCHAR[size_buff];
				wsprintf(Tbuff_text, L"%S", buff_text);
				RightAnswers(num_of_qu);
				SendMessage(list_box, LB_ADDSTRING, 0, LPARAM(Tbuff_text));
				if (buff_text[0] == '-')
					break;
			}
			count_str_file++;
		}
		num_ra = cnt_ra;
		cnt_ra = 0;
	}
	fin.close();
	c_num_ra.insert(std::make_pair(num_of_qu, num_ra));
}

void FileManager::RightAnswers(int num_of_qu)
{
	if (Tbuff_text[0] == '*')
	{
		//удаляем звездочку для записи правильного ответа в list box 
		Tbuff_text[0] = ' ';

		//ложим в контейнер
		wbuff_text = Tbuff_text;
		right_ans.insert(std::make_pair(num_of_qu, wbuff_text));
		cnt_ra++;
	}
}

void FileManager::ReadQuestionsPREW(HWND main_dialog, HWND edit_control, HWND list_box, int num_of_qu, std::wstring path)
{
	position_que = num_of_qu * 7;
	fin.open(path, std::ios_base::in);
	count_str_file = 0;
	if (!fin.is_open())
		MessageBox(main_dialog, L"Файл со списками тестов не найден", TEXT("Ошибка поиска"), MB_ICONWARNING);
	else {
		while (!fin.eof()) {
			fin.getline(buff_text, 512);
			if (count_str_file == position_que) {
				size_buff = strlen(buff_text) + 1;
				Tbuff_text = new TCHAR[size_buff];
				wsprintf(Tbuff_text, L"%S", buff_text);
				SetWindowText(edit_control, Tbuff_text);
			}
			else if (count_str_file > position_que) {
				size_buff = strlen(buff_text) + 1;
				Tbuff_text = new TCHAR[size_buff];
				wsprintf(Tbuff_text, L"%S", buff_text);
				RemoveStars(num_of_qu);
				SendMessage(list_box, LB_ADDSTRING, 0, LPARAM(Tbuff_text));
				if (buff_text[0] == '-')
					break;
			}
			count_str_file++;
		}
	}
	fin.close();
	
}

void FileManager::RemoveStars(int num_of_qu)
{
	std::multimap<int, std::wstring>::iterator itr_ra;
	if (Tbuff_text[0] == '*')
	{
		Tbuff_text[0] = ' ';
	}
	itr_ra = right_ans.find(num_of_qu+1);
	right_ans.erase(num_of_qu+1);
}

int FileManager::ReadSubjects(HWND main_dialog, HWND combo_box)
{
	fin.open("txt_files/Subjects.txt", std::ios_base::in);
	int cnt_subj =0;
	if (!fin.is_open())
	{
		MessageBox(main_dialog, L"Файл со списками тестов не найден", TEXT("Ошибка поиска"), MB_ICONWARNING);
	}
	else {
		while (!fin.eof())
		{
			fin.getline(buff_text, 512);
			size_buff = strlen(buff_text) + 1;
			Tbuff_text = new TCHAR[size_buff];//tchar должен быть динамическим
			wsprintf(Tbuff_text, L"%S", buff_text);//преобразование в tchar
			SendMessage(combo_box, CB_ADDSTRING, 0, LPARAM(Tbuff_text));
			wbuff_text = Tbuff_text;
			cont_subjs.push_back(wbuff_text);
			cnt_subj++;
		}
	}

	fin.close();
	return cnt_subj;
}

std::vector<std::wstring> FileManager::GetContSubjs()
{
	return cont_subjs;
}

void FileManager::WriteStudents(HWND main_dialog, TCHAR buff_name[], TCHAR buff_surname[], TCHAR buff_group[])
{
	std::locale::global(std::locale("Russian_Russia"));
	fout.open("txt_files/Students.txt", std::ios_base::out);

	if (!fout.is_open())
	{
		MessageBox(main_dialog, L"Файл со списками тестов не найден", TEXT("Ошибка поиска"), MB_ICONWARNING);
	}
	else {
		fout << buff_name << " " << buff_surname << " " << buff_group << std::endl;
	}
	fout.close();
}

TCHAR* FileManager::ReadStudents(HWND main_dialog)
{
	fin.open("txt_files/Students.txt", std::ios_base::in);
	if (!fin.is_open())
	{
		MessageBox(main_dialog, L"Файл со списками тестов не найден", TEXT("Ошибка поиска"), MB_ICONWARNING);
	}
	else
	{
		fin.getline(buff_text, 512);
		size_buff = strlen(buff_text) + 1;
		Tbuff_text = new TCHAR[size_buff];
		wsprintf(Tbuff_text, L"%S", buff_text);
		
	}
	fin.close();
	return Tbuff_text;
}

void FileManager::ReadQuestionsToLB(HWND main_dialog, HWND list_box, int num_of_qu, std::wstring path)
{
	TCHAR *num_buff;
	position_que = num_of_qu * 7;
	fin.open(path, std::ios_base::in);
	count_str_file = 0;
	if (!fin.is_open())
		MessageBox(main_dialog, L"Файл со списками тестов не найден", TEXT("Ошибка поиска"), MB_ICONWARNING);
	else {
		while (!fin.eof()) {
			fin.getline(buff_text, 512);
			if (buff_text[0] == '/')
				break;
			
			if (count_str_file == position_que) {
				size_buff = strlen(buff_text) + 1;
				Tbuff_text = new TCHAR[size_buff];
				num_buff = new TCHAR[10 + size_buff];
				if (num_of_qu < 9)
					wsprintf(num_buff, L"%d -    ", num_of_qu + 1);
				else
					wsprintf(num_buff, L"%d -  ", num_of_qu + 1);
				
				wsprintf(Tbuff_text, L"%S", buff_text);
				lstrcat(num_buff, Tbuff_text);
				SendMessage(list_box, LB_ADDSTRING, 0, LPARAM(num_buff));
			}
			
			count_str_file++;
		}
	}
	fin.close();
}

int FileManager::GetCntStr()
{
	return count_str_file;
}

void FileManager::ReadQuestionsToST(HWND main_dialog, HWND static_text, int num_of_qu, std::wstring path)
{
	TCHAR *num_buff;
	position_que = num_of_qu * 7;
	fin.open(path, std::ios_base::in);
	count_str_file = 0;
	if (!fin.is_open())
		MessageBox(main_dialog, L"Файл со списками тестов не найден", TEXT("Ошибка поиска"), MB_ICONWARNING);
	else {
		while (!fin.eof()) {
			fin.getline(buff_text, 512);
			if (buff_text[0] == '/')
				break;

			if (count_str_file == position_que) {
				size_buff = strlen(buff_text) + 1;
				Tbuff_text = new TCHAR[size_buff];
				num_buff = new TCHAR[10 + size_buff];
				if (num_of_qu < 9)
					wsprintf(num_buff, L"%d -    ", num_of_qu + 1);
				else
					wsprintf(num_buff, L"%d -  ", num_of_qu + 1);

				wsprintf(Tbuff_text, L"%S", buff_text);
				lstrcat(num_buff, Tbuff_text);
				SetWindowText(static_text, num_buff);
			}

			count_str_file++;
		}
	}
	fin.close();
}

void FileManager::ReadQuestionsToEC(HWND main_dialog, HWND edit_control, int num_of_qu, std::wstring path)
{
	position_que = num_of_qu * 7;
	fin.open(path, std::ios_base::in);
	count_str_file = 0;
	if (!fin.is_open())
		MessageBox(main_dialog, L"Файл со списками тестов не найден", TEXT("Ошибка поиска"), MB_ICONWARNING);
	else {
		while (!fin.eof()) {
			fin.getline(buff_text, 512);
			if (count_str_file == position_que) {
				size_buff = strlen(buff_text) + 1;
				Tbuff_text = new TCHAR[size_buff];
				wsprintf(Tbuff_text, L"%S", buff_text);
				SetWindowText(edit_control, Tbuff_text);
			}
			count_str_file++;
		}
	}
	fin.close();
}

void FileManager::ReadAnswersToEC(HWND main_dialog, HWND combo_box, int num_of_qu, std::wstring path)
{
	position_que = num_of_qu * 7;
	fin.open(path, std::ios_base::in);
	count_str_file = 0;
	if (!fin.is_open())
		MessageBox(main_dialog, L"Файл со списками тестов не найден", TEXT("Ошибка поиска"), MB_ICONWARNING);
	else {
		while (!fin.eof()) {
			fin.getline(buff_text, 512);
			if (count_str_file > position_que) {
				size_buff = strlen(buff_text) + 1;
				Tbuff_text = new TCHAR[size_buff];
				wsprintf(Tbuff_text, L"%S", buff_text);
				if (Tbuff_text[0] == '*')
				{
					Tbuff_text[0] = ' ';
					wbuff_text = Tbuff_text;
					right_anses.push_back(wbuff_text);
				}
				SendMessage(combo_box, CB_ADDSTRING, 0, LPARAM(Tbuff_text));
				if (buff_text[0] == '-')
					break;
			}
			count_str_file++;
		}
	}
	fin.close();
	int l_p = SendMessage(combo_box, CB_GETCOUNT, 0, 0);
	SendMessage(combo_box, CB_DELETESTRING, l_p-1, 0);
}

std::map<int, std::wstring> FileManager::GetQuestsCont(HWND main_dialog, std::wstring path, int qu_quest)
{
	cont_quests.clear();
	for (int i = 0; i < qu_quest; i++)
	{
		position_que = i * 7;

		fin.open(path, std::ios_base::in);

		count_str_file = 0;
		if (!fin.is_open())
			MessageBox(main_dialog, L"Файл со списками тестов не найден", TEXT("Ошибка поиска"), MB_ICONWARNING);
		else {
			while (!fin.eof()) {
				fin.getline(buff_text, 512);
				if (count_str_file == position_que) {
					size_buff = strlen(buff_text) + 1;
					Tbuff_text = new TCHAR[size_buff];
					wsprintf(Tbuff_text, L"%S", buff_text);
					wbuff_text = Tbuff_text;
					cont_quests.insert(std::make_pair(i,wbuff_text));
				}
				count_str_file++;
			}
		}
		fin.close();
	}
	
	return cont_quests;
}

std::multimap<int, std::wstring> FileManager::GetAnswersCont(HWND main_dialog, std::wstring path, int qu_quest)
{
	cont_anses.clear();
	for (int i = 0; i <qu_quest; i++)
	{
		position_que = i * 7;

		fin.open(path, std::ios_base::in);

		count_str_file = 0;
		if (!fin.is_open())
			MessageBox(main_dialog, L"Файл со списками тестов не найден", TEXT("Ошибка поиска"), MB_ICONWARNING);
		else {
			while (!fin.eof()) {
				fin.getline(buff_text, 512);
				if (count_str_file > position_que) {
					size_buff = strlen(buff_text) + 1;
					Tbuff_text = new TCHAR[size_buff];
					wsprintf(Tbuff_text, L"%S", buff_text);
					wbuff_text = Tbuff_text;
					cont_anses.insert(std::make_pair(i, wbuff_text));
					
					if (buff_text[0] == '-')
						break;
				}
				count_str_file++;
			}
		}
		fin.close();
	}

	return cont_anses;
}

void FileManager::ReWriteQuestions(HWND main_dialog, std::wstring path, std::map<int, std::wstring> &questions, std::multimap<int, std::wstring> &answers, int qu_quest)
{
	std::pair<std::multimap<int, std::wstring>::iterator, std::multimap<int, std::wstring>::iterator> key_range;
	std::map<int, std::wstring>::iterator itr_cq;
	std::multimap<int, std::wstring>::iterator itr_ca;
	fout.open(path, std::ios_base::out);
	if (!fout.is_open())
		MessageBox(main_dialog, L"Файл со списками тестов не найден", TEXT("Ошибка поиска"), MB_ICONWARNING);
	else {

		for (int i = 0; i <qu_quest; i++)
		{
			itr_cq = questions.find(i);
			fout << itr_cq->second << "\n";
			
			key_range = answers.equal_range(i);
			for (itr_ca = key_range.first; itr_ca != key_range.second; itr_ca++)
				fout << itr_ca->second << "\n";

			switch (answers.count(i))
			{
			case 3: fout << "\n\n\n";
				break;

			case 4: fout << "\n\n";
				break;

			case 5: fout << "\n";
				break;
			}
			
		}
		fout << "/the_end() "<<"\n";
	}
	
	fout.close();
}
