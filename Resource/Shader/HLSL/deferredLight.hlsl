
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

cbuffer cbBuffer2 : register(b2)
{
	float4 g_cameraPosition;
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

		colors = colorTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0, 0);

		normals = normalTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);

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
		colors = colorTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);
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
		normals = normalTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);
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

		colors = colorTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);

		positions = positionTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);

		normals = normalTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);
		lightDir = -lightDirection.xyz;

		lightIntensity = saturate(dot(normals.xyz, lightDir));

		outputColor = saturate(colors * lightIntensity) ;


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
		colors = colorTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);

		positions = positionTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);

		normals = normalTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);
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
		colors = colorTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);

		// 位置を取得
		positions = positionTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);

		// 法線を取得
		normals = normalTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);

		ambient = ambientTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);

		emissive = emissiveTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);

		specular = specularTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);


		lightDir = -lightDirection.xyz;

		lightIntensity = saturate(dot(normals.xyz, lightDir));

		outputColor = saturate(colors * lightIntensity) ;
		// *float4(1.0f, 1.0f, 1.0f, 1.0f);

		for (int i = 0; i < 64; i++)
		{
			lightDir = pointLight[i].position.xyz - positions.xyz;
			float len = (length(lightDir));
			float LD = -(normalize(lightDir));
			float at = pow(max((1.0f / len) * pointLight[i].attenuation, 0), pointLight[i].falloff);
			outputColor.xyz += colors.xyz * max(pointLight[i].color.xyz * at * step(len, pointLight[i].range) * dot(LD, normals), 0);

		}

		for (int i = 0; i < 64; i++)
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

class cSpecular : iBaseLight
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
		colors = colorTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);

		// 位置を取得
		positions = positionTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);

		// 法線を取得
		normals = normalTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);

		ambient = ambientTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);

		emissive = emissiveTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);

		specular = specularTexture.Load(uint2(input.tex.x*pixsize.x, input.tex.y*pixsize.y), 0);


		lightDir =normalize(-lightDirection.xyz);

		lightIntensity = saturate(dot(normals.xyz, lightDir));

		outputColor = saturate(colors * lightIntensity);

		float3 N = normalize(normals.xyz);
		//ライト方向で入力されるので、頂点 -> ライト位置とするために逆向きに変換する。なおアプリケーションで必ず正規化すること
		float3 V = normalize(positions.xyz - g_cameraPosition.xyz);
		float3 R;



		//ライトベクトルと法線ベクトルの内積を計算し、計算結果の色の最低値を環境光( m_Ambient )に制限する
		//float4 diffuseColor =  ambient * max(0.0, dot(lightDir, normals));
		//float4 diffuseColor = min(max(ambient, dot(N, lightDir)) + emissive, 1.0f);	 	
	//	float4 diffuseColor = min(max(0, dot(N, lightDir)), 1.0f) + ambient;
		float4 diffuseColor = ambient + 1 * max(0.0, dot(lightDir, N));
		//float4 diffuseColor = max(0, dot(N, lightDir)) + ambient;

		// *float4(1.0f, 1.0f, 1.0f, 1.0f);
		//頂点 -> ライト位置ベクトル + 頂点 -> 視点ベクトル(注意１)
		float3 H = normalize(lightDir + (V));
		R = reflect(V, N);
		R = normalize(R);


		//スペキュラーカラーを計算する(注意２)
		float4 S = pow(max(0.0f, dot(lightDir, R)), 50)*3 * specular;
		S = saturate(S);
		//スペキュラーカラーを加算する
		outputColor = diffuseColor * colors + S;

		// pointLight
		for (int i = 0; i < 64; i++)
		{
			// 光源と対象の差分を算出
			lightDir = pointLight[i].position.xyz - positions.xyz;
			// 光源との距離を算出
			float len = (length(lightDir));
			// 光源方向を算出
			// 減衰を算出
			float at = pow(max((1.0f / len) * pointLight[i].attenuation, 0), pointLight[i].falloff);

			//float4 diffuseColor = max(0, dot(N, lightDir)) + ambient;

			//頂点 -> ライト位置ベクトル + 頂点 -> 視点ベクトル(注意１)	  
			lightDir = normalize(lightDir.xyz);
		

			R = reflect(V, N);
			S = pow(max(0.0f, dot(lightDir, R)), 50) * 3 * specular;
			S = saturate(S);
			//	outputColor.xyz += colors.xyz * max(pointLight[i].color.xyz * at * step(len, pointLight[i].range) *  saturate(dot(LD, normals)), 0)+S * step(len, pointLight[i].range);
			outputColor.xyz += colors.xyz * max(((pointLight[i].color.xyz *  at * step(len, pointLight[i].range)) ) * dot(lightDir, normals), 0) + at * (S * step(len, pointLight[i].range));

		}


		// spotLight
		for (int i = 0; i < 64; i++)
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
	cSpecular		g_Phong;
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
