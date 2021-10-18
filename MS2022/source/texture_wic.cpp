
#include "main.h"
#include "renderer.h"
#include "texture_wic.h"
#include "WICTextureLoader11.h"

void CTextureWIC::Load(const wchar_t* FileName) {

    HRESULT hr = DirectX::CreateWICTextureFromFile(CRenderer::GetDevice(), 
        FileName, &m_Texture, &m_ShaderResourceView);

    if (FAILED(hr)) {
        assert(false);
    }
}

void CTextureWIC::Load(const unsigned char* Data, size_t Size) {
    HRESULT hr = DirectX::CreateWICTextureFromMemory(CRenderer::GetDevice(),
        Data, Size, &m_Texture, &m_ShaderResourceView);

    if (FAILED(hr)) {
        assert(false);
    }
}


void CTextureWIC::Unload() {
    m_Texture->Release();
    m_ShaderResourceView->Release();
}