
// 定数バッファ
cbuffer ConstatntBuffer : register(b0) {
	matrix World;
	matrix View;
	matrix Projection;
}

struct VS_IN {
	float4 pos  : POSITION0;
	float4 nor  : NORMAL0;
	float4 diff : COLOR0;
	float2 tex  : TEXCOORD0;
};

struct VS_OUT {
	float4 pos      : SV_POSITION;
	float4 nor      : NORMAL0;
	float4 diff     : COLOR0;
	float2 tex      : TEXCOORD0;
};


//=============================================================================
// 頂点シェーダ
//=============================================================================
void main(in VS_IN In, out VS_OUT Out) {
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

	Out.pos = mul(In.pos, wvp);
	Out.diff = In.diff;
	Out.tex = In.tex;
	Out.nor = In.nor;
}

