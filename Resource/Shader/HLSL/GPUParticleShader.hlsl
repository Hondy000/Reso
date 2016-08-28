// ���[���h�s�� �~ �r���[ �~ �ˉe�s��
cbuffer cbMatrixWVP : register(b0)
{
	// ��D��
	column_major  float4x4 g_matWVP : packoffset(c0);
	float1 g_Scale     : packoffset(c4.x);   // �p�[�e�B�N���̃X�P�[�����O�l
	float1 g_LimitTime : packoffset(c4.y);   // �^�C�}�[�̍ő�l( ���̒l�𒴂���Ə��������� )
	float1 g_Dummy2    : packoffset(c4.z);
	float1 g_Dummy3    : packoffset(c4.w);
};

// �e�N�X�`���[
Texture2D g_Tex : register(t0);

// �T���v���[�X�e�[�g
SamplerState  g_Sampler : register(s0);

// �W�I���g���V�F�[�_�[�̓��̓p�����[�^
struct VS_IN
{
	float3 pos    : POSITION;  // ���W
	float3 v0     : NORMAL;    // �����x
	float time : TEXCOORD;  // ����
};

typedef VS_IN VS_OUT;

// ���_�V�F�[�_�[�ł͂��̂܂܏o��
VS_OUT VS0_Main(VS_IN In)
{
	return In;
}

typedef VS_OUT GS_IN;
typedef GS_IN GS0_OUT;

[maxvertexcount(6)]   // �W�I���g���V�F�[�_�[�ŏo�͂���ő咸�_��
					  // �W�I���g���V�F�[�_�[
void GS0_Main(point GS_IN In[1],                   // �|�C���g �v���~�e�B�u�̓��͏��
	inout PointStream<GS0_OUT> PStream   // �|�C���g �v���~�e�B�u�̏o�̓X�g���[��
)
{
	GS0_OUT Out;

	// �p�[�e�B�N���̎��Ԃ� g_LimitTime �𒴂����̂ŏ���������
	if (In[0].time > g_LimitTime)
	{
		Out.pos = float3(0, 0, 0);
		Out.v0 = In[0].v0;
		Out.time = 0;
	}
	else
	{
		// X �ʒu = �����x �~ ����
		Out.pos.x = In[0].v0.x * In[0].time;

		// ���R�����^���̌����ɂ��AY ���W���v�Z����B
		// 9.80665f �͏d�͉����x�B
		Out.pos.y = -0.5f * 9.80665f * In[0].time * In[0].time + In[0].v0.y * In[0].time;

		// Z �ʒu = �����x �~ ����
		Out.pos.z = In[0].v0.z * In[0].time;

		Out.v0 = In[0].v0;

		// ���Ԃ�i�߂�
		Out.time = In[0].time + 0.001f;
	}

	PStream.Append(Out);
	PStream.RestartStrip();
}

struct GS1_OUT
{
	float4 pos    : SV_POSITION;  // �p�[�e�B�N���̈ʒu
	float4 color  : COLOR;        // �p�[�e�B�N���̐F
	float2 texel  : TEXCOORD0;    // �e�N�Z��
};

[maxvertexcount(4)]   // �W�I���g���V�F�[�_�[�ŏo�͂���ő咸�_��
					  // �W�I���g���V�F�[�_�[
void GS1_Main(point GS_IN In[1],                       // �|�C���g �v���~�e�B�u�̓��͏��
	inout TriangleStream<GS1_OUT> TriStream  // �g���C�A���O�� �v���~�e�B�u�̏o�̓X�g���[��
)
{
	GS1_OUT Out;

	// ���Ԃ� 0.0f �` g_LimitTime �͈͓̔��ŕω�����
	float c = 1.0f - In[0].time / g_LimitTime;

	// ���_�J���[�́A���Ԃ̌o�߂ɔ������X�ɉ��F����Ԃ��ۂ��������ɂȂ�悤�ɂ��Ă���B
	float4 color = float4(1, c * c, 0, c);

	Out.pos = mul(float4(In[0].pos.x + g_Scale, In[0].pos.y + g_Scale, In[0].pos.z, 1.0f), g_matWVP);
	Out.color = color;
	Out.texel = float2(1, 0);
	TriStream.Append(Out);

	Out.pos = mul(float4(In[0].pos.x - g_Scale, In[0].pos.y + g_Scale, In[0].pos.z, 1.0f), g_matWVP);
	Out.color = color;
	Out.texel = float2(0, 0);
	TriStream.Append(Out);

	Out.pos = mul(float4(In[0].pos.x + g_Scale, In[0].pos.y - g_Scale, In[0].pos.z, 1.0f), g_matWVP);
	Out.color = color;
	Out.texel = float2(1, 1);
	TriStream.Append(Out);

	Out.pos = mul(float4(In[0].pos.x - g_Scale, In[0].pos.y - g_Scale, In[0].pos.z, 1.0f), g_matWVP);
	Out.color = color;
	Out.texel = float2(0, 1);
	TriStream.Append(Out);

	TriStream.RestartStrip();
}

typedef GS1_OUT PS_IN;

// �s�N�Z���V�F�[�_
float4 PS1_Main(PS_IN In) : SV_TARGET
{
	return g_Tex.Sample(g_Sampler, In.texel) * In.color;
}
