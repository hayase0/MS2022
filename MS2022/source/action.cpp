/*==================================================================================================
    MS2022
    [action.cpp]
    ・アクション
----------------------------------------------------------------------------------------------------
    2021.11.04 @Author HAYASE SUZUKI
====================================================================================================
    History
        211104 作成

/*================================================================================================*/
#include "main.h"
#include "action.h"

bool CAction::Action(XMFLOAT3& pos, XMFLOAT3 &rot) {
    float rate = m_Counter / m_Frame;

    pos.x += (m_Goal.x - m_Start.x) / m_Frame;
    pos.y += (m_Goal.y - m_Start.y) / m_Frame;
    pos.z += (m_Goal.z - m_Start.z) / m_Frame;

    rot.y = atan2f((m_Goal.x - m_Start.x), (m_Goal.z - m_Start.z)) + XM_PI;
    m_Counter++;
    if (m_Frame <= m_Counter) {
        m_Counter = 0;
        return true;
    }
    return false;
}