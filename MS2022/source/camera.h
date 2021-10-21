/*==================================================================================================
	MS2022
	[camera.h]
	・カメラ
----------------------------------------------------------------------------------------------------
	2021.10.15 @Author HAYASE SUZUKI
====================================================================================================
	History
		211015 作成
		211021 hirano 
/*================================================================================================*/
#pragma once
#include "game_object.h"

// カメラクラス
class CCamera : public CGameObject
{
private:

//---211021 hirano
	XMFLOAT3 m_Target = XMFLOAT3();
//----------------
	float m_OffsetRad = XM_PI;
	float m_OffsetRaius = 20.0f;

	static CCamera* m_Instance;      // インスタンス

	RECT m_Viewport = RECT();		 // ビューポート

	XMFLOAT4X4	m_ViewMatrix = XMFLOAT4X4();		 // ビューマトリクス
	XMFLOAT4X4	m_InvViewMatrix = XMFLOAT4X4();      // ビュー転置マトリクス
	XMFLOAT4X4	m_ProjectionMatrix = XMFLOAT4X4();   // プロジェクションマトリクス


public:
	CCamera() { m_Instance = this; }
	static CCamera* GetInstance() { return m_Instance; }

	void Init();
	void Uninit();
	void Update();
	void Draw();
	//void DrawShadow();
	//void DrawWater();

	XMFLOAT3 GetForward() {
		return XMFLOAT3(m_ViewMatrix._13, m_ViewMatrix._23, m_ViewMatrix._33);
	}
	XMFLOAT3 GetRight() {
		return XMFLOAT3(m_ViewMatrix._11, m_ViewMatrix._21, m_ViewMatrix._31);
	}

	XMFLOAT4X4	GetViewMatrix() { return m_ViewMatrix; }
	XMFLOAT4X4	GetInvViewMatrix() { return m_InvViewMatrix; }
	XMFLOAT4X4	GetProjectionMatrix() { return m_ProjectionMatrix; }

};