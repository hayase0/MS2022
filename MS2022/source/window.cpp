/*==================================================================================================
    DirectX11
    [window.cpp]
    ・ウィンドウ生成
----------------------------------------------------------------------------------------------------
    2021.09.27 @Author WATARU FUKUOKA
====================================================================================================
    History
        210927 作成

/*================================================================================================*/
#include "window.h"
#include "manager.h"


static HWND g_Window;

HWND GetWindow() {
    return g_Window;
}

#if _DEBUG
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
#if _DEBUG
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;
#endif DEBUG

    switch (uMsg) {
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            SendMessage(hWnd, WM_CLOSE, 0, 0);
        }
        break;

    case WM_CLOSE:
        if (MessageBox(hWnd, "終了してよろしいですか？", "終了確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
            DestroyWindow(hWnd);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    };

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// ウィンドウの生成
void CWindow::Initialize(HINSTANCE hInstance) {
    WNDCLASSEX wcex = {
        sizeof(WNDCLASSEX),
        CS_CLASSDC,
        WndProc,
        0,
        0,
        hInstance,
        NULL,
        LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_BACKGROUND + 1),
        NULL,
        CLASS_NAME,
        NULL
    };

    // ウィンドウクラスの登録
    RegisterClassEx(&wcex);


    DWORD window_style;

    if (MessageBox(g_Window, "フルスクリーンで起動しますか？", "起動設定", MB_YESNO | MB_DEFBUTTON2) == IDYES) {
        window_style = WS_VISIBLE | WS_POPUP;
    }
    else {
        window_style = WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME);
    }

    // ウィンドウの作成
    g_Window = CreateWindowEx(
        0,
        CLASS_NAME,
        WINDOW_NAME,
        window_style,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        (SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
        (SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
        NULL,
        NULL,
        hInstance,
        NULL);
}

// ウインドウの表示(CRenderer::Init()の後に行う)
void CWindow::Display(int nCmdShow) {
    ShowWindow(g_Window, nCmdShow);
    UpdateWindow(g_Window);
}

//bool WINDOW_finalize() {
//    // ウィンドウクラスの登録を解除
//    UnregisterClass(CLASS_NAME, wcex.hInstance);
//}
