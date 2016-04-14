#pragma once
#include "../../../../../Core/Public/Common.h"
class DirectX11Adapter
{
public:
	DirectX11Adapter();
	~DirectX11Adapter();

	BOOL Setup(void);

	// アダプターの取得
	Microsoft::WRL::ComPtr<IDXGIAdapter> GetAdapter(void) const
	{
		return(m_cpAdapter);
	};

	// アダプターの作成
	BOOL CreateAdapter(void);

	// アダプターのリリース
	void ReleaseAdapter(void);

protected:

	Microsoft::WRL::ComPtr<IDXGIAdapter>           m_cpAdapter;                 // アダプター
};
