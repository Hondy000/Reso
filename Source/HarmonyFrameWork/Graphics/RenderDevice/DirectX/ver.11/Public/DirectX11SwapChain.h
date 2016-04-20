#pragma once
#include "../../../../../Core/Public/Common.h"
#include "DirectX11Adapter.h"

class DirectX11SwapChain
{
public:
	DirectX11SwapChain();
	~DirectX11SwapChain();

	// Access the CpSwapChain
	const Microsoft::WRL::ComPtr<IDXGISwapChain>& GetCpSwapChain(void) const
	{
		return(m_cpSwapChain);
	};

	// Access the WpAdapter
	void SetWpAdapter(const std::weak_ptr<DirectX11Adapter>& wpAdapter)
	{
		m_wpAdapter = wpAdapter;
	};

	// Access the CpDevice
	void SetCpDevice(const Microsoft::WRL::ComPtr<ID3D11Device>& cpDevice)
	{
		m_cpDevice = cpDevice;
	};

	HRESULT CreateSwapChain(DXGI_MODE_DESC* pDisplayMode, bool MultisampleEnabled,HWND hWnd);

protected:
	Microsoft::WRL::ComPtr<IDXGISwapChain>         m_cpSwapChain;               // スワップチェーン
	std::weak_ptr<DirectX11Adapter> m_wpAdapter;
	Microsoft::WRL::ComPtr<ID3D11Device> m_cpDevice;
};
