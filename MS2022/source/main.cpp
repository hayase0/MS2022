/*==================================================================================================
    MS2022
    [main.cpp]
    ・メイン
----------------------------------------------------------------------------------------------------
    2021.09.27 @Author HAYASE SUZUKI
====================================================================================================
    History
        210927 作成

/*================================================================================================*/
#include "main.h"
#include "window.h"
#include "manager.h"


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

    //フレームカウント初期化
    DWORD dwExecLastTime;
    DWORD dwCurrentTime;
    timeBeginPeriod(1);
    dwExecLastTime = timeGetTime();
    dwCurrentTime = 0;


    CManager::Init(hInstance, nCmdShow);

    // メッセージループ
    MSG msg;
    while (1) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {// PostQuitMessage()が呼ばれたらループ終了
                break;
            }
            else {
                // メッセージの翻訳とディスパッチ
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else {
            dwCurrentTime = timeGetTime();

            if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60)) {
                dwExecLastTime = dwCurrentTime;

                // 更新処理
                CManager::Update();

                // 描画処理
                CManager::Draw();
            }
        }
    }

    timeEndPeriod(1); // 分解能を戻す

    // 終了処理
    CManager::Uninit();

    return (int)msg.wParam;
}
