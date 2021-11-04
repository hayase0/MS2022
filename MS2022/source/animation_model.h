/*==================================================================================================
    MS2022
    [animation_model.h]
    ・アニメーションモデル
----------------------------------------------------------------------------------------------------
    2021.10.15 @Author HAYASE SUZUKI
====================================================================================================
    History
        211015 作成

/*================================================================================================*/
#pragma once

#include <map>
#include <vector>

#include "../include/assimp/cimport.h"
#include "../include/assimp//scene.h"
#include "../include/assimp//postprocess.h"
#include "../include/assimp/matrix4x4.h"
#pragma comment (lib, "assimp.lib")

//変形後頂点構造体
struct DEFORM_VERTEX {
    aiVector3D Position;
    aiVector3D Normal;

    int          BoneNum;
    std::string  BoneName[4];
    float        BoneWeight[4];
};

//ボーン構造体
struct BONE {
    aiMatrix4x4 Matrix;
    aiMatrix4x4 AnimationMatrix;
    aiMatrix4x4 OffsetMatrix;
    int No = NULL;
};

class CAnimationModel {
private:
    const aiScene* m_Scene = NULL;
    std::map<std::string, const aiScene*> m_Animation;
    char m_NowAnimationName[20] = "NONE";
    char m_NextAnimationName[20] = "NONE";
    float m_Per = 0.0f;
    float m_Frame1 = 0;
    float m_Frame2 = 0;

    ID3D11Buffer** m_VertexBuffer;
    ID3D11Buffer** m_IndexBuffer;

    std::map<std::string, CTextureWIC*> m_Texture;

    //std::vector<DEFORM_VERTEX>* m_DeformVertex; //変形後頂点データ
    std::map<const std::string, BONE> m_Bone;   //ボーンデータ(名前で参照)

    XMFLOAT4X4 *m_BoneMatrix;

    void CreateBone(aiNode* node);
    void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);

public:
    void Load(const char *FileName);
    void LoadAnimation(const char *FileName, const char *Name);
    void BrendAnimation();
    void Unload();
    void Update();
    void Draw();

    void SetAnimation(const char* AnimationName);

    int GetBoneNum() { return m_Bone.size(); }

    XMFLOAT4X4* GetBoneMatrix() { return m_BoneMatrix; }
    XMFLOAT4X4 GetBoneMatrix(const char* bonename) {
        if (m_Bone.find(bonename) == m_Bone.end())
            return XMFLOAT4X4(0,0,0,0, 0, 0, 0, 0, 
                0, 0, 0, 0, 0, 0, 0, 0);

        return m_BoneMatrix[m_Bone[bonename].No];
    }
        
};