// ************************************************************
// ���o�̓p�����[�^�̒�`
// ************************************************************

// ���_�V�F�[�_�[�̓��̓p�����[�^
struct VS_IN
{
	float3 pos    : POSITION;           // ���_���W
	float2 texel  : TEXCOORD;           // �e�N�Z��
	column_major float4x4 mat : MATRIX; // �C���X�^���X���Ƃɐݒ肳���s��
	float4 color  : COLOR;              // ���_�J���[
};

// ���_�V�F�[�_�[�̏o�̓p�����[�^
struct VS_OUT
{
	float4 sv_pos : SV_POSITION;
	float4 color  : COLOR0;
	float2 texel  : TEXCOORD0;
};

// ************************************************************
// �e�N�X�`���[�̐錾
// ************************************************************

Texture2D g_DecalMap : register(t0);  // �f�J�[���}�b�v

// �T���v���[�X�e�[�g
SamplerState  g_Sampler : register(s0);

// ************************************************************
// �萔�o�b�t�@�̐錾
// ************************************************************

// �萔�o�b�t�@�O
cbuffer cbBuffer0 : register(b0)
{
	float4 g_vecLight : packoffset(c0);      // ���s�����̕����x�N�g��
};

// ************************************************************
// �V�F�[�_�[�̎���
// ************************************************************

// ���_�V�F�[�_�[
VS_OUT VS_Main(VS_IN In)
{
	VS_OUT Out;
	Out.sv_pos = mul(float4(In.pos, 1.0f), In.mat);
	Out.texel = In.texel;
	Out.color = In.color;
	return Out;
}

// �s�N�Z���V�F�[�_
float4 PS_Main(VS_OUT In) : SV_TARGET
{
	return g_Tex.Sample(g_Sampler, In.texel);
}