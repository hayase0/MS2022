/*==================================================================================================
    MS2022
    [game_object.h]
    ・ゲームオブジェクト
----------------------------------------------------------------------------------------------------
    2021.09.27 @Author HAYASE SUZUKI
====================================================================================================
    History
        210927 作成

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

    ~CGameObject() {
    }

    virtual void Uninit() {
    }

    virtual void Update() {
    }

    virtual void Draw() {
    }
};
