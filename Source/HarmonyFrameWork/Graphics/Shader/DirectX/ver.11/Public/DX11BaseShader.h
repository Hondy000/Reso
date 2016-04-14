#pragma once
#include "../../../Basic/Public/BaseShader.h"
struct MeshData;

class DX11BaseShader
	:
	public BaseShader
{
public:

	DX11BaseShader()
	{
	};

	virtual ~DX11BaseShader()
	{
	};

	// ������
	virtual BOOL Init(const BYTE* pVS,
		size_t VSSize
		, const BYTE* pPS, size_t PSSize
		);
	virtual BOOL Init(TCHAR pSrcFile[], TCHAR pVSMain[], TCHAR pPSMain[]);
	virtual BOOL Init() = 0;

	virtual BOOL SetupBuffer(std::shared_ptr<BaseBuffer> spOutVertexBuffer, std::shared_ptr<BaseBuffer> spOutIndexBuffer, std::shared_ptr<MeshData> spInMeshData);

	// ���_�V�F�[�_�[�p�̒萔�o�b�t�@��ݒ肷��
	virtual BOOL SetCBVertexShader(Microsoft::WRL::ComPtr< ID3D11DeviceContext>  pD3DDeviceContext
		, HFMATRIX* p_matWVP
		);
	// �n�[�t�����o�[�g�p�̒萔�o�b�t�@��ݒ�
	BOOL SetCBHalfLambert(Microsoft::WRL::ComPtr< ID3D11DeviceContext>  pD3DDeviceContext
		, HFVECTOR4* p_vecLight
		, Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> pDecalMap
		);
	// �t�H���V�F�[�f�B���O�p�̒萔�o�b�t�@��ݒ�
	BOOL SetCBPhongShading(Microsoft::WRL::ComPtr< ID3D11DeviceContext>  pD3DDeviceContext
		, HFVECTOR4* p_vecLight
		, HFVECTOR4* p_EyePos
		, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pDecalMap
		);
	// �Z���V�F�[�f�B���O�p�̒萔�o�b�t�@��ݒ�
	BOOL SetCBCelShading(Microsoft::WRL::ComPtr< ID3D11DeviceContext> cpD3DDeviceContext
		, HFVECTOR4* p_vecLight
		, Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> cpDecalMap
		, Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> cpCelMap
		);
	// �`��J�n����
	virtual BOOL Render();
	// �`��I������
	virtual BOOL End();

protected:
	// ���I�V�F�[�_�[�����P�[�W( �T���v���ł̓s�N�Z���V�F�[�_�[�̂� )�p�̒萔�o�b�t�@��`
	// ���̕��я��̓V�F�[�_�[�\�[�X���Ő錾���Ă���萔�o�b�t�@�̕��я��Ɠ������Ȃ�悤�ɂ��邱��
	typedef struct _CBUFFER0
	{
		// �n�[�t�����o�[�g�p
		HFVECTOR4 vecLight0;

		// �t�H���V�F�[�f�B���O�p
		HFVECTOR4 vecLight1;
		HFVECTOR4 EyePos;

		// �Z���V�F�[�f�B���O�p
		HFVECTOR4 vecLight2;
	}CBUFFER0;

	// ���_�V�F�[�_�[�p�̒萔�o�b�t�@��`
	typedef struct _CBUFFER1
	{
		// ���[���h �~ �r���[ �~ �ˉe �s��
		HFMATRIX  matWVP;
	}CBUFFER1;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr< ID3D11InputLayout> m_cpLayout;

	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr< ID3D11Buffer> m_cpConstantBuffers[2];

	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr< ID3D11VertexShader> m_cpVertexShader;

	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr< ID3D11PixelShader> m_cpPixelShader;

	// ���I�V�F�[�_�[�����N
	// ID3D11ClassLinkage
	Microsoft::WRL::ComPtr< ID3D11ClassLinkage> m_cpPSClassLinkage;

	// �s�N�Z���V�F�[�_�[�ɐݒ莞�Ɏg�p����N���X�C���X�^���X
	// ID3D11ClassInstance
	Microsoft::WRL::ComPtr< ID3D11ClassInstance> m_cpClassInstance;
	LPCSTR m_pClassInstanceName;
};
