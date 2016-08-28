
#include "..\Public\GPUParticleShader.h"
#include "..\..\..\..\Public\GraphicsTypes.h"
#include "..\..\..\..\RenderDevice\Basic\Public\RendererManager.h"
#include "..\..\..\..\..\Utility\Public\HFString.h"


// 頂点定義
typedef struct _VERTEX
{
	HFVECTOR3 pos;  // 位置座標
	HFVECTOR3 v0;   // 初速度
	float time;       // 時間
}VERTEX;

// 定数定義
typedef struct _CBUFFER
{
	HFMATRIX  g_matWVP;    // ワールド × ビュー × 射影 行列
	float       g_Scale;     // パーティクルのスケーリング値
	float       g_LimitTime; // 時間の限界値( この値を超えると初期値に戻す )
	float       g_dummy2;    // 未使用
	float       g_dummy3;    // 未使用
}CBUFFER;

//// ターゲット入出力バッファー
//ID3D11Buffer* g_pSOBuffer[2] = { NULL, NULL };
//// 頂点シェーダー
//ID3D11VertexShader*   g_pVertexShader = NULL;
//// 入力レイアウト
//ID3D11InputLayout*    g_pLayout = NULL;
//// 定数バッファ
//ID3D11Buffer* g_pConstantBuffers = NULL;
//// ジオメトリシェーダー( パーティクルの座標更新用、描画用 )
//ID3D11GeometryShader* g_pGeometryShader[2] = { NULL, NULL };
//// ピクセルシェーダー
//ID3D11PixelShader* g_pPixelShader = NULL;
//// サンプラーステート
//ID3D11SamplerState* g_pSamplerState = NULL;
//// シェーダーリソースビュー
//ID3D11ShaderResourceView* g_pSRView = NULL;
// パーティクル数
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

	// パーティクルの初期値を設定
	VERTEX v[NUM_PARTICLE];
	for (int i = 0; i < NUM_PARTICLE; i++)
	{
		v[i].pos = HFVECTOR3(0.0f, 0.0f, 0.0f),
			v[i].v0 = HFVECTOR3((float)(rand() % 50 - 25) * 0.3f, (float)(rand() % 50) * 0.5f, (float)(rand() % 50 - 25) * 0.3f);
		v[i].time = (float)(rand() % 100) * 0.1f;
	};
	// ターゲット入出力バッファーを作成
	D3D11_BUFFER_DESC BufferDesc;
	::ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.ByteWidth = sizeof(v);  // バッファサイズ
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_STREAM_OUTPUT;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA mappedResource;
	mappedResource.pSysMem = v;  // バッファ・データの初期値
	mappedResource.SysMemPitch = 0;
	mappedResource.SysMemSlicePitch = 0;
	for (int i = 0; i < m_cpGeometryShaders.size(); i++)
	{
		hr = sRENDER_DEVICE_MANAGER->GetDevice()->CreateBuffer(&BufferDesc, &mappedResource, m_constantBuffers[i]->GetAddressOf());
		if (FAILED(hr))
		{
		}
	}

	// 頂点シェーダーの作成

	m_spVertexLayout = std::make_shared<BaseVertexLayout>();

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },  // 位置座標
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },  // 初速度
		{ "TEXCOORD", 0, DXGI_FORMAT_R32_FLOAT,       0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }   // 時間
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

	// ターゲット入出力バッファーの定義
	// D3D11_SO_DECLARATION_ENTRY
	// SemanticNameに指定可能な値は、"POSITION"、"NORMAL"、または "TEXCOORD0" らしい。
	D3D11_SO_DECLARATION_ENTRY decl[] = {
		{ 0, "POSITION",  0, 0, 3, 0 },
		{ 0, "NORMAL",    0, 0, 3, 0 },
		{ 0, "TEXCOORD",  0, 0, 1, 0 },
	};

	UINT stride[] = { sizeof(VERTEX) };

	// ストリームアウトプットとしてジオメトリシェーダーを作成
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

	// 描画用のジオメトリシェーダーを作成する
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

	// ピクセルシェーダーを作成する
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

	// 定数バッファを作成する。
	hr = sRENDER_DEVICE_MANAGER->CreateConstantBuffer(m_constantBuffers[0], NULL, sizeof(CBUFFER), D3D11_CPU_ACCESS_WRITE);
	if (FAILED(hr))
	{

	}

	// サンプラーステートの設定
	{
		D3D11_SAMPLER_DESC samplerDesc;
		::ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;         // サンプリング時に使用するフィルタ。ここでは異方性フィルターを使用する。
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;     // 0 ～ 1 の範囲外にある u テクスチャー座標の描画方法
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;     // 0 ～ 1 の範囲外にある v テクスチャー座標の描画方法
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;     // 0 ～ 1 の範囲外にある w テクスチャー座標の描画方法
		samplerDesc.MipLODBias = 0;                            // 計算されたミップマップ レベルからのバイアス
		samplerDesc.MaxAnisotropy = 16;                        // サンプリングに異方性補間を使用している場合の限界値。有効な値は 1 ～ 16 。
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;  // 比較オプション。
		::CopyMemory(samplerDesc.BorderColor, &HFVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), sizeof(HFVECTOR4)); // 境界色
		samplerDesc.MinLOD = 0;                                // アクセス可能なミップマップの下限値
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;                // アクセス可能なミップマップの上限値
	//	hr = sRENDER_DEVICE->CreateSamplerState(&samplerDesc, &g_pSamplerState);
		if (FAILED(hr))
		{

		}
	}

// 	画像ファイルを読み込んでテクスチャーリソースビューを作成する
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
// 			// パーティクルのテクスチャー
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

	// 定数バッファ
	CBUFFER* cbuffer = nullptr;
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	sRENDER_DEVICE_MANAGER->GetTransform(&matView, HFTS_VIEW);
	sRENDER_DEVICE_MANAGER->GetTransform(&matProj, HFTS_PERSPECTIVE);

	// ワールド行列
	matWorld = HFMATRIX::Identity;

	// 行列の合成
	matWVP = matWorld * matView * matProj;

	hr = sRENDER_DEVICE_MANAGER->GetImmediateContext()->Map(m_constantBuffers[0]->Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	
	cbuffer = (CBUFFER*)(mappedResource.pData);
	// シェーダー内では列優先にしているので転置行列を作成する。
	
	 cbuffer->g_matWVP = matWVP.Transpose();
	// スケーリング値
	cbuffer->g_Scale = 3.0f;

	// タイマーの最大値
	cbuffer->g_LimitTime = 10.0f;

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Unmap(m_constantBuffers[0]->Get(), 0);
	

	// *********************************************************************************************
	// パーティクルの更新
	// *********************************************************************************************
	
	// ターゲット出力バッファーを入れ替える
//ID3D11Buffer *pB = g_pSOBuffer[0];
//g_pSOBuffer[0] = g_pSOBuffer[1];
//g_pSOBuffer[1] = pB;

	// 入力アセンブラー ステージに頂点バッファーの配列をバインドする。
	// ID3D11DeviceContext::IASetVertexBuffers
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	//sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetVertexBuffers(0, 1, &g_pSOBuffer[0], &stride, &offset);

	// 出力バッファーの配列のオフセット値
	// パイプラインのストリーム出力ステージで使用されるターゲット出力バッファーを設定します。
	// ID3D11DeviceContext::SOSetTargets
	//sRENDER_DEVICE_MANAGER->GetImmediateContext()->SOSetTargets(1, &g_pSOBuffer[1], &offset);

	// プリミティブ タイプおよびデータの順序に関する情報を設定
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// ピクセルシェーダーを無効にした状態で深度ステンシルを有効にしているとエラーになるので無効にする
	ID3D11DepthStencilState*  pDepthStencilState = NULL;
	D3D11_DEPTH_STENCIL_DESC ddsDesc;
	UINT StencilRef;
	::ZeroMemory(&ddsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->OMGetDepthStencilState(&pDepthStencilState, &StencilRef);
	pDepthStencilState->GetDesc(&ddsDesc);
	ddsDesc.DepthEnable = FALSE;  // 深度テストを無効にする
	ddsDesc.StencilEnable = FALSE;
	SAFE_RELEASE(pDepthStencilState);
	hr = sRENDER_DEVICE->CreateDepthStencilState(&ddsDesc, &pDepthStencilState);
	if (FAILED(hr))
	{

	}
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->OMSetDepthStencilState(pDepthStencilState, StencilRef);
	SAFE_RELEASE(pDepthStencilState);

	// レイアウト設定
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetInputLayout(this->m_spVertexLayout->GetMain().Get());

	// 頂点シェーダーをデバイスに設定する。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetShader(m_cpVertexShader.Get(), NULL, 0);

	// ハルシェーダーを無効にする。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->HSSetShader(NULL, NULL, 0);

	// ドメインシェーダーを無効にする。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DSSetShader(NULL, NULL, 0);

	// ジオメトリシェーダーをデバイスに設定する。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->GSSetShader(m_cpGeometryShaders[0].Get(), NULL, 0);
	// ジオメトリシェーダーに定数バッファを設定する。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->GSSetConstantBuffers(0, 1, m_constantBuffers[0]->GetAddressOf());

	// ピクセルシェーダーをデバイスに無効にする。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShader(NULL, NULL, 0);

	// コンピュートシェーダーを無効にする。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->CSSetShader(NULL, NULL, 0);

	static bool bInit = true;
	// 最初は頂点数がわかるので ID3D11DeviceContext::Draw() で描画する
	if (bInit)
	{
		sRENDER_DEVICE_MANAGER->GetImmediateContext()->Draw(NUM_PARTICLE, 0);
		bInit = false;
	}
	// ２回目移行は処理する頂点数が不明なので ID3D11DeviceContext::DrawAuto() で描画する
	else
	{
		// ID3D11DeviceContext::DrawAuto
		sRENDER_DEVICE_MANAGER->GetImmediateContext()->DrawAuto();
	}

	ID3D11Buffer* pNullBuffer[] = { NULL };
	// パイプラインのストリーム出力ステージで使用されるターゲット出力バッファーを無効にする。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->SOSetTargets(1, pNullBuffer, NULL);

	// *********************************************************************************************
	// パーティクル描画
	// *********************************************************************************************
	
	// プリミティブ タイプおよびデータの順序に関する情報を設定
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// 深度テストを無効にする
	 pDepthStencilState = NULL;

	::ZeroMemory(&ddsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->OMGetDepthStencilState(&pDepthStencilState, &StencilRef);
	pDepthStencilState->GetDesc(&ddsDesc);
	ddsDesc.DepthEnable = FALSE;  // 深度テストを無効にする
	ddsDesc.StencilEnable = FALSE;
	SAFE_RELEASE(pDepthStencilState);
	hr = sRENDER_DEVICE->CreateDepthStencilState(&ddsDesc, &pDepthStencilState);
	if (FAILED(hr))
	{

	}
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->OMSetDepthStencilState(pDepthStencilState, StencilRef);
	SAFE_RELEASE(pDepthStencilState);

	// アルファブレンディングを線形合成で設定する
	D3D11_RENDER_TARGET_BLEND_DESC BlendDesc;
	BlendDesc = sRENDER_DEVICE_MANAGER->GetAlignmentBlendDesc();
	sRENDER_DEVICE_MANAGER->SetBlendState(&BlendDesc, 1, FALSE);

	// 入力アセンブラー ステージに頂点バッファーの配列をバインドする。
	 stride = sizeof(VERTEX);
	 offset = 0;
	//sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetVertexBuffers(0, 1, &g_pSOBuffer[1], &stride, &offset);

	// レイアウト設定
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->IASetInputLayout(this->m_spVertexLayout->GetMain().Get());

	// 頂点シェーダーをデバイスに設定する。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->VSSetShader(m_cpVertexShader.Get(), NULL, 0);

	// ハルシェーダーを無効にする。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->HSSetShader(NULL, NULL, 0);

	// ドメインシェーダーを無効にする。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DSSetShader(NULL, NULL, 0);

	// ジオメトリシェーダーをデバイスに設定する。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->GSSetShader(m_cpGeometryShaders[1].Get(), NULL, 0);
	// ジオメトリシェーダーに定数バッファを設定する。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->GSSetConstantBuffers(0, 1, m_constantBuffers[0]->GetAddressOf());

	// ピクセルシェーダーをデバイスに設定する。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShader(m_cpPixelShader.Get(), NULL, 0);
	// テクスチャーを設定する
	//sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetShaderResources(0, 1, &g_pSRView);
	// サンプラステートを設定する
	//sRENDER_DEVICE_MANAGER->GetImmediateContext()->PSSetSamplers(0, 1, &g_pSamplerState);

	// コンピュートシェーダーを無効にする。
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->CSSetShader(NULL, NULL, 0);

	// パーティクルの描画
	// 頂点数が不明なので ID3D11DeviceContext::DrawAuto() で描画する
	sRENDER_DEVICE_MANAGER->GetImmediateContext()->DrawAuto();
	

// 	// デバッグ専用フォント描画
// 	if (g_pDebugFontUser)
// 	{
// 		// FPS表示
// 		g_pDebugFontUser->RenderFPS(sRENDER_DEVICE_MANAGER->GetImmediateContext(), 0, 0);
// 	}
// 
// 	// レンダリングされたイメージを表示。
// 	hr = g_pD3D11User->m_SwapChain->Present(0, 0);
// 
// 	if (ScreenShot)
// 	{
// 		// スクリーンショット作成
// 		g_pD3D11User->CreateScreenShot();
// 		ScreenShot = false;
// 	}


	return hr;
}


bool GPUParticleShader::PostProcessOfRender()
{
	return true;
}
