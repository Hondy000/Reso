////////////////////////////////////////////////////////////////////////////////
// Filename: LightShaderOfDeferredRender.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _LightShader_H_
#define _LightShader_H_

#include "../../../Basic/Public/BaseShader.h"
#include "../../../../Lighting/Public/LightTypes.h"
#include "../../../../RenderDevice/DirectX/ver.11/Public/GeometryBuffers.h"

class BaseTexture2D;
struct MeshData;

////////////////////////////////////////////////////////////////////////////////
// Class name: LightShaderOfDeferredRender
////////////////////////////////////////////////////////////////////////////////
class LightShaderOfDeferredRender
	:
	public BaseShader
{
public:

private:
	struct MatrixBufferType
	{
		HFMATRIX WVP;
	};

	struct LightBufferType
	{
		HFVECTOR3 lightDirection;
		FLOAT padding;
	};

	// ���I�V�F�[�_�[�����P�[�W( �T���v���ł̓s�N�Z���V�F�[�_�[�̂� )�p�̒萔�o�b�t�@��`
	// ���̕��я��̓V�F�[�_�[�\�[�X���Ő錾���Ă���萔�o�b�t�@�̕��я��Ɠ������Ȃ�悤�ɂ��邱��
	typedef struct CBUFFER0
	{
		// �V���v���p
		HFVECTOR3 lightDirection0;
		FLOAT padding0;	  // 16�o�C�g �A���C�����g�p

		 // �A���x�h
		HFVECTOR4 lightDirection1;
		// position
		HFVECTOR4 lightDirection2;

		// Normal�p
		HFVECTOR4 lightDirection3;

		// �|�C���g���C�e�B���O�e�X�g�p
		HFVECTOR4 lightDirection4;
		HFGraphics::POINT_LIGHT_PRAM pointLight0;

		// �X�|�b�g���C�e�B���O�e�X�g�p
		HFVECTOR4 lightDirection5;
		HFGraphics::SPOT_LIGHT_PRAM spotLight0;

		//
		HFVECTOR4 lightDirection;
		HFGraphics::POINT_LIGHT_PRAM pointLightArray[64];
		HFGraphics::SPOT_LIGHT_PRAM spotLightArray[64];
	}CBUFFER0;

public:
	LightShaderOfDeferredRender();
	LightShaderOfDeferredRender(const LightShaderOfDeferredRender&);
	~LightShaderOfDeferredRender();

	bool Setup();
	void Destroy();

	bool PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials);

	bool Render();

	bool PostProcessOfRender();

	void SetGeometryBuffers(const std::shared_ptr<GeometryBuffers>& buffers)
	{
		m_spDefferBuffers = buffers;
	}
	const std::shared_ptr<GeometryBuffers>& GetGeometryBuffers(void) const
	{
		return m_spDefferBuffers;
	}

private:
	bool InitializeShader(TCHAR*, TCHAR*);

	bool SetShaderParameters(
		HFMATRIX,
		HFMATRIX,
		HFMATRIX,
		HFVECTOR3);

private:

	std::shared_ptr<GeometryBuffers> m_spDefferBuffers;
	int indexCount;
};

#endif