#include "MainDialogController.h"


MainDialogController* MainDialogController::ptr = NULL;//обнуление указателя
static Console c;//обьект для дебага
static Subjects subjects;//обьект предметов для тестов
static Students students;//обьект студенты
static TestDialogController test_dialog;
static EditorDialogController edit_dialog;
extern Subjects subj_num;


MainDialogController::MainDialogController() {
	ptr = this;//указатель следит за переключением управления
}

BOOL MainDialogController::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hWnd, WM_INITDIALOG, ptr->Cls_OnInitDilalog);
		HANDLE_MSG(hWnd, WM_COMMAND, ptr->Cls_ONCommand);
	}
	return FALSE;
}

BOOL MainDialogController::Cls_OnInitDilalog(HWND hWnd, HWND hWNDFocus, LPARAM lParam)
{
	//связываем контролы с диалоговым окном
	edName = GetDlgItem(hWnd, IDC_ED_NAME);
	edSurname = GetDlgItem(hWnd, IDC_ED_SURNAME);
	edGroup = GetDlgItem(hWnd, IDC_ED_GROUP);
	comboSubject = GetDlgItem(hWnd, IDC_C_SEL_SUBJECT);
	bStart_testing = GetDlgItem(hWnd, IDC_B_START_TESTING);
	bEdit_testing = GetDlgItem(hWnd, IDC_B_EDIT_TESTING);
	picControl = GetDlgItem(hWnd, IDC_ST_PICTURE);
	bRegistred = GetDlgItem(hWnd, IDC_B_REGISTER);
	
	//устанавливаем логотип на "Главное окно"
	logo = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP_LOGO));
	SendMessage(picControl, STM_SETIMAGE, (WPARAM)(IMAGE_BITMAP), (LPARAM)(logo));

	//производим чтение файла "TestList.txt"(названия предметов)
	subjects.ReadData(hWnd, comboSubject);
	
	//устанавливаем курсор 1-го предмета по умолчанию
	SendMessage(comboSubject, CB_SETCURSEL, 0, 0);
	return TRUE;
}

void MainDialogController::Cls_ONCommand(HWND hWnd, int id, HWND hCtl, UINT codeNotify) {
	
	//получаем индекс нужной категории
	int index_of_subj = SendMessage(comboSubject, CB_GETCURSEL, 0, 0);
	
	switch (id)
	{
	case IDC_B_REGISTER:
		//получаем данные с эдит контролов
		students.GetWindowTextStudents(hWnd, edName, edSurname, edGroup);
		
		//при регистрации записываем студентов у файл "Students.txt"
		students.ReadFile(hWnd);
		break;

	case IDC_B_START_TESTING:
		for (int i = 0; i < subjects.GetQuanSubj(); i++)
		{
			if (index_of_subj == i)
			{
				Subjects subj_buff(i, 0);
				subj_num = subj_buff;
				test_dialog.SelectSubject();
			}
		}
		DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG_TESTING), NULL, TestDialogController::DlgProc);
		break;

	case IDC_B_EDIT_TESTING:
		DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG_EDITOR), NULL, EditorDialogController::DlgProc);
		break;
	}
	

}


void MainDialogController::Cls_OnClose(HWND hWnd) {
	EndDialog(hWnd, 0);
}



