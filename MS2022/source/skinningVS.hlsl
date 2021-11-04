
// 定数バッファ
cbuffer ConstatntBuffer : register(b0) {
	matrix World;
	matrix View;
	matrix Projection;
}

cbuffer BoneMatrixBuffer : register(b2) {
	matrix BoneMatrix[100];
}

struct VS_IN {
	float4 pos          : POSITION0;
	float4 nor          : NORMAL0;
	float4 diff         : COLOR0;
	float2 tex          : TEXCOORD0;
	float4 boneweight : WEIGHT;
	int4   boneno    : BONENO;
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
	matrix bonemat;
	bonemat = BoneMatrix[In.boneno[0]] * In.boneweight[0]
		+ BoneMatrix[In.boneno[1]] * In.boneweight[1]
		+ BoneMatrix[In.boneno[2]] * In.boneweight[2]
		+ BoneMatrix[In.boneno[3]] * In.boneweight[3];
	float4 pos;
	pos = mul(In.pos, bonemat);

	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

	Out.pos = mul(pos, wvp);
	Out.diff = In.diff;
	Out.tex = In.tex;
	Out.nor = In.nor;
}

