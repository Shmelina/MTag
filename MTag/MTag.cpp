#include "MainWindow.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

MainWindow* MW = nullptr;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    MW = new MainWindow();
    int res = MW->Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WndProc);
    
    if (res == -1)
        return -1;

    return MW->MainLoop();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return MW->ProcessMessage(hWnd, message, wParam, lParam);
}
