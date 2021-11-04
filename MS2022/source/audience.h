/*==================================================================================================
	MS2022
	[audience.h]
	・観客
----------------------------------------------------------------------------------------------------
	2021.10.26 @Author HAYASE SUZUKI
====================================================================================================
	History
		211026 作成

/*================================================================================================*/
#pragma once

#include "game_object.h"
#include "animation_model.h"
#include "shader.h"
#include "audience_manager.h"

#include <vector>

// 観客クラス（ゲームオブジェクト）
class CAudience : public CGameObject {
private:
	AUDIENCE m_Data;
	int m_ActionIdx = 0;

	CAnimationModel* m_AnimModel = NULL;
	CShader* m_Shader = NULL;

public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

	CAnimationModel* GetAnim() { return m_AnimModel; }
	void LoadAnimModel(const char* fname) {
		if (m_AnimModel) {
			m_AnimModel->Unload();
			delete m_AnimModel;
		}
		m_AnimModel = new CAnimationModel;
		m_AnimModel->Load(fname);
	}
	void LoadAnimation(const char* fname, const char* aname) { m_AnimModel->LoadAnimation(fname, aname); }
	void SetAnimation(const char* name) { m_AnimModel->SetAnimation(name); }

	AUDIENCE GetData() { return m_Data; }
	void SetData(AUDIENCE data) {
		m_Data = data;
		if (m_Data.action.size() > 0) {
			m_Data.action[0].SetStart(GetPosition());
			m_AnimModel->SetAnimation(m_Data.action[0].GetAnimId().c_str());
		}
	}
	void SetModelNo(PLAYER_MODEL m) { m_Data.modelno = m; }
	void SetStartPos(XMFLOAT3 pos) { m_Data.startpos = pos; }

	void AddAction(CAction ac) { m_Data.action.push_back(ac); }
	CAction* GetAction(int id) { return &m_Data.action[id]; }

	int GetActionNum() { return m_Data.action.size(); }
};