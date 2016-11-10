#include "..\Public\DX11RenderTargetView.h"
#include "..\..\..\..\..\Debug\Public\Debug.h"
#include "..\..\..\Basic\Public\RendererManager.h"

DX11RenderTargetView::DX11RenderTargetView()
{
	m_spTexture2D = std::make_shared<BaseTexture2D>();
}

DX11RenderTargetView::~DX11RenderTargetView()
{

}

bool DX11RenderTargetView::Create(float width, float height,
	UINT mipLevels, DWORD format)
{
	HRESULT hr = E_FAIL;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2D = NULL;
	CONSOLE_LOG(_T("レンダリングターゲットビュー作成"), _T(""), _T("開始\n"));

	// スワップチェーンの情報を取得する
	DXGI_SWAP_CHAIN_DESC SCDesc;
	sRENDER_DEVICE_MANAGER->GetSpSwapChain()->GetCpSwapChain()->GetDesc(&SCDesc);


	D3D11_TEXTURE2D_DESC Tex2DDesc;
	D3D11_RENDER_TARGET_VIEW_DESC RTVDesc;

	::ZeroMemory(&Tex2DDesc, sizeof(D3D11_TEXTURE2D_DESC));
	Tex2DDesc.ArraySize = 1;
	Tex2DDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	Tex2DDesc.Usage = D3D11_USAGE_DEFAULT;
	Tex2DDesc.Format = (DXGI_FORMAT)format;
	Tex2DDesc.Width = width;
	Tex2DDesc.Height = height;
	Tex2DDesc.MipLevels = mipLevels;
	Tex2DDesc.SampleDesc.Count = SCDesc.SampleDesc.Count;
	Tex2DDesc.SampleDesc.Quality = SCDesc.SampleDesc.Quality;

	::ZeroMemory(&RTVDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	RTVDesc.Format = Tex2DDesc.Format;
	if (Tex2DDesc.SampleDesc.Count == 1)
	{
		RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	}
	else
	{
		RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
	}
	RTVDesc.Texture2D.MipSlice = 0;

	// ミップマップチェーンの作成を許可する
	if (mipLevels != 1)
	{
		Tex2DDesc.MiscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
	}

	 sRENDER_DEVICE->CreateTexture2D(&Tex2DDesc, NULL, pTexture2D.GetAddressOf());
	if (FAILED(hr))
	{
		LPVOID  message;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			hr,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&message,
			0,
			NULL);
		OutputDebugString((LPTSTR)message);
		LocalFree(message);
	}

	hr = sRENDER_DEVICE->CreateRenderTargetView(pTexture2D.Get(), &RTVDesc, (m_cpRenderTargetView).GetAddressOf());
	CONSOLE_LOG(_T("レンダリングターゲットビュー作成"), _T(""), _T("完了\n"));

	return true;

}

bool DX11RenderTargetView::CreateFromBackBuffer()
{

	HRESULT hr = E_FAIL;

	CONSOLE_LOG(_T("レンダリングターゲットビュー作成"), _T(""), _T("開始\n"));

	// スワップチェーンからバックバッファを取得する
	hr = sRENDER_DEVICE_MANAGER->GetSpSwapChain()->GetCpSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&(m_spTexture2D->GetCpTexture()) );
	if (FAILED(hr))
	{

		return false;
	}

	// レンダリングターゲットビューの作成
	// CreateRenderTargetView
	hr = sRENDER_DEVICE->CreateRenderTargetView(m_spTexture2D->GetCpTexture().Get(), NULL, m_cpRenderTargetView.GetAddressOf());
	if (FAILED(hr))
	{
		return false;
	}

	CONSOLE_LOG(_T("レンダリングターゲットビュー作成"), _T(""), _T("完了\n"));

	hr = S_OK;
	return true;

}

