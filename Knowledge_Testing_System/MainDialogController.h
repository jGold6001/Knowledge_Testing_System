#pragma once
#include "includes_libs.h"


struct MainDialogController {
	HBITMAP logo;//�������
	HWND picControl;//������� ��� ��������
	HWND bRegistred; //������ "����������������"
	HWND edName, edSurname, edGroup;//���� ��� �����������
	HWND comboSubject;//����� ��������
	HWND bStart_testing, bEdit_testing;//������ "������ ������", "�������� ������"
	
	MainDialogController();//����������� �� ���������
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);//����������� ����������
	static MainDialogController *ptr;//��� ���������� �����������

	//����������� �������
	BOOL Cls_OnInitDilalog(HWND hWnd, HWND hWNDFocus, LPARAM lParam);//������� �� default
	void Cls_ONCommand(HWND hWnd, int id, HWND hCtl, UINT codeNotify);//��������
	void Cls_OnClose(HWND hWnd);//�������� ����
};

