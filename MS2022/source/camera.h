#pragma once
#include "game_object.h"

// カメラクラス
class CCamera : public CGameObject
{
private:

	static CCamera* m_Instance;      // インスタンス

	RECT m_Viewport;                 // ビューポート

	XMFLOAT4X4	m_ViewMatrix;        // ビューマトリクス
	XMFLOAT4X4	m_InvViewMatrix;     // ビュー転置マトリクス
	XMFLOAT4X4	m_ProjectionMatrix;  // プロジェクションマトリクス


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