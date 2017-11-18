#pragma once
#include "includes_libs.h"

struct EditorDialogController
{
	HWND comboSubjects, listQuestions, stCurrentQuestion;
	HWND bAddQuestion, bChangeQuestions;
	int cur_subj, cur_quest;
	int qu_quests;

	EditorDialogController();
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static EditorDialogController *ptr;

	BOOL Cls_OnInitDilalog(HWND hWnd, HWND hWNDFocus, LPARAM lParam);
	void Cls_ONCommand(HWND hWnd, int id, HWND hCtl, UINT codeNotify);
	void Cls_OnClose(HWND hWnd);
};

