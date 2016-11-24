
cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer LightMatrixBuffer	: register(b1)
{
	column_major float4x4 lightMatrix : packoffset(c1);
};


cbuffer MaterialBuffer
{
	float4 ambient;
	float4 diffuse;
	float4 emissive;
	float4 specular;
};
struct VertexInputType
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD0;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 worldPosition : POSITION;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD0;
	float4 shadowTex : 	TEXCOORD1;
};

PixelInputType DeferredVertexShader(VertexInputType input)
{
	PixelInputType output;


	input.position.w = 1.0f;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.tex = input.tex;
	output.worldPosition = mul(input.position, worldMatrix);
	output.normal = mul(input.normal, worldMatrix);

	output.normal = normalize(output.normal);
	output.shadowTex = mul(lightMatrix, output.worldPosition);
	return output;
}


Texture2D shaderTexture : register(t0);
Texture2D shadowMapOfDirectionalLightTexture : register(t1);
SamplerState SampleTypeWrap : register(s0);
SamplerComparisonState ShadowSmp : register(s1);




struct PixelOutputType
{
	float4 color : SV_Target0;
	float4 position : SV_Target1;
	float4 normal : SV_Target2;
	float4 ambient : SV_Target3;
	float4 emissive : SV_Target4;
	float4 specular : SV_Target5;
	float4 shadowMap : SV_Target6;
};


PixelOutputType DeferredPixelShader(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;

	
	output.color = shaderTexture.Sample(SampleTypeWrap, input.tex) * diffuse;
	
	
	output.position = float4(input.worldPosition);
	
	output.normal = float4(input.normal, 1.0f);
	
	output.ambient = ambient;
	
	output.emissive = emissive;
	
	output.specular = specular;


	float4 SdwCoord = input.shadowTex;

	float3 shadowCoord = SdwCoord.xyz / SdwCoord.w;

	// 最大深度傾斜を求める.
	float  maxDepthSlope = max(abs(ddx(shadowCoord.z)), abs(ddy(shadowCoord.z)));

	float  shadowThreshold = 1.0f;      // シャドウにするかどうかの閾値です.
	float  bias = 0.00001f;     // 固定バイアスです.
	float  slopeScaledBias = 0.001f;     // 深度傾斜.
	float  depthBiasClamp = 0.0001f;      // バイアスクランプ値.

	float  shadowBias = bias + slopeScaledBias * maxDepthSlope;
	shadowBias = min(shadowBias, depthBiasClamp);

	float3 shadowColor = float4(0.1f, 0.1f, 0.1f,1.0f);
	shadowThreshold = shadowMapOfDirectionalLightTexture.SampleCmpLevelZero(ShadowSmp, shadowCoord.xy, shadowCoord.z - shadowBias);
	output.shadowMap.xyz = lerp(shadowColor, float3(1.0f, 1.0f, 1.0f), shadowThreshold);

	output.shadowMap.w = 1;

	return output;
}
