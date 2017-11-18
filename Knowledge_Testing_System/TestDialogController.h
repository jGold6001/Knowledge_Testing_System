#pragma once
#include "includes_libs.h"

struct TestDialogController
{
	HWND stQuestion, listAnswers, bPrew, bNext, bEndTest;
	int quan_quests;

	TestDialogController();
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static TestDialogController *ptr;

	BOOL Cls_OnInitDilalog(HWND hWnd, HWND hWNDFocus, LPARAM lParam);
	void Cls_ONCommand(HWND hWnd, int id, HWND hCtl, UINT codeNotify);
	void Cls_OnClose(HWND hWnd);

	void SelectSubject();
};

