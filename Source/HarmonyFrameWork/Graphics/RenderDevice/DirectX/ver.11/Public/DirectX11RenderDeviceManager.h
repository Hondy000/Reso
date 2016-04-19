/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\Renderer\DirectX\ver.11\CDirectX11RenderDeviceManager.h
 *
 * @brief	Declares the direct x coordinate 11 render device manager class.
 **************************************************************************************************/

#pragma once

#include "../../../../../Core/Public/Common.h"
#include "DirectX11Adapter.h"
#include "DirectX11SwapChain.h"
#include "../../../../Buffer/Public/IndexBuffer.h"
#include "../../../../Buffer/Public/ConstantBuffer.h"
#include "../../../../Buffer/Public/VertexBuffer.h"
#include "../../../Basic/Public/BaseRenderDeviceManager.h"	 
#include "../../../../../ResorceManager/Public/DDSTextureLoader.h"
#include "../../../../../Utility/Public/HFString.h"


/**********************************************************************************************//**
 * @class	DeferredBuffers CDirectX11RenderDeviceManager.h
 * 			Source\HarmonyFrame\Graphics\Renderer\DirectX\ver.11\CDirectX11RenderDeviceManager.h
 *
 * @brief	A deferred buffers.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

class GeometryBuffers;

class DirectX11RenderDeviceManager
	:public	BaseRenderDeviceManager
{
public:

	/**********************************************************************************************//**
	 * @fn	CDirectX11RenderDeviceManager::CDirectX11RenderDeviceManager();
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	DirectX11RenderDeviceManager();

	/**********************************************************************************************//**
	 * @fn	CDirectX11RenderDeviceManager::~CDirectX11RenderDeviceManager();
	 *
	 * @brief	Destructor.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	~DirectX11RenderDeviceManager();

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::Setup(void);
	 *
	 * @brief	Gets the setup.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	A BOOL.
	 **************************************************************************************************/

	BOOL Setup(void);

	/**********************************************************************************************//**
	 * @fn	void SetHWnd(HWND wnd)
	 *
	 * @brief	Sets h window.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/07/19
	 *
	 * @param	wnd	Handle of the window.
	 **************************************************************************************************/
	 // デバックウィンドウに出力
	void OutputMsg(TCHAR* pMsg1, TCHAR* pMsg2, TCHAR* pMsg3)
	{
#if defined(DEBUG) || defined(_DEBUG)
		TCHAR s[256];
		_stprintf_s(s, _T("■□■ %s [ %s ] ⇒ %s\n"), pMsg1, pMsg2, pMsg3);
		OutputDebugString(s);
#endif
	///< .
	};

	/**********************************************************************************************//**
	 * @fn	void CDirectX11RenderDeviceManager::SetHWnd(HWND wnd)
	 *
	 * @brief	Sets h window.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param	wnd	Handle of the window.
	 **************************************************************************************************/

	void SetHWnd(HWND wnd)
	{
		m_hWnd = wnd;
	};

	/**********************************************************************************************//**
	 * @fn	std::shared_ptr<CDirectX11Adapter> CDirectX11RenderDeviceManager::GetAdapter(void)
	 *
	 * @brief	Gets the adapter.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The adapter.
	 **************************************************************************************************/

	std::shared_ptr<DirectX11Adapter> GetAdapter(void)
	{
		return m_spAdapter;
	}

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::InitD3D11(DXGI_MODE_DESC* pDisplayMode, BOOL Windowed, BOOL DirectX11Only, BOOL MultisampleEnabled, BOOL UseDepthBuffer);
	 *
	 * @brief	Initialises the d 018`11.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pDisplayMode	If non-null, the display mode.
	 * @param	Windowed				true if windowed.
	 * @param	DirectX11Only			true to direct x coordinate 11 only.
	 * @param	MultisampleEnabled  	true to enable, false to disable the multisample.
	 * @param	UseDepthBuffer			true to use depth buffer.
	 *
	 * @return	A hResult.
	 **************************************************************************************************/

	BOOL InitD3D11(DXGI_MODE_DESC* pDisplayMode,
		BOOL Windowed, BOOL DirectX11Only, BOOL MultisampleEnabled, BOOL UseDepthBuffer);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::GetDisplayMode();
	 *
	 * @brief	デフォルトディスプレイのモードを列挙する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The display mode.
	 **************************************************************************************************/

	BOOL GetDisplayMode();

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateDevice(BOOL DirectX11Only);
	 *
	 * @brief	Creates a device.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param	DirectX11Only	true to direct x coordinate 11 only.
	 *
	 * @return	The new device.
	 **************************************************************************************************/

	BOOL CreateDevice(BOOL DirectX11Only);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateRenderTargetView();
	 *
	 * @brief	Creates render target view.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The new render target view.
	 **************************************************************************************************/

	BOOL CreateRenderTargetView();

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateDepthStencilView(void);
	 *
	 * @brief	Creates depth stencil view.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The new depth stencil view.
	 **************************************************************************************************/

	BOOL CreateDepthStencilView(void);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateViewport();
	 *
	 * @brief	Creates the viewport.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The new viewport.
	 **************************************************************************************************/

	BOOL CreateViewport();

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::SetWindowAssociation();
	 *
	 * @brief	Sets window association.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	A hResult.
	 **************************************************************************************************/

	BOOL SetWindowAssociation();

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::SetDefaultRasterize();
	 *
	 * @brief	Sets default rasterize.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	A hResult.
	 **************************************************************************************************/

	BOOL SetDefaultRasterize();

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::SetDefaultDepthStencilState();
	 *
	 * @brief	Sets default depth stencil state.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	A hResult.
	 **************************************************************************************************/

	BOOL SetDefaultDepthStencilState();

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::ChangeWindowModeOptimization(UINT Width, UINT Height);
	 *
	 * @brief	Change window mode optimization.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param	Width 	The width.
	 * @param	Height	The height.
	 *
	 * @return	A hResult.
	 **************************************************************************************************/

	BOOL ChangeWindowModeOptimization(UINT Width, UINT Height);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::ChangeWindowMode();
	 *
	 * @brief	Change window mode.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	A hResult.
	 **************************************************************************************************/

	BOOL ChangeWindowMode();

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer>& pBuffer, void* pData, size_t size, UINT CPUAccessFlag, D3D11_BIND_FLAG BindFlag);
	 *
	 * @brief	Creates a buffer.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pBuffer	The buffer.
	 * @param [in,out]	pData  	If non-null, the data.
	 * @param	size		   	The size.
	 * @param	CPUAccessFlag  	The CPU access flag.
	 * @param	BindFlag	   	The bind flag.
	 *
	 * @return	The new buffer.
	 **************************************************************************************************/

	BOOL CreateBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer>& pBuffer, void* pData, size_t size, UINT CPUAccessFlag, D3D11_BIND_FLAG BindFlag);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateVertexBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer>& pBuffer, void* pData, size_t size, UINT CPUAccessFlag);
	 *
	 * @brief	Creates vertex buffer.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pBuffer	The buffer.
	 * @param [in,out]	pData  	If non-null, the data.
	 * @param	size		   	The size.
	 * @param	CPUAccessFlag  	The CPU access flag.
	 *
	 * @return	The new vertex buffer.
	 **************************************************************************************************/

	BOOL CreateVertexBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer>& pBuffer, void* pData, size_t size, UINT CPUAccessFlag);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateIndexBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer>& pBuffer, void* pData, size_t size, UINT CPUAccessFlag);
	 *
	 * @brief	Creates index buffer.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pBuffer	The buffer.
	 * @param [in,out]	pData  	If non-null, the data.
	 * @param	size		   	The size.
	 * @param	CPUAccessFlag  	The CPU access flag.
	 *
	 * @return	The new index buffer.
	 **************************************************************************************************/

	BOOL CreateIndexBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer>& pBuffer, void* pData, size_t size, UINT CPUAccessFlag);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateConstantBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer>& pBuffer, void* pData, size_t size, UINT CPUAccessFlag);
	 *
	 * @brief	Creates constant buffer.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pBuffer	The buffer.
	 * @param [in,out]	pData  	If non-null, the data.
	 * @param	size		   	The size.
	 * @param	CPUAccessFlag  	The CPU access flag.
	 *
	 * @return	The new constant buffer.
	 **************************************************************************************************/

	BOOL CreateConstantBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer>& pBuffer, void* pData, size_t size, UINT CPUAccessFlag);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateShaderResourceViewArray( TCHAR* pTextureFileNames[], UINT NumTextures, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& pSRVView );
	 *
	 * @brief	Creates shader resource view array.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pTextureFileNames	If non-null, list of names of the texture files.
	 * @param	NumTextures				 	Number of textures.
	 * @param [in,out]	pSRVView		 	The server view.
	 *
	 * @return	The new shader resource view array.
	 **************************************************************************************************/

	BOOL CreateShaderResourceViewArray(
		const std::string pTextureFileNames[],
		UINT NumTextures,
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& pSRVView
		);


	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateVertexShaderFromFile( OUT Microsoft::WRL::ComPtr< ID3D11VertexShader>& pVertexShader, IN TCHAR pSrcFile[], IN CHAR pFunctionName[], IN CHAR pProfile[], OUT Microsoft::WRL::ComPtr< ID3D11InputLayout>& g_pLayout, IN D3D11_INPUT_ELEMENT_DESC pLayoutDesc[], UINT NumElements);
	 *
	 * @brief	Creates vertex shader from file.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pVertexShader	The vertex shader.
	 * @param	pSrcFile			 	Source file.
	 * @param	pFunctionName		 	Name of the function.
	 * @param	pProfile			 	The profile.
	 * @param [in,out]	g_pLayout	 	The layout.
	 * @param	pLayoutDesc			 	Information describing the layout.
	 * @param	NumElements			 	Number of elements.
	 *
	 * @return	The new vertex shader from file.
	 **************************************************************************************************/

	BOOL CreateVertexShaderFromFile(
		OUT Microsoft::WRL::ComPtr< ID3D11VertexShader>& pVertexShader,
		IN HFString pSrcFile, IN HFString pFunctionName, IN HFString pProfile,
		OUT Microsoft::WRL::ComPtr< ID3D11InputLayout>& g_pLayout,
		IN D3D11_INPUT_ELEMENT_DESC pLayoutDesc[], UINT NumElements);



	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateVertexShaderFromMemory(Microsoft::WRL::ComPtr< ID3D11VertexShader>& pVertexShader, const BYTE* pShader, size_t size, OUT Microsoft::WRL::ComPtr< ID3D11InputLayout>& g_pLayout, IN D3D11_INPUT_ELEMENT_DESC pLayoutDesc[], UINT NumElements);
	 *
	 * @brief	Creates vertex shader from memory.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pVertexShader	The vertex shader.
	 * @param	pShader				 	The shader.
	 * @param	size				 	The size.
	 * @param [in,out]	g_pLayout	 	The layout.
	 * @param	pLayoutDesc			 	Information describing the layout.
	 * @param	NumElements			 	Number of elements.
	 *
	 * @return	The new vertex shader from memory.
	 **************************************************************************************************/

	BOOL CreateVertexShaderFromMemory(Microsoft::WRL::ComPtr< ID3D11VertexShader>& pVertexShader,
		const BYTE* pShader, size_t size,
		OUT Microsoft::WRL::ComPtr< ID3D11InputLayout>& g_pLayout,
		IN D3D11_INPUT_ELEMENT_DESC pLayoutDesc[], UINT NumElements);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateHullShaderFromFile(ID3D11HullShader** pHullShader, TCHAR pSrcFile[], CHAR pFunctionName[], CHAR pProfile[]);
	 *
	 * @brief	ハルシェーダーをファイルから作成する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pHullShader	If non-null, the hull shader.
	 * @param	pSrcFile		   	Source file.
	 * @param	pFunctionName	   	Name of the function.
	 * @param	pProfile		   	The profile.
	 *
	 * @return	The new hull shader from file.
	 **************************************************************************************************/

	BOOL CreateHullShaderFromFile(ID3D11HullShader** pHullShader,
		HFString pSrcFile,
		HFString pFunctionName,
		HFString pProfile);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateHullShaderFromMemory(ID3D11HullShader** pHullShader, const BYTE* pShader, size_t size);
	 *
	 * @brief	ハルシェーダーをメモリから作成する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pHullShader	If non-null, the hull shader.
	 * @param	pShader			   	The shader.
	 * @param	size			   	The size.
	 *
	 * @return	The new hull shader from memory.
	 **************************************************************************************************/

	BOOL CreateHullShaderFromMemory(ID3D11HullShader** pHullShader, const BYTE* pShader, size_t size);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateDomainShaderFromFile(ID3D11DomainShader** pDomainShader, TCHAR pSrcFile[], CHAR pFunctionName[], CHAR pProfile[]);
	 *
	 * @brief	ドメインシェーダーをファイルから作成する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pDomainShader	If non-null, the domain shader.
	 * @param	pSrcFile			 	Source file.
	 * @param	pFunctionName		 	Name of the function.
	 * @param	pProfile			 	The profile.
	 *
	 * @return	The new domain shader from file.
	 **************************************************************************************************/

	BOOL CreateDomainShaderFromFile(ID3D11DomainShader** pDomainShader,
		HFString pSrcFile,
		HFString pFunctionName,
		HFString pProfile);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateDomainShaderFromMemory(ID3D11DomainShader** pDomainShader, const BYTE* pShader, size_t size);
	 *
	 * @brief	ドメインシェーダーをメモリから作成する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pDomainShader	If non-null, the domain shader.
	 * @param	pShader				 	The shader.
	 * @param	size				 	The size.
	 *
	 * @return	The new domain shader from memory.
	 **************************************************************************************************/

	BOOL CreateDomainShaderFromMemory(ID3D11DomainShader** pDomainShader, const BYTE* pShader, size_t size);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateGeometryShaderFromFile(ID3D11GeometryShader** pGeometryShader, TCHAR pSrcFile[], CHAR pFunctionName[], CHAR pProfile[]);
	 *
	 * @brief	ジオメトリシェーダーをファイルから作成する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pGeometryShader	If non-null, the geometry shader.
	 * @param	pSrcFile			   	Source file.
	 * @param	pFunctionName		   	Name of the function.
	 * @param	pProfile			   	The profile.
	 *
	 * @return	The new geometry shader from file.
	 **************************************************************************************************/

	BOOL CreateGeometryShaderFromFile(ID3D11GeometryShader** pGeometryShader,
		HFString pSrcFile,
		HFString pFunctionName,
		HFString pProfile);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateGeometryShaderFromMemory(ID3D11GeometryShader** pGeometryShader, const BYTE* pShader, size_t size);
	 *
	 * @brief	ジオメトリシェーダーをメモリから作成する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pGeometryShader	If non-null, the geometry shader.
	 * @param	pShader				   	The shader.
	 * @param	size				   	The size.
	 *
	 * @return	The new geometry shader from memory.
	 **************************************************************************************************/

	BOOL CreateGeometryShaderFromMemory(ID3D11GeometryShader** pGeometryShader, const BYTE* pShader, size_t size);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateGeometryShaderWithStreamOutputFromFile( ID3D11GeometryShader** pGeometryShader, TCHAR pSrcFile[], CHAR pFunctionName[], CHAR pProfile[], const D3D11_SO_DECLARATION_ENTRY *pSODeclaration, UINT NumEntries, const UINT *pBufferStrides, UINT NumStrides);
	 *
	 * @brief	ストリーミング出力バッファーへの書き込みが可能なジオメトリ シェーダーをファイルから作成する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pGeometryShader	If non-null, the geometry shader.
	 * @param	pSrcFile			   	Source file.
	 * @param	pFunctionName		   	Name of the function.
	 * @param	pProfile			   	The profile.
	 * @param	pSODeclaration		   	The so declaration.
	 * @param	NumEntries			   	Number of entries.
	 * @param	pBufferStrides		   	The buffer strides.
	 * @param	NumStrides			   	Number of strides.
	 *
	 * @return	The new geometry shader with stream output from file.
	 **************************************************************************************************/

	BOOL CreateGeometryShaderWithStreamOutputFromFile(
		ID3D11GeometryShader** pGeometryShader,
		HFString pSrcFile, HFString pFunctionName, HFString pProfile,
		const D3D11_SO_DECLARATION_ENTRY *pSODeclaration,
		UINT NumEntries,
		const UINT *pBufferStrides,
		UINT NumStrides);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateGeometryShaderWithStreamOutputFromMemory( ID3D11GeometryShader** pGeometryShader, const BYTE* pShader, size_t size, const D3D11_SO_DECLARATION_ENTRY *pSODeclaration, UINT NumEntries, const UINT *pBufferStrides, UINT NumStrides);
	 *
	 * @brief	ストリーミング出力バッファーへの書き込みが可能なジオメトリ シェーダーをメモリから作成する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pGeometryShader	If non-null, the geometry shader.
	 * @param	pShader				   	The shader.
	 * @param	size				   	The size.
	 * @param	pSODeclaration		   	The so declaration.
	 * @param	NumEntries			   	Number of entries.
	 * @param	pBufferStrides		   	The buffer strides.
	 * @param	NumStrides			   	Number of strides.
	 *
	 * @return	The new geometry shader with stream output from memory.
	 **************************************************************************************************/

	BOOL CreateGeometryShaderWithStreamOutputFromMemory(
		ID3D11GeometryShader** pGeometryShader,
		const BYTE* pShader, size_t size,
		const D3D11_SO_DECLARATION_ENTRY *pSODeclaration,
		UINT NumEntries,
		const UINT *pBufferStrides,
		UINT NumStrides);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreatePixelShaderFromFile( Microsoft::WRL::ComPtr<ID3D11PixelShader>& pPixelShader, TCHAR pSrcFile[], CHAR pFunctionName[], CHAR pProfile[] );
	 *
	 * @brief	ピクセルシェーダーをファイルから作成する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pPixelShader	The pixel shader.
	 * @param	pSrcFile				Source file.
	 * @param	pFunctionName			Name of the function.
	 * @param	pProfile				The profile.
	 *
	 * @return	The new pixel shader from file.
	 **************************************************************************************************/

	BOOL CreatePixelShaderFromFile(
		Microsoft::WRL::ComPtr<ID3D11PixelShader>& pPixelShader,
		Microsoft::WRL::ComPtr< ID3D11ClassLinkage>& cpPSClassLinkage
		,
		HFString pSrcFile,
		HFString pFunctionName,
		HFString pProfile ,BOOL
		);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::SetupDeferredBuffer();
	 *
	 * @brief	Sets up the deferred buffer.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	A BOOL.
	 **************************************************************************************************/

	BOOL SetupGeometryBuffer();

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreatePixelShaderFromMemory( Microsoft::WRL::ComPtr<ID3D11PixelShader>& pPixelShader, const BYTE* pShader, size_t size );
	 *
	 * @brief	ピクセルシェーダーをヘッダファイルから作成する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	pPixelShader	The pixel shader.
	 * @param	pShader					The shader.
	 * @param	size					The size.
	 *
	 * @return	The new pixel shader from memory.
	 **************************************************************************************************/

	BOOL CreatePixelShaderFromMemory(
		Microsoft::WRL::ComPtr<ID3D11PixelShader>& pPixelShader,
		const BYTE* pShader,
		size_t size
		);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateScreenShot();
	 *
	 * @brief	スクリーンショット作成.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The new screen shot.
	 **************************************************************************************************/

	BOOL CreateScreenShot();

	/**********************************************************************************************//**
	 * @fn	D3D11_RENDER_TARGET_BLEND_DESC CDirectX11RenderDeviceManager::GetDefaultBlendDesc();
	 *
	 * @brief	ブレンド ステートを無効にするための設定を取得する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The default blend description.
	 **************************************************************************************************/

	D3D11_RENDER_TARGET_BLEND_DESC GetDefaultBlendDesc();

	/**********************************************************************************************//**
	 * @fn	D3D11_RENDER_TARGET_BLEND_DESC CDirectX11RenderDeviceManager::GetAlignmentBlendDesc();
	 *
	 * @brief	線形合成用ブレンド ステートのためのを設定を取得する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The alignment blend description.
	 **************************************************************************************************/

	D3D11_RENDER_TARGET_BLEND_DESC GetAlignmentBlendDesc();

	/**********************************************************************************************//**
	 * @fn	D3D11_RENDER_TARGET_BLEND_DESC CDirectX11RenderDeviceManager::GetAddBlendDesc();
	 *
	 * @brief	加算合成用ブレンド ステートのためのを設定を取得する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The add blend description.
	 **************************************************************************************************/

	D3D11_RENDER_TARGET_BLEND_DESC GetAddBlendDesc();

	/**********************************************************************************************//**
	 * @fn	D3D11_RENDER_TARGET_BLEND_DESC CDirectX11RenderDeviceManager::GetSubtractBlendDesc();
	 *
	 * @brief	減算合成用ブレンド ステートのためのを設定を取得する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The subtract blend description.
	 **************************************************************************************************/

	D3D11_RENDER_TARGET_BLEND_DESC GetSubtractBlendDesc();

	/**********************************************************************************************//**
	 * @fn	D3D11_RENDER_TARGET_BLEND_DESC CDirectX11RenderDeviceManager::GetMultipleBlendDesc();
	 *
	 * @brief	積算合成用ブレンド ステートのためのを設定を取得する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The multiple blend description.
	 **************************************************************************************************/

	D3D11_RENDER_TARGET_BLEND_DESC GetMultipleBlendDesc();

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::SetBlendState(D3D11_RENDER_TARGET_BLEND_DESC BlendStateArray[], UINT NumBlendState, BOOL AlphaToCoverageEnable);
	 *
	 * @brief	ブレンドステートを設定する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param	BlendStateArray		 	Array of blend states.
	 * @param	NumBlendState		 	Number of blend states.
	 * @param	AlphaToCoverageEnable	true if alpha to coverage enable.
	 *
	 * @return	A hResult.
	 **************************************************************************************************/

	BOOL SetBlendState(D3D11_RENDER_TARGET_BLEND_DESC BlendStateArray[], UINT NumBlendState, BOOL AlphaToCoverageEnable);

	// フォント用ブレンドステート
	D3D11_RENDER_TARGET_BLEND_DESC GetFontBlendState();

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateSamplerState(Microsoft::WRL::ComPtr< ID3D11SamplerState> cpSamplerState, D3D11_FILTER Filter, UINT MaxAnisotropy);
	 *
	 * @brief	サンプラーステートを作成する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param	cpSamplerState	State of the cp sampler.
	 * @param	Filter		  	Specifies the filter.
	 * @param	MaxAnisotropy 	The maximum anisotropy.
	 *
	 * @return	The new sampler state.
	 **************************************************************************************************/

	BOOL DirectX11RenderDeviceManager::CreateSamplerState(Microsoft::WRL::ComPtr< ID3D11SamplerState>& cpSamplerState, D3D11_FILTER Filter, UINT MaxAnisotropy);
	// 深度ステンシルステートの中で設定変更頻度が高そうなパラメータを設定する
	BOOL SetDepthStencilState(BOOL DepthEnable, D3D11_DEPTH_WRITE_MASK DepthWriteEnabled);

	/**********************************************************************************************//**
	 * @fn	ID3D11ShaderResourceView* CDirectX11RenderDeviceManager::GetSRViewFromDepthStencil();
	 *
	 * @brief	深度ステンシルビューのシェーダーリソースビューを取得.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	null if it fails, else the sr view from depth stencil.
	 **************************************************************************************************/

	Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> GetSRViewFromDepthStencil();

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateRenderTargetView(Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& ppRTView, D3DXVECTOR2* pRTViewSize, DXGI_FORMAT Format);
	 *
	 * @brief	シェーダーにバインド可能なレンダーターゲットビューを作成する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	ppRTView   	The right view.
	 * @param [in,out]	pRTViewSize	If non-null, size of the right view.
	 * @param	Format			   	Describes the format to use.
	 *
	 * @return	The new render target view.
	 **************************************************************************************************/

	BOOL CreateRenderTargetView(Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& ppRTView, HFVECTOR2* pRTViewSize, DXGI_FORMAT Format);

	/**********************************************************************************************//**
	 * @fn	BOOL CDirectX11RenderDeviceManager::CreateRenderTargetView( Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& ppRTView, HFVECTOR2* pRTViewSize, DXGI_FORMAT Format, UINT MipLevels );
	 *
	 * @brief	シェーダーにバインド可能なレンダーターゲットビューを作成する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	ppRTView   	The right view.
	 * @param [in,out]	pRTViewSize	If non-null, size of the right view.
	 * @param	Format			   	Describes the format to use.
	 * @param	MipLevels		   	The mip levels.
	 *
	 * @return	The new render target view.
	 **************************************************************************************************/

	BOOL CreateRenderTargetView(
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& ppRTView,
		HFVECTOR2* pRTViewSize,
		DXGI_FORMAT Format,
		UINT MipLevels
		);

	/**********************************************************************************************//**
	 * @fn	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> CDirectX11RenderDeviceManager::GetSRViewFromRTView(Microsoft::WRL::ComPtr< ID3D11RenderTargetView> pRTView);
	 *
	 * @brief	レンダーターゲットビューからシェーダーリソースビューを取得する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param	pRTView	The right view.
	 *
	 * @return	The sr view from right view.
	 **************************************************************************************************/

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSRViewFromRTView(Microsoft::WRL::ComPtr< ID3D11RenderTargetView> pRTView);

	/**********************************************************************************************//**
	 * @fn	void CDirectX11RenderDeviceManager::SetBackBufferRenderTarget();
	 *
	 * @brief	Sets back buffer render target.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	void SetBackBufferRenderTarget();

	/**********************************************************************************************//**
	 * @fn	void CDirectX11RenderDeviceManager::SetDefaultRasterizerState();
	 *
	 * @brief	Sets default rasterizer state.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	void SetDefaultRasterizerState();

	void SetFrontCullingState();
	void SetBackCullingState();
	void SetNoneCullingState();

	/**********************************************************************************************//**
	 * @fn	void CDirectX11RenderDeviceManager::SetSolidRasterize();
	 *
	 * @brief	Sets solid rasterize.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	void SetSolidRasterize();

	/**********************************************************************************************//**
	 * @fn	void CDirectX11RenderDeviceManager::SetWireframeRasterize();
	 *
	 * @brief	Sets wireframe rasterize.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	void SetWireframeRasterize();

	/**********************************************************************************************//**
	 * @fn	void CDirectX11RenderDeviceManager::ResetViewport();
	 *
	 * @brief	Resets the viewport.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	void ResetViewport();

	/**********************************************************************************************//**
	 * @fn	void CDirectX11RenderDeviceManager::TurnZBufferOn();
	 *
	 * @brief	Turn z coordinate buffer on.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	void TurnZBufferOn();

	/**********************************************************************************************//**
	 * @fn	void CDirectX11RenderDeviceManager::TurnZBufferOff();
	 *
	 * @brief	Turn z coordinate buffer off.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	void TurnZBufferOff();

	/**********************************************************************************************//**
	 * @fn	void CDirectX11RenderDeviceManager::ZBufferNotWriteNotEnable();
	 *
	 * @brief	Buffer not write not enable.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	void ZBufferNotWriteNotEnable();

	/**********************************************************************************************//**
	 * @fn	Microsoft::WRL::ComPtr< ID3D11Device > CDirectX11RenderDeviceManager::GetDevice(void) const
	 *
	 * @brief	Access the D3DDevice.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The device.
	 **************************************************************************************************/

	Microsoft::WRL::ComPtr< ID3D11Device > GetDevice(void) const
	{
		return(m_cpD3DDevice);
	};

	/**********************************************************************************************//**
	 * @fn	void CDirectX11RenderDeviceManager::Clear(void);
	 *
	 * @brief	Clears this object to its blank/initial state.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	void ClearScreen(void);

	/**********************************************************************************************//**
	 * @fn	void CDirectX11RenderDeviceManager::BeginRender(void);
	 *
	 * @brief	Begins a render.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	void BeginRender(void);

	/**********************************************************************************************//**
	 * @fn	void CDirectX11RenderDeviceManager::EndRender(void);
	 *
	 * @brief	Ends a render.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	void EndRender(void);

	/**********************************************************************************************//**
	 * @fn	Microsoft::WRL::ComPtr< ID3D11DeviceContext> CDirectX11RenderDeviceManager::GetD3DDeviceContext(void) const
	 *
	 * @brief	Access the D3DDeviceContext.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The d 3D device context.
	 **************************************************************************************************/

	Microsoft::WRL::ComPtr< ID3D11DeviceContext> GetImmediateContext(void) const
	{
		return(m_cpImmediateContext);
	};

	/**********************************************************************************************//**
	 * @fn	virtual HFVECTOR2 CDirectX11RenderDeviceManager::GetScreenSize()
	 *
	 * @brief	Gets screen size.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The screen size.
	 **************************************************************************************************/

	virtual HFVECTOR2 GetScreenSize()
	{
		return HFVECTOR2(m_screenSize.x, m_screenSize.y);
	}

	/**********************************************************************************************//**
	 * @fn	std::shared_ptr<DeferredBuffers>GetDeferredBuffer();
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @tparam	DeferredBuffers	Type of the deferred buffers.
	 **************************************************************************************************/

	std::shared_ptr<GeometryBuffers>GetGeometryBuffer();

	/**********************************************************************************************//**
	 * @fn	const Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& CDirectX11RenderDeviceManager::GetCpDepthStencilView(void) const
	 *
	 * @brief	Access the CpDepthStencilView.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The cp depth stencil view.
	 **************************************************************************************************/

	void SetVertexBuffer(UINT startSlot,UINT bufferNum,std::vector<std::shared_ptr<VertexBuffer>>&vertexArray, const UINT* pStride,const UINT* pOffset);
	void SetIndexBuffer(std::shared_ptr<IndexBuffer>&indexBuffer,const UINT offset);
	void SetConstantBuffers(DWORD  shaderFlag,UINT startSlot, UINT bufferNum, std::vector<std::shared_ptr<ConstantBuffer>>& bufferArray);
	const Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& GetCpDepthStencilView(void) const
	{
		return(m_cpDepthStencilView);
	};

	void DepthStencilOff();

	// Access the SpSwapChain
	const std::shared_ptr<DirectX11SwapChain>& GetSpSwapChain(void) const
	{
		return(m_spSwapChain);
	};
	// Access the CpD3DDebug
	Microsoft::WRL::ComPtr< ID3D11Debug> GetCpD3DDebug(void) 
	{
		return(m_cpD3DDebug);
	};

private:

	/**********************************************************************************************//**
	 * @fn	void CDirectX11RenderDeviceManager::OutputShaderErrorMessage( Microsoft::WRL::ComPtr<ID3D10Blob> errorMessage, TCHAR* shaderFilename);
	 *
	 * @brief	Output shader error message.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param	errorMessage		  	Message describing the error.
	 * @param [in,out]	shaderFilename	If non-null, filename of the shader file.
	 **************************************************************************************************/

	void OutputShaderErrorMessage(
		Microsoft::WRL::ComPtr<ID3D10Blob> errorMessage,
		TCHAR* shaderFilename);

	/** @brief	Handle of the window. */
	HWND m_hWnd;
	/** @brief	Direct3D 初期化後、実際に採用されたフィーチャーレベル。. */
	D3D_FEATURE_LEVEL       m_FeatureLevel;
	/** @brief	Direct3D11 デバイス。. */
	Microsoft::WRL::ComPtr< ID3D11Device >         m_cpD3DDevice; 

	Microsoft::WRL::ComPtr< ID3D11Debug> m_cpD3DDebug;
	/** @brief	Direct3D11 デバイスコンテキスト。. */
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>    m_cpImmediateContext;
	/** @brief	レンダリングターゲットビュー. */
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_cpRenderTargetView;
	/** @brief	The cp depth stencil view. */
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_cpDepthStencilView;
	/** @brief	Information describing the display mode. */
	std::vector<DXGI_MODE_DESC> m_DisplayModeDesc;

	/** @brief	アダプター. */
	std::shared_ptr<DirectX11Adapter> m_spAdapter;
	/** @brief	スワップチェーン. */
	std::shared_ptr<DirectX11SwapChain> m_spSwapChain;

	/** @brief	true to use depth buffer. */
	BOOL m_UseDepthBuffer;
	/** @brief	D3D11_VIEWPORT. */
	D3D11_VIEWPORT m_viewport[1];
	/** @brief	State of the raster. */
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterState;
	/** @brief	State of the depth stencil. */
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	/** @brief	State of the depth disabled stencil. */
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthDisabledStencilState;
	/** @brief	深度バッファにに書き込ませない. */
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_notWriteDepthStencilState;
	/** @brief	State of the alpha enable bdlending. */
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_alphaEnableBdlendingState;
	/** @brief	State of the alpha disable blending. */
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_alphaDisableBlendingState;
	/** @brief	State of the font blending. */
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_fontBlendingState;

	/** @brief	The display mode. */
	DXGI_MODE_DESC m_displayMode;
	/** @brief	Information describing the raster state. */
	D3D11_RASTERIZER_DESC m_rasterStateDesc;
	//FLOAT near,far;
	std::shared_ptr<GeometryBuffers> m_spDeferredBuffer;
};
