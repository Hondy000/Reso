
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
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
	output.normal = mul(input.normal, (float3x3)worldMatrix);

	output.normal = normalize(float3(0,0,0));

	return output;
}

Texture2D shaderTexture : register(t0);

SamplerState SampleTypeWrap : register(s0);




struct PixelOutputType
{
	float4 color : SV_Target0;
	float4 position : SV_Target1;
	float4 normal : SV_Target2;
};


PixelOutputType DeferredPixelShader(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;


output.color = shaderTexture.Sample(SampleTypeWrap, input.tex);


output.position = float4(input.worldPosition);

output.normal = float4(input.normal, 1.0f);

return output;
}
