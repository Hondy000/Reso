// ************************************************************
// 入出力パラメータの定義
// ************************************************************

// 頂点シェーダーの入力パラメータ
struct VS_IN
{
	float3 pos    : POSITION;           // 頂点座標
	float2 texel  : TEXCOORD;           // テクセル
	column_major float4x4 mat : MATRIX; // インスタンスごとに設定される行列
	float4 color  : COLOR;              // 頂点カラー
};

// 頂点シェーダーの出力パラメータ
struct VS_OUT
{
	float4 sv_pos : SV_POSITION;
	float4 color  : COLOR0;
	float2 texel  : TEXCOORD0;
};

// ************************************************************
// テクスチャーの宣言
// ************************************************************

Texture2D g_DecalMap : register(t0);  // デカールマップ

// サンプラーステート
SamplerState  g_Sampler : register(s0);

// ************************************************************
// 定数バッファの宣言
// ************************************************************

// 定数バッファ０
cbuffer cbBuffer0 : register(b0)
{
	float4 g_vecLight : packoffset(c0);      // 平行光源の方向ベクトル
};

// ************************************************************
// シェーダーの実装
// ************************************************************

// 頂点シェーダー
VS_OUT VS_Main(VS_IN In)
{
	VS_OUT Out;
	Out.sv_pos = mul(float4(In.pos, 1.0f), In.mat);
	Out.texel = In.texel;
	Out.color = In.color;
	return Out;
}

// ピクセルシェーダ
float4 PS_Main(VS_OUT In) : SV_TARGET
{
	return g_Tex.Sample(g_Sampler, In.texel);
}