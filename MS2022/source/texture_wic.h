/*==================================================================================================
	MS2022
	[texture_wic.h]
	・テクスチャーウィック
----------------------------------------------------------------------------------------------------
	2021.10.15 @Author HAYASE SUZUKI
====================================================================================================
	History
		211015 作成

/*================================================================================================*/
#pragma once

#include "main.h"
#include "renderer.h"
#include <tchar.h>

#pragma comment( lib, "dxguid.lib")

class CTextureWIC {

public:

	void Load(const wchar_t* FileName);
	void Load(const unsigned char* Data, size_t Size);
	void Unload();

	ID3D11ShaderResourceView* GetShaderResourceView() { return m_ShaderResourceView; }


private:
	ID3D11Resource* m_Texture;
	ID3D11ShaderResourceView* m_ShaderResourceView;
};