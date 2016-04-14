
// ************************************************************
// 入出力パラメータの定義
// ************************************************************

// 頂点シェーダーの入力パラメータ
struct VS_IN
{
	float3 pos    : POSITION;   // 頂点座標
	float3 normal : NORMAL;     // 法線
	float2 texel  : TEXCOORD;   // テクセル
};

// 頂点シェーダーの出力パラメータ
struct VS_OUT
{
	float4 sv_pos : SV_POSITION;
	float3 normal : NORMAL;
	float2 texel  : TEXCOORD0;
	float3 pos    : TEXCOORD1;
};

// ************************************************************
// インターフェースの定義
// ************************************************************

interface iBaseLight
{
	float4 GetColor(VS_OUT In);
};

// インターフェースの宣言
iBaseLight g_abstractLight;

// ************************************************************
// テクスチャーの宣言
// ************************************************************

Texture2D g_DecalMap : register(t0);  // デカールマップ
Texture2D g_TexMap01 : register(t1);  // 汎用目的で使用するテクスチャー

// サンプラーステート
SamplerState  g_Sampler : register(s0);

// ************************************************************
// 共通関数
// ************************************************************

// Diffuse
float GetDiffuseColor(float3 lightdir, float3 normal)
{
	float Out;

	// ハーフランバートにて拡散反射率を計算する
	Out = dot(lightdir, normal);
	Out = Out * 0.5f + 0.5f;
	Out *= Out;

	return Out;
};

// Specular
float GetSpecularColor(float3 lightdir, float3 normal, float3 lookat)
{
	float Out = 0;

	// ハーフベクトルを計算する
	float3 half = normalize(lightdir + lookat);

	// 鏡面反射率を計算する
	Out = pow(max(0.0f, dot(normal, half)), 50.0f);

	return Out;
};

// Material
float3 GetMaterialColor(float2 texel)
{
	float3 Out;

	Out = g_DecalMap.Sample(g_Sampler, texel).rgb;

	return Out;
}

// ************************************************************
// クラスの実装
// ************************************************************

// ハーフランバート
class cHalfLambert : iBaseLight
{
	// 定数バッファ

	float4 g_vecLight;    // 平行光源の方向ベクトル

	// 色を計算する
	float4 GetColor(VS_OUT In)
	{
		float4 Out;

		float3 lightdir = normalize(-g_vecLight.xyz);
			float3 normal = normalize(In.normal);
			// 拡散反射率を計算する
			float diffuse = GetDiffuseColor(lightdir, normal);

		// 合成
		Out = float4(GetMaterialColor(In.texel) * diffuse, 1);

		return Out;
	}
};

// フォンシェーディング
class cPhongShading : iBaseLight
{
	// 定数バッファ

	float4 g_vecLight;    // 平行光源の方向ベクトル
	float4 g_EyePos;      // 視点座標

	// 色を計算する
	float4 GetColor(VS_OUT In)
	{
		float4 Out;

		float3 lightdir = normalize(-g_vecLight.xyz);
			float3 normal = normalize(In.normal);
			// 拡散反射率を計算する
			float diffuse = GetDiffuseColor(lightdir, normal);

		// 視線ベクトルを計算
		float3 lookat = normalize(g_EyePos.xyz - In.pos);
			// 鏡面反射率を計算する
			float specular = GetSpecularColor(lightdir, normal, lookat);

		// 合成
		Out = float4(GetMaterialColor(In.texel) * diffuse + diffuse * specular, 1);

		return Out;
	}
};

// セルシェーディング
class cCelShading : iBaseLight
{
	// 定数バッファ

	float4 g_vecLight;    // 平行光源の方向ベクトル

	// 色を計算する
	float4 GetColor(VS_OUT In)
	{
		float4 Out;

		float3 lightdir = normalize(-g_vecLight.xyz);
			float3 normal = normalize(In.normal);
			// 拡散反射率を計算する
			float diffuse = GetDiffuseColor(lightdir, normal);

		float celcolor = g_TexMap01.Sample(g_Sampler, diffuse).r;

		// 合成
		Out = float4(GetMaterialColor(In.texel) * celcolor, 1);

		return Out;
	}
};

// ************************************************************
// 定数バッファの宣言
// ************************************************************

// 使用するクラスを選択するための定数バッファ
cbuffer cbBuffer0 : register(b0)
{
	// この並び順はBASE_SHADINGクラス内の定数バッファの並び順と同じくなるようにすること
	cHalfLambert    g_HalfLambert;
	cPhongShading   g_PhongShading;
	cCelShading     g_CelShading;
};

// 頂点シェーダーで使用する定数バッファ
cbuffer cbBuffer1 : register(b1)
{
	// 列優先
	column_major float4x4 g_matWVP : packoffset(c0);   // ワールド × ビュー × 射影 行列
};

// ************************************************************
// シェーダーの実装
// ************************************************************

// 頂点シェーダー
VS_OUT BaseShading_VS_Main(VS_IN In)
{
	VS_OUT Out;
	Out.sv_pos = mul(float4(In.pos, 1.0f), g_matWVP);
	Out.normal = In.normal;
	Out.texel = In.texel;
	Out.pos = In.pos;

	return Out;
}

// ピクセルシェーダ
float4 BaseShading_PS_Main(VS_OUT In) : SV_TARGET
{
	float4 Out;

	Out = g_abstractLight.GetColor(In);

	return Out;
}