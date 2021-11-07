/*==================================================================================================
    MS2022
    [audience_manager.cpp]
    ÅEäœãqä«óù
----------------------------------------------------------------------------------------------------
    2021.10.26 @Author HAYASE SUZUKI
====================================================================================================
    History
        211026 çÏê¨

/*================================================================================================*/
#include "main.h"
#include "action.h"
#include "audience_manager.h"
#include "manager.h"
#include "scene.h"
#include "audience.h"

#include "nlohmann\json.hpp"
#include <fstream>
#include <vector>

using json = nlohmann::json;

CAudienceManager* CAudienceManager::m_Instance;

void to_json(json& j, const AUDIENCE& p);
void from_json(const json& j, AUDIENCE& p);

void CAudienceManager::Init() {
    std::vector<AUDIENCE> audiences;
    
    std::ifstream read("audience.json");
    if (read.fail()) {
        assert(false);
    }
    int num;
    read >> num;

    std::string data;
    for (int i = 0; i < num; i++) {
        read >> data;
        json in;
        in = json::parse(data);
        AUDIENCE tmp;
        in.get_to(tmp);
        audiences.push_back(tmp);
    }

    for (unsigned int i = 0; i < audiences.size(); i++) {
        CAudience* p = CManager::GetScene()->AddGameObject<CAudience>(1);
        p->SetPosition(audiences[i].startpos);
        p->LoadAnimModel(m_ModelData[audiences[i].modelno].modelfile);

        for (int j = 0; j < m_ModelData[audiences[i].modelno].animnum; j++) {
            p->LoadAnimation(m_ModelData[audiences[i].modelno].animfile[j],
                m_ModelData[audiences[i].modelno].animid[j]);
        }
        p->SetData(audiences[i]);
    }
}

void CAudienceManager::Save() {
    std::vector<CAudience*> audiences = CManager::GetScene()->GetGameObjects<CAudience>();
    std::vector<AUDIENCE> dataes;

    for (auto p : audiences) {
        dataes.push_back(p->GetData());
    }

    json j_num = dataes.size();

    std::ofstream write("audience.json");
    if (!write) {
        assert(false);
    }

    std::string out = j_num.dump();
    write << out << std::endl;
    for (unsigned int i = 0; i < dataes.size(); i++) {
        json j_vec(dataes[i]);
        out = j_vec.dump();
        write << out << std::endl;
    }
}

void to_json(json& j, const CAction& p) {
    j = json{ {"frame", p.GetFrame() },{"GoalPosX", p.GetGoal().x},
    {"GoalPosY", p.GetGoal().y} ,{"GoalPosZ", p.GetGoal().z},{"AnimID", p.GetAnimId()} };
}

void from_json(const json& j, CAction& p) {
    float f;
    XMFLOAT3 pos;
    std::string str;
    j.at("frame").get_to(f);       // get_to(T& arg) ÇÕ arg = get<T>() Ç∆ìØÇ∂
    j.at("GoalPosX").get_to(pos.x);
    j.at("GoalPosY").get_to(pos.y);
    j.at("GoalPosZ").get_to(pos.z);
    j.at("AnimID").get_to(str);
    p.SetFrame(f);
    p.SetGoal(pos);
    p.SetAnimId(str);
}

void to_json(json& j, const AUDIENCE& p) {
    j = json{ {"modelNo", p.modelno },{"StartPosX", p.startpos.x},
    {"StartPosY", p.startpos.y} ,{"StartPosZ", p.startpos.z},
    { "ActionArray", p.action }, {"Chat", p.chat}, {"ChatFrame", p.chatframe}};
}

void from_json(const json& j, AUDIENCE& p) {
    j.at("modelNo").get_to(p.modelno);       // get_to(T& arg) ÇÕ arg = get<T>() Ç∆ìØÇ∂
    j.at("StartPosX").get_to(p.startpos.x);
    j.at("StartPosY").get_to(p.startpos.y);
    j.at("StartPosZ").get_to(p.startpos.z);
    j.at("ActionArray").get_to(p.action);
    j.at("Chat").get_to(p.chat);
    j.at("ChatFrame").get_to(p.chatframe);
}