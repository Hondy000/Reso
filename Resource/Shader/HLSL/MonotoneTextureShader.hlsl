
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
	float2 texel  : TEXCOORD;           // �e�N�Z��
};

// ���_�V�F�[�_�[�̏o�̓p�����[�^
struct VS0_OUT
{
	float4 pos : SV_POSITION;
	float2 texel  : TEXCOORD0;
};

// �e�N�X�`���[
Texture2D g_Tex : register(t0);

// �T���v���[�X�e�[�g
SamplerState  g_Sampler : register(s0);
// ���_�V�F�[�_�[
VS0_OUT VS_Main(VS0_IN In)
{
	VS0_OUT Out;
	Out.pos = mul(float4(In.pos, 1), g_matWVP);
	Out.texel = In.texel;
	return Out;
}

// �s�N�Z���V�F�[�_
float4 PS_Main(VS0_OUT In) : SV_TARGET0
{
	float4 Col = g_Tex.Sample(g_Sampler, In.texel);
	float4 m_Color = float4(0.9f, 0.7f, 0.4f, 1.0f);
	//RGB �R�F�̕��ϒl���擾���A���m�g�[���ɕϊ�����
	float C = (Col.r + Col.g + Col.b) * 0.3333f;

	//�ŏI�I�ȃJ���[���v�Z����						 
	Col = C;

	return Col;
}

