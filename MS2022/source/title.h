/*==================================================================================================
    MS2022
    [title.h]
    ・タイトルシーン
----------------------------------------------------------------------------------------------------
    2021.09.27 @Author HAYASE SUZUKI
====================================================================================================
    History
        210927 作成

/*================================================================================================*/
#pragma once

#include "scene.h"

#define LAYER 3

class CTitle : public CScene {
protected:
    std::list<CGameObject*>	m_GameObject[LAYER];

public:
    CTitle() {}
    ~CTitle() {}

    void Init() {

    }

    void Uninit() {
        for (int i = 0; i < LAYER; i++) {
            for (auto object : m_GameObject[i]) {
                object->Uninit();
                delete object;
            }
            m_GameObject[i].clear();
        }
    }

    void Update() {
        for (int i = 0; i < LAYER; i++) {
            for (auto object : m_GameObject[i]) {
                object->Update();
            }

            m_GameObject[i].remove_if([](auto object) { return object->Destroy(); });
        }
    }

    void Draw() {
        for (int i = 0; i < LAYER; i++) {
            for (auto object : m_GameObject[i]) {
                object->Draw();
            }
        }
    }
};
