
#include "../Public/DefaultSpriteShader.h"
#include "../../../../RenderDevice/Basic/Public/RendererManager.h"

using namespace std;

DefaultSpriteShader::DefaultSpriteShader()
{
	DefaultSpriteShader::Setup();
}

DefaultSpriteShader::~DefaultSpriteShader()
{
}

bool DefaultSpriteShader::Setup()
{
	m_spVertexLayout = std::shared_ptr<BaseVertexLayout>(new BaseVertexLayout);
	// Initialize the vertex and pixel shaders.
	bool result;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	UINT numElements;
	
	
	m_constantBuffers.push_back(std::shared_ptr<ConstantBuffer>(new ConstantBuffer));


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
	polygonLayout[1].AlignedByteOffset = 0;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	result = sRENDER_DEVICE_MANAGER->CreateVertexShaderFromFile
		(
			m_cpVertexShader,
			_T("Resource/Shader/HLSL/Polygon2D.hlsl"),
			"VS_Main",
			"vs_4_0",m_spVertexLayout->GetMain(),polygonLayout, numElements
			);


	if (FAILED(result))
	{
		return false;
	}

	result = sRENDER_DEVICE_MANAGER->CreatePixelShaderFromFile
		(
			m_cpPixelShader, m_cpPSClassLinkage,
			_T("Resource/Shader/HLSL/Polygon2D.hlsl"),
			"PS_Main"
			,
			"ps_4_0",
			false);


	if ((!result))
	{
		return false;
	}

	result = sRENDER_DEVICE_MANAGER->CreateSamplerState(m_cpSamplerState, D3D11_FILTER_MIN_MAG_MIP_LINEAR, 1);
	
	if ((!result))
	{
		return false;
	}

	m_constantBuffers.resize(1);
	m_constantBuffers[0] = shared_ptr<ConstantBuffer>(new ConstantBuffer);
	HFMATRIX mat;
	result = sRENDER_DEVICE_MANAGER->CreateConstantBuffer(m_constantBuffers[0], &mat, sizeof(HFMATRIX), 0);

	return result;
}

void DefaultSpriteShader::Destroy()
{
}

bool DefaultSpriteShader::PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials)
{
	HRESULT hr;
	hr = E_FAIL;

	vector<shared_ptr<VertexBuffer>> vertexBuffers;
	DWORD semantics[2]=
	{
		HF_SEMANTICS_POSITION,
		HF_SEMANTICS_TEXCOORD0
	};

	UINT stride[2] = 
	{
		sizeof(HFVECTOR3),
		sizeof(HFVECTOR2)
	};
	UINT offset[2] =
	{
		0,0
	};


	HFMATRIX world, view, ortho;
	HFMATRIX scale, trans, d3dmMatrixPos;
	sRENDER_DEVICE_MANAGER->GetTransform(&world, HFTS_WORLD);
	sRENDER_DEVICE_MANAGER->GetTransform(&view, HFTS_WORLD);
	sRENDER_DEVICE_MANAGER->GetTransform(&ortho, HFTS_ORTHOGONAL);		
	HFMatrixLookAtLH(&view, &HFVECTOR3(0, 0, -10), &HFVECTOR3(0, 0, 0), &HFVECTOR3(0, -1, 0));

	HFMatrixTranslation(&d3dmMatrixPos, -sRENDER_DEVICE_MANAGER->GetScreenSize().x*0.5, sRENDER_DEVICE_MANAGER->GetScreenSize().y * 0.5, 0.0f);
	

	HFMatrixOrthoLH
		(
			&ortho,
			sRENDER_DEVICE_MANAGER->GetScreenSize().x,
			sRENDER_DEVICE_MANAGER->GetScreenSize().y,
			0.1,
			10000);
	//HFMatrixOrthoLH(&ortho, sRENDER_DEVICE_MANAGER->GetScreenSize().x, sRENDER_DEVICE_MANAGER->GetScreenSize().y, 1, 10000);

	HFMATRIX wvp;
	//D3DXMatrixMultiply(&ortho, &d3dmMatrixPos, &ortho);

	wvp = world * view * ortho;
	wvp = HFMatrixTranspose(wvp);
	m_constantBuffers[0]->SetData(&wvp,sizeof(HFMATRIX),1,BaseBuffer::ACCESS_FLAG::WRITEONLY);


	shape->GetVertexBuffers(2,semantics,vertexBuffers);
	sRENDER_DEVICE_MANAGER->SetIndexBuffer(shape->GetIndexBuffer(),0);
	sRENDER_DEVICE_MANAGER->SetVertexBuffer(0,2,vertexBuffers,stride,offset);
	sRENDER_DEVICE_MANAGER->SetConstantBuffers(HF_D3D11_VERTEX_SHADER, 0, 1, m_constantBuffers);
	
	
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShaderResources(0, 1, materials->GetDiffuseTexture()->GetSharderResorceView().GetAddressOf());

	return hr;
}


bool DefaultSpriteShader::Render()
{
	HRESULT hr;
	hr = E_FAIL;
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetShader(m_cpVertexShader.Get(), nullptr, 0);

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShader(m_cpPixelShader.Get(), NULL, 0);
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetInputLayout(m_spVertexLayout->GetMain().Get());
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetSamplers(0, 1, m_cpSamplerState.GetAddressOf());
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DrawIndexed(/*indexCount*/6, 0, 0);

	return hr;
}

bool DefaultSpriteShader::PostProcessOfRender()
{
	HRESULT hr;
	hr = E_FAIL;
	sRENDER_DEVICE_MANAGER->SetBackCullingState();

	return hr;
}
