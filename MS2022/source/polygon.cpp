
#include "main.h"
#include "window.h"
#include "renderer.h"

#include "game_object.h"
#include "polygon.h"



void CPolygon::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(100.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(0.0f, 100.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(100.0f, 100.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof( VERTEX_3D ) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory( &sd, sizeof(sd) );
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer( &bd, &sd, &m_VertexBuffer );


	m_Shader = new CShader();
	m_Shader->Init( "shaderVS.cso", "shaderPS.cso" );
	

	m_Texture = new CTexture();
	m_Texture->Load( "Assets/Textures/field004.tga" );

	m_TextureWic = new CTextureWIC();
	m_TextureWic->Load(L"Assets/Textures/robot.jpg");
}


void CPolygon::Uninit()
{
	m_Shader->Uninit();
	delete m_Shader;

	m_Texture->Unload();
	delete m_Texture;

	m_TextureWic->Unload();
	delete m_TextureWic;

	m_VertexBuffer->Release();

}


void CPolygon::Update()
{

}


void CPolygon::Draw()
{
	CRenderer::SetDepthEnable(false);
	// 頂点バッファ設定
	UINT stride = sizeof( VERTEX_3D );
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers( 0, 1, &m_VertexBuffer, &stride, &offset );


	XMFLOAT4X4 identity;
	DirectX::XMStoreFloat4x4(&identity, XMMatrixIdentity());

	m_Shader->SetWorldMatrix(&identity);
	m_Shader->SetViewMatrix(&identity);

	XMFLOAT4X4 projection;
	DirectX::XMStoreFloat4x4(&projection, XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
	m_Shader->SetProjectionMatrix(&projection);

	//m_Shader->SetPrameter( m_Blend );

	m_Shader->Set();


	// テクスチャ設定
	CRenderer::SetTexture( m_TextureWic, 0 );

	// プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	// ポリゴン描画
	CRenderer::GetDeviceContext()->Draw( 4, 0 );

	CRenderer::SetDepthEnable(true);
}

void CPolygon::SetVertex(XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT2 uv, XMFLOAT2 uvsize) {
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
	memcpy(msr.pData, vertex, sizeof(VERTEX_3D)*4); // 3頂点分コピー
	CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
}