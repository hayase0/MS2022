/*==================================================================================================
    MS2022
    [action.h]
    ・アクション
----------------------------------------------------------------------------------------------------
    2021.11.04 @Author HAYASE SUZUKI
====================================================================================================
    History
        211104 作成

/*================================================================================================*/
#pragma once

#include <string>

class CAction {
private:
    float m_Frame;
    XMFLOAT3 m_Goal;
    std::string m_AnimId;

    float m_Counter = 0;
    XMFLOAT3 m_Start;
public:
    CAction(){}
    CAction(float f, XMFLOAT3 p, std::string s) : m_Frame(f),m_Goal(p),m_AnimId(s){}

    bool Action(XMFLOAT3& pos, XMFLOAT3& rot);

    void SetStart(XMFLOAT3 pos) { m_Start = pos; }

    float GetFrame()const { return m_Frame; }
    void SetFrame(float f) { m_Frame = f; }

    XMFLOAT3 GetGoal()const { return m_Goal; }
    void SetGoal(XMFLOAT3 v) { m_Goal = v; }

    std::string GetAnimId()const { return m_AnimId; }
    void SetAnimId(std::string str) { m_AnimId = str; }
};