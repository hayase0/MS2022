/*==================================================================================================
    MS2022
    [chat_manager.h]
    ・チャット管理
----------------------------------------------------------------------------------------------------
    2021.11.08 @Author HAYASE SUZUKI
====================================================================================================
    History
        211108 作成

/*================================================================================================*/
#pragma once

class CChatManager {
private:
    static CChatManager* m_Instance;

    bool m_Chat = false;

    CChatManager(){}
public:
    static CChatManager* GetInstance() { return m_Instance; }

    static void Create() {
        if (!m_Instance)
            m_Instance = new CChatManager();
    }

    static void Destroy() {
        if (m_Instance)
            delete m_Instance;
    }

    void Update();
};