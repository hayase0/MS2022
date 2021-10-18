/*==================================================================================================
	MS2022
	[camera.h]
	・カメラ
----------------------------------------------------------------------------------------------------
	2021.10.15 @Author HAYASE SUZUKI
====================================================================================================
	History
		211015 作成

/*================================================================================================*/
#pragma once
#include "game_object.h"

// カメラクラス
class CCamera : public CGameObject
{
private:

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


	XMFLOAT4X4	GetViewMatrix() { return m_ViewMatrix; }
	XMFLOAT4X4	GetInvViewMatrix() { return m_InvViewMatrix; }
	XMFLOAT4X4	GetProjectionMatrix() { return m_ProjectionMatrix; }

};