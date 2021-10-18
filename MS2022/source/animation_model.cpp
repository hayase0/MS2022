/*==================================================================================================
    MS2022
    [animation_model.cpp]
    ・アニメーションモデル
----------------------------------------------------------------------------------------------------
    2021.10.15 @Author HAYASE SUZUKI
====================================================================================================
    History
        211015 作成

/*================================================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "main.h"
#include "renderer.h"
#include "animation_model.h"
#include "texture.h"
#include "texture_wic.h"

void CAnimationModel::Update() {
    if (strcmp(m_NowAnimationName, "NONE") != 0) {

        if (strcmp(m_NextAnimationName, "NONE") != 0)
            BrendAnimation();

        else {
            int frame = (int)m_Frame1;
            //アニメーションデータからボーンマトリクス算出
            aiAnimation* animation = m_Animation[m_NowAnimationName]->mAnimations[0];

            for (unsigned int c = 0; c < animation->mNumChannels; c++) {
                aiNodeAnim* nodeAnim = animation->mChannels[c];
                BONE* bone = &m_Bone[nodeAnim->mNodeName.C_Str()];

                int f;
                f = frame % nodeAnim->mNumRotationKeys; //簡易実装
                aiQuaternion rot = nodeAnim->mRotationKeys[f].mValue;

                f = frame % nodeAnim->mNumPositionKeys; //簡易実装
                aiVector3D pos = nodeAnim->mPositionKeys[f].mValue;

                bone->AnimationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot, pos);
            }
        }
        m_Frame1+= 1.0f;

        //再帰的にボーンマトリクスを更新
        UpdateBoneMatrix(m_Scene->mRootNode, aiMatrix4x4());
    }

    int i = 0;
    for (auto itr = m_Bone.begin(); itr != m_Bone.end(); ++itr) {
        m_BoneMatrix[i]._11 = itr->second.Matrix.a1;
        m_BoneMatrix[i]._12 = itr->second.Matrix.a2;
        m_BoneMatrix[i]._13 = itr->second.Matrix.a3;
        m_BoneMatrix[i]._14 = itr->second.Matrix.a4;

        m_BoneMatrix[i]._21 = itr->second.Matrix.b1;
        m_BoneMatrix[i]._22 = itr->second.Matrix.b2;
        m_BoneMatrix[i]._23 = itr->second.Matrix.b3;
        m_BoneMatrix[i]._24 = itr->second.Matrix.b4;

        m_BoneMatrix[i]._31 = itr->second.Matrix.c1;
        m_BoneMatrix[i]._32 = itr->second.Matrix.c2;
        m_BoneMatrix[i]._33 = itr->second.Matrix.c3;
        m_BoneMatrix[i]._34 = itr->second.Matrix.c4;

        m_BoneMatrix[i]._41 = itr->second.Matrix.d1;
        m_BoneMatrix[i]._42 = itr->second.Matrix.d2;
        m_BoneMatrix[i]._43 = itr->second.Matrix.d3;
        m_BoneMatrix[i]._44 = itr->second.Matrix.d4;
        i++;
    }
    // 頂点変換(CPUスキニング)
    //for (unsigned int m = 0; m < m_Scene->mNumMeshes; m++) {
    //    aiMesh* mesh = m_Scene->mMeshes[m];

    //    D3D11_MAPPED_SUBRESOURCE ms;
    //    CRenderer::GetDeviceContext()->Map(m_VertexBuffer[m], 0,
    //                                       D3D11_MAP_WRITE_DISCARD, 0, &ms);

    //    VERTEX_3D *vertex = (VERTEX_3D*)ms.pData;

    //    for (unsigned int v = 0; v < mesh->mNumVertices; v++) {
    //        DEFORM_VERTEX * deformVertex = &m_DeformVertex[m][v];

    //        aiMatrix4x4 matrix[4];
    //        aiMatrix4x4 outMatrix;
    //        matrix[0] = m_Bone[deformVertex->BoneName[0]].Matrix;
    //        matrix[1] = m_Bone[deformVertex->BoneName[1]].Matrix;
    //        matrix[2] = m_Bone[deformVertex->BoneName[2]].Matrix;
    //        matrix[3] = m_Bone[deformVertex->BoneName[3]].Matrix;

    //        //ウェイトを考慮してマトリクス算出
    //        {
    //            outMatrix.a1 = (matrix[0].a1 * deformVertex->BoneWeight[0]
    //                + matrix[1].a1 * deformVertex->BoneWeight[1]
    //                + matrix[2].a1 * deformVertex->BoneWeight[2]
    //                + matrix[3].a1 * deformVertex->BoneWeight[3]);

    //            outMatrix.a2 = matrix[0].a2 * deformVertex->BoneWeight[0]
    //                + matrix[1].a2 * deformVertex->BoneWeight[1]
    //                + matrix[2].a2 * deformVertex->BoneWeight[2]
    //                + matrix[3].a2 * deformVertex->BoneWeight[3];

    //            outMatrix.a3 = matrix[0].a3 * deformVertex->BoneWeight[0]
    //                + matrix[1].a3 * deformVertex->BoneWeight[1]
    //                + matrix[2].a3 * deformVertex->BoneWeight[2]
    //                + matrix[3].a3 * deformVertex->BoneWeight[3];

    //            outMatrix.a4 = matrix[0].a4 * deformVertex->BoneWeight[0]
    //                + matrix[1].a4 * deformVertex->BoneWeight[1]
    //                + matrix[2].a4 * deformVertex->BoneWeight[2]
    //                + matrix[3].a4 * deformVertex->BoneWeight[3];


    //            outMatrix.b1 = matrix[0].b1 * deformVertex->BoneWeight[0]
    //                + matrix[1].b1 * deformVertex->BoneWeight[1]
    //                + matrix[2].b1 * deformVertex->BoneWeight[2]
    //                + matrix[3].b1 * deformVertex->BoneWeight[3];

    //            outMatrix.b2 = matrix[0].b2 * deformVertex->BoneWeight[0]
    //                + matrix[1].b2 * deformVertex->BoneWeight[1]
    //                + matrix[2].b2 * deformVertex->BoneWeight[2]
    //                + matrix[3].b2 * deformVertex->BoneWeight[3];

    //            outMatrix.b3 = matrix[0].b3 * deformVertex->BoneWeight[0]
    //                + matrix[1].b3 * deformVertex->BoneWeight[1]
    //                + matrix[2].b3 * deformVertex->BoneWeight[2]
    //                + matrix[3].b3 * deformVertex->BoneWeight[3];

    //            outMatrix.b4 = matrix[0].b4 * deformVertex->BoneWeight[0]
    //                + matrix[1].b4 * deformVertex->BoneWeight[1]
    //                + matrix[2].b4 * deformVertex->BoneWeight[2]
    //                + matrix[3].b4 * deformVertex->BoneWeight[3];


    //            outMatrix.c1 = matrix[0].c1 * deformVertex->BoneWeight[0]
    //                + matrix[1].c1 * deformVertex->BoneWeight[1]
    //                + matrix[2].c1 * deformVertex->BoneWeight[2]
    //                + matrix[3].c1 * deformVertex->BoneWeight[3];

    //            outMatrix.c2 = matrix[0].c2 * deformVertex->BoneWeight[0]
    //                + matrix[1].c2 * deformVertex->BoneWeight[1]
    //                + matrix[2].c2 * deformVertex->BoneWeight[2]
    //                + matrix[3].c2 * deformVertex->BoneWeight[3];

    //            outMatrix.c3 = matrix[0].c3 * deformVertex->BoneWeight[0]
    //                + matrix[1].c3 * deformVertex->BoneWeight[1]
    //                + matrix[2].c3 * deformVertex->BoneWeight[2]
    //                + matrix[3].c3 * deformVertex->BoneWeight[3];

    //            outMatrix.c4 = matrix[0].c4 * deformVertex->BoneWeight[0]
    //                + matrix[1].c4 * deformVertex->BoneWeight[1]
    //                + matrix[2].c4 * deformVertex->BoneWeight[2]
    //                + matrix[3].c4 * deformVertex->BoneWeight[3];


    //            outMatrix.d1 = matrix[0].d1 * deformVertex->BoneWeight[0]
    //                + matrix[1].d1 * deformVertex->BoneWeight[1]
    //                + matrix[2].d1 * deformVertex->BoneWeight[2]
    //                + matrix[3].d1 * deformVertex->BoneWeight[3];

    //            outMatrix.d2 = matrix[0].d2 * deformVertex->BoneWeight[0]
    //                + matrix[1].d2 * deformVertex->BoneWeight[1]
    //                + matrix[2].d2 * deformVertex->BoneWeight[2]
    //                + matrix[3].d2 * deformVertex->BoneWeight[3];

    //            outMatrix.d3 = matrix[0].d3 * deformVertex->BoneWeight[0]
    //                + matrix[1].d3 * deformVertex->BoneWeight[1]
    //                + matrix[2].d3 * deformVertex->BoneWeight[2]
    //                + matrix[3].d3 * deformVertex->BoneWeight[3];

    //            outMatrix.d4 = matrix[0].d4 * deformVertex->BoneWeight[0]
    //                + matrix[1].d4 * deformVertex->BoneWeight[1]
    //                + matrix[2].d4 * deformVertex->BoneWeight[2]
    //                + matrix[3].d4 * deformVertex->BoneWeight[3];
    //        }

    //        deformVertex->Position = mesh->mVertices[v];
    //        deformVertex->Position *= outMatrix;


    //        //法線変換用に移動成分を削除
    //        outMatrix.a4 = 0.0f;
    //        outMatrix.b4 = 0.0f;
    //        outMatrix.c4 = 0.0f;

    //        deformVertex->Normal = mesh->mNormals[v];
    //        deformVertex->Normal *= outMatrix;

    //        //頂点バッファ―へ書き込み
    //        vertex[v].Position.x = deformVertex->Position.x;
    //        vertex[v].Position.y = deformVertex->Position.y;
    //        vertex[v].Position.z = deformVertex->Position.z;

    //        vertex[v].Normal.x = deformVertex->Normal.x;
    //        vertex[v].Normal.y = deformVertex->Normal.y;
    //        vertex[v].Normal.z = deformVertex->Normal.z;
    //        
    //        vertex[v].TexCoord.x = mesh->mTextureCoords[0][v].x;
    //        vertex[v].TexCoord.y = mesh->mTextureCoords[0][v].y;

    //        vertex[v].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    //    }
    //    CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer[m], 0);
    //}
}

void CAnimationModel::Draw() {
    //プリミティブ
    CRenderer::GetDeviceContext()->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    //マテリアル設定
    MATERIAL material;
    ZeroMemory(&material, sizeof(material));
    material.Diffuse = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    material.Ambient = COLOR(1.0f, 1.0f, 1.0f, 1.0f);

    //CRenderer::SetMaterial(material);

    for (unsigned int m = 0; m < m_Scene->mNumMaterials; m++) {
        aiMesh* mesh = m_Scene->mMeshes[m];

        aiMaterial* material = m_Scene->mMaterials[mesh->mMaterialIndex];

        //テクスチャ設定
        aiString path;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
        CRenderer::SetTexture(m_Texture[path.data], 0);
        //CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, m_Texture[path.data]);

        //頂点バッファ設定
        UINT stride = sizeof(VERTEX_3D_ANIMATION);
        UINT offset = 0;
        CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1,
                                                          &m_VertexBuffer[m], &stride, &offset);

        // インデックスバッファ設定
        CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer[m], DXGI_FORMAT_R32_UINT, 0);

        //ポリゴン描画
        CRenderer::GetDeviceContext()->DrawIndexed(mesh->mNumFaces * 3, 0, 0);
    }
}

void CAnimationModel::Load(const char *FileName) {
    const std::string modelPath(FileName);

    m_Scene = aiImportFile(FileName,
                           aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded);
    assert(m_Scene);

    m_VertexBuffer = new ID3D11Buffer*[m_Scene->mNumMeshes];
    m_IndexBuffer = new ID3D11Buffer*[m_Scene->mNumMeshes];

    //変形後頂点配列生成
    //m_DeformVertex = new std::vector<DEFORM_VERTEX>[m_Scene->mNumMeshes];

    //再帰的にボーン生成
    CreateBone(m_Scene->mRootNode);
    m_Bone[""].No = 0;
    int no = 0;
    for (auto itr = m_Bone.begin(); itr != m_Bone.end(); ++itr) {
        itr->second.No = no++;
    }
    m_BoneMatrix = new XMFLOAT4X4[m_Bone.size()];

    for (unsigned int m = 0; m < m_Scene->mNumMeshes; m++) {
        aiMesh* mesh = m_Scene->mMeshes[m];

        //頂点バッファ生成
        {
            VERTEX_3D_ANIMATION* vertex = new VERTEX_3D_ANIMATION[mesh->mNumVertices];
            int* bonenum = new int[mesh->mNumVertices];

            for (unsigned int v = 0; v < mesh->mNumVertices; v++) {
                vertex[v].Position = XMFLOAT3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);
                vertex[v].Normal = XMFLOAT3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z);
                vertex[v].TexCoord = XMFLOAT2(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y);
                vertex[v].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

                bonenum[v] = 0;
                for (int i = 0; i < 4; i++) {
                    vertex[v].BoneNo[i] = 0;
                    vertex[v].BoneWeight[i] = 0;
                }
            }

            //ボーンデータ初期化
            for (unsigned int b = 0; b < mesh->mNumBones; b++) {
                aiBone* bone = mesh->mBones[b];

                //変形後頂点にボーンデータ格納
                for (unsigned int w = 0; w < bone->mNumWeights; w++) {
                    aiVertexWeight weight = bone->mWeights[w];

                    vertex[weight.mVertexId].BoneWeight[bonenum[weight.mVertexId]] = weight.mWeight;
                    vertex[weight.mVertexId].BoneNo[bonenum[weight.mVertexId]] = m_Bone[bone->mName.C_Str()].No;
                    bonenum[weight.mVertexId]++;
                }
            }
            delete[] bonenum;

            D3D11_BUFFER_DESC bd;
            ZeroMemory(&bd, sizeof(bd));
            bd.Usage = D3D11_USAGE_DYNAMIC;
            bd.ByteWidth = sizeof(VERTEX_3D_ANIMATION) * mesh->mNumVertices;
            bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

            D3D11_SUBRESOURCE_DATA sd;
            ZeroMemory(&sd, sizeof(sd));
            sd.pSysMem = vertex;

            CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer[m]);

            delete[] vertex;
        }

        //インデックスバッファ生成
        {
            unsigned int* index = new unsigned int[mesh->mNumFaces * 3];

            for (unsigned int f = 0; f < mesh->mNumFaces; f++) {
                const aiFace* face = &mesh->mFaces[f];

                assert(face->mNumIndices == 3);

                index[f * 3 + 0] = face->mIndices[0];
                index[f * 3 + 1] = face->mIndices[1];
                index[f * 3 + 2] = face->mIndices[2];
            }

            D3D11_BUFFER_DESC bd;
            ZeroMemory(&bd, sizeof(bd));
            bd.Usage = D3D11_USAGE_DEFAULT;
            bd.ByteWidth = sizeof(unsigned int) * mesh->mNumFaces * 3;
            bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
            bd.CPUAccessFlags = 0;

            D3D11_SUBRESOURCE_DATA sd;
            ZeroMemory(&sd, sizeof(sd));
            sd.pSysMem = index;

            CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer[m]);

            delete[] index;
        }

        //変形後頂点データ初期化
        /*for (unsigned int v = 0; v < mesh->mNumVertices; v++) {
            DEFORM_VERTEX deformVertex;
            deformVertex.Position = mesh->mVertices[v];
            deformVertex.Normal = mesh->mNormals[v];
            deformVertex.BoneNum = 0;

            for (unsigned int b = 0; b < 4; b++) {
                deformVertex.BoneName[b] = "";
                deformVertex.BoneWeight[b] = 0.0f;
            }
            m_DeformVertex[m].push_back(deformVertex);
        }*/

        //ボーンデータ初期化
        for (unsigned int b = 0; b < mesh->mNumBones; b++) {
            aiBone* bone = mesh->mBones[b];

            m_Bone[bone->mName.C_Str()].OffsetMatrix =
                bone->mOffsetMatrix;

            //変形後頂点にボーンデータ格納
            /*for (unsigned int w = 0; w < bone->mNumWeights; w++) {
                aiVertexWeight weight = bone->mWeights[w];

                int num = m_DeformVertex[m][weight.mVertexId].BoneNum;

                m_DeformVertex[m][weight.mVertexId].BoneWeight[num] =
                    weight.mWeight;
                m_DeformVertex[m][weight.mVertexId].BoneName[num] =
                    bone->mName.C_Str();
                m_DeformVertex[m][weight.mVertexId].BoneNum++;

                assert(m_DeformVertex[m][weight.mVertexId].BoneNum <= 4);
            }*/
        }
    }
    //テクスチャ読み込み
    {
        for (unsigned int m = 0; m < m_Scene->mNumMaterials; m++) {
            aiString path;

            if (m_Scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
                if (path.data[0] == '*') {
                    //FBXファイル内から読み込み
                    if (m_Texture[path.data] == nullptr) {
                        //ID3D11Resource* resource;
                        CTextureWIC* texture;
                        texture = new CTextureWIC;
                        int id = atoi(&path.data[1]);
                        
                        /*D3DX11CreateShaderResourceViewFromMemory(
                            CRenderer::GetDevice(),
                            (const unsigned char*)m_Scene->mTextures[id]->pcData,
                            m_Scene->mTextures[id]->mWidth,
                            NULL,
                            NULL,
                            &texture,
                            NULL);*/

                        //m_Texture[path.data] = texture;
                        texture->Load((const unsigned char*)m_Scene->mTextures[id]->pcData,
                            m_Scene->mTextures[id]->mWidth);

                        m_Texture[path.data] = texture;
                    }
                }
                else {
                     //外部ファイルから読み込み
                }
            }
            else {
                m_Texture[path.data] = NULL;
            }
            
        }
    }
}

void CAnimationModel::Unload() {
    for (unsigned int m = 0; m < m_Scene->mNumMeshes; m++) {
        m_VertexBuffer[m]->Release();
        m_IndexBuffer[m]->Release();
    }
    delete[] m_VertexBuffer;
    delete[] m_IndexBuffer;

    //delete[] m_DeformVertex;

    delete[] m_BoneMatrix;

    for (auto pair : m_Texture)
        pair.second->Unload();

    aiReleaseImport(m_Scene);

    for(auto pair : m_Animation)
        aiReleaseImport(pair.second);
}

void CAnimationModel::LoadAnimation(const char *FileName, const char *Name) {
    m_Animation[Name] = aiImportFile(FileName, aiProcess_ConvertToLeftHanded);
    assert(m_Animation[Name]);
}

void CAnimationModel::CreateBone(aiNode* node) {
    BONE bone;

    m_Bone[node->mName.C_Str()] = bone;

    for (unsigned int n = 0; n < node->mNumChildren; n++)
        CreateBone(node->mChildren[n]);
}

void CAnimationModel::UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix) {
    BONE* bone = &m_Bone[node->mName.C_Str()];

    //マトリクスの乗算順番に注意
    aiMatrix4x4 worldMatrix;

    worldMatrix = matrix;
    worldMatrix *= bone->AnimationMatrix;

    bone->Matrix = worldMatrix;
    bone->Matrix *= bone->OffsetMatrix;

    for (unsigned int n = 0; n < node->mNumChildren; n++)
        UpdateBoneMatrix(node->mChildren[n], worldMatrix);
}

void CAnimationModel::BrendAnimation() {
    //アニメーションデータからボーンマトリクス算出
    aiAnimation* animation1 = m_Animation[m_NowAnimationName]->mAnimations[0];
    aiAnimation* animation2 = m_Animation[m_NextAnimationName]->mAnimations[0];

    int frame1, frame2;
    frame1 = (int)m_Frame1;
    frame2 = (int)m_Frame2;
    for (unsigned int c = 0; c < animation1->mNumChannels; c++) {
        aiNodeAnim* nodeAnim = animation1->mChannels[c];
        aiNodeAnim* nodeAnim2 = animation2->mChannels[c];
        BONE* bone = &m_Bone[nodeAnim->mNodeName.C_Str()];

        int f;
        f = frame1 % nodeAnim->mNumRotationKeys; //簡易実装
        aiQuaternion rot = nodeAnim->mRotationKeys[f].mValue;

        f = frame1 % nodeAnim->mNumPositionKeys; //簡易実装
        aiVector3D pos = nodeAnim->mPositionKeys[f].mValue;

        f = frame2 % nodeAnim2->mNumRotationKeys; //簡易実装
        aiQuaternion rot2 = nodeAnim2->mRotationKeys[f].mValue;

        f = frame2 % nodeAnim2->mNumPositionKeys; //簡易実装
        aiVector3D pos2 = nodeAnim2->mPositionKeys[f].mValue;

        aiQuaternion::Interpolate(rot, rot, rot2, m_Per);
        /*rot.x += (rot2.x - rot.x) * cosf(m_Per);
        rot.y += (rot2.y - rot.y) * cosf(m_Per);
        rot.z += (rot2.z - rot.z) * cosf(m_Per);
        rot.w += (rot2.w - rot.w) * cosf(m_Per);*/
        
        pos += (pos2 - pos) * m_Per;

        bone->AnimationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot, pos);
    }
    
    if (m_Per >= 1) {
        m_Frame1 = m_Frame2;
        m_Frame2 = 0;
        strcpy(m_NowAnimationName, m_NextAnimationName);
        strcpy(m_NextAnimationName, "NONE");
        m_Per = 0.0f;
        return;
    }

    m_Per += 0.02f;
    m_Frame2 += 1.0f;
}

void CAnimationModel::SetAnimation(const char* AnimationName) {
    if (m_Animation[AnimationName]->HasAnimations() == false)
        return;

    if (strcmp(m_NowAnimationName, "NONE") == 0) {
        strcpy(m_NowAnimationName, AnimationName);
    }
    else {
        if (strcmp(m_NowAnimationName, AnimationName) != 0) {
            strcpy(m_NextAnimationName, AnimationName);
        }
    }
}