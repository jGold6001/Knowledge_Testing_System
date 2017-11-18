#pragma once

//win_api
#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "resource.h"

//��� ���������� ������
#include <CommCtrl.h>
#pragma comment(lib, "comctl32")

//��� ������ � ������� � �������
#include <fstream>
#include <string>

//STL - ����������
#include <vector>
#include <map>
#include <set>

//��� ������ Console(����������� � ���������� ����� ����� � �����)
#include "Console.h"
#include <fcntl.h>
#include <io.h>
#include <iostream>

//���������� ����
#include "MainDialogController.h"
#include "TestDialogController.h"
#include "EditorDialogController.h"
#include "EditQuestDialogController.h"

//������� ������
#include "Subjects.h"
#include "Students.h"
#include "Questions.h"
#include "FileManager.h"
#include "RedactorManager.h"
#include "NewQuestDialogController.h"

//��������� ����. �����
#include <cstdlib>
#include <ctime>

