// ************************************************************
// ParticlesIntoBuffer �t�F�[�Y
// ************************************************************

// ���_�V�F�[�_�[�̓��̓p�����[�^
struct VS0_IN
{
	float3 pos    : POSITION;           // ���_���W
	float2 texel  : TEXCOORD;           // �e�N�Z��
	column_major float4x4 mat : MATRIX; // �C���X�^���X���Ƃɐݒ肳���s��
	float4 color  : COLOR;              // ���_�J���[( �g�p����̂̓A���t�@�l�̂� )
};

// ���_�V�F�[�_�[�̏o�̓p�����[�^
struct VS0_OUT
{
	float4 sv_pos : SV_POSITION;
	float4 color  : COLOR0;
	float2 texel  : TEXCOORD0;
};

Texture2D g_DecalMap : register(t0);  // �f�J�[���}�b�v

// �T���v���[�X�e�[�g
SamplerState  g_Sampler0 : register(s0);

// ���_�V�F�[�_�[
VS0_OUT ParticlesIntoBuffer_VS_Main(VS0_IN In)
{
	VS0_OUT Out;
	Out.sv_pos = mul(float4(In.pos, 1.0f), In.mat);
	Out.texel = In.texel;
	Out.color = In.color;
	return Out;
}

// �s�N�Z���V�F�[�_
float4 ParticlesIntoBuffer_PS_Main(VS0_OUT In) : SV_TARGET0
{
	float4 Out;

	float4 decalmap = g_DecalMap.Sample(g_Sampler0, In.texel);

		float alpha = In.color.a * decalmap.a;

	// �@���x�N�g���� 0 �` 1 �͈͂� -1 �` 1 �ɕϊ�����
	decalmap.rg = decalmap.rg * 2.0f - 1.0f;
	decalmap.r *= -1.0f;
	// �@���x�N�g������сA�A���t�@�l���o��
	Out = float4(decalmap.rg, 0, alpha);

	return Out;
}

// ************************************************************
// CompositeParticles �t�F�[�Y
// ************************************************************

// ���_�V�F�[�_�[�̓��̓p�����[�^
struct VS1_IN
{
	float3 pos    : POSITION;           // ���_���W
	float2 texel  : TEXCOORD;           // �e�N�Z��
};

// ���_�V�F�[�_�[�̏o�̓p�����[�^
struct VS1_OUT
{
	float4 sv_pos : SV_POSITION;
	float2 texel  : TEXCOORD0;
};

Texture2D g_NormalMap : register(t0);  // �@���}�b�v

// �T���v���[�X�e�[�g
SamplerState  g_Sampler1 : register(s0);

// �萔�o�b�t�@�O
cbuffer cbBuffer0 : register(b0)
{
	float4 g_vecLight    : packoffset(c0);    // ���s�����̕����x�N�g��
	float4 g_Color       : packoffset(c1);    // �p�[�e�B�N���J���[
};

// ���_�V�F�[�_�[
VS1_OUT CompositeParticles_VS_Main(VS1_IN In)
{
	VS1_OUT Out;
	Out.sv_pos = float4(In.pos, 1);
	Out.texel = In.texel;
	return Out;
}

// �s�N�Z���V�F�[�_
float4 CompositeParticles_PS_Main(VS1_OUT In) : SV_TARGET0
{
	float4 Out;

	float4 normalmap = g_NormalMap.Sample(g_Sampler1, In.texel);

		float3 normal = float3(0, 0, -1);
		normal.rg += float2(normalmap.x, normalmap.y);
	normal = normalize(normal);

	// ���C�e�B���O
	float diffuse = dot(normal, -g_vecLight.xyz);
	diffuse = diffuse * 0.5f + 0.5f;

	Out = float4(g_Color.rgb * diffuse, normalmap.a);

	return Out;
}