/*==================================================================================================
    MS2022
    [manager.h]
    ・マネージャー
----------------------------------------------------------------------------------------------------
    2021.09.27 @Author HAYASE SUZUKI
====================================================================================================
    History
        210927 作成

/*================================================================================================*/
#pragma once

#include "scene.h"

class CManager {
private:
    static CScene* m_Scene;

public:
    static void Init(HINSTANCE, int);
    static void Uninit();
    static void Update();
    static void Draw();

    static CScene* GetScene() { return m_Scene; }

    template<typename T>
    static void SetScene() {
        if (m_Scene) {
            m_Scene->Uninit();
            delete m_Scene;
        }
        m_Scene = new T();
        m_Scene->Init();
    }
};
