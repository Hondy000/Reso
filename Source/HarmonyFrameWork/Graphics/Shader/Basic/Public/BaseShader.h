#pragma once
#ifdef	DIRECTX11

#endif
#include "../../../../Core/Public/Common.h"
#include "../../../Texture/Public/BaseTexture2D.h"
#include "../../../Buffer/Public/ConstantBuffer.h"
#include "../../../VertexLayout/Public/BaseVertexLayout.h"
#include "../../../RenderObject/Public/SubMesh.h"


/**********************************************************************************************//**
 * @class	CBaseShader CBaseShader.h Source\HarmonyFrame\Graphics\Shader\Basic\CBaseShader.h
 *
 * @brief	�S�ẴV�F�[�_�̊��.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/03
 **************************************************************************************************/

class BaseShader
{
public:

	/**********************************************************************************************//**
	 * @fn	CBaseShader::CBaseShader();
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 **************************************************************************************************/

	BaseShader();

	/**********************************************************************************************//**
	 * @fn	virtual CBaseShader::~CBaseShader();
	 *
	 * @brief	Destructor.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 **************************************************************************************************/

	virtual ~BaseShader();
	virtual void OutputShaderErrorMessage(
		Microsoft::WRL::ComPtr<ID3D10Blob> errorMessage,
		TCHAR* shaderFilename);



	/**********************************************************************************************//**
	 * @fn	virtual bool CBaseShader::Init() = 0;
	 *
	 * @brief	������.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 *
	 * @return	A bool.
	 **************************************************************************************************/

	virtual bool Setup() = 0;
	virtual void Destroy() = 0;

	/**********************************************************************************************//**
	 * @fn	virtual bool CBaseShader::PreRenderProcess() = 0;
	 *
	 * @brief	Pre render process.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 *
	 * @return	A bool.
	 **************************************************************************************************/

	virtual bool PreProcessOfRender(std::shared_ptr<SubMesh> shape,std::shared_ptr<Material>materials) = 0;




	/**********************************************************************************************//**
	 * @fn	virtual bool CBaseShader::Render() = 0;
	 *
	 * @brief	Renders this object.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 *
	 * @return	A bool.
	 **************************************************************************************************/

	virtual bool Render() = 0;

	/**********************************************************************************************//**
	 * @fn	virtual bool CBaseShader::PostRenderProcess() = 0;
	 *
	 * @brief	Posts the render process.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/04
	 *
	 * @return	A bool.
	 **************************************************************************************************/

	virtual bool PostProcessOfRender() = 0;

	// Access the PathPriority
	const DWORD& GetPathPriority(void) const		{ return(m_pathPriority);			};
	void SetPathPriority(const DWORD& pathPriority)	{ m_pathPriority = pathPriority;	};

protected:
	/** @brief	�Œ�buffer��. */
	int m_constatBufferCount;
	std::vector<std::shared_ptr<ConstantBuffer>> m_constantBuffers;	// �V�F�[�_�ŕK�v�ȏ��
	std::shared_ptr<BaseVertexLayout> m_spVertexLayout;		// �V�F�[�_���ƂɕK�v�Ȓ��_���
	int m_indexCount;

	DWORD m_pathPriority;	// DeferredRendering��̃p�X���H

#ifdef DIRECTX11
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_cpPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_cpVertexShader;
	Microsoft::WRL::ComPtr<ID3D11HullShader> m_cpHullShader;
	Microsoft::WRL::ComPtr<ID3D11DomainShader> m_cpDomainShader;
	Microsoft::WRL::ComPtr<ID3D11ComputeShader> m_cpComputeShader;
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_cpGeometryShader;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_cpSamplerState;
	// ���I�V�F�[�_�[�����N
	// ID3D11ClassLinkage
	Microsoft::WRL::ComPtr< ID3D11ClassLinkage> m_cpPSClassLinkage;

	// �s�N�Z���V�F�[�_�[�ɐݒ莞�Ɏg�p����N���X�C���X�^���X
	// ID3D11ClassInstance
	Microsoft::WRL::ComPtr< ID3D11ClassInstance> m_cpClassInstance;

#endif
};
