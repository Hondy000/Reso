/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\Renderer\DirectX\ver.11\CDirectX11SwapChain.cpp
 *
 * @brief	Implements the direct x coordinate 11 swap chain class.
 **************************************************************************************************/

#include "../Public/DirectX11SwapChain.h"
#include "../../../../../Debug/Public/Debug.h"
#include "../../../../../Utility/Public/HFString.h"

/**********************************************************************************************//**
 * @fn	DirectX11SwapChain::DirectX11SwapChain()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 **************************************************************************************************/

DirectX11SwapChain::DirectX11SwapChain()
{
}

/**********************************************************************************************//**
 * @fn	DirectX11SwapChain::~DirectX11SwapChain()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 **************************************************************************************************/

DirectX11SwapChain::~DirectX11SwapChain()
{
}

/**********************************************************************************************//**
 * @fn	HRESULT DirectX11SwapChain::CreateSwapChain( DXGI_MODE_DESC* pDisplayMode, bool MultisampleEnabled, HWND hWnd )
 *
 * @brief	Creates swap chain.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pDisplayMode	If non-null, the display mode.
 * @param	MultisampleEnabled  	true to enable, false to disable the multisample.
 * @param	hWnd					Handle of the window.
 *
 * @return	The new swap chain.
 **************************************************************************************************/

HRESULT DirectX11SwapChain::CreateSwapChain(
	DXGI_MODE_DESC* pDisplayMode,
	bool MultisampleEnabled,
	HWND hWnd
	)
{
	HRESULT hr = E_FAIL;  HFString test;
	TCHAR s[256];
	IDXGIFactory* pFactory = NULL;

	//CONSOLE_LOG(_T("スワップチェーン作成"), _T(""), _T("開始"));

	// DXGI_SWAP_CHAIN_DESC
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	// DXGI_MODE_DESC
	::CopyMemory(&(sd.BufferDesc), pDisplayMode, sizeof(DXGI_MODE_DESC));
	sd.BufferDesc.Format = D3D11USER_FORMAT;                         // バックバッファフォーマット
	// バックバッファのサーフェス使用法および CPU アクセス オプションを表す DXGI_USAGE 列挙型のメンバー
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;                // バックバッファにレンダリング可能にする。
	//スワップ チェーンのバッファー数を表す値。
	sd.BufferCount = 1;
	// 出力ウィンドウへの HWND ハンドル。このメンバーを NULL にはできない。
	sd.OutputWindow = hWnd;
	// 出力がウィンドウ モードの場合は TRUE。それ以外の場合は FALSE。
	// 初期起動時の表示モードはウィンドウモードに固定とする。
	sd.Windowed = TRUE;
	// サーフェスのスワップ処理後にバックバッファの内容を保持するか。
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;                        // バックバッファの内容を保持しない。
	// スワップ チェーンの動作のオプション。
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;               // フルスクリーンモードに切り替えると、アプリケーション ウィンドウのサイズに合わせて解像度が変更される。

	// ファクトリーを作成する
	// CreateDXGIFactoryで作成したファクトリーを使用すると実行できるがワーニングエラーになるので IDXGIAdapter から作成する。
	hr = m_wpAdapter.lock()->GetAdapter()->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);
	if (FAILED(hr)) goto EXIT;

	// マルチサンプリングの設定
	// マルチサンプルを使用しない場合の設定
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	int startMultisample;

	// サンプリング数が最大のものを採用する
	if (MultisampleEnabled == TRUE)
		startMultisample = D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT;
	// マルチサンプルを無効にする。
	else
		startMultisample = 1;

	UINT Quality = 0;
	for (int i = startMultisample; i >= 0; i--)
	{
		// サポートするクォリティレベルの最大値を取得する
		// CheckMultisampleQualityLevels
		hr = m_cpDevice->CheckMultisampleQualityLevels(pDisplayMode->Format, (UINT)i, &Quality);
		if (FAILED(hr)) goto EXIT;

		// 0 以外のときフォーマットとサンプリング数の組み合わせをサポートする
		// オンラインヘルプではCheckMultisampleQualityLevelsの戻り値が 0 のときサポートされないとかかれているが
		// pNumQualityLevels の戻り値が 0 かで判断する。
		// Direct3D 10 版 のオンラインヘルプにはそうかかれているので、オンラインヘルプの間違い。
		if (Quality != 0)
		{
			sd.SampleDesc.Count = i;
			sd.SampleDesc.Quality = Quality-1;

			// スワップチェーンを作成する。
			// CreateSwapChain
			hr = pFactory->CreateSwapChain(m_cpDevice.Get(), &sd, m_cpSwapChain.GetAddressOf());
			_stprintf_s(s, _T("Count(%d) Quality(%d)"), sd.SampleDesc.Count, sd.SampleDesc.Quality);
			if (SUCCEEDED(hr))
			{			
			//	HFDebug::Debug::GetInstance()->SetConsoleTextRed();
				CONSOLE_LOG(("マルチサンプル"), (s), ("OK\n"));
				break;
			}
			else
			{
				HFDebug::Debug::Log(HFString("マルチサンプル")+HFString(s)+ HFString("ＮＧ\n"));
			}
		}
	}
	if (m_cpSwapChain == NULL)
	{
		hr = E_FAIL;
		goto EXIT;
	}


	_stprintf_s(s, _T("解像度( %d : %d )　リフレッシュレート( %d / %d )"),pDisplayMode->Width, pDisplayMode->Height, pDisplayMode->RefreshRate.Denominator, pDisplayMode->RefreshRate.Numerator);
	CONSOLE_LOG(_T("ディスプレイモード"), s, _T("選択"));

	CONSOLE_LOG(_T("スワップチェーン作成"),  _T("完了"));

	//使用可能なMSAAを取得
	DXGI_SAMPLE_DESC MSAA;
	for (int i = 0; i <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; i++) {
		UINT Quality;
		if (SUCCEEDED(m_cpDevice->CheckMultisampleQualityLevels(D3D11USER_FORMAT, i, &Quality)))
		{
			if (0 < Quality)
			{
				MSAA.Count = i;
				MSAA.Quality = Quality - 1;
			}
		}
	}

	hr = S_OK;

EXIT:
	(pFactory)->Release();

	return hr;
}