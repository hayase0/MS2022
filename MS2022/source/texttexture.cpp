/*==================================================================================================
    MS2022
    [texttexture.cpp]
    ・テキストテクスチャ作成
----------------------------------------------------------------------------------------------------
    2021.11.07 @Author HAYASE SUZUKI
====================================================================================================
    History
        211107 作成

/*================================================================================================*/
#include "main.h"
#include "renderer.h"
#include "texttexture.h"
#include <locale.h>

ID2D1DeviceContext* CTextTexture::m_D2DContext;
ID3D11Texture2D* CTextTexture::m_TextTexture;
IDWriteFactory* CTextTexture::pDWFactory;

void CTextTexture::Init() {
    ID3D11Device* d3ddevice = CRenderer::GetDevice();

    // DXGIFactoryとDXGIDeviceを作成
    IDXGIFactory1* dxgiFactory = nullptr;
    IDXGIDevice* dxgiDevice = nullptr;

    HRESULT hr = d3ddevice->QueryInterface(IID_PPV_ARGS(&dxgiDevice));
    if (FAILED(hr))
        assert(false);

    IDXGIAdapter* adapter = nullptr;
    hr = dxgiDevice->GetAdapter(&adapter);
    if (FAILED(hr))
        assert(false);

    hr = adapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
    if (FAILED(hr))
        assert(false);
    adapter->Release();

    // Direct2D,DirectWriteの初期化
    ID2D1Factory1* D2DFactory;
    ID2D1Device* d2ddevice;
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, IID_PPV_ARGS(&D2DFactory));
    if (FAILED(hr))
        assert(false);
    hr = D2DFactory->CreateDevice(dxgiDevice, &d2ddevice);
    if (FAILED(hr))
        assert(false);
    hr = d2ddevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m_D2DContext);
    if (FAILED(hr))
        assert(false);

    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWFactory));
    if (FAILED(hr))
        assert(false);
}

void CTextTexture::MakeTexture(ID3D11Texture2D* &texture,
    ID3D11ShaderResourceView* &srv, ID2D1Bitmap1* &d2dTargetBitmap) {
    int width, height;
    width = 500;
    height = 100;

    D3D11_TEXTURE2D_DESC td;
    ZeroMemory(&td, sizeof(td));
    td.Width = width;
    td.Height = height;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    td.SampleDesc.Count = 1;
    td.SampleDesc.Quality = 0;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    td.CPUAccessFlags = 0;
    td.MiscFlags = 0;
    HRESULT hr = CRenderer::GetDevice()->CreateTexture2D(&td, NULL, &texture);

    D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
    SRVDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    SRVDesc.Texture2D.MipLevels = 1;

    hr = CRenderer::GetDevice()->CreateShaderResourceView(texture, &SRVDesc, &srv);
    if (FAILED(hr)) {
        assert(false);
    }

    IDXGISurface1* surface;
    hr = texture->QueryInterface(IID_PPV_ARGS(&surface));
    if (FAILED(hr)) {
        assert(false);
    }

    D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
        D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
        D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
        96,
        96
    );
    hr = m_D2DContext->CreateBitmapFromDxgiSurface(surface, bitmapProperties, &d2dTargetBitmap);
    if (FAILED(hr)) {
        assert(false);
    }   
}

void CTextTexture::Draw2D(ID2D1Bitmap1* d2dTargetBitmap, const wchar_t* text) {
    // テクスチャ書き込み
    m_D2DContext->BeginDraw();
    m_D2DContext->Clear(D2D1::ColorF(D2D1::ColorF::White));
    m_D2DContext->SetTarget(d2dTargetBitmap);

    IDWriteTextFormat* pTextFormat = NULL;
    {
        pDWFactory->CreateTextFormat(
            L"Meiryo"
            , NULL
            , DWRITE_FONT_WEIGHT_NORMAL
            , DWRITE_FONT_STYLE_NORMAL
            , DWRITE_FONT_STRETCH_NORMAL
            , 50
            , L""
            , &pTextFormat
        );
    }
    ID2D1SolidColorBrush* pBrush = NULL;
    {
        m_D2DContext->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::Black)
            , &pBrush
        );
    }

    
   /* wchar_t wc[100];
    MultiByteToWideChar(CP_UTF8, 0U, text, -1, wc, strlen(text));*/
    size_t len = wcslen(text);
    m_D2DContext->DrawTextA(text, len,
        pTextFormat, &D2D1::RectF(0, 0, 1000, 100), pBrush);

    m_D2DContext->EndDraw();
}
