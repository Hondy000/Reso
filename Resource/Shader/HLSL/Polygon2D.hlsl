// ���[���h�s�� �~ �r���[ �~ �ˉe�s��

cbuffer MatrixBuffer : register(b0)
{
	column_major float4x4 wvp;
};



// ���_�V�F�[�_�[�̓��̓p�����[�^
struct VS_IN
{
   float3 pos   : POSITION;   // ���_���W  
   float2 tex   : TEXCOORD0;   // ���_���W
};

// ���_�V�F�[�_�[�̏o�̓p�����[�^
struct VS_OUT
{
   float4 pos    : SV_POSITION;
   float2 tex	: TEXCOORD0;
};

// ���_�V�F�[�_�[			
VS_OUT VS_Main( VS_IN In )
{
	VS_OUT Out;
	Out.pos = mul( float4( In.pos, 1 ), wvp);
	Out.tex = In.tex;
	return Out;
}
						  
// �e�N�X�`���[
Texture2D g_Tex : register(t0);

// �T���v���[�X�e�[�g
SamplerState  g_Sampler : register(s0);
										   
// �s�N�Z���V�F�[�_
float4 PS_Main( VS_OUT In ) : SV_TARGET
{
	float4 color = g_Tex.Sample(g_Sampler, In.tex);
	return color;
}