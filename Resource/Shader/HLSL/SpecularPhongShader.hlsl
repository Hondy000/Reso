
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
	float power;
	float range;
	float2 dummy;
};

cbuffer CBuffer
{
	float4 g_cameraPosition;
	float4 g_LightDirection;
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
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 worldPosition : POSITION;
};


PixelInputType VS_Main(VertexInputType input)
{
	PixelInputType output;


	input.position.w = 1.0f;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.tex = input.tex;
	output.worldPosition = mul(input.position, worldMatrix);
	output.normal = mul(input.normal, (float3x3)worldMatrix);

	output.normal = normalize(output.normal);



	return output;
}

Texture2D shaderTexture : register(t0);

SamplerState SampleTypeWrap : register(s0);






float4 PS_Main(PixelInputType input) : SV_TARGET0
{

	float3 N = normalize(input.normal.xyz);
	//���C�g�����œ��͂����̂ŁA���_ -> ���C�g�ʒu�Ƃ��邽�߂ɋt�����ɕϊ�����B�Ȃ��A�v���P�[�V�����ŕK�����K�����邱��
	float3 L = normalize(-float3(g_LightDirection.xyz));
	float3 V = normalize(input.worldPosition.xyz - g_cameraPosition.xyz);
	float3 R;



	//���C�g�x�N�g���Ɩ@���x�N�g���̓��ς��v�Z���A�v�Z���ʂ̐F�̍Œ�l������( m_Ambient )�ɐ�������
	//float4 diffuseColor = min( max( ambient, dot( N, L ) ) + emissive, 1.0f );
	float4 diffuseColor = ambient + diffuse * max(0.0,dot(L,N));


	//���_ -> ���C�g�ʒu�x�N�g�� + ���_ -> ���_�x�N�g��(���ӂP)
	float3 H = normalize(L + (V));
	R = reflect(V, N);
	R = normalize(R);


	//�X�y�L�����[�J���[���v�Z����(���ӂQ)
	float4 S = pow(max(0.0f, dot(L,R)), power)*range * specular;
	S = saturate(S);
	//�X�y�L�����[�J���[�����Z����
	float4 Out = diffuseColor * shaderTexture.Sample(SampleTypeWrap, input.tex) + S;

	return Out;
}



