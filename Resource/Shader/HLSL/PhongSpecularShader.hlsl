
// ���[���h�s�� �~ �r���[ �~ �ˉe�s��
cbuffer cbMatrixWVP : register(b0)
{
	// ��D��
	column_major  float4x4 g_matW : packoffset(c0);
	column_major  float4x4 g_matV : packoffset(c1);
	column_major  float4x4 g_matP : packoffset(c2);
};

cbuffer cbLightBuffer : register(b1)
{
	float4 g_lghitDirection;
};

cbuffer cbMaterialBuffer : register(b2)
{
	float4 g_diffuse;
	float4 g_specular;
	float4 g_ambient;
	float4 g_emissive;
	float g_power;
	float3 dummy;
};


cbuffer cbCameraBuffer : register(b3)
{
	float4 g_cameraPosition;
};

// ���_�V�F�[�_�[�̓��̓p�����[�^
struct VS0_IN
{
	float3 pos    : POSITION;           // ���_���W
	float2 texel  : TEXCOORD;           // �e�N�Z��	 
	float3 normal : NORMAL
};

// ���_�V�F�[�_�[�̏o�̓p�����[�^
struct VS0_OUT
{
	float4 pos : SV_POSITION;
	float2 texel  : TEXCOORD0;
	float3 normal  : TEXCOORD1;
	float3 color  : COLOER0;
};

// �e�N�X�`���[
Texture2D g_Tex : register(t0);

// �T���v���[�X�e�[�g
SamplerState  g_Sampler : register(s0);

// ���_�V�F�[�_�[
VS0_OUT VS_Main(VS0_IN In)
{
	VS0_OUT Out;

	pos = mul(float4(pos,1.0f) g_matW);
	pos = mul(pos, g_matV);
	Out.pos = mul(pos, g_matP);
	Out.texel = In.texel; 
	
	Out.normal = normalize(mul(In.normal, (float3x3)g_matW));

	return Out;
}

// �s�N�Z���V�F�[�_
float4 PS_Main(VS0_OUT In) : SV_TARGET0
{
	float4 color = g_Tex.Sample(g_Sampler, In.texel);
	float4 L;
	float4 N;

	float4 R;	// ���˃x�N�g�������߂�
	float4 V = g_camerapos - In.pos;
 	R = reflect(-V, N);
 	R = normalize(R);

	L = normalize(-g_LightDirection);
	N = normalize(In.Normal);
	color = suturate( color * suturate(dot(N, L)));

	color = g_diffuse*color + g_specular;

	return color;
}
