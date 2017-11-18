#pragma once
#include "includes_libs.h"


struct MainDialogController {
	HBITMAP logo;//логотип
	HWND picControl;//контрол для логотипа
	HWND bRegistred; //кнопка "Зарегестрировать"
	HWND edName, edSurname, edGroup;//поля для регестрации
	HWND comboSubject;//выбор предмета
	HWND bStart_testing, bEdit_testing;//кнопки "Начало тестов", "Редактор тестов"
	
	MainDialogController();//конструктор по умолчанию
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);//статические компоненты
	static MainDialogController *ptr;//для управление екземпляров

	//оброботчики событий
	BOOL Cls_OnInitDilalog(HWND hWnd, HWND hWNDFocus, LPARAM lParam);//команды по default
	void Cls_ONCommand(HWND hWnd, int id, HWND hCtl, UINT codeNotify);//контролы
	void Cls_OnClose(HWND hWnd);//закрытие окна
};

