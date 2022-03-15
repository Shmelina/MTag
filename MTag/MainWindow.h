#pragma once
#include <atlstr.h>
#include <algorithm>

#include "Graphics/Graphics.h"
#include "Menue.h"
#include "Resource.h"
#include "Framework.h"
#include "Settings/Locale.h"
#include "Settings/Settings.h"
#include "Settings/Theme.h"

constexpr auto MAX_LOADSTRING = 50;

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

class MainWindow : Locale, Settings, Theme
{
private:

	HWND			hWnd;

	bool            fExit;
	Graphics*		G;
	Coordinate      cursor;
	Coordinate      cursor2;

	string		    positionstring;

	// Global vars:
	HINSTANCE hInst;                                // current instance
	WCHAR szTitle[MAX_LOADSTRING];                  // title string text
	WCHAR szWindowClass[MAX_LOADSTRING];            // main window class name

	//UserInterface*	UI = nullptr;

public:

	MainWindow();

	int Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, WNDPROC WndProc);
	ATOM MyRegisterClass(HINSTANCE hInstance, WNDPROC WndProc);

	bool leftbuttondown = false;
	

	int MainLoop();
	LRESULT ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

