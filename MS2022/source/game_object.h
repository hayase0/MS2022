/*==================================================================================================
    MS2022
    [game_object.h]
    ・ゲームオブジェクト
----------------------------------------------------------------------------------------------------
    2021.10.15 @Author HAYASE SUZUKI
====================================================================================================
    History
        211015 作成
        211021 hirano GetForward関数追加(オブジェクトがどこを向いているかを取得する)
/*================================================================================================*/
#pragma once

#include <list>
#include "main.h"
#include "renderer.h"

class CGameObject {

protected:

    XMFLOAT3					m_Position = XMFLOAT3(0, 0, 0);
    XMFLOAT3					m_Rotation = XMFLOAT3(0, 0, 0);
    XMFLOAT3					m_Scale = XMFLOAT3(0, 0, 0);

    bool                        m_Destroy = false;
    
public:

    XMFLOAT3 GetPosition() { return m_Position; }
    XMFLOAT3 GetRotation() { return m_Rotation; }
    XMFLOAT3 GetScale() { return m_Scale; }

    void SetPosition(XMFLOAT3 Position) { m_Position = Position; }
    void SetRotation(XMFLOAT3 Rotation) { m_Rotation = Rotation; }
    void SetScale(XMFLOAT3 Scale) { m_Scale = Scale; }

    //---211021 hirano GetForward関数
    XMFLOAT3 GetForward() {
        XMMATRIX rot;
        rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

        XMFLOAT4X4 rotf;
        XMStoreFloat4x4(&rotf, rot);

        XMFLOAT3 forward;
        forward.x = rotf._31;
        forward.y = rotf._32;
        forward.z = rotf._33;

        return forward;
    }
    //----------------

    void SetDestroy() { m_Destroy = true; }
    bool Destroy() {
        if (m_Destroy) {
            Uninit();
            delete this;
            return true;
        }
        else
            return false;
    }

public:

    CGameObject() {}

    ~CGameObject() {}

    virtual void Uninit() {
    }

    virtual void Update() {
    }

    virtual void Draw() {
    }
};
