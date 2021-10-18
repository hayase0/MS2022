/*==================================================================================================
	MS2022
	[cube.cpp]
	・キューブ
----------------------------------------------------------------------------------------------------
	2021.10.11 @Author HAYASE SUZUKI
====================================================================================================
	History
		211011 作成

/*================================================================================================*/
#include "cube.h"
#include "camera.h"

void CCube::Init() {
	m_Model = new CModel();
	m_Model->Load("Assets/Models/cube.obj");

	m_Shader = new CShader();
	m_Shader->Init("shaderVS.cso", "shaderPS.cso");

	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(5.0f, 5.0f, 5.0f);
}

void CCube::Uninit() {
	m_Model->Unload();
	delete m_Model;

	m_Shader->Uninit();
	delete m_Shader;
}

void CCube::Update() {
	m_Rotation.y += 0.02f;
}

void CCube::Draw() {
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


	/*CSky* sky = CManager::GetScene()->GetGameObject<CSky>();
	float lightrotation = sky->GetLightRotation();
	LIGHT light;
	light.Direction = XMFLOAT4(0.0f, -cosf(lightrotation), sinf(lightrotation), 0.0f);
	light.Diffuse = COLOR(0.9f, 0.9f, 0.9f, 1.0f);
	light.Ambient = COLOR(0.1f, 0.1f, 0.1f, 1.0f);
	m_Shader->SetLight(light);*/

	m_Shader->Set();

	m_Model->Draw();
}

