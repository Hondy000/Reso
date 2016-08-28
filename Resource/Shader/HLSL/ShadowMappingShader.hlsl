
// 定数バッファ
cbuffer CBuffer : register(b0)
{
	column_major float4x4 g_matLightWorldViewProj    : packoffset(c0);  // ライトビューの正射影行列
};

// 頂点シェーダーの入力パラメータ
struct VS_IN
{
	float3 pos    : POSITION;    // 頂点座標
};

// 頂点シェーダーの出力パラメータ
struct VS_OUT_PS_IN
{
	float4 pos      : SV_POSITION;
};

// 頂点シェーダー
VS_OUT_PS_IN VS_Main(VS_IN In)
{
	VS_OUT_PS_IN Out;
	Out.pos = mul(float4(In.pos, 1.0f), g_matLightWorldViewProj);
	return Out;
}