/*==================================================================================================
	MS2022
	[audience.cpp]
	・観客
----------------------------------------------------------------------------------------------------
	2021.10.26 @Author HAYASE SUZUKI
====================================================================================================
	History
		211026 作成

/*================================================================================================*/
#include "main.h"
#include "audience.h"
#include "input.h"
#include "manager.h"
#include "scene.h"
#include "camera.h"

#define SPEED 0.5f


void CAudience::Init() {
	m_AnimModel = new CAnimationModel();
	m_AnimModel->Load("Assets/Models/Akai_Idle.fbx");

	m_Data.modelno = AKAI;
	m_Data.startpos = XMFLOAT3(0, 0, 0);

	m_Shader = new CShader();
	m_Shader->Init("skinningVS.cso", "shaderPS.cso");

	m_Position = XMFLOAT3(0.0f, -5.0f, 10.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.05f, 0.05f, 0.05f);
}

void CAudience::Uninit() {
	m_AnimModel->Unload();
	delete m_AnimModel;

	m_Shader->Uninit();
	delete m_Shader;
}

void CAudience::Update() {
	m_AnimModel->Update();

	XMFLOAT3 pos = GetPosition();
	XMFLOAT3 rot = GetRotation();
	if (m_Data.action.size() > 0) {
		if (m_Data.action[m_ActionIdx].Action(pos, rot)) {
			m_ActionIdx++;
			if (m_Data.action.size() <= m_ActionIdx)
				m_ActionIdx = 0;
			m_Data.action[m_ActionIdx].SetStart(pos);
			m_AnimModel->SetAnimation(m_Data.action[m_ActionIdx].GetAnimId().c_str());
		}
	}
	SetPosition(pos);
	SetRotation(rot);
}

void CAudience::Draw() {
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

	m_Shader->Set();

	m_AnimModel->Draw();
}

