/*==================================================================================================
	MS2022
	[player.h]
	・プレイヤー
----------------------------------------------------------------------------------------------------
	2021.10.15 @Author HAYASE SUZUKI
====================================================================================================
	History
		211015 作成

/*================================================================================================*/
#pragma once

#include "game_object.h"
#include "animation_model.h"
#include "shader.h"

// プレイヤークラス（ゲームオブジェクト）
class CPlayer : public CGameObject {
private:
	CAnimationModel* m_AnimModel = NULL;
	CShader* m_Shader = NULL;

public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

	CAnimationModel* GetAnim() { return m_AnimModel; }

};