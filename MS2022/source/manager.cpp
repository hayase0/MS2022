#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "title.h"

CScene*	CManager::m_Scene;


void CManager::Init()
{
	CRenderer::Init();
	
    SetScene<CTitle>();

}

void CManager::Uninit()
{

	m_Scene->Uninit();
	delete m_Scene;

	CRenderer::Uninit();

}

void CManager::Update()
{
	m_Scene->Update();
}

void CManager::Draw()
{
	CRenderer::Begin();

	m_Scene->Draw();

	CRenderer::End();

}
