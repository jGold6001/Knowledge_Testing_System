#include "includes_libs.h"


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow) {
	MainDialogController main_controller;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, MainDialogController::DlgProc);
}