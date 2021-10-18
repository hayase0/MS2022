/*==================================================================================================
	MS2022
	[player.cpp]
	・プレイヤ
----------------------------------------------------------------------------------------------------
	2021.10.15 @Author HAYASE SUZUKI
====================================================================================================
	History
		211015 作成

/*================================================================================================*/
#include "player.h"
#include "camera.h"

void CPlayer::Init() {
	m_AnimModel = new CAnimationModel();
	m_AnimModel->Load("Assets/Models/Akai_Idle.fbx");
	m_AnimModel->LoadAnimation("Assets/Models/Akai_Idle.fbx", "Idle");
	m_AnimModel->LoadAnimation("Assets/Models/Akai_Run.fbx", "Run");

	m_Shader = new CShader();
	m_Shader->Init("skinningVS.cso", "shaderPS.cso");

	m_Position = XMFLOAT3(0.0f, -5.0f, 10.0f);
	m_Rotation = XMFLOAT3(0.0f, XM_PI * 0.5f, 0.0f);
	m_Scale = XMFLOAT3(0.05f, 0.05f, 0.05f);

	m_AnimModel->SetAnimation("Run");
}

void CPlayer::Uninit() {
	m_AnimModel->Unload();
	delete m_AnimModel;

	m_Shader->Uninit();
	delete m_Shader;
}

void CPlayer::Update() {
	//m_Rotation.y += 0.02f;
	m_Frame += 1;
	m_AnimModel->Update();
}

void CPlayer::Draw() {
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

	m_Shader->SetBoneMatrix(m_AnimModel->GetBoneMatrix(), m_AnimModel->GetBoneNum());

	/*CSky* sky = CManager::GetScene()->GetGameObject<CSky>();
	float lightrotation = sky->GetLightRotation();
	LIGHT light;
	light.Direction = XMFLOAT4(0.0f, -cosf(lightrotation), sinf(lightrotation), 0.0f);
	light.Diffuse = COLOR(0.9f, 0.9f, 0.9f, 1.0f);
	light.Ambient = COLOR(0.1f, 0.1f, 0.1f, 1.0f);
	m_Shader->SetLight(light);*/

	m_Shader->Set();

	m_AnimModel->Draw();
}

