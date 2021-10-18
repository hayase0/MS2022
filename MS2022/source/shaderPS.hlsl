//*****************************************************************************
// グローバル変数
//*****************************************************************************
Texture2D		g_Texture : register(t0);
SamplerState	g_SamplerState : register(s0);

struct VS_OUT {
	float4 pos      : SV_POSITION;
	float4 nor      : NORMAL0;
	float4 diff     : COLOR0;
	float2 tex      : TEXCOORD0;
};

//=============================================================================
// ピクセルシェーダ
//=============================================================================
void main(in VS_OUT In, out float4 outDiffuse : SV_Target) {

	outDiffuse = g_Texture.Sample(g_SamplerState, In.tex);

	//outDiffuse *= In.diff;

}