/*==================================================================================================
    MS2022
    [audience_editor.cpp]
    ・観客配置
----------------------------------------------------------------------------------------------------
    2021.11.04 @Author HAYASE SUZUKI
====================================================================================================
    History
        211104 作成

/*================================================================================================*/
#include "main.h"
#include "audience_editor.h"
#include "camera.h"
#include "game_object.h"
#include "manager.h"
#include "scene.h"
#include "audience.h"

int cid = 0;
CAudienceEditor* CAudienceEditor::m_Instance;

void CAudienceEditor::Draw() {
    // 観客リスト取得
    std::vector<CAudience*> audiences = CManager::GetScene()->GetGameObjects<CAudience>();

    ImGui::Begin("Audience Editor");
    if (ImGui::Button("Add")) {
        CManager::GetScene()->AddGameObject<CAudience>(1);
    }
    ImGui::SameLine();
    if (ImGui::Button("Remove")) {
        m_Confirm = true;
    }
    if (m_Confirm) {
        ImGui::Begin("Confirm");
        if (ImGui::Button("OK")) {
            audiences[m_CurrendId]->SetDestroy();
            m_Confirm = false;
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
            m_Confirm = false;
        ImGui::End();
    }

    ImGui::SliderInt("CurrentID", &m_CurrendId, 0, max(audiences.size() - 1, 0));
    if ((signed)audiences.size() > m_CurrendId) {
        float trans[3];
        trans[0] = audiences[m_CurrendId]->GetData().startpos.x;
        trans[1] = audiences[m_CurrendId]->GetData().startpos.y;
        trans[2] = audiences[m_CurrendId]->GetData().startpos.z;
        if (ImGui::InputFloat3("StartPos", trans)) {
            audiences[m_CurrendId]->SetStartPos(XMFLOAT3(trans[0], trans[1], trans[2]));
        }

        int modelno = audiences[m_CurrendId]->GetData().modelno;
        if (ImGui::SliderInt("Model", &modelno, 0, max(PLAYER_MODEL_MAX - 1, 0))) {
            audiences[m_CurrendId]->SetModelNo((PLAYER_MODEL)modelno);
            MODEL_DATA md = CAudienceManager::GetInstance()->GetModelData(modelno);
            audiences[m_CurrendId]->LoadAnimModel(md.modelfile);

            for (int j = 0; j < md.animnum; j++) {
                audiences[m_CurrendId]->LoadAnimation(md.animfile[j],
                    md.animid[j]);
            }
        }

        ImGui::Separator();
        if (ImGui::Button("AddAction")) {
            if (audiences[m_CurrendId]->GetActionNum() != 0)
                audiences[m_CurrendId]->AddAction(*audiences[m_CurrendId]->GetAction(audiences[m_CurrendId]->GetActionNum() - 1));
            else {
                CAction ac(60.0f, XMFLOAT3(0, 0, 0), "Idle");
                audiences[m_CurrendId]->AddAction(ac);
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("RemoveAction")) {
            m_ConfirmAction = true;
        }
        if (m_ConfirmAction) {
            ImGui::Begin("Confirm");
            if (ImGui::Button("OK")) {
                audiences[m_CurrendId]->RemoveAction(m_ActionId);
                m_ConfirmAction = false;
            }

            ImGui::SameLine();
            if (ImGui::Button("Cancel"))
                m_ConfirmAction = false;
            ImGui::End();
        }

        ImGui::SliderInt("ActionID", &m_ActionId, 0, max(audiences[m_CurrendId]->GetActionNum() - 1, 0));
        if (m_ActionId < audiences[m_CurrendId]->GetActionNum()) {
            CAction* ac = audiences[m_CurrendId]->GetAction(m_ActionId);
            int frame = (int)ac->GetFrame();
            if (ImGui::InputInt("Frame", &frame))
                audiences[m_CurrendId]->GetAction(m_ActionId)->SetFrame((float)frame);
            float pos[3] = { ac->GetGoal().x, ac->GetGoal().y,ac->GetGoal().z };
            if (ImGui::InputFloat3("Goal", pos))
                audiences[m_CurrendId]->GetAction(m_ActionId)->SetGoal(XMFLOAT3(pos[0], pos[1], pos[2]));
            
            char animid[20];
            std::strcpy(animid, ac->GetAnimId().c_str());
            if (ImGui::InputText("AnimID", animid, 20))
                audiences[m_CurrendId]->GetAction(m_ActionId)->SetAnimId(animid);
        }

        ImGui::Separator();
        char chat[100];
        strcpy(chat, audiences[m_CurrendId]->GetData().chat.c_str());
        if (ImGui::InputText("Chat", chat, IM_ARRAYSIZE(chat)))
            audiences[m_CurrendId]->SetChat(chat);

        int chatframe = audiences[m_CurrendId]->GetData().chatframe;
        if (ImGui::InputInt("ChatFrame", &chatframe))
            audiences[m_CurrendId]->SetChatFrame(chatframe);
    }

    if (ImGui::Button("Save"))
        CAudienceManager::GetInstance()->Save();


    ImGui::End();

}
