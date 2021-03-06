/*==================================================================================================
    MS2022
    [main.h]
    ・メイン
----------------------------------------------------------------------------------------------------
    2021.09.27 @Author HAYASE SUZUKI
====================================================================================================
    History
        210927 作成

/*================================================================================================*/
#pragma once

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <windows.h>
#include <assert.h>

#include "../include/imgui/imgui_impl_win32.h"
#include "../include/imgui/imgui_impl_dx11.h"

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "winmm.lib")
