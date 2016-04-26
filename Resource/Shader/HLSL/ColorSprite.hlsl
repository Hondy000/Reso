// ���[���h�s�� �~ �r���[ �~ �ˉe�s��

cbuffer MatrixBuffer : register(b0)
{
	column_major float4x4 wvp;
};



// ���_�V�F�[�_�[�̓��̓p�����[�^
struct VS_IN
{
	float3 pos   : POSITION;   // ���_���W  
	float4 color   : COLOR0;   // ���_���W
};

// ���_�V�F�[�_�[�̏o�̓p�����[�^
struct VS_OUT
{
	float4 pos    : SV_POSITION;
	float4 color	: COLOR0;
};

// ���_�V�F�[�_�[			
VS_OUT VS_Main(VS_IN In)
{
	VS_OUT Out;
	Out.pos = mul(float4(In.pos, 1), wvp);
	Out.color = In.color;
	return Out;
}

// �s�N�Z���V�F�[�_
float4 PS_Main(VS_OUT In) : SV_TARGET
{
	float4 color = In.color;
	return color;
}