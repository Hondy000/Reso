// ************************************************************
// ParticlesIntoBuffer フェーズ
// ************************************************************

// 頂点シェーダーの入力パラメータ
struct VS0_IN
{
	float3 pos    : POSITION;           // 頂点座標
	float2 texel  : TEXCOORD;           // テクセル
	column_major float4x4 mat : MATRIX; // インスタンスごとに設定される行列
	float4 color  : COLOR;              // 頂点カラー( 使用するのはアルファ値のみ )
};

// 頂点シェーダーの出力パラメータ
struct VS0_OUT
{
	float4 sv_pos : SV_POSITION;
	float4 color  : COLOR0;
	float2 texel  : TEXCOORD0;
};

Texture2D g_DecalMap : register(t0);  // デカールマップ

// サンプラーステート
SamplerState  g_Sampler0 : register(s0);

// 頂点シェーダー
VS0_OUT ParticlesIntoBuffer_VS_Main(VS0_IN In)
{
	VS0_OUT Out;
	Out.sv_pos = mul(float4(In.pos, 1.0f), In.mat);
	Out.texel = In.texel;
	Out.color = In.color;
	return Out;
}

// ピクセルシェーダ
float4 ParticlesIntoBuffer_PS_Main(VS0_OUT In) : SV_TARGET0
{
	float4 Out;

	float4 decalmap = g_DecalMap.Sample(g_Sampler0, In.texel);

		float alpha = In.color.a * decalmap.a;

	// 法線ベクトルを 0 ～ 1 範囲を -1 ～ 1 に変換する
	decalmap.rg = decalmap.rg * 2.0f - 1.0f;
	decalmap.r *= -1.0f;
	// 法線ベクトルおよび、アルファ値を出力
	Out = float4(decalmap.rg, 0, alpha);

	return Out;
}

// ************************************************************
// CompositeParticles フェーズ
// ************************************************************

// 頂点シェーダーの入力パラメータ
struct VS1_IN
{
	float3 pos    : POSITION;           // 頂点座標
	float2 texel  : TEXCOORD;           // テクセル
};

// 頂点シェーダーの出力パラメータ
struct VS1_OUT
{
	float4 sv_pos : SV_POSITION;
	float2 texel  : TEXCOORD0;
};

Texture2D g_NormalMap : register(t0);  // 法線マップ

// サンプラーステート
SamplerState  g_Sampler1 : register(s0);

// 定数バッファ０
cbuffer cbBuffer0 : register(b0)
{
	float4 g_vecLight    : packoffset(c0);    // 平行光源の方向ベクトル
	float4 g_Color       : packoffset(c1);    // パーティクルカラー
};

// 頂点シェーダー
VS1_OUT CompositeParticles_VS_Main(VS1_IN In)
{
	VS1_OUT Out;
	Out.sv_pos = float4(In.pos, 1);
	Out.texel = In.texel;
	return Out;
}

// ピクセルシェーダ
float4 CompositeParticles_PS_Main(VS1_OUT In) : SV_TARGET0
{
	float4 Out;

	float4 normalmap = g_NormalMap.Sample(g_Sampler1, In.texel);

		float3 normal = float3(0, 0, -1);
		normal.rg += float2(normalmap.x, normalmap.y);
	normal = normalize(normal);

	// ライティング
	float diffuse = dot(normal, -g_vecLight.xyz);
	diffuse = diffuse * 0.5f + 0.5f;

	Out = float4(g_Color.rgb * diffuse, normalmap.a);

	return Out;
}