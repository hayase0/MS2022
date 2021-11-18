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
#include "input.h"
#include "manager.h"
#include "scene.h"

#define SPEED 0.5f


void CPlayer::Init() {
    m_AnimModel = new CAnimationModel();
    m_AnimModel->Load("Assets/Models/Akai_Idle.fbx");
    m_AnimModel->LoadAnimation("Assets/Models/Akai_Idle.fbx", "Idle");
    m_AnimModel->LoadAnimation("Assets/Models/Akai_Run.fbx", "Run");

    m_Shader = new CShader();
    m_Shader->Init("skinningVS.cso", "shaderPS.cso");

    m_Position = XMFLOAT3(0.0f, -5.0f, 10.0f);
    m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_Scale = XMFLOAT3(0.05f, 0.05f, 0.05f);

    m_AnimModel->SetAnimation("Idle");
}

void CPlayer::Uninit() {
    m_AnimModel->Unload();
    delete m_AnimModel;

    m_Shader->Uninit();
    delete m_Shader;
}

void CPlayer::Update() {

    // 移動値
    XMFLOAT3 velocity = XMFLOAT3();

    ////m_Rotation.y += 0.02f;
    //if (CInput::GetKeyPress('W') || CInput::GetKeyPress('S') ||
    //	CInput::GetKeyPress('D') || CInput::GetKeyPress('A'))
    //	m_AnimModel->SetAnimation("Run");
    //else
    //	m_AnimModel->SetAnimation("Idle");


    CCamera *cam = CManager::GetScene()->GetGameObject<CCamera>();

    if (CInput::GetKeyPress('W') && !CInput::GetKeyPress('S')) {
        velocity.x += cam->GetForward().x;
        velocity.z += cam->GetForward().z;

        //m_Position.x += cam->GetForward().x;
        ////m_Position.y += cam->GetForward().y;
        //m_Position.z += cam->GetForward().z;


        m_Rotation.y = atan2f(cam->GetForward().x, cam->GetForward().z) + XM_PI;
    }
    if (CInput::GetKeyPress('S') && !CInput::GetKeyPress('W')) {
        velocity.x += -(cam->GetForward().x);
        velocity.z += -(cam->GetForward().z);

        //m_Position.x -= cam->GetForward().x;
        ////m_Position.y += cam->GetForward().y;
        //m_Position.z -= cam->GetForward().z;

        m_Rotation.y = atan2f(cam->GetForward().x, cam->GetForward().z);
    }
    if (CInput::GetKeyPress('D') && !CInput::GetKeyPress('A')) {
        velocity.x += cam->GetRight().x;
        velocity.z += cam->GetRight().z;

        //m_Position.x += cam->GetRight().x;
        ////m_Position.y += cam->GetForward().y;
        //m_Position.z += cam->GetRight().z;

        m_Rotation.y = atan2f(cam->GetForward().x, cam->GetForward().z) - XM_PI / 2;
    }
    if (CInput::GetKeyPress('A') && !CInput::GetKeyPress('D')) {
        velocity.x += -(cam->GetRight().x);
        velocity.z += -(cam->GetRight().z);

        //m_Position.x -= cam->GetRight().x;
        ////m_Position.y += cam->GetForward().y;
        //m_Position.z -= cam->GetRight().z;

        m_Rotation.y = atan2f(cam->GetForward().x, cam->GetForward().z) + XM_PI / 2;
    }

    if (CInput::GetKeyPress('W') && CInput::GetKeyPress('A')) {
        m_Rotation.y = atan2f(cam->GetForward().x, cam->GetForward().z) - XM_PI * 1.25f;
    }
    if (CInput::GetKeyPress('W') && CInput::GetKeyPress('D')) {
        m_Rotation.y = atan2f(cam->GetForward().x, cam->GetForward().z) + XM_PI * 1.25f;
    }
    if (CInput::GetKeyPress('S') && CInput::GetKeyPress('A')) {
        m_Rotation.y = atan2f(cam->GetForward().x, cam->GetForward().z) + XM_PI / 4;
    }
    if (CInput::GetKeyPress('S') && CInput::GetKeyPress('D')) {
        m_Rotation.y = atan2f(cam->GetForward().x, cam->GetForward().z) - XM_PI / 4;
    }

    m_Position.x += velocity.x;
    m_Position.y += velocity.y;
    m_Position.z += velocity.z;

    // 移動してたらRunモーション
    if (velocity.x || velocity.y || velocity.z)
        m_AnimModel->SetAnimation("Run");
    else
        m_AnimModel->SetAnimation("Idle");



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

    CCamera *camera = CCamera::GetInstance();
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

