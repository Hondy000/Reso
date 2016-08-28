
#include "../Public/LightShaderOfDeferredRender.h"
#include "../../../../RenderDevice/Basic/Public/RendererManager.h"
#include "../../../../Lighting/Public/LightManager.h"
#include "..\..\..\..\RenderObject\Public\SubMesh.h"
#include "../../../../Public/GraphicsTypes.h"

using namespace std;

/**********************************************************************************************//**
 * @fn	LightShaderOfDeferredRender::LightShaderOfDeferredRender()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 **************************************************************************************************/

LightShaderOfDeferredRender::LightShaderOfDeferredRender()
	
{
	m_pathPriority = HF_LIGHTING_PATH_OF_DEFERRED_RENDERING;
}

/**********************************************************************************************//**
 * @fn	LightShaderOfDeferredRender::LightShaderOfDeferredRender(const LightShaderOfDeferredRender& other)
 *
 * @brief	Copy constructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	other	The other.
 **************************************************************************************************/

LightShaderOfDeferredRender::LightShaderOfDeferredRender(const LightShaderOfDeferredRender& other)
{
}

/**********************************************************************************************//**
 * @fn	LightShaderOfDeferredRender::~LightShaderOfDeferredRender()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 **************************************************************************************************/

LightShaderOfDeferredRender::~LightShaderOfDeferredRender()
{
}

/**********************************************************************************************//**
 * @fn	bool LightShaderOfDeferredRender::Setup()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @return	A bool.
 **************************************************************************************************/

bool LightShaderOfDeferredRender::Setup()
{
	m_pathPriority = HF_LIGHTING_PATH_OF_DEFERRED_RENDERING;
	m_spVertexLayout = std::shared_ptr<BaseVertexLayout>(new BaseVertexLayout);
	sRENDER_DEVICE_MANAGER->SetupGeometryBuffer();
	// Initialize the vertex and pixel shaders.
	return InitializeShader(_T("Resource/Shader/HLSL/deferredLight.hlsl"), _T("Resource/Shader/HLSL/deferredLight.hlsl"));
}

/**********************************************************************************************//**
 * @fn	void LightShaderOfDeferredRender::Destroy()
 *
 * @brief	Destroys this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 **************************************************************************************************/

void LightShaderOfDeferredRender::Destroy()
{
}



/**********************************************************************************************//**
 * @fn	bool LightShaderOfDeferredRender::PreProcessOfRender ( std::shared_ptr<CBaseObject>renderPram )
 *
 * @brief	Pre render process.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	parameter1	The render pram.
 *
 * @return	A bool.
 **************************************************************************************************/

bool LightShaderOfDeferredRender::PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials)
{
	bool result;
	// Reset the render target back to the original back buffer and not the render buffers anymore.
	sRENDER_DEVICE_MANAGER->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	sRENDER_DEVICE_MANAGER->ResetViewport();

	HFMATRIX world, view, projection;

	HFMatrixScaling(&world, sRENDER_DEVICE_MANAGER->GetScreenSize().x, sRENDER_DEVICE_MANAGER->GetScreenSize().y, 0);

	HFMatrixLookAtLH(&view, &HFVECTOR3(0, 0, -50), &HFVECTOR3(0, 0, 0), &HFVECTOR3(0, -1, 0));
	HFMatrixOrthoLH(&projection, sRENDER_DEVICE_MANAGER->GetScreenSize().x * 2, sRENDER_DEVICE_MANAGER->GetScreenSize().y * 2, 1, 10000);

	HFVECTOR3 directionalLight = { 0,-1,0 };

	UINT stride[2] = { 12 ,8 };
	UINT offset[2] = { 0 ,0};

	// バッファの取得
	std::vector<shared_ptr<VertexBuffer>> buffers;
	HFGraphics::MeshShaderBufferLayout bufferlayout;
	bufferlayout.AddBufferSemantics(0, HFGraphics::BufferSemantics(HFString("POSITION"), 0, sizeof(HFVECTOR3), HFGraphics::INPUT_PER_VERTEX_DATA, 0));
	bufferlayout.AddBufferSemantics(1, HFGraphics::BufferSemantics(HFString("TEXCOORD"), 0, sizeof(HFVECTOR2), HFGraphics::INPUT_PER_VERTEX_DATA, 0));
	std::vector<bool> boolenArray;
	shape->GetVertexBuffers( bufferlayout, buffers,boolenArray);
	for (int i = 0;i < boolenArray.size();i++)
	{
		if (boolenArray[i] == false)
		{
			return false;
		}
	}


	sRENDER_DEVICE_MANAGER->SetVertexBuffer(0,2,buffers,stride,offset);
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetIndexBuffer(shape->GetIndexBuffer()->Get(), DXGI_FORMAT_R32_UINT, 0);

	// Set the shader parameters that it will use for rendering.
	result =
		SetShaderParameters
		(
			world,
			view,
			projection,
			directionalLight
			);

	if (!result)
	{
		return false;
	}

	sRENDER_DEVICE_MANAGER->SetBlendState(&sRENDER_DEVICE_MANAGER->GetDefaultBlendDesc(), 1, false);

	// Turn off the Z buffer to begin all 2D rendering.
	sRENDER_DEVICE_MANAGER->ZBufferNotWriteNotEnable();

	sRENDER_DEVICE_MANAGER->SetSolidRasterize();

	return true;
}

/**********************************************************************************************//**
 * @fn	bool LightShaderOfDeferredRender::Render()
 *
 * @brief	Renders this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @return	A bool.
 **************************************************************************************************/

bool LightShaderOfDeferredRender::Render()
{
	// Now render the prepared buffers with the shader.
	HRESULT hr = m_cpPSClassLinkage->GetClassInstance(LPCSTR("g_Phong"), 0, m_cpClassInstance.GetAddressOf());

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// ハルシェーダーを無効にする。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->HSSetShader(NULL, NULL, 0);

	// ドメインシェーダーを無効にする。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DSSetShader(NULL, NULL, 0);

	// ジオメトリシェーダーを無効にする。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->GSSetShader(NULL, NULL, 0);
	// ピクセルシェーダーを動的シェーダーリンクとして設定する
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShader(m_cpPixelShader.Get(), m_cpClassInstance.GetAddressOf(), 1);

	// Set the vertex input layout.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetInputLayout(m_spVertexLayout->GetMain().Get());

	// Set the vertex and pixel shaders that will be used to render.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetShader(m_cpVertexShader.Get(), NULL, 0);
	//deviceContext->PSSetShader(m_cpPixelShader.Get(), NULL, 0);

	// Set the sampler state in the pixel shader.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetSamplers(0, 1, m_cpSamplerState.GetAddressOf());

	// Render the geometry.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DrawIndexed(6, 0, 0);

	return S_OK;
}

bool LightShaderOfDeferredRender::PostProcessOfRender()
{
	// Turn the Z buffer back on now that all 2D rendering has completed.
	sRENDER_DEVICE_MANAGER->TurnZBufferOn();
	Microsoft::WRL::ComPtr< ID3D11RenderTargetView> pNullRTV[7];

	//ID3D11ShaderResourceView *const pSRV[7] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL };
	//sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShaderResources(0, 7, pSRV);

	//ID3D11RenderTargetView* pView[1] = { NULL };

	//sRENDER_DEVICE_MANAGER->GetImmediateContext()->OMSetRenderTargets(1, pView, NULL); 
	//sRENDER_DEVICE_MANAGER->GetGeometryBuffer()->CleanUpRenderTargets();
	return S_OK;
}

/**********************************************************************************************//**
 * @fn	bool LightShaderOfDeferredRender::InitializeShader ( TCHAR* vsFilename, TCHAR* psFilename )
 *
 * @brief	Initializes the shader.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param [in,out]	vsFilename	If non-null, filename of the vs file.
 * @param [in,out]	psFilename	If non-null, filename of the ps file.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool LightShaderOfDeferredRender::InitializeShader
(
	TCHAR* vsFilename,
	TCHAR* psFilename
	)
{
	bool result;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	UINT numElements;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC lightBufferDesc;
	m_constantBuffers.resize(3);
	m_constantBuffers[0] = std::shared_ptr<ConstantBuffer>(new ConstantBuffer);
	m_constantBuffers[1] = std::shared_ptr<ConstantBuffer>(new ConstantBuffer);
	m_constantBuffers[2] = std::shared_ptr<ConstantBuffer>(new ConstantBuffer);


	// 行列を列優先で設定し、古い形式の記述を許可しないようにする
	UINT Flag1 = D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_ENABLE_STRICTNESS;
	// 最適化レベルを設定する
#if defined(DEBUG) || defined(_DEBUG)
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL0;
#else
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif


	// Create the vertex input layout description.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 1;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	result = sRENDER_DEVICE_MANAGER->CreateVertexShaderFromFile(m_cpVertexShader, vsFilename,
		"LightVertexShader",
		"vs_5_0", m_spVertexLayout->GetMain(), polygonLayout, numElements);

	result = sRENDER_DEVICE_MANAGER->CreatePixelShaderFromFile(m_cpPixelShader, m_cpPSClassLinkage, psFilename, "LightPixelShader", "ps_5_0",true);

	// Create a texture sampler state description.
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	result = sRENDER_DEVICE->CreateSamplerState(&samplerDesc, m_cpSamplerState.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = sRENDER_DEVICE->CreateBuffer(&matrixBufferDesc, NULL, m_constantBuffers[0]->GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(CBUFFER0);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the pixel shader constant buffer from within this class.
	result = sRENDER_DEVICE->CreateBuffer(&lightBufferDesc, NULL, m_constantBuffers[1]->GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	m_constantBuffers[2]->SetData(NULL, sizeof(CBUFFER1), 1, BaseBuffer::ACCESS_FLAG::WRITEONLY);
	return true;
}

/**********************************************************************************************//**
 * @fn	bool LightShaderOfDeferredRender::SetShaderParameters ( D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, std::shared_ptr<CBaseTexture> colorTexture, std::shared_ptr<CBaseTexture> positionTexture, std::shared_ptr<CBaseTexture> normalTexture, D3DXVECTOR3 lightDirection)
 *
 * @brief	Sets shader parameters.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	worldMatrix			The world matrix.
 * @param	viewMatrix			The view matrix.
 * @param	projectionMatrix	The projection matrix.
 * @param	colorTexture		The color texture.
 * @param	positionTexture 	The position texture.
 * @param	normalTexture   	The normal texture.
 * @param	lightDirection  	The light direction.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool LightShaderOfDeferredRender::SetShaderParameters
(
	HFMATRIX worldMatrix,
	HFMATRIX viewMatrix,
	HFMATRIX projectionMatrix,
	HFVECTOR3 lightDirection)
{
	bool result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	UINT bufferNumber;
	MatrixBufferType* dataPtr;
	CBUFFER0* dataPtr2;
	CBUFFER1* dataPtr3;

	HFMATRIX WVP = worldMatrix * viewMatrix * projectionMatrix;

	result = sRENDER_DEVICE_MANAGER->GetImmediateContext()->Map(m_constantBuffers[0]->Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->WVP = WVP;

	// Unlock the constant buffer.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Unmap(m_constantBuffers[0]->Get(), 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Now set the constant buffer in the vertex shader with the updated values.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetConstantBuffers(bufferNumber, 1, m_constantBuffers[0]->GetAddressOf());


	// Set shader texture resources in the pixel shader.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShaderResources(0, 1, sRENDER_DEVICE_MANAGER->GetGeometryBuffer()->GetShaderResourceView(0)->GetSharderResorceView().GetAddressOf());
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShaderResources(1, 1, sRENDER_DEVICE_MANAGER->GetGeometryBuffer()->GetShaderResourceView(1)->GetSharderResorceView().GetAddressOf());
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShaderResources(2, 1,sRENDER_DEVICE_MANAGER->GetGeometryBuffer()->GetShaderResourceView(2)->GetSharderResorceView().GetAddressOf());
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShaderResources(3, 1, sRENDER_DEVICE_MANAGER->GetGeometryBuffer()->GetShaderResourceView(3)->GetSharderResorceView().GetAddressOf());
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShaderResources(4, 1, sRENDER_DEVICE_MANAGER->GetGeometryBuffer()->GetShaderResourceView(4)->GetSharderResorceView().GetAddressOf());
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShaderResources(5, 1, sRENDER_DEVICE_MANAGER->GetGeometryBuffer()->GetShaderResourceView(5)->GetSharderResorceView().GetAddressOf());

	// Lock the light constant buffer so it can be written to.
	result = sRENDER_DEVICE_MANAGER->GetImmediateContext()->Map(m_constantBuffers[1]->Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr2 = (CBUFFER0*)mappedResource.pData;

	// Copy the lighting variables into the constant buffer.  
	std::shared_ptr< HFGraphics::DirectinalLight  > spLight;
	HFGraphics::LightManager::GetInstance()->GetDirectionalLight(spLight);
	if (spLight)
	{
		dataPtr2->lightDirection0 = HFVECTOR4(spLight->GetPram().direction);


		// アルベドと法線はデバッグ用の表示みたいなもんでダミーなので入力なし 
		dataPtr2->lightDirection4 = HFVECTOR4(spLight->GetPram().direction);
		::ZeroMemory(&dataPtr2->pointLight0, sizeof(HFGraphics::POINT_LIGHT_PRAM));


		dataPtr2->lightDirection5 = HFVECTOR4(spLight->GetPram().direction);
		::ZeroMemory(&dataPtr2->spotLight0, sizeof(HFGraphics::SPOT_LIGHT_PRAM));
		dataPtr2->lightDirection = HFVECTOR4(spLight->GetPram().direction);

	}

	vector<shared_ptr<HFGraphics::PointLight>> pointLightArray;
	sLIGHT_MANAGER->GetPointLight(pointLightArray, HFVECTOR3(worldMatrix._41, worldMatrix._42, worldMatrix._43), 64);
	for (int i = 0; i < 64; i++)
	{
		::ZeroMemory(&dataPtr2->pointLightArray[i], sizeof(HFGraphics::POINT_LIGHT_PRAM));

		if (pointLightArray[i])
		{
			dataPtr2->pointLightArray[i].attenuation = pointLightArray[i]->GetPram().attenuation;
			dataPtr2->pointLightArray[i].color = pointLightArray[i]->GetPram().color;
			dataPtr2->pointLightArray[i].falloff = pointLightArray[i]->GetPram().falloff;
			dataPtr2->pointLightArray[i].position = pointLightArray[i]->GetPram().position;
			dataPtr2->pointLightArray[i].range = pointLightArray[i]->GetPram().range;
		}
	}

	for (int i = 0; i < 64; i++)
	{
		::ZeroMemory(&dataPtr2->pointLightArray2[i], sizeof(HFGraphics::POINT_LIGHT_PRAM));

		if (pointLightArray[i])
		{
			dataPtr2->pointLightArray2[i].attenuation = pointLightArray[i]->GetPram().attenuation;
			dataPtr2->pointLightArray2[i].color = pointLightArray[i]->GetPram().color;
			dataPtr2->pointLightArray2[i].falloff = pointLightArray[i]->GetPram().falloff;
			dataPtr2->pointLightArray2[i].position = pointLightArray[i]->GetPram().position;
			dataPtr2->pointLightArray2[i].range = pointLightArray[i]->GetPram().range;
		}
	}

	vector<shared_ptr<HFGraphics::SpotLight>> spotLightArray;
	sLIGHT_MANAGER->GetSpotLight(spotLightArray, HFVECTOR3(worldMatrix._41, worldMatrix._42, worldMatrix._43), 64);
	for (int i = 0; i < 64; i++)
	{
		::ZeroMemory(&dataPtr2->spotLightArray[i], sizeof(HFGraphics::SPOT_LIGHT_PRAM));


	}


	if (spLight)
	{
		dataPtr2->lightDirection6 = HFVECTOR4(spLight->GetPram().direction);
	}


	// Unlock the constant buffer.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Unmap(m_constantBuffers[1]->Get(), 0);


	// Set the position of the light constant buffer in the pixel shader.
	bufferNumber = 1;

	// Finally set the light constant buffer in the pixel shader with the updated values.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetConstantBuffers(bufferNumber, 1, m_constantBuffers[1]->GetAddressOf());




	result = sRENDER_DEVICE_MANAGER->GetImmediateContext()->Map(m_constantBuffers[2]->Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr3 = (CBUFFER1*)mappedResource.pData;

	// Copy the matrices into the constant buffer.										 
	dataPtr3->cameraPosition = HFVECTOR4(sRENDER_DEVICE_MANAGER->GetViewPosition().x, sRENDER_DEVICE_MANAGER->GetViewPosition().y, sRENDER_DEVICE_MANAGER->GetViewPosition().z, 0);

	// Unlock the constant buffer.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Unmap(m_constantBuffers[2]->Get(), 0);
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetConstantBuffers(2, 1, m_constantBuffers[2]->GetAddressOf());


	return true;
}