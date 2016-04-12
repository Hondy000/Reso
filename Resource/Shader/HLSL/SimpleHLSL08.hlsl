// ���[���h�s�� �~ �r���[ �~ �ˉe�s��
cbuffer cbMatrixWVP : register( b0 )
{
   // ��D��
   column_major  float4x4 g_matWVP : packoffset( c0 );
};

cbuffer cbVecLight : register( b1 )
{
   float4 g_vecLight : packoffset( c0 );
};

// �e�N�X�`���[
Texture2D g_Tex : register( t0 );

// �T���v���[�X�e�[�g
SamplerState  g_Sampler : register( s0 );

// ���_�V�F�[�_�[�̓��̓p�����[�^
struct VS_IN
{
   float3 pos   : POSITION;   // ���_���W
};

// ���_�V�F�[�_�[�̏o�̓p�����[�^
struct VS_OUT
{
   float4 pos    : SV_POSITION;
};

// ���_�V�F�[�_�[
VS_OUT VS_Main( VS_IN In )
{
   VS_OUT Out;

   Out.pos = mul( float4( In.pos, 1 ), g_matWVP );

   return Out;
}

// �s�N�Z���V�F�[�_
float4 PS_Main( VS_OUT In ) : SV_TARGET
{
   return float4(1.0,0,0,1.0);
}