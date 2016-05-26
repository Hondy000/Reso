
// ワールド行列 × ビュー × 射影行列
cbuffer cbMatrixWVP : register(b0)
{
	// 列優先
	matrix g_matWVP : packoffset(c0);
};

// 頂点シェーダーの入力パラメータ
struct VS0_IN
{
	float3 pos    : POSITION;           // 頂点座標
	float2 texel  : TEXCOORD;           // テクセル
};

// 頂点シェーダーの出力パラメータ
struct VS0_OUT
{
	float4 pos : SV_POSITION;
	float2 texel  : TEXCOORD0;
};

// テクスチャー
Texture2D g_Tex : register(t0);

// サンプラーステート
SamplerState  g_Sampler : register(s0);
// 頂点シェーダー
VS0_OUT VS_Main(VS0_IN In)
{
	VS0_OUT Out;
	Out.pos = mul(float4(In.pos, 1), g_matWVP);
	Out.texel = In.texel;
	return Out;
}

// ピクセルシェーダ
float4 PS_Main(VS0_OUT In) : SV_TARGET0
{
	float4 color = g_Tex.Sample(g_Sampler, In.texel);
	return color;
}
