/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\Shader\DirectX\ver.11\CDirectX11BaseShader.cpp
 *
 * @brief	Implements the direct x coordinate 11 base shader class.
 **************************************************************************************************/

#include "../Public/DX11BaseShader.h"
#include "../../../../RenderDevice/Basic/Public/RendererManager.h"
#include "..\..\..\..\Public\BaseGraphicsCommand.h"
#include "..\..\..\..\..\Core\Task\Public\TaskSystem.h"

/**********************************************************************************************//**
  * @fn	bool CDirectX11BaseShader::Init( const BYTE* pVS, size_t VSSize, const BYTE* pPS, size_t PSSize )
  *
  * @brief	初期化.
  *
  * @author	Kazuyuki Honda
  * @date	2015/11/04
  *
  * @param	pVS   	The vs.
  * @param	VSSize	Size of the vs.
  * @param	pPS   	The ps.
  * @param	PSSize	Size of the ps.
  *
  * @return	A hResult.
  **************************************************************************************************/

bool DX11BaseShader::Init(
	const BYTE* pVS,
	size_t VSSize,
	const BYTE* pPS,
	size_t PSSize
	)
{
	HRESULT hr = E_FAIL;


	// ピクセルシェーダー用の動的シェーダー リンクを有効にするクラス リンク ライブラリを作成する
	sRENDER_DEVICE->CreateClassLinkage(m_cpPSClassLinkage.GetAddressOf());

	hr = sRENDER_DEVICE->CreatePixelShader(pPS, PSSize, m_cpPSClassLinkage.Get(),
		m_cpPixelShader.GetAddressOf());
	if (FAILED(hr)) goto EXIT;

	// *****************************************************************************************************************
	// 定数バッファを作成
	// *****************************************************************************************************************

	D3D11_BUFFER_DESC BufferDesc;
	// 動的シェーダーリンケージ内で使用する定数バッファオブジェクトを作成する
	::ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.ByteWidth = sizeof(CBUFFER0);        // バッファサイズ
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;       // リソース使用法を特定する
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;// バッファの種類
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // CPU アクセス
	BufferDesc.MiscFlags = 0;                         // その他のフラグも設定しない
	hr = sRENDER_DEVICE->CreateBuffer(&BufferDesc, NULL, m_cpConstantBuffers[0].GetAddressOf());
	if (FAILED(hr)) goto EXIT;

	// 頂点シェーダーで使用する定数バッファオブジェクトを作成する
	::ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.ByteWidth = sizeof(CBUFFER1);        // バッファサイズ
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;       // リソース使用法を特定する
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;// バッファの種類
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // CPU アクセス
	BufferDesc.MiscFlags = 0;                         // その他のフラグも設定しない
	hr = sRENDER_DEVICE->CreateBuffer(&BufferDesc, NULL, m_cpConstantBuffers[1].GetAddressOf());
	if (FAILED(hr)) goto EXIT;

	hr = S_OK;

EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11BaseShader::Init( TCHAR pSrcFile[], LPCSTR pVSMain, LPCSTR pPSMain)
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	pSrcFile	Source file.
 * @param	pVSMain 	The vs main.
 * @param	pPSMain 	The ps main.
 *
 * @return	A hResult.
 **************************************************************************************************/

bool DX11BaseShader::Init(TCHAR pSrcFile[], TCHAR pVSMain[], TCHAR pPSMain[])
{
	HRESULT hr = E_FAIL;

	ID3D10Blob* pVSBlob = NULL, *pPSBlob = NULL;

	// 行列を列優先で設定し、古い形式の記述を許可しないようにする
	UINT Flag1 = D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_ENABLE_STRICTNESS;
	// 最適化レベルを設定する
#if defined(DEBUG) || defined(_DEBUG)
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL0;
#else
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif
	// 入力レイアウトは固定設定にしておく
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	sRENDER_DEVICE_MANAGER->CreateVertexShaderFromFile(m_cpVertexShader, pSrcFile, (pVSMain), "vs_5_0", m_cpLayout, layout,2);


	sRENDER_DEVICE_MANAGER->CreatePixelShaderFromFile(m_cpPixelShader, m_cpPSClassLinkage,pSrcFile,pPSMain,"ps_5_0",false);

	// 初期化する
	hr = Init(
		reinterpret_cast<BYTE*>(pVSBlob->GetBufferPointer()), pVSBlob->GetBufferSize()
		, reinterpret_cast<BYTE*>(pPSBlob->GetBufferPointer()), pPSBlob->GetBufferSize()
		);
	if (FAILED(hr)) goto EXIT;

	hr = S_OK;
EXIT:
	SAFE_RELEASE(pVSBlob);
	SAFE_RELEASE(pPSBlob);

	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11BaseShader::SetupBuffer(std::shared_ptr<BaseBuffer> spOutVertexBuffer, std::shared_ptr<BaseBuffer> spOutIndexBuffer, std::shared_ptr<MESH_BASE_DATA> spInMeshData)
 *
 * @brief	Sets up the buffer.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	spOutVertexBuffer	Buffer for sp out vertex data.
 * @param	spOutIndexBuffer 	Buffer for sp out index data.
 * @param	spInMeshData	 	Information describing the sp in mesh.
 *
 * @return	A bool.
 **************************************************************************************************/

bool DX11BaseShader::SetupBuffer(std::shared_ptr<BaseBuffer> spOutVertexBuffer, std::shared_ptr<BaseBuffer> spOutIndexBuffer, std::shared_ptr<MeshData> spInMeshData)
{
	return S_OK;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11BaseShader::SetCBVertexShader(Microsoft::WRL::ComPtr< ID3D11DeviceContext> cpDeviceContext, HFMATRIX* p_matWVP)
 *
 * @brief	頂点シェーダー用の定数バッファを設定する.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	cpDeviceContext 	Context for the cp device.
 * @param [in,out]	p_matWVP	If non-null, the matrix wvp.
 *
 * @return	A hResult.
 **************************************************************************************************/

bool DX11BaseShader::SetCBVertexShader(Microsoft::WRL::ComPtr< ID3D11DeviceContext> cpDeviceContext, HFMATRIX* p_matWVP)
{
	HRESULT hr = E_FAIL;

	if (p_matWVP == NULL) goto EXIT;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	CBUFFER1* cbuffer;

	hr = cpDeviceContext->Map(m_cpConstantBuffers[1].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(hr)) goto EXIT;
	cbuffer = (CBUFFER1*)(mappedResource.pData);

	::CopyMemory(&cbuffer->matWVP, p_matWVP, sizeof(HFMATRIX));

	cpDeviceContext->Unmap(m_cpConstantBuffers[1].Get(), 0);

	hr = S_OK;
EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11BaseShader::SetCBHalfLambert(Microsoft::WRL::ComPtr< ID3D11DeviceContext> cpDeviceContext , HFVECTOR4* p_vecLight , Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> cpDecalMap )
 *
 * @brief	ハーフランバート用の定数バッファを設定.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	cpDeviceContext   	Context for the cp device.
 * @param [in,out]	p_vecLight	If non-null, the std::vector light.
 * @param	cpDecalMap		  	The cp decal std::map.
 *
 * @return	A hResult.
 **************************************************************************************************/

bool DX11BaseShader::SetCBHalfLambert(Microsoft::WRL::ComPtr< ID3D11DeviceContext> cpDeviceContext
	, HFVECTOR4* p_vecLight
	, Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> cpDecalMap
	)
{
	HRESULT hr = E_FAIL;

	if (p_vecLight == NULL) goto EXIT;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	CBUFFER0* cbuffer;

	hr = cpDeviceContext->Map(m_cpConstantBuffers[0].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(hr)) goto EXIT;
	cbuffer = (CBUFFER0*)(mappedResource.pData);

	::CopyMemory(&cbuffer->vecLight0, p_vecLight, sizeof(HFVECTOR4));

	cpDeviceContext->Unmap(m_cpConstantBuffers[0].Get(), 0);

	// シェーダーリソースビューを設定
	cpDeviceContext->PSSetShaderResources(0, 1, cpDecalMap.GetAddressOf());

	hr = S_OK;
EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11BaseShader::SetCBPhongShading(Microsoft::WRL::ComPtr< ID3D11DeviceContext> cpDeviceContext , HFVECTOR4* p_vecLight , HFVECTOR4* p_EyePos , Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> cpDecalMap )
 *
 * @brief	フォンシェーディング用の定数バッファを設定.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	cpDeviceContext   	Context for the cp device.
 * @param [in,out]	p_vecLight	If non-null, the std::vector light.
 * @param [in,out]	p_EyePos  	If non-null, the eye position.
 * @param	cpDecalMap		  	The cp decal std::map.
 *
 * @return	A hResult.
 **************************************************************************************************/

bool DX11BaseShader::SetCBPhongShading(Microsoft::WRL::ComPtr< ID3D11DeviceContext> cpDeviceContext

	, HFVECTOR4* p_vecLight
	, HFVECTOR4* p_EyePos
	, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> cpDecalMap
	)
{
	HRESULT hr = E_FAIL;

	if (p_vecLight == NULL) goto EXIT;
	if (p_EyePos == NULL) goto EXIT;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	CBUFFER0* cbuffer;

	hr = cpDeviceContext->Map(m_cpConstantBuffers[0].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(hr)) goto EXIT;
	cbuffer = (CBUFFER0*)(mappedResource.pData);

	::CopyMemory(&cbuffer->vecLight1, p_vecLight, sizeof(HFVECTOR4));
	::CopyMemory(&cbuffer->EyePos, p_EyePos, sizeof(HFVECTOR4));

	cpDeviceContext->Unmap(m_cpConstantBuffers[0].Get(), 0);

	// シェーダーリソースビューを設定
	cpDeviceContext->PSSetShaderResources(0, 1, cpDecalMap.GetAddressOf());

	hr = S_OK;
EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11BaseShader::SetCBCelShading(Microsoft::WRL::ComPtr< ID3D11DeviceContext> cpDeviceContext , HFVECTOR4* p_vecLight , Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> cpDecalMap , Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> cpCelMap )
 *
 * @brief	セルシェーディング用の定数バッファを設定.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	cpDeviceContext   	Context for the cp device.
 * @param [in,out]	p_vecLight	If non-null, the std::vector light.
 * @param	cpDecalMap		  	The cp decal std::map.
 * @param	cpCelMap		  	The cp cel std::map.
 *
 * @return	A hResult.
 **************************************************************************************************/

bool DX11BaseShader::SetCBCelShading(Microsoft::WRL::ComPtr< ID3D11DeviceContext> cpDeviceContext
	, HFVECTOR4* p_vecLight
	, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> cpDecalMap
	, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> cpCelMap
	)
{
	HRESULT hr = E_FAIL;

	if (p_vecLight == NULL) goto EXIT;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	CBUFFER0* cbuffer;

	hr = cpDeviceContext->Map(m_cpConstantBuffers[0].Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(hr)) goto EXIT;
	cbuffer = (CBUFFER0*)(mappedResource.pData);

	::CopyMemory(&cbuffer->vecLight2, p_vecLight, sizeof(HFVECTOR4));

	cpDeviceContext->Unmap(m_cpConstantBuffers[0].Get(), 0);

	// シェーダーリソースビューを設定
	cpDeviceContext->PSSetShaderResources(0, 1, cpDecalMap.GetAddressOf());
	cpDeviceContext->PSSetShaderResources(1, 1, cpCelMap.GetAddressOf());

	hr = S_OK;
EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11BaseShader::Render()
 *
 * @brief	Begins.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @return	A hResult.
 *
 * ### param	cpDeviceContext   	Context for the cp device.
 * ### param	pClassInstanceName	Name of the class instance.
 **************************************************************************************************/

bool DX11BaseShader::Render()
{
	HRESULT hr = E_FAIL;

	// 指定された HLSL クラスを表すクラスインスタンス オブジェクトを取得する
	// http://msdn.microsoft.com/ja-jp/library/ee419541(v=vs.85).aspx
	hr = m_cpPSClassLinkage->GetClassInstance(m_pClassInstanceName, 0, m_cpClassInstance.GetAddressOf());
	if (FAILED(hr)) goto EXIT;

	// レイアウト設定
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetInputLayout(m_cpLayout.Get());

	// 頂点シェーダーをデバイスに設定する。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetShader(m_cpVertexShader.Get(), NULL, 0);

	// 頂点シェーダーに定数バッファを設定する
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetConstantBuffers(1, 1, m_cpConstantBuffers[1].GetAddressOf());

	// ハルシェーダーを無効にする。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->HSSetShader(NULL, NULL, 0);

	// ドメインシェーダーを無効にする。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DSSetShader(NULL, NULL, 0);

	// ジオメトリシェーダーを無効にする。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->GSSetShader(NULL, NULL, 0);

	// ピクセルシェーダーを動的シェーダーリンクとして設定する
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShader(m_cpPixelShader.Get(), m_cpClassInstance.GetAddressOf(), 1);

	// ピクセルシェーダーに定数バッファを設定する
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetConstantBuffers(0, 1, m_cpConstantBuffers[0].GetAddressOf());

	// コンピュートシェーダーを無効にする。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->CSSetShader(NULL, NULL, 0);

	hr = S_OK;
EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11BaseShader::End()
 *
 * @brief	Ends this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @return	A bool.
 **************************************************************************************************/

bool DX11BaseShader::End()
{
	return S_OK;
}	

void DX11BaseShader::CreateAndRegisterGraphicsCommand(std::shared_ptr<BaseRenderMeshObject> renderObject, UINT element)
{
	std::shared_ptr<RenderMeshCommmand> rmCommand = std::make_shared<RenderMeshCommmand>();
	rmCommand->SetRenderMeshElement(element);
	rmCommand->SetRenderObject(renderObject);
	rmCommand->SetGraphicsPriority(m_graphicsPriority);

	sTASK_SYSTEM->RegisterGraphicsCommand(rmCommand);
}
