/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\Renderer\DirectX\ver.11\CDirectX11Adapter.cpp
 *
 * @brief	Implements the direct x coordinate 11 adapter class.
 **************************************************************************************************/

#include "../Public/DirectX11Adapter.h"

/**********************************************************************************************//**
 * @fn	DirectX11Adapter::DirectX11Adapter()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 **************************************************************************************************/

DirectX11Adapter::DirectX11Adapter()
{
}

/**********************************************************************************************//**
 * @fn	DirectX11Adapter::~DirectX11Adapter()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 **************************************************************************************************/

DirectX11Adapter::~DirectX11Adapter()
{
}

/**********************************************************************************************//**
 * @fn	bool DirectX11Adapter::Setup()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	A bool.
 **************************************************************************************************/

bool DirectX11Adapter::Setup()
{
	HRESULT hr = E_FAIL;
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool DirectX11Adapter::CreateAdapter()
 *
 * @brief	デフォルトアダプターのインターフェースを作成する.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	The new adapter.
 **************************************************************************************************/

bool DirectX11Adapter::CreateAdapter()
{
	HRESULT hr = E_FAIL;
	IDXGIFactory* pFactory = NULL;

	if (m_cpAdapter == NULL)
	{
		// ファクトリを作成する。
		// CreateDXGIFactory
		hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));
		if (FAILED(hr)) goto EXIT;

		// デフォルトアダプターを取得
		// IDXGIFactory::EnumAdapters
		hr = pFactory->EnumAdapters(0, m_cpAdapter.GetAddressOf());
		if (FAILED(hr)) goto EXIT;
	}

	hr = S_OK;
EXIT:
	SAFE_RELEASE(pFactory);

	return hr;
}

/**********************************************************************************************//**
 * @fn	void DirectX11Adapter::ReleaseAdapter(void)
 *
 * @brief	Releases the adapter.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 **************************************************************************************************/

void DirectX11Adapter::ReleaseAdapter(void)
{
	m_cpAdapter.Detach();
}