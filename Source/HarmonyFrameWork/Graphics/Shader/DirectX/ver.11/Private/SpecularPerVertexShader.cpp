							 
#include "../../../../RenderDevice/Basic/Public/RendererManager.h"
#include "../../../../RenderDevice/DirectX/ver.11/Public/GeometryBuffers.h"
#include "..\Public\SpecularPerVertexShader.h"
#include "..\..\..\..\Lighting\Public\LightManager.h"
#include "..\..\..\..\RenderObject\Public\SubMesh.h"

struct CBUFFER2
{
	HFVECTOR4 pos;
	HFVECTOR4 dire;
};

SpecularPerVertexShader::SpecularPerVertexShader()
{
	m_pathPriority = HF_FORWARD_RENDERING_SHADER;
}

/**********************************************************************************************//**
																								* @fn	SpecularPerVertexShader::SpecularPerVertexShader(const SpecularPerVertexShader& other)
																								*
																								* @brief	Copy constructor.
																								*
																								* @author	Kazuyuki Honda
																								* @date	2015/11/04
																								*
																								* @param	other	The other.
																								**************************************************************************************************/

SpecularPerVertexShader::SpecularPerVertexShader(const SpecularPerVertexShader& other)
{
	m_pathPriority = HF_FORWARD_RENDERING_SHADER;
}

/**********************************************************************************************//**
																								* @fn	SpecularPerVertexShader::~SpecularPerVertexShader()
																								*
																								* @brief	Destructor.
																								*
																								* @author	Kazuyuki Honda
																								* @date	2015/11/04
																								**************************************************************************************************/

SpecularPerVertexShader::~SpecularPerVertexShader()
{
}

/**********************************************************************************************//**
																								* @fn	bool SpecularPerVertexShader::Init()
																								*
																								* @brief	Initialises this object.
																								*
																								* @author	Kazuyuki Honda
																								* @date	2015/11/04
																								*
																								* @return	A bool.
																								**************************************************************************************************/

bool SpecularPerVertexShader::Setup()
{
	m_spVertexLayout = std::shared_ptr<BaseVertexLayout>(new BaseVertexLayout);
	bool result;
	Microsoft::WRL::ComPtr<ID3D10Blob> errorMessage;
	Microsoft::WRL::ComPtr<ID3D10Blob> vertexShaderBuffer;
	Microsoft::WRL::ComPtr<ID3D10Blob> pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	UINT numElements;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC materialBufferDesc;

	m_constantBuffers.push_back(std::shared_ptr<ConstantBuffer>(new ConstantBuffer));
	m_constantBuffers.push_back(std::shared_ptr<ConstantBuffer>(new ConstantBuffer));
	m_constantBuffers.push_back(std::shared_ptr<ConstantBuffer>(new ConstantBuffer));


	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "NORMAL";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[1].InputSlot = 1;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "TEXCOORD";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[2].InputSlot = 2;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);


	bool res;
	res = sRENDER_DEVICE_MANAGER->CreateVertexShaderFromFile(
		m_cpVertexShader,
		"Resource/Shader/HLSL/SpecularShaderPerVertex.hlsl",
		"VS_Main",
		"vs_5_0",
		m_spVertexLayout->GetMain(),
		polygonLayout,
		numElements
	);

	res = sRENDER_DEVICE_MANAGER->CreatePixelShaderFromFile(m_cpPixelShader, m_cpPSClassLinkage,
		_T("Resource/Shader/HLSL/SpecularShaderPerVertex.hlsl"),
		"PS_Main",
		"ps_5_0", false);

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = sRENDER_DEVICE->CreateSamplerState(&samplerDesc, m_cpSamplerState.GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	result = sRENDER_DEVICE->CreateBuffer(&matrixBufferDesc, NULL, m_constantBuffers[0]->GetAddressOf());


	result = m_constantBuffers[1]->SetData(nullptr, sizeof(MaterialBufferType), 1, BaseBuffer::ACCESS_FLAG::WRITEONLY);


	result = m_constantBuffers[2]->SetData(nullptr, sizeof(CBUFFER2), 1, BaseBuffer::ACCESS_FLAG::WRITEONLY);

	return S_OK;
}

/**********************************************************************************************//**
																								* @fn	void SpecularPerVertexShader::Destroy()
																								*
																								* @brief	Destroys this object.
																								*
																								* @author	Kazuyuki Honda
																								* @date	2015/11/04
																								**************************************************************************************************/

void SpecularPerVertexShader::Destroy()
{
}





/**********************************************************************************************//**
																								* @fn	bool SpecularPerVertexShader::Render()
																								*
																								* @brief	Renders this object.
																								*
																								* @author	Kazuyuki Honda
																								* @date	2015/11/04
																								* @atention	バッファは事前にContextに入れておく
																								*
																								* @return	A bool.
																								**************************************************************************************************/

bool SpecularPerVertexShader::Render()
{
	bool result = E_FAIL;

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetInputLayout(m_spVertexLayout->GetMain().Get());

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetShader(m_cpVertexShader.Get(), NULL, 0);
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShader(m_cpPixelShader.Get(), NULL, 0);

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetSamplers(0, 1, m_cpSamplerState.GetAddressOf());

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DrawIndexed(m_indexCount, 0, 0);

	return result;
}

bool SpecularPerVertexShader::PostProcessOfRender()
{
	//Microsoft::WRL::ComPtr< ID3D11RenderTargetView> pNullRTV[7];

	//sRENDER_DEVICE_MANAGER->GetImmediateContext()->OMSetRenderTargets(7, pNullRTV[0].ReleaseAndGetAddressOf(), NULL);
	return true;
}

/**********************************************************************************************//**
																								* @fn	bool SpecularPerVertexShader::PreRenderProcess ( std::shared_ptr<CBaseObject> spPram )
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

bool SpecularPerVertexShader::PreProcessOfRender(std::shared_ptr<SubMesh> mesh, std::shared_ptr<Material>materials)
{
	// GeometryBuffferに書き込み
	//sRENDER_DEVICE_MANAGER->GetGeometryBuffer()->SetRenderTargets(sRENDER_DEVICE_MANAGER->GetImmediateContext());
	
	bool result;
	sRENDER_DEVICE_MANAGER->SetBackBufferRenderTarget();
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	UINT bufferNumber;

	MatrixBufferType* matrixPtr;
	MaterialBufferType* materialPtr;
	HFMATRIX world, view, proj;

	sRENDER_DEVICE_MANAGER->GetTransform(&world, HFTS_WORLD);
	sRENDER_DEVICE_MANAGER->GetTransform(&view, HFTS_VIEW);
	sRENDER_DEVICE_MANAGER->GetTransform(&proj, HFTS_PERSPECTIVE);

	result = sRENDER_DEVICE_MANAGER->GetImmediateContext()->Map(m_constantBuffers[0]->Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	matrixPtr = (MatrixBufferType*)mappedResource.pData;

	matrixPtr->world = HFMatrixTranspose(world);
	matrixPtr->view = HFMatrixTranspose(view);
	matrixPtr->projection = HFMatrixTranspose(proj);

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Unmap(m_constantBuffers[0]->Get(), 0);

	// マテリアルのバッファ更新		
	result = sRENDER_DEVICE_MANAGER->GetImmediateContext()->Map(m_constantBuffers[1]->Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	materialPtr = (MaterialBufferType*)mappedResource.pData;

	materialPtr->ambient = mesh->GetMaterial()->GetAmbient();
	materialPtr->diffuse = mesh->GetMaterial()->GetDiffuse();
	materialPtr->emissive = mesh->GetMaterial()->GetEmissive();
	materialPtr->specular = mesh->GetMaterial()->GetSpecular();
	materialPtr->power = 50;
	materialPtr->range = 3;

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Unmap(m_constantBuffers[1]->Get(), 0);


	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Map(m_constantBuffers[2]->Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	CBUFFER2* cbptr;
	cbptr = (CBUFFER2*)mappedResource.pData;					
	cbptr->pos = HFVECTOR4(sRENDER_DEVICE_MANAGER->GetViewPosition().x, sRENDER_DEVICE_MANAGER->GetViewPosition().y, sRENDER_DEVICE_MANAGER->GetViewPosition().z, 0);
	std::shared_ptr< HFGraphics::DirectinalLight  > spLight;
	HFGraphics::LightManager::GetInstance()->GetDirectionalLight(spLight);
	cbptr->dire = HFVECTOR4(spLight->GetPram().direction);

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Unmap(m_constantBuffers[2]->Get(), 0);



	bufferNumber = 0;

	// テクスチャをセット

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShaderResources(0, 1, materials->GetDiffuseTexture()->GetSharderResorceView().GetAddressOf());
	// マトリクスをセット
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetConstantBuffers(bufferNumber, 1, m_constantBuffers[0]->GetAddressOf());
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetConstantBuffers(1, 1, m_constantBuffers[1]->GetAddressOf());
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetConstantBuffers(2, 1, m_constantBuffers[2]->GetAddressOf());
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetConstantBuffers(0, 1, m_constantBuffers[1]->GetAddressOf());
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetConstantBuffers(1, 1, m_constantBuffers[2]->GetAddressOf());


	Microsoft::WRL::ComPtr<ID3D11Buffer>  buffers[3];
	buffers[0] = mesh->GetVertexBuffers()[0]->GetBuffer();
	buffers[1] = mesh->GetVertexBuffers()[1]->GetBuffer();
	buffers[2] = mesh->GetVertexBuffers()[2]->GetBuffer();

	UINT stride[3] = { sizeof(HFVECTOR3), sizeof(HFVECTOR3),sizeof(HFVECTOR2) };
	UINT offset[3] = { 0, 0 ,0 };

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetVertexBuffers(0, 3, buffers[0].GetAddressOf(), stride, offset);

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetIndexBuffer(mesh->GetIndexBuffer()->Get(), DXGI_FORMAT_R32_UINT, 0);
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_indexCount = mesh->GetIndexCount();

	return true;
}