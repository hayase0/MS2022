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




HWND g_Window;

HWND GetWindow() {
    return g_Window;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            SendMessage(hWnd, WM_CLOSE, 0, 0);
        }
        break;

    case WM_CLOSE:
        if (MessageBox(hWnd, "本当に終了してよろしいですか？", "終了", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
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

// ウィンドウ生成
bool WINDOW_initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    WNDCLASSEX wcex = {
        sizeof(WNDCLASSEX),
        CS_CLASSDC,
        WndProc,
        0,
        0,
        hInstance,
        NULL,
        LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_WINDOW + 1),
        NULL,
        CLASS_NAME,
        NULL
    };

    // ウィンドウクラスの登録
    RegisterClassEx(&wcex);

    // ウィンドウの作成
    g_Window = CreateWindowEx(
        0,
        CLASS_NAME,
        WINDOW_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        (SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
        (SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
        NULL,
        NULL,
        hInstance,
        NULL);
}