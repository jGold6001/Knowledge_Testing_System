#include "TestDialogController.h"

TestDialogController * TestDialogController::ptr = NULL;
static Questions quest;
static Subjects subj;
static Console c;
FileManager fm;
Subjects subj_num;


TestDialogController::TestDialogController()
{
	ptr = this;
}

BOOL TestDialogController::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDilalog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_ONCommand);
	}
	return FALSE;
}

BOOL TestDialogController::Cls_OnInitDilalog(HWND hWnd, HWND hWNDFocus, LPARAM lParam)
{
	stQuestion = GetDlgItem(hWnd, IDC_ST_QUESTION);
	listAnswers = GetDlgItem(hWnd, IDC_LIST_ANSWERS);
	bPrew = GetDlgItem(hWnd, IDC_B_PREW);
	bNext = GetDlgItem(hWnd, IDC_B_NEXT);
	bEndTest = GetDlgItem(hWnd, IDC_B_ENDTEST);

	quest.ReadTextFile_NEXT(hWnd, stQuestion, listAnswers);//получаем по умолчанию 1-й вопрос с вариантами ответов
	quan_quests = fm.GetQuantQuest(hWnd, quest.GetPath());
	EnableWindow(bEndTest, FALSE);//блокируем кнопку "Завершить тест" 
	EnableWindow(bPrew, FALSE);//блокируем кнопку "Предыдущий ответ"
	return TRUE;
}

void TestDialogController::Cls_ONCommand(HWND hWnd, int id, HWND hCtl, UINT codeNotify)
{
	if ((id == IDC_LIST_ANSWERS) && (codeNotify == LBN_SELCHANGE))
	{
		quest.GetCurrentPoint(listAnswers);//выбираем нужный нам ответ
	}


	switch (id)
	{
	case IDC_B_NEXT://переход к следющему вопросу
		EnableWindow(bPrew, TRUE);
		EnableWindow(bEndTest, FALSE);
		if (quest.IfNotAllSelect(listAnswers, hWnd) == true)
		{
			quest.SelectAnswers(listAnswers);//подсчитываем ответы
			quest.IncrementNumOfQuest();//получаем номер
			
			if (quest.GetNUmberQuest() < quan_quests)
			{
				quest.ClearListBox(listAnswers);//чистим list box			

				quest.ReadTextFile_NEXT(hWnd, stQuestion, listAnswers);//считываем вопрос с файла
				quest.SetCurSelAns(listAnswers);
				if (quest.GetNUmberQuest() == quan_quests-1)
				{
					EnableWindow(bNext, FALSE);
					EnableWindow(bEndTest, TRUE);
				}
			}
		}
		else
			MessageBox(hWnd, L"Недостаточно выбрано ответов", L"Сообщение", MB_ICONWARNING);

		break;

	case IDC_B_PREW:
		EnableWindow(bNext, TRUE);
		EnableWindow(bEndTest, FALSE);
		if (quest.IfNotAllSelect(listAnswers, hWnd) == true)
		{
			quest.SelectAnswers(listAnswers);//подсчитываем ответы
			quest.DecrementNumOfQuest();
			if (quest.GetNUmberQuest() > -1)
			{			
				quest.ClearListBox(listAnswers);//чистим list box			
					
				quest.ReadTextFile_PREW(hWnd, stQuestion, listAnswers);//считываем вопрос с файла		
			
				quest.SetCurSelAns(listAnswers); 
				if (quest.GetNUmberQuest() == 0)
					EnableWindow(bPrew, FALSE);
			}
		}
		else
			MessageBox(hWnd, L"Недостаточно выбрано ответов", L"Сообщение", MB_ICONWARNING);
			
		break;

	case IDC_B_ENDTEST:
		if (quest.IfNotAllSelect(listAnswers, hWnd) == true)
		{
			EnableWindow(bPrew, FALSE);
			EnableWindow(bEndTest, FALSE);	
			quest.SelectAnswers(listAnswers);
			quest.IncrementNumOfQuest();												   
			quest.PrintResults(listAnswers);
		}
		else 
			MessageBox(hWnd, L"Недостаточно выбрано ответов", L"Сообщение", MB_ICONWARNING);
		break;
	}
}

void TestDialogController::Cls_OnClose(HWND hWnd)
{
	EndDialog(hWnd, 0);
}

void TestDialogController::SelectSubject()
{
	Questions quest_buff(subj.SetPath(subj_num.GetNumSubj()));
	quest = quest_buff;
}
