#pragma once

//win_api
#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "resource.h"

//для визуальных стилей
#include <CommCtrl.h>
#pragma comment(lib, "comctl32")

//для роботы с файлами и данными
#include <fstream>
#include <string>

//STL - контейнеры
#include <vector>
#include <map>
#include <set>

//для класса Console(тестировать и отлаживать вывод строк и чисел)
#include "Console.h"
#include <fcntl.h>
#include <io.h>
#include <iostream>

//диалоговые окна
#include "MainDialogController.h"
#include "TestDialogController.h"
#include "EditorDialogController.h"
#include "EditQuestDialogController.h"

//робочие классы
#include "Subjects.h"
#include "Students.h"
#include "Questions.h"
#include "FileManager.h"
#include "RedactorManager.h"
#include "NewQuestDialogController.h"

//генератор случ. чисел
#include <cstdlib>
#include <ctime>

