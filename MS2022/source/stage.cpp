/*==================================================================================================
	MS2022
	[stage.h]
	・ステージ　外観
----------------------------------------------------------------------------------------------------
	2021.10.18 @Author OTA KANAME
====================================================================================================
	History
		211018 作成

/*================================================================================================*/
#include "stage.h"
#include "camera.h"

void CStage::Init() {
	m_Model = new CModel();
	m_Model->Load("Assets/Models/stage01.obj");

	m_Shader = new CShader();
	m_Shader->Init("shaderVS.cso", "shaderPS.cso");

	m_Position = XMFLOAT3(0.0f, -14.5f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(20.0f, 20.0f, 20.0f);
}

void CStage::Uninit() {
	m_Model->Unload();
	delete m_Model;

	m_Shader->Uninit();
	delete m_Shader;
}

void CStage::Update() {

}

void CStage::Draw() {
	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	//CRenderer::SetWorldMatrix( &world );

	XMFLOAT4X4 worldf;
	DirectX::XMStoreFloat4x4(&worldf, world);

	m_Shader->SetWorldMatrix(&worldf);

	CCamera* camera = CCamera::GetInstance();
	m_Shader->SetViewMatrix(&CRenderer::GetViewMatrix());
	m_Shader->SetProjectionMatrix(&CRenderer::GetProjectionMatrix());

	m_Shader->Set();

	m_Model->Draw();
}
