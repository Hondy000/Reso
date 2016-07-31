// ワールド行列 × ビュー × 射影行列
cbuffer cbMatrixWVP : register( b0 )
{
   // 列優先
   column_major  float4x4 g_matWVP : packoffset( c0 );
};

cbuffer cbVecLight : register( b1 )
{
   float4 g_vecLight : packoffset( c0 );
};

// テクスチャー
Texture2D g_Tex : register( t0 );

// サンプラーステート
SamplerState  g_Sampler : register( s0 );

// 頂点シェーダーの入力パラメータ
struct VS_IN
{
   float3 pos   : POSITION;   // 頂点座標
};

// 頂点シェーダーの出力パラメータ
struct VS_OUT
{
   float4 pos    : SV_POSITION;
};

// 頂点シェーダー
VS_OUT VS_Main( VS_IN In )
{
   VS_OUT Out;

   Out.pos = mul( float4( In.pos, 1 ), g_matWVP );

   return Out;
}

// ピクセルシェーダ
float4 PS_Main( VS_OUT In ) : SV_TARGET
{
   return float4(1.0,0,0,1.0);
}