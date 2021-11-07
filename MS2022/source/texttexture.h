/*==================================================================================================
    MS2022
    [texttexture.h]
    ・テキストテクスチャ作成
----------------------------------------------------------------------------------------------------
    2021.11.07 @Author HAYASE SUZUKI
====================================================================================================
    History
        211107 作成

/*================================================================================================*/
#pragma once

#include <string>
#include <d2d1.h>
#include <d2d1_1.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment( lib, "dwrite.lib" )

class CTextTexture {
private:
    static ID2D1DeviceContext* m_D2DContext;
    static ID3D11Texture2D* m_TextTexture;
    static IDWriteFactory* pDWFactory;

public:

    static void Init();
    static void MakeTexture(ID3D11Texture2D* &texture,
        ID3D11ShaderResourceView* &srv, ID2D1Bitmap1*& d2dTargetBitmap);
    static void Draw2D(ID2D1Bitmap1* d2dTargetBitmap, const char* text);
};