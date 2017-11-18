#include "EditorDialogController.h"

EditorDialogController *EditorDialogController::ptr = NULL;
static Questions quest;
static Subjects subjects;
static Console c;
static RedactorManager rm;
static EditQuestDialogController edit_quest;
static NewQuestDialogController new_quest;
extern Subjects subj_global_1;
extern Subjects subj_global_2;
static FileManager fm;

EditorDialogController::EditorDialogController()
{
	ptr = this;
	cur_subj = 0;
	cur_quest = 0;
}

BOOL EditorDialogController::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDilalog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_ONCommand);
	}
	return FALSE;
}

BOOL EditorDialogController::Cls_OnInitDilalog(HWND hWnd, HWND hWNDFocus, LPARAM lParam)
{
	comboSubjects = GetDlgItem(hWnd, IDC_C_LIST_SUBJECTS);
	listQuestions = GetDlgItem(hWnd, IDC_L_LIST_QUESTIONS);
	stCurrentQuestion = GetDlgItem(hWnd, IDC_ST_CURRENT_QUESTION);
	bAddQuestion = GetDlgItem(hWnd, IDC_B_ADD_QUESTION);
	bChangeQuestions = GetDlgItem(hWnd, IDC_B_CHANGE_QUESTION);

	subj_global_1.ReadData(hWnd, comboSubjects);//выводим список предметов из файла в комбо-бокс
	SendMessage(comboSubjects, CB_SETCURSEL, 0, 0);

	Questions quest_buff(L"txt_files/tests/1.txt");//открываем файл предмета по умолчанию
	quest = quest_buff;
	qu_quests = fm.GetQuantQuest(hWnd, quest.GetPath());//счетчик количества вопросов в файле
	rm.QuestionsLoad(hWnd, listQuestions, quest.GetPath(), qu_quests);//выводим список вопросов для редактирования в list-box
	SetWindowText(stCurrentQuestion,L"Выберете вопрос");
	
	EnableWindow(bChangeQuestions, FALSE);
	return TRUE;
}

void EditorDialogController::Cls_ONCommand(HWND hWnd, int id, HWND hCtl, UINT codeNotify)
{
	if ((id == IDC_C_LIST_SUBJECTS) && (codeNotify == CBN_SELCHANGE))
	{
		SetWindowText(stCurrentQuestion, L"Выберете вопрос");
		cur_subj = rm.GetCurrentSubject(comboSubjects);
		Questions quest_buff(subj_global_1.SetPath(cur_subj));//при выборе предмета в комбо-боксе устанавливается его файл с вопросами
		quest = quest_buff;
		SendMessage(listQuestions, LB_RESETCONTENT, 0, 0);
		rm.QuestionsLoad(hWnd, listQuestions, quest.GetPath(), qu_quests);//загружаем вопросы в list-box для редактирования
		EnableWindow(bChangeQuestions, FALSE);

	}

	if ((id == IDC_L_LIST_QUESTIONS) && (codeNotify == LBN_SELCHANGE))
	{
		cur_quest = rm.GetCurrentQuestion(listQuestions);
		rm.SetCurrentQuestion(hWnd, stCurrentQuestion,cur_quest, quest.GetPath());//выбираем вопрос для редактирования
		EnableWindow(bChangeQuestions, TRUE);
	}

	int num_subj = rm.GetNumSubj(comboSubjects, cur_subj);
	int num_quest = rm.GetNumQuest(listQuestions, cur_quest);
	Subjects subj_buff_1(num_subj, -1);
	Subjects subj_buff_2(num_subj, num_quest);
	switch (id)
	{

		//при нажатии на клавишу выводится диалоговое окно для редактирования или добавления вопроса
	case IDC_B_ADD_QUESTION:
		subj_global_1 = subj_buff_1;
		DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG_EDIT_QUESTION), NULL, NewQuestDialogController::DlgProc);
		break;

	case IDC_B_CHANGE_QUESTION:
		subj_global_2 = subj_buff_2;
		DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG_EDIT_QUESTION), NULL, EditQuestDialogController::DlgProc);
		break;
	}
}

void EditorDialogController::Cls_OnClose(HWND hWnd)
{
	EndDialog(hWnd, 0);
}

