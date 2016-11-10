
// vertex
cbuffer MatrixBuffer : register (b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};


cbuffer LightMatrixBuffer : register (b1)
{
	float4x4 lightMatrix;
}

// pixel
cbuffer MaterialBuffer : register (b0)
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
	float2 texcoord : TEXCOORD0;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 worldPosition : POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD0;
	float4 shadowTexcoord : TEXCOORD1;
};

// vertex shader
PixelInputType DeferredVertexShader(VertexInputType input)
{
	PixelInputType output;


	input.position.w = 1.0f;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.texcoord = input.texcoord;
	output.worldPosition = mul(input.position, worldMatrix);
	output.normal = mul(input.normal, worldMatrix);

	output.normal = normalize(output.normal);

	output.shadowTexcoord = mul(output.position, lightMatrix);

	return output;
}


Texture2D shaderTexture : register(t0);
Texture2D shadowMapTexture : register(t0);
SamplerState SampleTypeWrap : register(s0);
SamplerComparisonState shadowSampler :register(s1);



// pixel shader
struct PixelOutputType
{
	float4 color : SV_Target0;
	float4 position : SV_Target1;
	float4 normal : SV_Target2;
	float4 ambient : SV_Target3;
	float4 emissive : SV_Target4;
	float4 specular : SV_Target5;
};


PixelOutputType DeferredPixelShader(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;

	
	output.color = shaderTexture.Sample(SampleTypeWrap, input.texcoord) * diffuse;
	
	
	output.position = float4(input.worldPosition);
	
	output.normal = float4(input.normal, 1.0f);
	
	output.ambient = ambient;
	
	output.emissive = emissive;
	
	output.specular = specular;
	
	// シャドウマップの深度値と比較する.
	float3 shadowCoord = input.shadowTexcoord.xyz / input.shadowTexcoord.w;

	// 最大深度傾斜を求める.
	float  maxDepthSlope = max(abs(ddx(shadowCoord.z)), abs(ddy(shadowCoord.z)));

	float  shadowThreshold = 1.0f;      // シャドウにするかどうかの閾値です.
	float  bias = 0.000001f;     // 固定バイアスです.
	float  slopeScaledBias = 0.000001f;     // 深度傾斜.
	float  depthBiasClamp = 0.000001f;      // バイアスクランプ値.

	float  shadowBias = bias + slopeScaledBias * maxDepthSlope;
	shadowBias = min(shadowBias, depthBiasClamp);

	float3 shadowColor = float3(0.25f, 0.25f, 0.25f);
	shadowThreshold = shadowMapTexture.SampleCmpLevelZero(shadowSampler, shadowCoord.xy, shadowCoord.z - shadowBias);
	shadowColor = lerp(shadowColor, float3(1.0f, 1.0f, 1.0f), shadowThreshold);
	
	return output;
}
