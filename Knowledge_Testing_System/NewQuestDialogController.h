#pragma once
#include "includes_libs.h" 

struct NewQuestDialogController
{
	HWND edQuestion, edAns, comboAnswers, bAddAns, bDelAns, bOk, bCancel, checkRight;
	int qu_quests;

	NewQuestDialogController();
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static NewQuestDialogController *ptr;

	BOOL Cls_OnInitDilalog(HWND hWnd, HWND hWNDFocus, LPARAM lParam);
	void Cls_ONCommand(HWND hWnd, int id, HWND hCtl, UINT codeNotify);
	void Cls_OnClose(HWND hWnd);

};

