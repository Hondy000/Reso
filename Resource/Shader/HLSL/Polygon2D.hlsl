// ワールド行列 × ビュー × 射影行列

cbuffer MatrixBuffer : register(b0)
{
	column_major float4x4 wvp;
};



// 頂点シェーダーの入力パラメータ
struct VS_IN
{
   float3 pos   : POSITION;   // 頂点座標  
   float2 tex   : TEXCOORD0;   // 頂点座標
};

// 頂点シェーダーの出力パラメータ
struct VS_OUT
{
   float4 pos    : SV_POSITION;
   float2 tex	: TEXCOORD0;
};

// 頂点シェーダー			
VS_OUT VS_Main( VS_IN In )
{
	VS_OUT Out;
	Out.pos = mul( float4( In.pos, 1 ), wvp);
	Out.tex = In.tex;
	return Out;
}
						  
// テクスチャー
Texture2D g_Tex : register(t0);

// サンプラーステート
SamplerState  g_Sampler : register(s0);
										   
// ピクセルシェーダ
float4 PS_Main( VS_OUT In ) : SV_TARGET
{
	float4 color = g_Tex.Sample(g_Sampler, In.tex);
	return color;
}