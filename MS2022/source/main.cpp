/*==================================================================================================
    MS2022
    [main.cpp]
    ÅEÉÅÉCÉì
----------------------------------------------------------------------------------------------------
    2021.09.27 @Author HAYASE SUZUKI
====================================================================================================
    History
        210927 çÏê¨

/*================================================================================================*/
#include "main.h"
#include "window.h"
#include "manager.h"
#include "frame_rate.h"


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    CManager::Init(hInstance, nCmdShow);

    MSG msg = {};

    while (WM_QUIT != msg.message) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            if (CFrameRate::FPS_check(VALUE_FPS)) {
                CManager::Update();
                CManager::Draw();
            }
        }
    }

    CManager::Uninit();

    return (int)msg.wParam;
}
