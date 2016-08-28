
// �萔�o�b�t�@
cbuffer CBuffer : register(b0)
{
	column_major float4x4 g_matLightWorldViewProj    : packoffset(c0);  // ���C�g�r���[�̐��ˉe�s��
};

// ���_�V�F�[�_�[�̓��̓p�����[�^
struct VS_IN
{
	float3 pos    : POSITION;    // ���_���W
};

// ���_�V�F�[�_�[�̏o�̓p�����[�^
struct VS_OUT_PS_IN
{
	float4 pos      : SV_POSITION;
};

// ���_�V�F�[�_�[
VS_OUT_PS_IN VS_Main(VS_IN In)
{
	VS_OUT_PS_IN Out;
	Out.pos = mul(float4(In.pos, 1.0f), g_matLightWorldViewProj);
	return Out;
}