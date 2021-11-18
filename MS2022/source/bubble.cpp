/*==================================================================================================
	MS2022
	[bubble.cpp]
	・吹き出し
----------------------------------------------------------------------------------------------------
	2021.11.07 @Author HAYASE SUZUKI
====================================================================================================
	History
		211107 作成

/*================================================================================================*/
#include "main.h"
#include "window.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "camera.h"
#include "player.h"

#include "game_object.h"
#include "bubble.h"

#include <locale.h>

void CBubble::Init() {
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(-1.0f, 0.2f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(1.0f, 0.2f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-1.0f, -0.2f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(1.0f, -0.2f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


	m_Shader = new CShader();
	m_Shader->Init("shaderVS.cso", "shaderPS.cso");

	CTextTexture::MakeTexture(m_Texture, m_SRV, m_TargetBitMap);

	m_Position = XMFLOAT3(0, 0, 0);
	m_Rotation = XMFLOAT3(0, 0, 0);
	m_Scale = XMFLOAT3(5, 2, 2);
}


void CBubble::Uninit() {

	m_Texture->Release();
	m_SRV->Release();
	m_TargetBitMap->Release();

	m_Shader->Uninit();
	delete m_Shader;

	m_VertexBuffer->Release();

}


void CBubble::Update() {
	if (m_Parent) {
		m_Position = m_Parent->GetPosition();
		m_Position.y += 10;
	}

	m_Counter++;
	if (m_Counter > 300)
		SetDestroy();
}


void CBubble::Draw() {
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);

	// ビルボード
	CCamera* camera = CCamera::GetInstance();
	XMFLOAT4X4 invview = camera->GetInvViewMatrix();
	invview._41 = 0.0f;
	invview._42 = 0.0f;
	invview._43 = 0.0f;
	XMMATRIX invmat = XMLoadFloat4x4(&invview);
	world *= invmat;

	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	//CRenderer::SetWorldMatrix( &world );

	
	XMFLOAT4X4 worldf;
	DirectX::XMStoreFloat4x4(&worldf, world);

	m_Shader->SetWorldMatrix(&worldf);

	m_Shader->SetViewMatrix(&CRenderer::GetViewMatrix());
	m_Shader->SetProjectionMatrix(&CRenderer::GetProjectionMatrix());

	//m_Shader->SetPrameter( m_Blend );

	m_Shader->Set();


	CTextTexture::Draw2D(m_TargetBitMap, m_Text.c_str());
	// テクスチャ設定
	//CRenderer::SetTexture( m_TextureWic, 0 );
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_SRV);

	// プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);
}

void CBubble::SetVertex(XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT2 uv, XMFLOAT2 uvsize) {
	VERTEX_3D vertex[4];
	vertex[0].Position = pos;
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = uv;

	vertex[1].Position = XMFLOAT3(pos.x + size.x, pos.y, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(uv.x + uvsize.x, uv.y);

	vertex[2].Position = XMFLOAT3(pos.x, pos.y + size.y, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(uv.x, uv.y + uvsize.y);

	vertex[3].Position = XMFLOAT3(pos.x + size.x, pos.y + size.y, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(uv.x + uvsize.x, uv.y + uvsize.y);

	D3D11_MAPPED_SUBRESOURCE msr;
	CRenderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	memcpy(msr.pData, vertex, sizeof(VERTEX_3D) * 4); // 3頂点分コピー
	CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
}