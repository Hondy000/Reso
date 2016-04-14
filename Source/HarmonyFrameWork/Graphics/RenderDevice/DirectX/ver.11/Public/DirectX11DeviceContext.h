#pragma once
#include "../../../../../Core/Public/Common.h"
class DirectX11DeviceContext
{
public:
	DirectX11DeviceContext();
	~DirectX11DeviceContext();
	BOOL Init(void);
protected:
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>m_D3DDeviceContext;        // Direct3D11 デバイスコンテキスト。
};
