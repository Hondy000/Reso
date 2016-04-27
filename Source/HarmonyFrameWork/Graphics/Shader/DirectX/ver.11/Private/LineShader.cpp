
#include "../Public/LineShader.h"
#include "../../../../VertexLayout/Public/BaseVertexLayout.h"
#include "../../../../Buffer/Public/ConstantBuffer.h"
#include "../../../../RenderDevice/Basic/Public/RendererManager.h"

/**********************************************************************************************//**
																								* @fn	DeferredLineShader::DeferredLineShader()
																								*
																								* @brief	Default constructor.
																								*
																								* @author	Kazuyuki Honda
																								* @date	2015/11/04
																								**************************************************************************************************/

LineShader::LineShader()
{
}

/**********************************************************************************************//**
																								* @fn	DeferredLineShader::DeferredLineShader(const DeferredLineShader& other)
																								*
																								* @brief	Copy constructor.
																								*
																								* @author	Kazuyuki Honda
																								* @date	2015/11/04
																								*
																								* @param	other	The other.
																								**************************************************************************************************/

LineShader::LineShader(const LineShader& other)
{
}

/**********************************************************************************************//**
 * @fn	DeferredLineShader::~DeferredLineShader()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 **************************************************************************************************/

LineShader::~LineShader()
{
}

bool LineShader::Setup()
{
	m_spVertexLayout = std::shared_ptr<BaseVertexLayout>(new BaseVertexLayout);
	// Initialize the vertex and pixel shaders.
	bool result;
	HRESULT hr = E_FAIL;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[1];
	UINT numElements;
	m_constantBuffers.push_back(std::shared_ptr<ConstantBuffer>(new ConstantBuffer));

	// Initialize the pointers this function will use to null.
	// Create the vertex input layout description.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Compile the vertex shader code.		 
	sRENDER_DEVICE_MANAGER->CreateVertexShaderFromFile( m_cpVertexShader,_T("Resource/Shader/HLSL/SimpleHLSL08.hlsl"),
		 "VS_Main", "vs_4_0",
		m_spVertexLayout->GetMain(),
		polygonLayout,
		numElements
		);
	

	sRENDER_DEVICE_MANAGER->CreatePixelShaderFromFile(m_cpPixelShader, m_cpPSClassLinkage,
		_T("Resource/Shader/HLSL/SimpleHLSL08.hlsl"),
		"PS_Main",
		"ps_4_0"
		,false);

	hr = m_constantBuffers[0]->SetData(NULL, sizeof(MatrixBufferType), 1,BaseBuffer::ACCESS_FLAG::WRITEONLY);


	if (SUCCEEDED(hr))
	{
		result = true;
	}
	return result;
}

/**********************************************************************************************//**
																								* @fn	void DeferredLineShader::Destroy()
																								*
																								* @brief	Destroys this object.
																								*
																								* @author	Kazuyuki Honda
																								* @date	2015/11/04
																								**************************************************************************************************/

void LineShader::Destroy()
{
}




/**********************************************************************************************//**
																								* @fn	bool DeferredLineShader::Render()
																								*
																								* @brief	Renders this object.
																								*
																								* @author	Kazuyuki Honda
																								* @date	2015/11/04
																								* @atention	バッファは事前にContextに入れておく
																								*
																								* @return	A bool.
																								**************************************************************************************************/

bool LineShader::Render()
{
	bool result = E_FAIL;

	// Set the vertex input layout.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetInputLayout(m_spVertexLayout->GetMain().Get());
						 
	// Set the vertex and pixel shaders that will be used to render.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetShader(m_cpVertexShader.Get(), NULL, 0);
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShader(m_cpPixelShader.Get(), NULL, 0);

	// Set the sampler states in the pixel shader.
	//sRENDER_DEVICE_MANAGER->GetD3DDeviceContext()->PSSetSamplers(0, 1, m_cpSamplerState.GetAddressOf());


	// Render the geometry.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DrawIndexed(m_indexCount, 0, 0);

	return result;
}

/**********************************************************************************************//**
																								* @fn	bool DeferredLineShader::PreRenderProcess ( std::shared_ptr<CBaseObject> spPram )
																								*
																								* @brief	Pre render process.
																								*
																								* @author	Kazuyuki Honda
																								* @date	2015/11/04
																								*
																								* @param	spPram	The sp pram.
																								*
																								* @return	A bool.
																								**************************************************************************************************/

bool LineShader::PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials)
{
	bool result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	UINT bufferNumber;

	MatrixBufferType* datapt;
	HFMATRIX world, view, proj;

	sRENDER_DEVICE_MANAGER->GetTransform(&world, HFTS_WORLD);
	sRENDER_DEVICE_MANAGER->GetTransform(&view, HFTS_VIEW);
	sRENDER_DEVICE_MANAGER->GetTransform(&proj, HFTS_PERSPECTIVE);

	// Lock the constant buffer so it can be written to.
	result = sRENDER_DEVICE_MANAGER->GetImmediateContext()->Map(m_constantBuffers[0]->Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	datapt = (MatrixBufferType*)mappedResource.pData;
	HFMATRIX wvp;
	wvp = world*view*proj;
	// Transpose the matrices to prepare them for the shader.
	datapt->wvp = HFMatrixTranspose(wvp);

	// Unlock the constant buffer.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Unmap(m_constantBuffers[0]->Get(), 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;


	// マトリクスをセット
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetConstantBuffers(bufferNumber, 1, m_constantBuffers[0]->GetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11Buffer>  buffers[1];
	buffers[0] = shape->GetVertexBuffers()[0]->GetBuffer();

	UINT stride[1] = { sizeof(HFVECTOR3)};
	UINT offset[1] = { 0 };

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetVertexBuffers(0, 1, buffers[0].GetAddressOf(), stride, offset);

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetIndexBuffer(shape->GetIndexBuffer()->Get(), DXGI_FORMAT_R32_UINT, 0);
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	m_indexCount = shape->GetIndexCount();
	sRENDER_DEVICE_MANAGER->SetBackBufferRenderTarget();
	return true;
}