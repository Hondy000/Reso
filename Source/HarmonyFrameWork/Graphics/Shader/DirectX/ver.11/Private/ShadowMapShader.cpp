#include "..\Public\ShadowMapShader.h"
#include "..\..\..\..\RenderDevice\Basic\Public\RendererManager.h"
#include "..\..\..\..\RenderObject\Public\SubMesh.h"
#include "..\..\..\..\Lighting\Public\LightManager.h"
#include "..\..\..\..\RenderObject\Public\BaseRenderMeshObject.h"
#include "..\Public\ColorVertexSpriteShader.h"
#include "..\..\..\..\Public\BaseGraphicsCommand.h"

struct CBUFFER
{

	HFMATRIX matLightWorldViewProj;

};

ShadowMapShader::ShadowMapShader()
{

}

ShadowMapShader::~ShadowMapShader()
{

}

bool ShadowMapShader::Setup()
{
	m_graphicsPriority = HF_SHADOW_MAPPING_SHADER;
	m_constantBuffers.resize(1);
	m_constantBuffers[0] = std::make_shared<ConstantBuffer>();
	m_spVertexLayout = std::make_shared<BaseVertexLayout>();
	// ラスタライザーステートを作成する
	sRENDER_DEVICE_MANAGER->SetDefaultRasterize();

	// 深度ステンシルステートを作成する
	sRENDER_DEVICE_MANAGER->SetDepthStencilState( TRUE, D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL);

	// ブレンドステートを作成する
	sRENDER_DEVICE_MANAGER->SetBlendState( &sRENDER_DEVICE_MANAGER->GetDefaultBlendDesc(), 1,false);

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// シェーダーを作成する
	sRENDER_DEVICE_MANAGER->CreateVertexShaderFromFile( m_cpVertexShader,("Resource/Shader/HLSL/ShadowMappingShader.hlsl"), "VS_Main", "vs_5_0",m_spVertexLayout->GetMain(),layout,_countof(layout));



	m_constantBuffers[0]->SetData(nullptr,sizeof(CBUFFER),1, BaseBuffer::ACCESS_FLAG::WRITEONLY );

	return true;

}

void ShadowMapShader::Destroy()
{

}

bool ShadowMapShader::PreProcessOfRender(std::shared_ptr<BaseRenderMeshObject> shape)
{
	return true;
}

bool ShadowMapShader::PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials)
{
	{
		

		switch (0)
		{
		case 0:
		{
			// レンダーターゲットビューと深度ステンシルビューとビューポートを切り替える

			D3D11_VIEWPORT Viewport[1];
			Viewport[0].TopLeftX = 0;
			Viewport[0].TopLeftY = 0;
			Viewport[0].Width = (FLOAT)sRENDER_DEVICE_MANAGER->GetScreenSize().x;
			Viewport[0].Height = (FLOAT)sRENDER_DEVICE_MANAGER->GetScreenSize().x;
			Viewport[0].MinDepth = 0.0f;
			Viewport[0].MaxDepth = 1.0f;
			sRENDER_DEVICE_MANAGER->GetImmediateContext()->RSSetViewports(1, Viewport);
		}
		break;
		}

	}
	bool result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	UINT bufferNumber;

	CBUFFER* matPtr;
	HFMATRIX world, view, proj;

	sRENDER_DEVICE_MANAGER->GetTransform(&world, HFTS_WORLD);
	sRENDER_DEVICE_MANAGER->GetTransform(&view, HFTS_VIEW);
	sRENDER_DEVICE_MANAGER->GetTransform(&proj, HFTS_PERSPECTIVE);


	std::shared_ptr<HFGraphics::DirectinalLight> dlight;
	HFGraphics::LightManager::GetInstance()->GetDirectionalLight(dlight);
	view = HFMATRIX::CreateLookAt(HFVECTOR3(0,1,-1), HFVECTOR3(0,0,0), HFVECTOR3(0, 1, 0));

	proj = HFMATRIX::CreateOrthographic((float)16, (float)9 , 0.1f, 800.0f);
	// Lock the constant buffer so it can be written to.
	result = sRENDER_DEVICE_MANAGER->GetImmediateContext()->Map(m_constantBuffers[0]->Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	matPtr = (CBUFFER*)mappedResource.pData;
	HFMATRIX wvp;
	wvp = world*view*proj;
	// Transpose the matrices to prepare them for the shader.
	matPtr->matLightWorldViewProj = HFMatrixTranspose(wvp);

	// Unlock the constant buffer.
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Unmap(m_constantBuffers[0]->Get(), 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;


	// マトリクスをセット
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetConstantBuffers(bufferNumber, 1, m_constantBuffers[0]->GetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11Buffer>  buffers[1];
	buffers[0] = shape->GetVertexBuffers()[0]->GetBuffer();

	UINT stride[1] = { sizeof(HFVECTOR3) };
	UINT offset[1] = { 0 };

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetVertexBuffers(0, 1, buffers[0].GetAddressOf(), stride, offset);

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetIndexBuffer(shape->GetIndexBuffer()->Get(), DXGI_FORMAT_R32_UINT, 0);
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	m_indexCount = shape->GetIndexCount();
	sRENDER_DEVICE_MANAGER->SetBackBufferRenderTarget();

	return true;

}

bool ShadowMapShader::Render()
{
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetShader(m_cpVertexShader.Get(), NULL, 0);
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShader(nullptr, NULL, 0);
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetInputLayout(m_spVertexLayout->GetMain().Get());
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DrawIndexed(m_indexCount,0,0);

	return true;

}

bool ShadowMapShader::PostProcessOfRender()
{
	sRENDER_DEVICE_MANAGER->GetSRViewFromDepthStencil();
	D3D11_VIEWPORT Viewport[1];
	Viewport[0].TopLeftX = 0;
	Viewport[0].TopLeftY = 0;
	Viewport[0].Width = (FLOAT)sRENDER_DEVICE_MANAGER->GetScreenSize().x;
	Viewport[0].Height = (FLOAT)sRENDER_DEVICE_MANAGER->GetScreenSize().y;
	Viewport[0].MinDepth = 0.0f;
	Viewport[0].MaxDepth = 1.0f;
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->RSSetViewports(1, Viewport);

	return true;
}

void ShadowMapShader::CreateAndRegisterGraphicsCommand(std::shared_ptr<BaseRenderMeshObject> renderObject, UINT element)
{

}
