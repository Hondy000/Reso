
#include "..\Public\GPUParticleShader.h"
#include "..\..\..\..\Public\GraphicsTypes.h"
#include "..\..\..\..\RenderDevice\Basic\Public\RendererManager.h"
#include "..\..\..\..\..\Utility\Public\HFString.h"


// ���_��`
typedef struct _VERTEX
{
	HFVECTOR3 pos;  // �ʒu���W
	HFVECTOR3 v0;   // �����x
	float time;       // ����
}VERTEX;

// �萔��`
typedef struct _CBUFFER
{
	HFMATRIX  g_matWVP;    // ���[���h �~ �r���[ �~ �ˉe �s��
	float       g_Scale;     // �p�[�e�B�N���̃X�P�[�����O�l
	float       g_LimitTime; // ���Ԃ̌��E�l( ���̒l�𒴂���Ə����l�ɖ߂� )
	float       g_dummy2;    // ���g�p
	float       g_dummy3;    // ���g�p
}CBUFFER;

//// �^�[�Q�b�g���o�̓o�b�t�@�[
//ID3D11Buffer* g_pSOBuffer[2] = { NULL, NULL };
//// ���_�V�F�[�_�[
//ID3D11VertexShader*   g_pVertexShader = NULL;
//// ���̓��C�A�E�g
//ID3D11InputLayout*    g_pLayout = NULL;
//// �萔�o�b�t�@
//ID3D11Buffer* g_pConstantBuffers = NULL;
//// �W�I���g���V�F�[�_�[( �p�[�e�B�N���̍��W�X�V�p�A�`��p )
//ID3D11GeometryShader* g_pGeometryShader[2] = { NULL, NULL };
//// �s�N�Z���V�F�[�_�[
//ID3D11PixelShader* g_pPixelShader = NULL;
//// �T���v���[�X�e�[�g
//ID3D11SamplerState* g_pSamplerState = NULL;
//// �V�F�[�_�[���\�[�X�r���[
//ID3D11ShaderResourceView* g_pSRView = NULL;
// �p�[�e�B�N����
#define NUM_PARTICLE 100


GPUParticleShader::GPUParticleShader(const GPUParticleShader&)
{

}


GPUParticleShader::GPUParticleShader()
{

}

GPUParticleShader::~GPUParticleShader()
{

}

bool GPUParticleShader::Setup()
{


	HRESULT hr = E_FAIL;
	m_cpGeometryShaders.resize(2);
	for (int i = 0 ;i < m_cpGeometryShaders.size();i++)
	{
		Microsoft::WRL::ComPtr<::ID3D11GeometryShader> shader;
		m_cpGeometryShaders[i] = shader;
	}

	m_constantBuffers.resize(2);
	for (int i = 0; i < m_constantBuffers.size(); i++)
	{
		std::shared_ptr<ConstantBuffer> buffer = std::make_shared<ConstantBuffer>();
		m_constantBuffers[i] = buffer;
	}

	// �p�[�e�B�N���̏����l��ݒ�
	VERTEX v[NUM_PARTICLE];
	for (int i = 0; i < NUM_PARTICLE; i++)
	{
		v[i].pos = HFVECTOR3(0.0f, 0.0f, 0.0f),
			v[i].v0 = HFVECTOR3((float)(rand() % 50 - 25) * 0.3f, (float)(rand() % 50) * 0.5f, (float)(rand() % 50 - 25) * 0.3f);
		v[i].time = (float)(rand() % 100) * 0.1f;
	};
	// �^�[�Q�b�g���o�̓o�b�t�@�[���쐬
	D3D11_BUFFER_DESC BufferDesc;
	::ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.ByteWidth = sizeof(v);  // �o�b�t�@�T�C�Y
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_STREAM_OUTPUT;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA mappedResource;
	mappedResource.pSysMem = v;  // �o�b�t�@�E�f�[�^�̏����l
	mappedResource.SysMemPitch = 0;
	mappedResource.SysMemSlicePitch = 0;
	for (int i = 0; i < m_cpGeometryShaders.size(); i++)
	{
		hr = sRENDER_DEVICE_MANAGER->GetDevice()->CreateBuffer(&BufferDesc, &mappedResource, m_constantBuffers[i]->GetAddressOf());
		if (FAILED(hr))
		{
		}
	}

	// ���_�V�F�[�_�[�̍쐬

	m_spVertexLayout = std::make_shared<BaseVertexLayout>();

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },  // �ʒu���W
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },  // �����x
		{ "TEXCOORD", 0, DXGI_FORMAT_R32_FLOAT,       0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }   // ����
	};

#ifndef UNCOMPILED_SHADER
	hr = g_pD3D11User->CreateVertexShaderFromMemory(&g_pVertexShader, g_VS0_Main, sizeof(g_VS0_Main), &g_pLayout, layout, _countof(layout));
	if (FAILED(hr))
	{

	}
#else
	hr = sRENDER_DEVICE_MANAGER->CreateVertexShaderFromFile(this->m_cpVertexShader,
		_T("Resource/Shader/HLSL/GPUParticleShader.hlsl"), "VS0_Main", "vs_4_0",
		m_spVertexLayout->GetMain(), layout, _countof(layout));
	if (FAILED(hr))
	{

	}
#endif

	// �^�[�Q�b�g���o�̓o�b�t�@�[�̒�`
	// D3D11_SO_DECLARATION_ENTRY
	// SemanticName�Ɏw��\�Ȓl�́A"POSITION"�A"NORMAL"�A�܂��� "TEXCOORD0" �炵���B
	D3D11_SO_DECLARATION_ENTRY decl[] = {
		{ 0, "POSITION",  0, 0, 3, 0 },
		{ 0, "NORMAL",    0, 0, 3, 0 },
		{ 0, "TEXCOORD",  0, 0, 1, 0 },
	};

	UINT stride[] = { sizeof(VERTEX) };

	// �X�g���[���A�E�g�v�b�g�Ƃ��ăW�I���g���V�F�[�_�[���쐬
#ifndef UNCOMPILED_SHADER
	hr = g_pD3D11User->CreateGeometryShaderWithStreamOutputFromMemory(
		&g_pGeometryShader[0],
		g_GS0_Main,
		sizeof(g_GS0_Main),
		decl,
		_countof(decl),
		stride,
		_countof(stride)
	);
#else
	hr = sRENDER_DEVICE_MANAGER->CreateGeometryShaderWithStreamOutputFromFile(
		m_cpGeometryShaders[0],
		_T("Resource/Shader/HLSL/GPUParticleShader.hlsl"),
		"GS0_Main",
		"gs_4_0",
		decl,
		_countof(decl),
		stride,
		_countof(stride)
	);
#endif

	// �`��p�̃W�I���g���V�F�[�_�[���쐬����
#ifndef UNCOMPILED_SHADER
	hr = g_pD3D11User->CreateGeometryShaderFromMemory(&g_pGeometryShader[1], g_GS1_Main, sizeof(g_GS1_Main));
	if (FAILED(hr))
#else
	hr = sRENDER_DEVICE_MANAGER->CreateGeometryShaderFromFile(m_cpGeometryShaders[1],
		("Resource/Shader/HLSL/GPUParticleShader.hlsl"),  "GS1_Main", "gs_4_0");
	if (FAILED(hr))
	{

	}
#endif

	// �s�N�Z���V�F�[�_�[���쐬����
#ifndef UNCOMPILED_SHADER
	hr = g_pD3D11User->CreatePixelShaderFromMemory(&g_pPixelShader, g_PS1_Main, sizeof(g_PS1_Main));
	if (FAILED(hr))
	{

	}
#else
	hr = sRENDER_DEVICE_MANAGER->CreatePixelShaderFromFile(m_cpPixelShader,
		m_cpPSClassLinkage,
		("Resource/Shader/HLSL/GPUParticleShader.hlsl"),
		"PS1_Main", "ps_4_0", false);
	if (FAILED(hr))
	{

	}
#endif

	// �萔�o�b�t�@���쐬����B
	hr = sRENDER_DEVICE_MANAGER->CreateConstantBuffer(m_constantBuffers[0], NULL, sizeof(CBUFFER), D3D11_CPU_ACCESS_WRITE);
	if (FAILED(hr))
	{

	}

	// �T���v���[�X�e�[�g�̐ݒ�
	{
		D3D11_SAMPLER_DESC samplerDesc;
		::ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;         // �T���v�����O���Ɏg�p����t�B���^�B�����ł͈ٕ����t�B���^�[���g�p����B
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;     // 0 �` 1 �͈̔͊O�ɂ��� u �e�N�X�`���[���W�̕`����@
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;     // 0 �` 1 �͈̔͊O�ɂ��� v �e�N�X�`���[���W�̕`����@
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;     // 0 �` 1 �͈̔͊O�ɂ��� w �e�N�X�`���[���W�̕`����@
		samplerDesc.MipLODBias = 0;                            // �v�Z���ꂽ�~�b�v�}�b�v ���x������̃o�C�A�X
		samplerDesc.MaxAnisotropy = 16;                        // �T���v�����O�Ɉٕ�����Ԃ��g�p���Ă���ꍇ�̌��E�l�B�L���Ȓl�� 1 �` 16 �B
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;  // ��r�I�v�V�����B
		::CopyMemory(samplerDesc.BorderColor, &HFVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), sizeof(HFVECTOR4)); // ���E�F
		samplerDesc.MinLOD = 0;                                // �A�N�Z�X�\�ȃ~�b�v�}�b�v�̉����l
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;                // �A�N�Z�X�\�ȃ~�b�v�}�b�v�̏���l
	//	hr = sRENDER_DEVICE->CreateSamplerState(&samplerDesc, &g_pSamplerState);
		if (FAILED(hr))
		{

		}
	}

// 	�摜�t�@�C����ǂݍ���Ńe�N�X�`���[���\�[�X�r���[���쐬����
// 		{
// 			D3DX11_IMAGE_LOAD_INFO info;
// 			::ZeroMemory(&info, sizeof(D3DX11_IMAGE_LOAD_INFO));
// 			info.Width = D3DX11_DEFAULT;
// 			info.Height = D3DX11_DEFAULT;
// 			info.Depth = D3DX11_DEFAULT;
// 			info.FirstMipLevel = D3DX11_DEFAULT;
// 			info.MipLevels = 1;
// 			info.Usage = D3D11_USAGE_DEFAULT;
// 			info.BindFlags = D3D11_BIND_SHADER_RESOURCE;
// 			info.CpuAccessFlags = 0;
// 			info.MiscFlags = 0;
// 			info.Format = DXGI_FORMAT_FROM_FILE;
// 			info.Filter = D3DX11_FILTER_POINT;
// 			info.MipFilter = D3DX11_FILTER_POINT;
// 			info.pSrcInfo = NULL;
// 			// �p�[�e�B�N���̃e�N�X�`���[
// 			hr = D3DX11CreateShaderResourceViewFromFile(g_pD3D11User->m_D3DDevice, _T("res\\Smoke.dds"), &info, NULL, &g_pSRView, NULL);
// 			if (FAILED(hr))
// 			{
// 	
// 			}
// 		}

	hr = S_OK;


	return true;
}


void GPUParticleShader::Destroy()
{

}

bool GPUParticleShader::PreProcessOfRender(std::shared_ptr<SubMesh> mesh, std::shared_ptr<Material>materials)
{

	return true;
}

bool GPUParticleShader::Render()
{
	HRESULT hr = E_FAIL;

	HFMATRIX matWVP, matWorld, matView, matProj;
	HFVECTOR3 v;

	// �萔�o�b�t�@
	CBUFFER* cbuffer = nullptr;
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	sRENDER_DEVICE_MANAGER->GetTransform(&matView, HFTS_VIEW);
	sRENDER_DEVICE_MANAGER->GetTransform(&matProj, HFTS_PERSPECTIVE);

	// ���[���h�s��
	matWorld = HFMATRIX::Identity;

	// �s��̍���
	matWVP = matWorld * matView * matProj;

	hr = sRENDER_DEVICE_MANAGER->GetImmediateContext()->Map(m_constantBuffers[0]->Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	
	cbuffer = (CBUFFER*)(mappedResource.pData);
	// �V�F�[�_�[���ł͗�D��ɂ��Ă���̂œ]�u�s����쐬����B
	
	 cbuffer->g_matWVP = matWVP.Transpose();
	// �X�P�[�����O�l
	cbuffer->g_Scale = 3.0f;

	// �^�C�}�[�̍ő�l
	cbuffer->g_LimitTime = 10.0f;

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Unmap(m_constantBuffers[0]->Get(), 0);
	

	// *********************************************************************************************
	// �p�[�e�B�N���̍X�V
	// *********************************************************************************************
	
	// �^�[�Q�b�g�o�̓o�b�t�@�[�����ւ���
//ID3D11Buffer *pB = g_pSOBuffer[0];
//g_pSOBuffer[0] = g_pSOBuffer[1];
//g_pSOBuffer[1] = pB;

	// ���̓A�Z���u���[ �X�e�[�W�ɒ��_�o�b�t�@�[�̔z����o�C���h����B
	// ID3D11DeviceContext::IASetVertexBuffers
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	//sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetVertexBuffers(0, 1, &g_pSOBuffer[0], &stride, &offset);

	// �o�̓o�b�t�@�[�̔z��̃I�t�Z�b�g�l
	// �p�C�v���C���̃X�g���[���o�̓X�e�[�W�Ŏg�p�����^�[�Q�b�g�o�̓o�b�t�@�[��ݒ肵�܂��B
	// ID3D11DeviceContext::SOSetTargets
	//sRENDER_DEVICE_MANAGER->GetImmediateContext()->SOSetTargets(1, &g_pSOBuffer[1], &offset);

	// �v���~�e�B�u �^�C�v����уf�[�^�̏����Ɋւ������ݒ�
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// �s�N�Z���V�F�[�_�[�𖳌��ɂ�����ԂŐ[�x�X�e���V����L���ɂ��Ă���ƃG���[�ɂȂ�̂Ŗ����ɂ���
	ID3D11DepthStencilState*  pDepthStencilState = NULL;
	D3D11_DEPTH_STENCIL_DESC ddsDesc;
	UINT StencilRef;
	::ZeroMemory(&ddsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->OMGetDepthStencilState(&pDepthStencilState, &StencilRef);
	pDepthStencilState->GetDesc(&ddsDesc);
	ddsDesc.DepthEnable = FALSE;  // �[�x�e�X�g�𖳌��ɂ���
	ddsDesc.StencilEnable = FALSE;
	SAFE_RELEASE(pDepthStencilState);
	hr = sRENDER_DEVICE->CreateDepthStencilState(&ddsDesc, &pDepthStencilState);
	if (FAILED(hr))
	{

	}
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->OMSetDepthStencilState(pDepthStencilState, StencilRef);
	SAFE_RELEASE(pDepthStencilState);

	// ���C�A�E�g�ݒ�
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetInputLayout(this->m_spVertexLayout->GetMain().Get());

	// ���_�V�F�[�_�[���f�o�C�X�ɐݒ肷��B
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetShader(m_cpVertexShader.Get(), NULL, 0);

	// �n���V�F�[�_�[�𖳌��ɂ���B
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->HSSetShader(NULL, NULL, 0);

	// �h���C���V�F�[�_�[�𖳌��ɂ���B
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DSSetShader(NULL, NULL, 0);

	// �W�I���g���V�F�[�_�[���f�o�C�X�ɐݒ肷��B
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->GSSetShader(m_cpGeometryShaders[0].Get(), NULL, 0);
	// �W�I���g���V�F�[�_�[�ɒ萔�o�b�t�@��ݒ肷��B
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->GSSetConstantBuffers(0, 1, m_constantBuffers[0]->GetAddressOf());

	// �s�N�Z���V�F�[�_�[���f�o�C�X�ɖ����ɂ���B
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShader(NULL, NULL, 0);

	// �R���s���[�g�V�F�[�_�[�𖳌��ɂ���B
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->CSSetShader(NULL, NULL, 0);

	static bool bInit = true;
	// �ŏ��͒��_�����킩��̂� ID3D11DeviceContext::Draw() �ŕ`�悷��
	if (bInit)
	{
		sRENDER_DEVICE_MANAGER->GetImmediateContext()->Draw(NUM_PARTICLE, 0);
		bInit = false;
	}
	// �Q��ڈڍs�͏������钸�_�����s���Ȃ̂� ID3D11DeviceContext::DrawAuto() �ŕ`�悷��
	else
	{
		// ID3D11DeviceContext::DrawAuto
		sRENDER_DEVICE_MANAGER->GetImmediateContext()->DrawAuto();
	}

	ID3D11Buffer* pNullBuffer[] = { NULL };
	// �p�C�v���C���̃X�g���[���o�̓X�e�[�W�Ŏg�p�����^�[�Q�b�g�o�̓o�b�t�@�[�𖳌��ɂ���B
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->SOSetTargets(1, pNullBuffer, NULL);

	// *********************************************************************************************
	// �p�[�e�B�N���`��
	// *********************************************************************************************
	
	// �v���~�e�B�u �^�C�v����уf�[�^�̏����Ɋւ������ݒ�
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// �[�x�e�X�g�𖳌��ɂ���
	 pDepthStencilState = NULL;

	::ZeroMemory(&ddsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->OMGetDepthStencilState(&pDepthStencilState, &StencilRef);
	pDepthStencilState->GetDesc(&ddsDesc);
	ddsDesc.DepthEnable = FALSE;  // �[�x�e�X�g�𖳌��ɂ���
	ddsDesc.StencilEnable = FALSE;
	SAFE_RELEASE(pDepthStencilState);
	hr = sRENDER_DEVICE->CreateDepthStencilState(&ddsDesc, &pDepthStencilState);
	if (FAILED(hr))
	{

	}
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->OMSetDepthStencilState(pDepthStencilState, StencilRef);
	SAFE_RELEASE(pDepthStencilState);

	// �A���t�@�u�����f�B���O����`�����Őݒ肷��
	D3D11_RENDER_TARGET_BLEND_DESC BlendDesc;
	BlendDesc = sRENDER_DEVICE_MANAGER->GetAlignmentBlendDesc();
	sRENDER_DEVICE_MANAGER->SetBlendState(&BlendDesc, 1, FALSE);

	// ���̓A�Z���u���[ �X�e�[�W�ɒ��_�o�b�t�@�[�̔z����o�C���h����B
	 stride = sizeof(VERTEX);
	 offset = 0;
	//sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetVertexBuffers(0, 1, &g_pSOBuffer[1], &stride, &offset);

	// ���C�A�E�g�ݒ�
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetInputLayout(this->m_spVertexLayout->GetMain().Get());

	// ���_�V�F�[�_�[���f�o�C�X�ɐݒ肷��B
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetShader(m_cpVertexShader.Get(), NULL, 0);

	// �n���V�F�[�_�[�𖳌��ɂ���B
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->HSSetShader(NULL, NULL, 0);

	// �h���C���V�F�[�_�[�𖳌��ɂ���B
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DSSetShader(NULL, NULL, 0);

	// �W�I���g���V�F�[�_�[���f�o�C�X�ɐݒ肷��B
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->GSSetShader(m_cpGeometryShaders[1].Get(), NULL, 0);
	// �W�I���g���V�F�[�_�[�ɒ萔�o�b�t�@��ݒ肷��B
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->GSSetConstantBuffers(0, 1, m_constantBuffers[0]->GetAddressOf());

	// �s�N�Z���V�F�[�_�[���f�o�C�X�ɐݒ肷��B
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShader(m_cpPixelShader.Get(), NULL, 0);
	// �e�N�X�`���[��ݒ肷��
	//sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShaderResources(0, 1, &g_pSRView);
	// �T���v���X�e�[�g��ݒ肷��
	//sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetSamplers(0, 1, &g_pSamplerState);

	// �R���s���[�g�V�F�[�_�[�𖳌��ɂ���B
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->CSSetShader(NULL, NULL, 0);

	// �p�[�e�B�N���̕`��
	// ���_�����s���Ȃ̂� ID3D11DeviceContext::DrawAuto() �ŕ`�悷��
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DrawAuto();
	

// 	// �f�o�b�O��p�t�H���g�`��
// 	if (g_pDebugFontUser)
// 	{
// 		// FPS�\��
// 		g_pDebugFontUser->RenderFPS(sRENDER_DEVICE_MANAGER->GetImmediateContext(), 0, 0);
// 	}
// 
// 	// �����_�����O���ꂽ�C���[�W��\���B
// 	hr = g_pD3D11User->m_SwapChain->Present(0, 0);
// 
// 	if (ScreenShot)
// 	{
// 		// �X�N���[���V���b�g�쐬
// 		g_pD3D11User->CreateScreenShot();
// 		ScreenShot = false;
// 	}


	return hr;
}


bool GPUParticleShader::PostProcessOfRender()
{
	return true;
}
