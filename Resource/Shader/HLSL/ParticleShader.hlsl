// ************************************************************
// ���o�̓p�����[�^�̒�`
// ************************************************************

// ���_�V�F�[�_�[�̓��̓p�����[�^
struct VS_IN
{
	float3 pos    : POSITION;           // ���_���W
	float2 texel  : TEXCOORD;           // �e�N�Z��
	column_major float4x4 mat : MATRIX; // �C���X�^���X���Ƃɐݒ肳���s��	 
	float4 col : COLOR0; 
};

// ���_�V�F�[�_�[�̏o�̓p�����[�^
struct VS_OUT
{
	float4 sv_pos : SV_POSITION;
	float2 texel  : TEXCOORD0;	
	float4 col : COLOR0; 
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
	Out.col = In.col;
	return Out;
}

// �s�N�Z���V�F�[�_
float4 PS_Main(VS_OUT In) : SV_TARGET0
{
	float4 Out;
	
	float4 decalmap = g_DecalMap.Sample(g_Sampler, In.texel);
	
	//// �@���x�N�g���� 0 �` 1 �͈͂� -1 �` 1 �ɕϊ�����
	//decalmap.rg = decalmap.rg * 2.0f - 1.0f;
	//decalmap.rb *= -1.0f;
	//
	//// ���C�e�B���O
	//float diffuse = dot(decalmap.rgb, -g_vecLight.xyz);
	//diffuse = diffuse * 0.5f + 0.5f;
	//
	Out = decalmap * In.col;
	return Out;
}