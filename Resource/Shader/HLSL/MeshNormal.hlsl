// ���[���h�s�� �~ �r���[ �~ �ˉe�s��
cbuffer cbMatrixWVP : register(b0)
{
	// ��D��
	column_major  float4x4 g_matWVP : packoffset(c0);
};

// ���_�V�F�[�_�[�̓��̓p�����[�^
struct VS0_IN
{
	float3 pos    : POSITION;           // ���_���W
};

// ���_�V�F�[�_�[�̏o�̓p�����[�^
struct VS0_OUT
{
	float4 sv_pos : SV_POSITION;
};

// ���_�V�F�[�_�[
VS0_OUT VS_Main(VS0_IN In)
{
	VS0_OUT Out;
	Out.sv_pos = mul(float4(In.pos, 1.0f), g_matWVP);
	return Out;
}

// �s�N�Z���V�F�[�_
float4 PS_Main(VS0_OUT In) : SV_TARGET
{
	float4 Out;

	Out = float4(1,0,0,1);

	return Out;
}

