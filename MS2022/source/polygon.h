#pragma once
#include "shader.h"
#include "texture.h"
#include "texture_wic.h"

// ポリゴンクラス（ゲームオブジェクト）
class CPolygon : public CGameObject
{
private:

	ID3D11Buffer*	m_VertexBuffer = NULL; // 頂点バッファ
	CShader*		m_Shader;              // シェーダー

	CTexture*		m_Texture;             // テクスチャ
	CTextureWIC*    m_TextureWic;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(const char* FileName) { m_Texture->Load(FileName); }
	void SetVertex(XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT2 uv = XMFLOAT2(0, 0), XMFLOAT2 uvsize = XMFLOAT2(1.0, 1.0));
};