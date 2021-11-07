#pragma once

#include "scene.h"

#include "polygon.h"
#include "camera.h"
#include "cube.h"
#include "player.h"
#include "stage.h"
#include "audience.h"
#include "bubble.h"

#include "audience_editor.h"
#include "audience_manager.h"

#define LAYER 3

class CTitle : public CScene {
public:
    CTitle() {}
    ~CTitle() {}

    void Init() {
        AddGameObject<CCamera>(0);
        //AddGameObject<CCube>(1);
        AddGameObject<CPlayer>(1);
        AddGameObject<CStage>(1);
        //AddGameObject<CAudience>(1);
        AddGameObject<CPolygon>(2);

        CAudienceManager::Create();
        CAudienceManager::GetInstance()->Init();
#if _DEBUG
        CAudienceEditor::Create();
#endif
    }

    void Uninit() {
#if _DEBUG
        CAudienceManager::GetInstance()->Save();
#endif

        for (int i = 0; i < LAYER; i++) {
            for (auto object : m_GameObject[i]) {
                object->Uninit();
                delete object;
            }
            m_GameObject[i].clear();
        }

#if _DEBUG
        CAudienceEditor::Destroy();
#endif
        CAudienceManager::Destroy();
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

        CAudienceEditor::GetInstance()->Draw();
    }
};
