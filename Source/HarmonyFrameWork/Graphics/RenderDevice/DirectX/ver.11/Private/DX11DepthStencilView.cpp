#include "..\Public\DX11DepthStencilView.h"
#include "..\..\..\..\..\Debug\Public\Debug.h"
#include "..\..\..\Basic\Public\RendererManager.h"

DX11DepthStencilView::DX11DepthStencilView()
{

}

DX11DepthStencilView::~DX11DepthStencilView()
{

}

Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DX11DepthStencilView::Create(
	float width, 
	float height,
	DWORD format
)
{

	HRESULT hr = E_FAIL;


	DXGI_SWAP_CHAIN_DESC desc;
	hr = sRENDER_DEVICE_MANAGER->GetSpSwapChain()->GetCpSwapChain()->GetDesc(&desc);

	// D3D11_TEXTURE2D_DESC
	D3D11_TEXTURE2D_DESC descDS;

	// D3D11_DEPTH_STENCIL_VIEW_DESC
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;

	//if (m_SwapChain == NULL) goto EXIT;

	CONSOLE_LOG(_T("深度バッファビュー作成 開始\n"));


	// スワップチェーンの設定を取得する

	::ZeroMemory(&descDS, sizeof(D3D11_TEXTURE2D_DESC));
	descDS.Width = desc.BufferDesc.Width;   // バックバッファと同じにする。
	descDS.Height = desc.BufferDesc.Height;  // バックバッファと同じにする。
	descDS.MipLevels = 1;                            // ミップマップを作成しない
	descDS.ArraySize = 1;                            // テクスチャーの配列数
	descDS.Format = DXGI_FORMAT_R32_TYPELESS;       // フォーマット
	descDS.SampleDesc.Count = desc.SampleDesc.Count;   // バックバッファと同じにする。
	descDS.SampleDesc.Quality = desc.SampleDesc.Quality; // バックバッファと同じにする。
	descDS.Usage = D3D11_USAGE_DEFAULT;          // GPU による読み取りおよび書き込みアクセスを必要とするリソース。

												 //   descDS.BindFlags          = D3D11_BIND_DEPTH_STENCIL;     // ステンシルバッファ
	descDS.BindFlags = D3D11_BIND_DEPTH_STENCIL |    // 深度ステンシルバッファとして作成する
		D3D11_BIND_SHADER_RESOURCE;   // シェーダーリソースビューとして作成する
	descDS.CPUAccessFlags = 0;                            // CPU アクセスが不要。
	descDS.MiscFlags = 0;                            // その他のフラグも設定しない。

													 // 深度バッファ用のテクスチャー作成
													 // CreateTexture2D
	m_depthMap = std::make_shared<BaseTexture2D>();

	hr = sRENDER_DEVICE->CreateTexture2D(&descDS, NULL, m_depthMap->GetCpTexture().GetAddressOf());
	if (FAILED(hr)) goto EXIT;

	::ZeroMemory(&descDSV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

	// テクスチャー作成時に指定したフォーマットと互換性があり、深度ステンシルビューとして指定できるフォーマットを指定する
	//   descDSV.Format = descDS.Format;
	switch (descDS.Format)
	{
		// 8ビットフォーマットは使用できない？
	case DXGI_FORMAT_R8_TYPELESS:
		descDSV.Format = DXGI_FORMAT_R8_UNORM;
		break;
	case DXGI_FORMAT_R16_TYPELESS:
		descDSV.Format = DXGI_FORMAT_D16_UNORM;
		break;
	case DXGI_FORMAT_R32_TYPELESS:
		descDSV.Format = DXGI_FORMAT_D32_FLOAT;
		break;
	case DXGI_FORMAT_R24G8_TYPELESS:
		descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		break;
	default:
		descDSV.Format = descDS.Format;
	}

	// マルチサンプルを使用している場合
	if (desc.SampleDesc.Count > 1)
	{
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	}

	// マルチサンプルを使用していない場合
	else
	{
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	}

	descDSV.Texture2D.MipSlice = 0;

	// 深度ステンシルビューを作成								

	// CreateDepthStencilView
	hr = sRENDER_DEVICE->CreateDepthStencilView(m_depthMap->GetCpTexture().Get(), &descDSV, m_cpDepthStencilView.GetAddressOf());
	if (FAILED(hr)) goto EXIT;

	CONSOLE_LOG(_T("深度バッファビュー作成"), _T(""), _T("完了\n"));

	hr = S_OK;

EXIT:

	return m_cpDepthStencilView;
}

Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& DX11DepthStencilView::GetDepthStencilView()
{
	return m_cpDepthStencilView;
}

void DX11DepthStencilView::SetDepthStencilView(Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& _val)
{
	m_cpDepthStencilView = _val;
}


Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& DX11DepthStencilView::GetDepthStencilState()
{
	return m_cpDepthStencilState;
}

void DX11DepthStencilView::SetDepthStencilState(Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& _val)
{
	m_cpDepthStencilState = _val;
}
