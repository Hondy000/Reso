////////////////////////////////////////////////////////////////////////////////
// Filename: LightShaderOfDeferredRender.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _LightShader_H_
#define _LightShader_H_

#include "../../../Basic/Public/BaseGraphicsShader.h"
#include "../../../../Lighting/Public/LightTypes.h"
#include "../../../../RenderDevice/DirectX/ver.11/Public/GeometryBuffers.h"

class BaseTexture2D;
struct MeshData;

////////////////////////////////////////////////////////////////////////////////
// Class name: LightShaderOfDeferredRender
////////////////////////////////////////////////////////////////////////////////
class LightShaderOfDeferredRender
	:
	public BaseGraphicsShader
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
		HFVECTOR4 lightDirection0;

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


		HFVECTOR4 lightDirection6;
		HFGraphics::POINT_LIGHT_PRAM pointLightArray2[64];
		HFGraphics::SPOT_LIGHT_PRAM spotLightArray2[64];

		HFMATRIX lightMatrix;
	}CBUFFER0;

	typedef struct CBUFFER1
	{
		HFVECTOR4 cameraPosition;
	}CBUFFER1;
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

	void CreateAndRegisterGraphicsCommand(std::shared_ptr<BaseRenderMeshObject> renderObject, UINT element);
private:

	std::shared_ptr<GeometryBuffers> m_spDefferBuffers;
	int indexCount;
};

#endif