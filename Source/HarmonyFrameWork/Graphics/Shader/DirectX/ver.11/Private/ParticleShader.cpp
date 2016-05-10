/**=================================================================================================
 * @file Source\HarmonyFrameWork\Graphics\Shader\DirectX\ver.11\Private\ParticleShader.cpp
 *
 * @brief Implements the particle shader class.
 *===============================================================================================**/

#include "..\Public\ParticleShader.h"
#include "..\..\..\..\RenderDevice\Basic\Public\RendererManager.h"
#include "..\..\..\..\ParticleSystem\Public\BaseEmitter.h"


struct IBUFFER0
{
	HFMATRIX instanceMatWVP;
};


struct CBUFFER0
{
	HFVECTOR4 lightDirection;
};

/**=================================================================================================
 * @fn ParticleShader::ParticleShader(const ParticleShader&)
 *
 * @brief Initializes a new instance of the ParticleShader class.
 *
 * @author Kazuyuki
 *
 * @param parameter1 The first parameter.
 *===============================================================================================**/

ParticleShader::ParticleShader(const ParticleShader&)
{

}

/**=================================================================================================
 * @fn ParticleShader::ParticleShader()
 *
 * @brief Initializes a new instance of the ParticleShader class.
 *
 * @author Kazuyuki
 *===============================================================================================**/

ParticleShader::ParticleShader()
{

}

/**=================================================================================================
 * @fn ParticleShader::~ParticleShader()
 *
 * @brief Finalizes an instance of the ParticleShader class.
 *
 * @author Kazuyuki
 *===============================================================================================**/

ParticleShader::~ParticleShader()
{

}

/**=================================================================================================
 * @fn bool ParticleShader::Setup()
 *
 * @brief Setups this object.
 *
 * @author Kazuyuki
 *
 * @return true if it succeeds, false if it fails.
 *===============================================================================================**/

bool ParticleShader::Setup()
{
	HRESULT hr = E_FAIL;

	D3D11_BUFFER_DESC BufferDesc;



	// create vertex shader

	m_spVertexLayout = std::make_shared<BaseVertexLayout>();

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       1, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// 各インスタンスのパラメータ
		{ "MATRIX",   0, DXGI_FORMAT_R32G32B32A32_FLOAT, 2,  0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "MATRIX",   1, DXGI_FORMAT_R32G32B32A32_FLOAT, 2, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "MATRIX",   2, DXGI_FORMAT_R32G32B32A32_FLOAT, 2, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "MATRIX",   3, DXGI_FORMAT_R32G32B32A32_FLOAT, 2, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1 }
	};
	sRENDER_DEVICE_MANAGER->CreateVertexShaderFromFile(m_cpVertexShader, "Resource/Shader/HLSL/ParticleShader.hlsl", "VS_Main", "vs_4_0_level_9_1", m_spVertexLayout->GetMain(), layout,6);


	// create pixel shader
	sRENDER_DEVICE_MANAGER->CreatePixelShaderFromFile(m_cpPixelShader, m_cpPSClassLinkage,"Resource/Shader/HLSL/ParticleShader.hlsl", "PS_Main", "ps_4_0_level_9_1",false);


 	// create constant buffer
	m_constantBuffers.resize(1);
	m_constantBuffers[0] = std::make_shared<ConstantBuffer>();
	m_constantBuffers[0]->SetData(NULL, sizeof(CBUFFER0), 1, BaseBuffer::ACCESS_FLAG::WRITEONLY);


	// create sampler state
	if (sRENDER_DEVICE_MANAGER->CreateSamplerState(m_cpSamplerState, D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR, 1))
	{
		return false;
	}

	return true;
}

bool ParticleShader::WriteInstanceData(std::shared_ptr<SubMesh> subMesh, void* pData, size_t stride,UINT count)
{


	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = E_FAIL;
	hr = sRENDER_DEVICE_MANAGER->GetImmediateContext()->Map(subMesh->GetVertexBuffers()[2]->Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	if(FAILED(hr))
	{
		return false;
	}
	// Get matrix pointer 

	HFMATRIX* pMat = (HFMATRIX*)(mappedResource.pData);
	HFMATRIX* updateData = (HFMATRIX*)(pData);
	// set transpose data
	for (int i = 0; i < count; i++)
	{
		pMat[i] = updateData[i];
	}

	// Unlock the constant buffer.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Unmap(m_constantBuffers[0]->Get(), 0);

	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

/**=================================================================================================
 * @fn void ParticleShader::Destroy()
 *
 * @brief Destroys this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void ParticleShader::Destroy()
{

}

/**=================================================================================================
 * @fn bool ParticleShader::PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials)
 *
 * @brief Pre process of render.
 *
 * @author Kazuyuki
 *
 * @param shape		 The shape.
 * @param parameter2 The second parameter.
 *
 * @return true if it succeeds, false if it fails.
 *===============================================================================================**/

bool ParticleShader::PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials)
{
	bool result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	UINT bufferNumber;


	HFMATRIX world, view, proj;

	// Lock the constant buffer so it can be written to.
	result = sRENDER_DEVICE_MANAGER->GetImmediateContext()->Map(m_constantBuffers[0]->Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get matrix pointer 

	CBUFFER0* buffer0 = (CBUFFER0*)(mappedResource.pData);
	// set transpose data
	buffer0->lightDirection = HFVECTOR4(1, 0, 0, 0);

	// Unlock the constant buffer.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Unmap(m_constantBuffers[0]->Get(), 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;





	// テクスチャをセット
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShaderResources(0, 1, materials->GetDiffuseTexture()->GetSharderResorceView().GetAddressOf());


	// マトリクスをセット
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetConstantBuffers(bufferNumber, 1, m_constantBuffers[0]->GetAddressOf());

	const UINT stride[3] = { sizeof(HFVECTOR3) , sizeof(HFVECTOR2),sizeof(HFMATRIX) };
	const UINT offset[3] = {0,0,0};

	const DWORD sematics[] = { HF_SEMANTICS_POSITION , HF_SEMANTICS_TEXCOORD0 , HF_SEMANTICS_MATRIX0 };

	std::vector<std::shared_ptr<VertexBuffer>> bufferArray;
	shape->GetVertexBuffers(3,sematics, bufferArray);
	// 頂点バッファのセット
	for (int i = 0;i <3;i++)
	{
		sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetVertexBuffers(i, 1, bufferArray[i]->GetAddressOf(), &stride[i], &offset[i]);

	}
	// インデックスバッファのセット
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetIndexBuffer(shape->GetIndexBuffer()->Get(), DXGI_FORMAT_R32_UINT, 0);

	// プリミティブ タイプおよびデータの順序に関する情報を設定
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// get index count
	m_indexCount = shape->GetIndexCount();

	return true;
}

/**=================================================================================================
 * @fn bool ParticleShader::Render()
 *
 * @brief Renders this object.
 *
 * @author Kazuyuki
 *
 * @return true if it succeeds, false if it fails.
 *===============================================================================================**/

bool ParticleShader::Render()
{
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetShader(m_cpVertexShader.Get(), nullptr, 0);

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShader(m_cpPixelShader.Get(), NULL, 0);
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetInputLayout(m_spVertexLayout->GetMain().Get());
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetSamplers(0, 1, m_cpSamplerState.GetAddressOf());
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DrawIndexed(m_indexCount, 0, 0);


	return true;
}

/**=================================================================================================
 * @fn bool ParticleShader::PostProcessOfRender()
 *
 * @brief Posts the process of render.
 *
 * @author Kazuyuki
 *
 * @return true if it succeeds, false if it fails.
 *===============================================================================================**/

bool ParticleShader::PostProcessOfRender()
{

	return true;
}

