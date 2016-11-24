#pragma once
#ifdef	DIRECTX11

#endif
#include "../../../../Core/Public/Common.h"
#include "../../../Texture/Public/BaseTexture2D.h"
#include "../../../Buffer/Public/ConstantBuffer.h"
#include "../../../VertexLayout/Public/BaseVertexLayout.h"

class SubMesh;
class Material;
class BaseGraphicsCommand;
class BaseRenderMeshObject;

/**********************************************************************************************//**
 * @class	CBaseShader CBaseShader.h Source\HarmonyFrame\Graphics\Shader\Basic\CBaseShader.h
 *
 * @brief	全てのシェーダの基底.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/03
 **************************************************************************************************/

class BaseGraphicsShader
	:
	public IBaseObject
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

	BaseGraphicsShader();

	/**********************************************************************************************//**
	 * @fn	virtual CBaseShader::~CBaseShader();
	 *
	 * @brief	Destructor.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 **************************************************************************************************/

	virtual ~BaseGraphicsShader();
	virtual void OutputShaderErrorMessage(
		Microsoft::WRL::ComPtr<ID3D10Blob> errorMessage,
		TCHAR* shaderFilename);



	/**********************************************************************************************//**
	 * @fn	virtual bool CBaseShader::Init() = 0;
	 *
	 * @brief	初期化.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 *
	 * @return	A bool.
	 **************************************************************************************************/

	virtual bool Setup() = 0;
	virtual void Destroy() = 0;

	/***********************************************************************************************
	 * シェーダを実行するグラフィックスコマンドを生成し登録.
	 *
	 * @author Kazuyuki
	 *
	 * @param parameter1 The first parameter.
	 *
	 * @return true if it succeeds, false if it fails.
	 *************************************************************************************************/

	virtual void CreateAndRegisterGraphicsCommand(std::shared_ptr<BaseRenderMeshObject> renderObject,UINT element) = 0;

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

	virtual bool PreProcessOfRender(std::shared_ptr<SubMesh> subMesh,  std::shared_ptr<Material>materials) = 0;




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
	const DWORD& GetPathPriority(void) const
	{
		return(m_graphicsPriority);
	};
	void SetPathPriority(const DWORD& pathPriority)
	{
		m_graphicsPriority = pathPriority;
	};

protected:
	/** @brief	固定buffer数. */
	int m_constatBufferCount;
	std::vector<std::shared_ptr<ConstantBuffer>> m_constantBuffers;	// シェーダで必要な情報
	std::shared_ptr<BaseVertexLayout> m_spVertexLayout;		// シェーダごとに必要な頂点情報
	int m_indexCount;

	DWORD m_graphicsPriority;	// DeferredRendering後のパスか？

#ifdef DIRECTX11
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_cpPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_cpVertexShader;
	Microsoft::WRL::ComPtr<ID3D11HullShader> m_cpHullShader;
	Microsoft::WRL::ComPtr<ID3D11DomainShader> m_cpDomainShader;
	Microsoft::WRL::ComPtr<ID3D11ComputeShader> m_cpComputeShader;
	std::vector<Microsoft::WRL::ComPtr<ID3D11GeometryShader>> m_cpGeometryShaders;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_cpSamplerState;
	std::vector< Microsoft::WRL::ComPtr<ID3D11SamplerState>> m_cpSamplerStateArray;
	// 動的シェーダーリンク
	// ID3D11ClassLinkage
	Microsoft::WRL::ComPtr< ID3D11ClassLinkage> m_cpPSClassLinkage;

	// ピクセルシェーダーに設定時に使用するクラスインスタンス
	// ID3D11ClassInstance
	Microsoft::WRL::ComPtr< ID3D11ClassInstance> m_cpClassInstance;

#endif
};
