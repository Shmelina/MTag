#include "MainWindow.h"

MainWindow::MainWindow()
{
    fExit = false;
    G = nullptr;
    cursor = Coordinate(0, 0);
    positionstring = "";
}

int MainWindow::Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, WNDPROC WndProc)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Global Strings Init:
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MTAG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance, WndProc);

    // Application Init:
    hInst = hInstance; // Save Instance

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, WindowWidth.Value, WindowHeight.Value, nullptr, nullptr, hInstance, nullptr);


    if (!hWnd)
    {
        return -1;
    }

    SetMenu(hWnd, NULL);

    SendMessage(hWnd, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);

    G = new Graphics();
    if (!G->Init(hWnd))
    {
        delete G;
        return -1;
    }

    //UI = new UserInterface(G, &hWnd);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MTAG));

    return 0;
};

int MainWindow::MainLoop()
{
    MSG msg;

    msg.message = WM_NULL;

    while (msg.message != WM_DESTROY)
    {
        TranslateMessage(&msg);
        if (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
            DispatchMessage(&msg);
        else
        {
            //todraw
            G->BeginDraw();

            G->ClrScr(MainWindowBckg.Value);
            G->DrawTextM(positionstring, Coordinate(200, 200), Coordinate(200, 200), DebugText.Value);
            //UI->render();

            G->EndDraw();
        }
        if (fExit)
            break;
    }
    //UI->~UserInterface();
    delete G;
    return (int)msg.wParam;
}


LRESULT MainWindow::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;
    case WM_CHAR:
    {
        //MW->Keyup_handler(wParam);
        //UI->Keydown_handler(wParam);
        /*wchar_t tmp = wParam;
        halo += tmp;*/
    }
    break;
    case WM_LBUTTONUP:
    {
        //UI->LButton_handler();
    }
    break;
    case WM_SYSKEYUP:
    {
        if ((GetKeyState(VK_MENU) && wParam == VK_SHIFT) || (GetKeyState(VK_SHIFT) && wParam == VK_MENU))
        {
            PostMessage(GetForegroundWindow(), WM_INPUTLANGCHANGEREQUEST, 2, 0);
        }
    }
    break;
    case WM_MOUSEMOVE:
    {
        positionstring = to_string(LOWORD(lParam)) + " " + to_string(HIWORD(lParam));

        cursor.Set_Coordinate(LOWORD(lParam), HIWORD(lParam));

        //UI->Mouse_move_handler(cursor.X, cursor.Y);
    }
    break;
    case WM_MOUSEWHEEL:
    {
        //UI->Mouse_wheel_handler(-GET_WHEEL_DELTA_WPARAM(wParam) / 120);
    }
    break;
    case WM_KEYDOWN:
    {

    }
    break;
    case WM_KEYUP:
    {
        //UI->Keyup_handler(wParam);
    }
    break;
    case WM_DESTROY:
    {
        fExit = true;
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
};


ATOM MainWindow::MyRegisterClass(HINSTANCE hInstance, WNDPROC WndProc)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MTAG));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MTAG);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
};



INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

