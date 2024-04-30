﻿// Editor_Window.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Editor_Window.h"

#include "..\Engine_SOURCE\yaApplication.h"
#include "..\Engine_SOURCE\yaRenderer.h"
#include "..\Engine_SOURCE\yaResources.h"
#include "..\Engine_SOURCE\yaFmod.h"

#include "SEngine/LoadScenes.h"

#include "guiEditor.h"

#include "yaDebugLog.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\SEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\SEngine.lib")
#endif

ya::Application application;

#define WINDOW_SIZE_W 1280
#define WINDOW_SIZE_H 720

#define DEBUGLOG_WINDOW_SIZE_W 500
#define DEBUGLOG_WINDOW_SIZE_H 250

#define MAX_LOADSTRING 100

// 디버그 로그 출력 함수 전방 선언
void PrintDebugLog();

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance, LPCWSTR name, WNDPROC proc);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    DebugLogWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(592);
    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EDITORWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance, szWindowClass, WndProc);
    MyRegisterClass(hInstance, L"DebugLogWindow", DebugLogWndProc);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EDITORWINDOW));

    MSG msg;
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 여기서 게임 로직이 돌아가야한다.
            application.Run();
            gui::Editor::Run();
            application.Present();

            // DebugLog 로직
            PrintDebugLog();
        }
    }

    renderer::Release();
    ya::SceneManager::Release();
    ya::Fmod::Release();
    gui::Editor::Release();

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance, LPCWSTR name, WNDPROC proc)// 윈도우 구성요소 설정
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = proc;  // lpfnWndProc 타고 가면 나오는 CALLBACK(__stdcall)은 함수호출 규약 중 하나
    // 함수 포인터가 들어간 형태
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION)); // 리소스 파일의 Client.ico를 바꾸면 아이콘 모습 변경
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // 커서 변경
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ICON);
    wcex.lpszClassName = name;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//

HWND hDebugLogWnd = nullptr;

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, WINDOW_SIZE_W, WINDOW_SIZE_H, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   application.SetWindow(hWnd, WINDOW_SIZE_W, WINDOW_SIZE_H);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   application.Initialize();
   ya::InitializeScenes();
   gui::Editor::Initialize();

   //
   hDebugLogWnd = CreateWindowW(L"DebugLogWindow", L"Debug Log", WS_OVERLAPPEDWINDOW,
       WINDOW_SIZE_W, 0, DEBUGLOG_WINDOW_SIZE_W, DEBUGLOG_WINDOW_SIZE_H, nullptr, nullptr, hInstance, nullptr);

   if (!hDebugLogWnd)
   {
       return FALSE;
   }

   // 디버그 로그 창 보이기
   ShowWindow(hDebugLogWnd, nCmdShow);
   UpdateWindow(hDebugLogWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

std::wstring debugLogText;

void PrintDebugLog()
{
    if (debugLogText.size() > 100)
    {
        debugLogText = L"";
    }
    debugLogText += ya::DebugLog::GetDebugLog() + L"\n"; // 새로운 줄로 이동

    InvalidateRect(hDebugLogWnd, nullptr, TRUE); // 창 다시 그리기 요청
}

LRESULT CALLBACK DebugLogWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
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
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        
        // 디버그 로그 텍스트 출력
        RECT rect;
        rect.left = 10;
        rect.top = 10;
        rect.right = 500; // 적절한 값으로 변경
        rect.bottom = 500; // 적절한 값으로 변경
        DrawText(hdc, debugLogText.c_str(), -1, &rect, DT_WORDBREAK);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
