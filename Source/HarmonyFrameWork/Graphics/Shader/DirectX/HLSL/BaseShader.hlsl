
// ************************************************************
// ���o�̓p�����[�^�̒�`
// ************************************************************

// ���_�V�F�[�_�[�̓��̓p�����[�^
struct VS_IN
{
	float3 pos    : POSITION;   // ���_���W
	float3 normal : NORMAL;     // �@��
	float2 texel  : TEXCOORD;   // �e�N�Z��
};

// ���_�V�F�[�_�[�̏o�̓p�����[�^
struct VS_OUT
{
	float4 sv_pos : SV_POSITION;
	float3 normal : NORMAL;
	float2 texel  : TEXCOORD0;
	float3 pos    : TEXCOORD1;
};

// ************************************************************
// �C���^�[�t�F�[�X�̒�`
// ************************************************************

interface iBaseLight
{
	float4 GetColor(VS_OUT In);
};

// �C���^�[�t�F�[�X�̐錾
iBaseLight g_abstractLight;

// ************************************************************
// �e�N�X�`���[�̐錾
// ************************************************************

Texture2D g_DecalMap : register(t0);  // �f�J�[���}�b�v
Texture2D g_TexMap01 : register(t1);  // �ėp�ړI�Ŏg�p����e�N�X�`���[

// �T���v���[�X�e�[�g
SamplerState  g_Sampler : register(s0);

// ************************************************************
// ���ʊ֐�
// ************************************************************

// Diffuse
float GetDiffuseColor(float3 lightdir, float3 normal)
{
	float Out;

	// �n�[�t�����o�[�g�ɂĊg�U���˗����v�Z����
	Out = dot(lightdir, normal);
	Out = Out * 0.5f + 0.5f;
	Out *= Out;

	return Out;
};

// Specular
float GetSpecularColor(float3 lightdir, float3 normal, float3 lookat)
{
	float Out = 0;

	// �n�[�t�x�N�g�����v�Z����
	float3 half = normalize(lightdir + lookat);

	// ���ʔ��˗����v�Z����
	Out = pow(max(0.0f, dot(normal, half)), 50.0f);

	return Out;
};

// Material
float3 GetMaterialColor(float2 texel)
{
	float3 Out;

	Out = g_DecalMap.Sample(g_Sampler, texel).rgb;

	return Out;
}

// ************************************************************
// �N���X�̎���
// ************************************************************

// �n�[�t�����o�[�g
class cHalfLambert : iBaseLight
{
	// �萔�o�b�t�@

	float4 g_vecLight;    // ���s�����̕����x�N�g��

	// �F���v�Z����
	float4 GetColor(VS_OUT In)
	{
		float4 Out;

		float3 lightdir = normalize(-g_vecLight.xyz);
			float3 normal = normalize(In.normal);
			// �g�U���˗����v�Z����
			float diffuse = GetDiffuseColor(lightdir, normal);

		// ����
		Out = float4(GetMaterialColor(In.texel) * diffuse, 1);

		return Out;
	}
};

// �t�H���V�F�[�f�B���O
class cPhongShading : iBaseLight
{
	// �萔�o�b�t�@

	float4 g_vecLight;    // ���s�����̕����x�N�g��
	float4 g_EyePos;      // ���_���W

	// �F���v�Z����
	float4 GetColor(VS_OUT In)
	{
		float4 Out;

		float3 lightdir = normalize(-g_vecLight.xyz);
			float3 normal = normalize(In.normal);
			// �g�U���˗����v�Z����
			float diffuse = GetDiffuseColor(lightdir, normal);

		// �����x�N�g�����v�Z
		float3 lookat = normalize(g_EyePos.xyz - In.pos);
			// ���ʔ��˗����v�Z����
			float specular = GetSpecularColor(lightdir, normal, lookat);

		// ����
		Out = float4(GetMaterialColor(In.texel) * diffuse + diffuse * specular, 1);

		return Out;
	}
};

// �Z���V�F�[�f�B���O
class cCelShading : iBaseLight
{
	// �萔�o�b�t�@

	float4 g_vecLight;    // ���s�����̕����x�N�g��

	// �F���v�Z����
	float4 GetColor(VS_OUT In)
	{
		float4 Out;

		float3 lightdir = normalize(-g_vecLight.xyz);
			float3 normal = normalize(In.normal);
			// �g�U���˗����v�Z����
			float diffuse = GetDiffuseColor(lightdir, normal);

		float celcolor = g_TexMap01.Sample(g_Sampler, diffuse).r;

		// ����
		Out = float4(GetMaterialColor(In.texel) * celcolor, 1);

		return Out;
	}
};

// ************************************************************
// �萔�o�b�t�@�̐錾
// ************************************************************

// �g�p����N���X��I�����邽�߂̒萔�o�b�t�@
cbuffer cbBuffer0 : register(b0)
{
	// ���̕��я���BASE_SHADING�N���X���̒萔�o�b�t�@�̕��я��Ɠ������Ȃ�悤�ɂ��邱��
	cHalfLambert    g_HalfLambert;
	cPhongShading   g_PhongShading;
	cCelShading     g_CelShading;
};

// ���_�V�F�[�_�[�Ŏg�p����萔�o�b�t�@
cbuffer cbBuffer1 : register(b1)
{
	// ��D��
	column_major float4x4 g_matWVP : packoffset(c0);   // ���[���h �~ �r���[ �~ �ˉe �s��
};

// ************************************************************
// �V�F�[�_�[�̎���
// ************************************************************

// ���_�V�F�[�_�[
VS_OUT BaseShading_VS_Main(VS_IN In)
{
	VS_OUT Out;
	Out.sv_pos = mul(float4(In.pos, 1.0f), g_matWVP);
	Out.normal = In.normal;
	Out.texel = In.texel;
	Out.pos = In.pos;

	return Out;
}

// �s�N�Z���V�F�[�_
float4 BaseShading_PS_Main(VS_OUT In) : SV_TARGET
{
	float4 Out;

	Out = g_abstractLight.GetColor(In);

	return Out;
}