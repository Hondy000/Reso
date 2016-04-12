
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
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

	return output;
}


Texture2D shaderTexture : register(t0);
SamplerState SampleTypeWrap : register(s0);




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


output.color = shaderTexture.Sample(SampleTypeWrap, input.tex);


output.position = float4(input.worldPosition);

output.normal = float4(input.normal, 1.0f);

output.ambient = ambient;

output.emissive = emissive;

output.specular = specular;


return output;
}
