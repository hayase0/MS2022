/*==================================================================================================
    MS2022
    [manager.cpp]
    ・マネージャー
----------------------------------------------------------------------------------------------------
    2021.09.27 @Author HAYASE SUZUKI
====================================================================================================
    History
        210927 作成

/*================================================================================================*/
#include "main.h"
#include "window.h"
#include "manager.h"
#include "frame_rate.h"
#include "renderer.h"
#include "title.h"
#include "input.h"
#include "texttexture.h"


CScene* CManager::m_Scene;

void CManager::Init(HINSTANCE hInstance, int nCmdShow) {
    CFrameRate::Initialize();
    CWindow::Initialize(hInstance);
    CRenderer::Init();
    CTextTexture::Init();
    CWindow::Display(nCmdShow);
    CInput::Init();

#if _DEBUG
    // ImGui初期化
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(GetWindow());
    ImGui_ImplDX11_Init(CRenderer::GetDevice(), CRenderer::GetDeviceContext());
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("Assets/Fonts/meiryo.ttc", 20.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
#endif

    SetScene<CTitle>();

}

void CManager::Uninit() {

    m_Scene->Uninit();
    delete m_Scene;

#if _DEBUG
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
#endif

    CInput::Uninit();
    CRenderer::Uninit();
    CFrameRate::Finalize();
}

void CManager::Update() {
    CInput::Update();   
    m_Scene->Update();
}

void CManager::Draw() {
#if _DEBUG
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
#endif

    CRenderer::Begin();

    m_Scene->Draw();


#if _DEBUG
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif

    CRenderer::End();
}
