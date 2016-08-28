// ************************************************************
// 入出力パラメータの定義
// ************************************************************

// 頂点シェーダーの入力パラメータ
struct VS_IN
{
	float3 pos    : POSITION;           // 頂点座標
	float2 texel  : TEXCOORD;           // テクセル
	column_major float4x4 mat : MATRIX; // インスタンスごとに設定される行列	 
	float4 col : COLOR0; 
};

// 頂点シェーダーの出力パラメータ
struct VS_OUT
{
	float4 sv_pos : SV_POSITION;
	float2 texel  : TEXCOORD0;	
	float4 col : COLOR0; 
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
	Out.col = In.col;
	return Out;
}

// ピクセルシェーダ
float4 PS_Main(VS_OUT In) : SV_TARGET0
{
	float4 Out;
	
	float4 decalmap = g_DecalMap.Sample(g_Sampler, In.texel);
	
	//// 法線ベクトルを 0 ～ 1 範囲を -1 ～ 1 に変換する
	//decalmap.rg = decalmap.rg * 2.0f - 1.0f;
	//decalmap.rb *= -1.0f;
	//
	//// ライティング
	//float diffuse = dot(decalmap.rgb, -g_vecLight.xyz);
	//diffuse = diffuse * 0.5f + 0.5f;
	//
	Out = decalmap * In.col;
	return Out;
}