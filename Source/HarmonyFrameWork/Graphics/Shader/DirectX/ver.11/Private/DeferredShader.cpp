
#include "../Public/DeferredShader.h"
#include "../../../../RenderDevice/Basic/Public/RendererManager.h"
#include "../../../../RenderDevice/DirectX/ver.11/Public/GeometryBuffers.h"
#include "..\..\..\..\Matetial\Public\Material.h"
#include "..\..\..\..\RenderObject\Public\SubMesh.h"
#include "..\..\..\..\Public\BaseGraphicsCommand.h"
#include "..\..\..\..\..\Core\Task\Public\TaskSystem.h"
#include "../../../../../Debug/Public/Debug.h"

DeferredShader::DeferredShader()
{
	m_graphicsPriority = HF_DEFERRED_RENDERING_SHADER;
}

/**********************************************************************************************//**
 * @fn	DeferredShader::DeferredShader(const DeferredShader& other)
 *
 * @brief	Copy constructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	other	The other.
 **************************************************************************************************/

DeferredShader::DeferredShader(const DeferredShader& other)
{
	m_graphicsPriority = HF_DEFERRED_RENDERING_SHADER;
}

/**********************************************************************************************//**
 * @fn	DeferredShader::~DeferredShader()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 **************************************************************************************************/

DeferredShader::~DeferredShader()
{
}

/**********************************************************************************************//**
 * @fn	bool DeferredShader::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @return	A bool.
 **************************************************************************************************/

bool DeferredShader::Setup()
{
	m_graphicsPriority = HF_DEFERRED_RENDERING_SHADER;
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



	sRENDER_DEVICE_MANAGER->CreateVertexShaderFromFile(
		m_cpVertexShader,
		"Resource/Shader/HLSL/DeferredShader.hlsl",
		"DeferredVertexShader",
		"vs_5_0",
		m_spVertexLayout->GetMain(),
		polygonLayout,
		numElements
		);

	sRENDER_DEVICE_MANAGER->CreatePixelShaderFromFile(m_cpPixelShader, m_cpPSClassLinkage,
		_T("Resource/Shader/HLSL/DeferredShader.hlsl"),
		"DeferredPixelShader",
		"ps_5_0",false);

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

	m_cpSamplerStateArray.resize(1);
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.BorderColor[0] = 1.0f;
	desc.BorderColor[1] = 1.0f;
	desc.BorderColor[2] = 1.0f;
	desc.BorderColor[3] = 1.0f;
	desc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
	desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	desc.MaxAnisotropy = 1;
	desc.MipLODBias = 0;
	desc.MinLOD = -FLT_MAX;
	desc.MaxLOD = +FLT_MAX;
	
	 // サンプラーステートを生成.
	HRESULT hr = sRENDER_DEVICE->CreateSamplerState(&desc, m_cpSamplerStateArray[0].GetAddressOf());
	if (FAILED(hr))
	{
	        HFDebug::Debug::GetInstance()->Log("Error : ID3D11Device::CreateSamplerState() Failed.");
	        return false;
	}

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	result = sRENDER_DEVICE->CreateBuffer(&matrixBufferDesc, NULL, m_constantBuffers[0]->GetAddressOf());
	if (FAILED(result))
	{
		return false;
	}

	materialBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	materialBufferDesc.ByteWidth = sizeof(MaterialBufferType);
	materialBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	materialBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	materialBufferDesc.MiscFlags = 0;
	materialBufferDesc.StructureByteStride = 0;
	result = sRENDER_DEVICE->CreateBuffer(&materialBufferDesc, NULL, m_constantBuffers[1]->GetAddressOf());


	return S_OK;
}

/**********************************************************************************************//**
 * @fn	void DeferredShader::Destroy()
 *
 * @brief	Destroys this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 **************************************************************************************************/

void DeferredShader::Destroy()
{
}





/**********************************************************************************************//**
 * @fn	bool DeferredShader::Render()
 *
 * @brief	Renders this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 * @atention	バッファは事前にContextに入れておく
 *
 * @return	A bool.
 **************************************************************************************************/

bool DeferredShader::Render()
{
	bool result = E_FAIL;

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetInputLayout(m_spVertexLayout->GetMain().Get());

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetShader(m_cpVertexShader.Get(), NULL, 0);
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShader(m_cpPixelShader.Get(), NULL, 0);

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetSamplers(0, 1, m_cpSamplerState.GetAddressOf());

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetSamplers(0, 1, m_cpSamplerStateArray[0].GetAddressOf());

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DrawIndexed(m_indexCount, 0, 0);

	return result;
}

bool DeferredShader::PostProcessOfRender()
{
	Microsoft::WRL::ComPtr< ID3D11RenderTargetView> pNullRTV[7];

//	sRENDER_DEVICE_MANAGER->GetImmediateContext()->OMSetRenderTargets(7, pNullRTV[0].ReleaseAndGetAddressOf(), NULL);
	return true;
}

/**********************************************************************************************//**
 * @fn	bool DeferredShader::PreRenderProcess ( std::shared_ptr<CBaseObject> spPram )
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

bool DeferredShader::PreProcessOfRender(std::shared_ptr<SubMesh> mesh, std::shared_ptr<Material>materials)
{
	// GeometryBuffferに書き込み
	sRENDER_DEVICE_MANAGER->GetGeometryBuffer()->SetRenderTargets(sRENDER_DEVICE_MANAGER->GetImmediateContext());
	bool result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	UINT bufferNumber;

	MatrixBufferType* matrixPtr;
	MaterialBufferType* materialPtr;
	HFMATRIX world, view, proj;

	sRENDER_DEVICE_MANAGER->GetTransform(&world, HFTS_WORLD);
	sRENDER_DEVICE_MANAGER->GetTransform(&view, HFTS_VIEW);
	sRENDER_DEVICE_MANAGER->GetTransform(&proj, HFTS_PERSPECTIVE );

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

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Unmap(m_constantBuffers[1]->Get(), 0);



	bufferNumber = 0;

	// テクスチャをセット

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShaderResources(0, 1, materials->GetDiffuseTexture()->GetSharderResorceView().GetAddressOf());
	// マトリクスをセット
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetConstantBuffers(bufferNumber, 1, m_constantBuffers[0]->GetAddressOf());
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetConstantBuffers(0, 1, m_constantBuffers[1]->GetAddressOf());


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
	sRENDER_DEVICE_MANAGER->TurnZBufferOn();

	return true;
}

void DeferredShader::CreateAndRegisterGraphicsCommand(std::shared_ptr<BaseRenderMeshObject> renderObject, UINT element)
{
	std::shared_ptr<RenderMeshCommmand> rmCommand = std::make_shared<RenderMeshCommmand>();
	rmCommand->SetRenderMeshElement(element);
	rmCommand->SetRenderObject(renderObject);
	rmCommand->SetGraphicsPriority(m_graphicsPriority);

	sTASK_SYSTEM->RegisterGraphicsCommand(rmCommand);
}
