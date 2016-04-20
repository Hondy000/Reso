﻿
#include "../Public/SimplePolygon3DShader.h"
#include "../../../../RenderDevice/Basic/Public/RendererManager.h"
#include "../../../../VertexLayout/Public/BaseVertexLayout.h"
#include "../../../../RenderObject/Public/BaseRenderObject.h"
#include "../../../../Texture/Public/BaseTexture2D.h"
#include "../../../../RenderDevice/Basic/Public/BaseRenderDeviceManager.h"
#include "../../../../RenderDevice/DirectX/ver.11/Public/DirectX11RenderDeviceManager.h"
using namespace std;

bool SimplePolygon3DShader::Setup()
{
	HRESULT hr;
	m_spVertexLayout = std::shared_ptr<BaseVertexLayout>(new BaseVertexLayout);

	D3D11_INPUT_ELEMENT_DESC layput[2];
	layput[0].SemanticName = "POSITION";
	layput[0].SemanticIndex = 0;
	layput[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	layput[0].InputSlot = 0;
	layput[0].AlignedByteOffset = 0;
	layput[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layput[0].InstanceDataStepRate = 0;

	layput[1].SemanticName = "TEXCOORD";
	layput[1].SemanticIndex = 0;
	layput[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	layput[1].InputSlot = 0;
	layput[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	layput[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layput[1].InstanceDataStepRate = 0;

	// 使う固定バッファは1
	m_constantBuffers.resize(1);
	m_constantBuffers[0] = std::shared_ptr<ConstantBuffer>(new ConstantBuffer);

	hr = sRENDER_DEVICE_MANAGER->CreatePixelShaderFromFile(m_cpPixelShader, m_cpPSClassLinkage, _T("Resource/Shader/HLSL/SimplePolygon3D.hlsl"), "PS_Main", "ps_4_0_level_9_1",false);

	hr = sRENDER_DEVICE_MANAGER->CreateVertexShaderFromFile(m_cpVertexShader, _T("Resource/Shader/HLSL/SimplePolygon3D.hlsl"), "VS_Main", "vs_4_0_level_9_1", m_spVertexLayout->GetMain(), layput, 2);

	// 空で固定バッファを用意
	HFMATRIX mat[3];
	hr = m_constantBuffers[0]->SetData(mat, sizeof(HFMATRIX), 3, BaseBuffer::ACCESS_FLAG::WRITEONLY);

	return  hr;
}

void SimplePolygon3DShader::Destroy()
{
}

bool SimplePolygon3DShader::PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials)
{
	bool result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	UINT bufferNumber;


	HFMATRIX world, view, proj;

	sRENDER_DEVICE_MANAGER->GetTransform(&world, HFTS_WORLD);
	sRENDER_DEVICE_MANAGER->GetTransform(&view, HFTS_VIEW);
	sRENDER_DEVICE_MANAGER->GetTransform(&proj, HFTS_PERSPECTIVE );

	// Lock the constant buffer so it can be written to.
	result = sRENDER_DEVICE_MANAGER->GetImmediateContext()->Map(m_constantBuffers[0]->Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	HFMATRIX* wvp = (HFMATRIX*)(mappedResource.pData);
	*wvp = world*view*proj;
	*wvp = HFMatrixTranspose( *wvp);

	// Unlock the constant buffer.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Unmap(m_constantBuffers[0]->Get(), 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// テクスチャをセット
		std::shared_ptr<BaseTexture2D> spTexture;					
		////GeneralFactory<BaseTexture2D>::GetInstance().Get(index.searchID, index.pMaterialIndex[0], spTexture);
		sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShaderResources(0, 1, materials->GetDiffuseTexture()->GetSharderResorceView().GetAddressOf());


	// マトリクスをセット
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetConstantBuffers(bufferNumber, 1, m_constantBuffers[0]->GetAddressOf());

	const UINT stride = shape->GetStride();
	const UINT offset = 0;

	// 頂点バッファのセット
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetVertexBuffers(0, 1, shape->GetVertexBuffers()[0]->GetAddressOf(), &stride, &offset);

	// インデックスバッファのセット
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetIndexBuffer(shape->GetIndexBuffer()->Get(), DXGI_FORMAT_R32_UINT, 0);

	// プリミティブ タイプおよびデータの順序に関する情報を設定
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	return 0;
}

bool SimplePolygon3DShader::Render()
{
	bool result = E_FAIL;

	// Set the vertex input layout.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetInputLayout(m_spVertexLayout->GetMain().Get());

	// Set the vertex and pixel shaders that will be used to render.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetShader(m_cpVertexShader.Get(), NULL, 0);
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShader(m_cpPixelShader.Get(), NULL, 0);

	// Set the sampler states in the pixel shader.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetSamplers(0, 1, m_cpSamplerState.GetAddressOf());

	// Render the geometry.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DrawIndexed(6, 0, 0);

	return result;
}

bool SimplePolygon3DShader::PostProcessOfRender()
{
	return bool();
}

