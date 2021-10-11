/*==================================================================================================
    MS2022
    [frame_rate.cpp]
    ・フレームレート管理
----------------------------------------------------------------------------------------------------
    2021.09.27 @Author WATARU FUKUOKA
====================================================================================================
    History
        210927 作成

/*================================================================================================*/
#include "main.h"
#include "frame_rate.h"

DWORD dwExecLastTime;
DWORD dwCurrentTime;

void CFrameRate::Initialize() {
    //フレームカウント初期化
    timeBeginPeriod(1);
    dwExecLastTime = timeGetTime();
    dwCurrentTime = 0;
}

void CFrameRate::Finalize() {
    timeEndPeriod(1); // 分解能を戻す
}

bool CFrameRate::FPS_check(float fps) {
    
    dwCurrentTime = timeGetTime();

    if ((dwCurrentTime - dwExecLastTime) >= (1000.0f / fps)) {
        dwExecLastTime = dwCurrentTime;
        return true;
    }

    return false;
}