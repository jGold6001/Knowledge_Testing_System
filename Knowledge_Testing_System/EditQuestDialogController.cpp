#include "EditQuestDialogController.h"

EditQuestDialogController *EditQuestDialogController::ptr = NULL;
static Questions quest;
static Subjects subjects;
static Console c;
static RedactorManager rm;
Subjects subj_global_2;
static FileManager fm;


EditQuestDialogController::EditQuestDialogController()
{
	ptr = this;
	qu_quests = 0;
}

BOOL EditQuestDialogController::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDilalog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_ONCommand);
	}
	return FALSE;
}

BOOL EditQuestDialogController::Cls_OnInitDilalog(HWND hWnd, HWND hWNDFocus, LPARAM lParam)
{
	edQuestion = GetDlgItem(hWnd, IDC_ED_QUESTION);
	edAns = GetDlgItem(hWnd, IDC_ED_ANS);
	comboAnswers = GetDlgItem(hWnd, IDC_C_LIST_ANSWERS);
	bAddAns = GetDlgItem(hWnd, IDC_B_ADD_ANS);
	bDelAns = GetDlgItem(hWnd, IDC_B_DEL_ANS);
	bOk = GetDlgItem(hWnd, IDOK);
	bCancel = GetDlgItem(hWnd, IDCANCEL);
	checkRight = GetDlgItem(hWnd, IDC_CH_RIGHT_ANS);
	

	Questions quest_buff(subjects.SetPath(subj_global_2.GetNumSubj()));
	quest = quest_buff;
	qu_quests = fm.GetQuantQuest(hWnd, quest.GetPath());//�������� ���������� �������� 
	rm.LoadQuestionToEQDC(hWnd, edQuestion, subj_global_2.GetNumQuest(), quest.GetPath());//����������� �������� ������ �� EditorDiaalog
	rm.LoadAnswersToEQDC(hWnd, comboAnswers, subj_global_2.GetNumQuest(), quest.GetPath());// � � ������� �������������� ������
	SendMessage(comboAnswers, CB_SETCURSEL, 0, 0);
	EnableWindow(checkRight, FALSE);

	return TRUE;
}

void EditQuestDialogController::Cls_ONCommand(HWND hWnd, int id, HWND hCtl, UINT codeNotify)
{
	if ((id == IDC_ED_ANS) && (codeNotify == EN_CHANGE))
	{
		EnableWindow(checkRight, TRUE);
	}
	
	switch (id)
	{
		//���������� ������
	case IDC_B_ADD_ANS:
		rm.AddAnswer(comboAnswers, edAns);
		rm.FillVectorRA(checkRight, edAns);
		SendMessage(comboAnswers, CB_SETCURSEL, 0, 0);
		EnableWindow(bDelAns, TRUE);
		EnableWindow(checkRight, FALSE);
		SendMessage(checkRight, BM_SETCHECK, BST_UNCHECKED, 0);

		if (SendMessage(comboAnswers, CB_GETCOUNT, 0, 0) > 4)
			EnableWindow(bAddAns, FALSE);

		break;
		//�������� ������
	case IDC_B_DEL_ANS:
		SendMessage(comboAnswers, CB_SHOWDROPDOWN, TRUE, 0);
		rm.DelAnswer(comboAnswers);
		if (SendMessage(comboAnswers, CB_GETCOUNT, 0, 0) == 0)
			EnableWindow(bDelAns, FALSE); 
	
		EnableWindow(bAddAns, TRUE);
		break;

	case IDOK://������ "Ok"
		rm.LoadQuestionsToCont(hWnd, quest.GetPath(), qu_quests);//��������� ��� ������� �� ����� � std::map
		rm.LoadAnswersToCont(hWnd, quest.GetPath(), qu_quests);//��������� ������ � std::multimap
		rm.GetEditQuest(edQuestion);//�������� ���������������� ������
		rm.GetEditAns(comboAnswers);//���������������� ������
		rm.UpdateMaps(subj_global_2.GetNumQuest());//����� ������� �� "map �����������" ������ ������ � �������� � ������ ��� ���������� ������ ��� ����������������
		rm.ReWriteData(hWnd, quest.GetPath(), qu_quests);//�� ����������� ����������� ���������� ������ � ����
		EndDialog(hWnd, 0);
		break;

	case IDCANCEL:
		
		EndDialog(hWnd, 0);
		break;

	}
}

void EditQuestDialogController::Cls_OnClose(HWND hWnd)
{
	EndDialog(hWnd, 0);
}




