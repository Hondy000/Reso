
// ************************************************************
// インターフェースの定義
// ************************************************************
struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};
interface iBaseLight
{
	float4 GetColor(PixelInputType In);
};


// インターフェースの宣言
iBaseLight g_abstractLight;

struct VertexInputType
{
	float3 position : POSITION;
	float2 tex : TEXCOORD0;
};

// ポイントライト
struct PointLight
{
	float4 position;
	float4 color;
	float range;
	float attenuation;	// 減衰係数
	float falloff;		// 輝度の減少量
	float dummy;  // 16バイトにするためのダミー
};

// スポットライト
struct SpotLight
{
	float4 position;
	float4 color;
	float4 direction;
	float range;
	float attenuation;
	float falloff;
	float phi;
};


/////////////
// GLOBALS //
/////////////

Texture2DMS <float4, 8> colorTexture : register(t0);
Texture2DMS <float4, 8> positionTexture : register(t1);
Texture2DMS <float4, 8> normalTexture : register(t2);
Texture2DMS <float4, 8> ambientTexture : register(t3);
Texture2DMS <float4, 8> emissiveTexture : register(t4);
Texture2DMS <float4, 8> specularTexture : register(t5);



SamplerState SampleTypePoint : register(s0);


class cDeferredLight :iBaseLight
{

	float3 lightDirection;
	float padding;
	// 色を計算する
	float4 GetColor(PixelInputType input)
	{
		float4 colors;
		float4 normals;
		float3 lightDir;
		float lightIntensity;
		float4 outputColor;

		float2	pixsize;
		int sampleCnt;
		colorTexture.GetDimensions(pixsize.x, pixsize.y, sampleCnt);

		colors = colorTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0,0);

		normals = normalTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0);

		lightDir = -lightDirection;

		lightIntensity = saturate(dot(normals.xyz, lightDir));

		outputColor = saturate(colors * lightIntensity);

		return outputColor;
	}
};


class cAlbedoLight :iBaseLight
{
	float4 dummy;
	// 色を計算する
	float4 GetColor(PixelInputType input)
	{
		float4 colors;
		float4 outputColor;
		float2	pixsize;
		int sampleCnt;
		colorTexture.GetDimensions(pixsize.x, pixsize.y, sampleCnt);
		colors = colorTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0);
		outputColor = colors;//saturate(normals * lightIntensity);

		return outputColor;
	}
};

class cPositionLight :iBaseLight
{
	float4 dummy;
	// 色を計算する
	float4 GetColor(PixelInputType input)
	{
		float4 postiions;
		float4 outputColor;
		float2	pixsize;
		int sampleCnt;
		positionTexture.GetDimensions(pixsize.x, pixsize.y, sampleCnt);

		postiions = positionTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);
		outputColor = postiions;

		return outputColor;
	}
};


class cNormalLight :iBaseLight
{
	float4 dummy;
	// 色を計算する
	float4 GetColor(PixelInputType input)
	{
		float4 normals;
		float4 outputColor;
		float2	pixsize;
		int sampleCnt;
		normalTexture.GetDimensions(pixsize.x, pixsize.y, sampleCnt);
		normals = normalTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0);
		outputColor = normals;//saturate(normals * lightIntensity);

		return outputColor;
	}
};


class cPointLight :iBaseLight
{
	// 平行光源
	float4 lightDirection;
	// ポイントライト
	PointLight light;

	// 色を計算する
	float4 GetColor(PixelInputType input)
	{
		float4 colors;
		float4 positions;
		float4 normals;
		float3 lightDir;
		float lightIntensity;
		float4 outputColor;

		float2	pixsize;
		int sampleCnt;
		colorTexture.GetDimensions(pixsize.x, pixsize.y, sampleCnt);

		colors = colorTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0);

		positions = positionTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0);

		normals = normalTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0);
		lightDir = -lightDirection.xyz;

		lightIntensity = saturate(dot(normals.xyz, lightDir));

		outputColor = saturate(colors * lightIntensity) * 0.5;


		lightDir = light.position.xyz - positions.xyz;
		float len = length(lightDir);
		float LD = normalize(lightDir);
		float at = pow(max((1.0f / len) * light.attenuation, 0), light.falloff);
		outputColor.xyz += colors.xyz * max(light.color.xyz * at * step(len, light.range) * dot(LD, normals), 0);


		return outputColor;
	}
};


class cSpotLight : iBaseLight
{
	// 平行光源
	float4 lightDirection;
	// スポットライト
	SpotLight light;

	// 色を計算する
	float4 GetColor(PixelInputType input)
	{
		float4 colors;
		float4 positions;
		float4 normals;
		float3 lightDir;
		float lightIntensity;
		float4 outputColor;


		float2	pixsize;
		int sampleCnt;
		colorTexture.GetDimensions(pixsize.x, pixsize.y, sampleCnt);
		colors = colorTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0);

		positions = positionTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0);

		normals = normalTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0);
		lightDir = -lightDirection.xyz;

		lightIntensity = saturate(dot(normals.xyz, lightDir));

		outputColor = saturate(colors * lightIntensity);


		lightDir = light.position.xyz - positions.xyz;
		float len = length(lightDir);
		float LD = normalize(light.direction.xyz);
		float dif = (1.0f / len) * light.attenuation;
		float d2 = -dot(LD, normalize(lightDir));
		float a = 1.0f - sin(light.phi);
		float at = (1 - pow(max(a / 2, 0), light.falloff)) * step(d2, a);
		outputColor.xyz += colors.xyz * max(light.color.xyz * at  *dif * step(len, light.range) * dot(normalize(lightDir), normals), 0);


		return outputColor;
	}
};


class cAllLight : iBaseLight
{
	// 平行光源
	float4 lightDirection;
	// ポイントライト
	PointLight pointLight[64];
	// スポットライト
	SpotLight spotLight[64];

	// 色を計算する
	float4 GetColor(PixelInputType input)
	{
		float4 colors;
		float4 positions;
		float4 normals;
		float4 ambient;
		float4 emissive;
		float4 specular;

		float3 lightDir;
		float lightIntensity;
		float4 outputColor;


		float2	pixsize;
		int sampleCnt;
		colorTexture.GetDimensions(pixsize.x, pixsize.y, sampleCnt);
		// アルベドを取得
		colors = colorTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0);

		// 位置を取得
		positions = positionTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0);

		// 法線を取得
		normals = normalTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0);
		
		ambient = ambientTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0);

		emissive = emissiveTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0);
		
		specular = specularTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y),0);

		
		lightDir = -lightDirection.xyz;

		lightIntensity = saturate(dot(normals.xyz, lightDir));

		outputColor = saturate(colors * lightIntensity) * 0.1;
		// *float4(1.0f, 1.0f, 1.0f, 1.0f);

		for (int i = 0; i < 6; i++)
		{
			lightDir = pointLight[i].position.xyz - positions.xyz;
			float len = length(lightDir);
			float LD = normalize(lightDir);
			float at = pow(max((1.0f / len) * pointLight[i].attenuation, 0), pointLight[i].falloff);
			outputColor.xyz += colors.xyz * max(pointLight[i].color.xyz * at * step(len, pointLight[i].range) * dot(LD, normals), 0);

		}
		
		for (int i = 0; i < 6; i++)
		{
			lightDir = spotLight[i].position.xyz - positions.xyz;
			float len = length(lightDir);
			float LD = normalize(spotLight[i].direction.xyz);
			float dif = (1.0f / len) * spotLight[i].attenuation;
			float d2 = -dot(LD, normalize(lightDir));
			float a = 1.0f - sin(spotLight[i].phi);
			float at = (1 - pow(max(a / 2, 0), spotLight[i].falloff)) * step(d2, a);
			outputColor.xyz += colors.xyz * max(spotLight[i].color.xyz * at  *dif * step(len, spotLight[i].range) * dot(normalize(lightDir), normals), 0);
		}
		return outputColor;
	}
};



// ************************************************************
// 定数バッファの宣言
// ************************************************************



// 頂点シェーダーで使用する定数バッファ
cbuffer cbBuffer1 : register(b0)
{
	// 列優先
	column_major float4x4 g_matWVP : packoffset(c0);   // ワールド × ビュー × 射影 行列
};

// 使用するクラスを選択するための定数バッファ
cbuffer cbBuffer0 : register(b1)
{
	// この並び順はクラス内の定数バッファの並び順と同じくなるようにすること
	cDeferredLight   g_SimpleDeferred;
	cAlbedoLight	g_AlbedoDeferred;
	cPositionLight    g_PositionDeferred;
	cNormalLight    g_NormalDeferred;
	cPointLight		g_PointDeferred;
	cSpotLight		g_SpotDeferred;
	cAllLight		g_AllDeferred;
};

PixelInputType LightVertexShader(VertexInputType input)
{
	PixelInputType output;

	output.position = mul(float4(input.position, 1.0f), g_matWVP);

	output.tex = input.tex;

	return output;
}


float4 LightPixelShader(PixelInputType input) : SV_TARGET
{
	float4 outputColor;

outputColor = g_abstractLight.GetColor(input);
return outputColor;
}
