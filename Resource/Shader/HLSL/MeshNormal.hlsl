// ワールド行列 × ビュー × 射影行列
cbuffer cbMatrixWVP : register(b0)
{
	// 列優先
	column_major  float4x4 g_matWVP : packoffset(c0);
};

// 頂点シェーダーの入力パラメータ
struct VS0_IN
{
	float3 pos    : POSITION;           // 頂点座標
};

// 頂点シェーダーの出力パラメータ
struct VS0_OUT
{
	float4 sv_pos : SV_POSITION;
};

// 頂点シェーダー
VS0_OUT VS_Main(VS0_IN In)
{
	VS0_OUT Out;
	Out.sv_pos = mul(float4(In.pos, 1.0f), g_matWVP);
	return Out;
}

// ピクセルシェーダ
float4 PS_Main(VS0_OUT In) : SV_TARGET
{
	float4 Out;

	Out = float4(1,0,0,1);

	return Out;
}

