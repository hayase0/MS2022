/*==================================================================================================
    MS2022
    [audience_editor.h]
    ÅEäœãqîzíu
----------------------------------------------------------------------------------------------------
    2021.11.04 @Author HAYASE SUZUKI
====================================================================================================
    History
        211104 çÏê¨

/*================================================================================================*/
#pragma once

class CAudienceEditor {
private:
    static CAudienceEditor* m_Instance;

    int m_CurrendId = 0;
    int m_ActionId = 0;

    CAudienceEditor() {}
public:
    static CAudienceEditor* GetInstance() { return m_Instance; }

    static void Create() {
        if (!m_Instance)
            m_Instance = new CAudienceEditor;
    }

    static void Destroy() {
        if (m_Instance)
            delete m_Instance;
    }

    void Draw();
};