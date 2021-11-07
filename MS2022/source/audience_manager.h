/*==================================================================================================
    MS2022
    [audience_manager.h]
    ÅEäœãqä«óù
----------------------------------------------------------------------------------------------------
    2021.10.26 @Author HAYASE SUZUKI
====================================================================================================
    History
        211026 çÏê¨

/*================================================================================================*/
#pragma once

#include <vector>
#include "action.h"

enum PLAYER_MODEL{
    AKAI,
    ZOMBIE,
    MUTANT,
    PLAYER_MODEL_MAX,
};

struct MODEL_DATA {
    char modelfile[30];
    char animfile[5][30];
    char animid[5][10];
    int animnum;
};

struct AUDIENCE {
    PLAYER_MODEL modelno;
    XMFLOAT3 startpos;
    std::vector<CAction> action;
    std::string chat;
    int chatframe;
};


class CAudienceManager {
private:
    static CAudienceManager* m_Instance;

    MODEL_DATA m_ModelData[PLAYER_MODEL_MAX] = {
        {"Assets/Models/Akai_Idle.fbx",
        {"Assets/Models/Akai_Idle.fbx", "Assets/Models/Akai_Run.fbx"},
        {"Idle", "Run"},
        2},
        {"Assets/Models/Zombie_Idle.fbx",
        {"Assets/Models/Zombie_Idle.fbx", "Assets/Models/Zombie_Run.fbx"},
        {"Idle", "Run"},
        2},
        {"Assets/Models/Mutant_Idle.fbx",
        {"Assets/Models/Mutant_Idle.fbx", "Assets/Models/Mutant_Run.fbx"},
        {"Idle", "Run"},
        2}
    };

    CAudienceManager(){}
public:
    static CAudienceManager* GetInstance() { return m_Instance; }

    static void Create() {
        if (!m_Instance)
            m_Instance = new CAudienceManager;
    }

    static void Destroy() {
        if (m_Instance)
            delete m_Instance;
    }

    void Init();
    void Save();

    MODEL_DATA GetModelData(int id) { return m_ModelData[id]; }
};