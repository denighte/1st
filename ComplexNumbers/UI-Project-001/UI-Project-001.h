
// UI-Project-001.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы
#include <complex>


// CApp:
// О реализации данного класса см. UI-Project-001.cpp
//

class CApp : public CWinApp
{
public:
	CApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CApp theApp;