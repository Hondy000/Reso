#pragma once
#include "..\..\..\Basic\Public\BaseRenderTarget.h"	 
#include "../../../../../Core/Public/Common.h"
#include "..\..\..\..\Texture\Public\BaseTexture2D.h"

class DX11RenderTargetView
	:
	public BaseRenderTarget
{
public:
	DX11RenderTargetView();
	~DX11RenderTargetView();
	bool Create
	(
		float width,
		float height,
		UINT mipLevels,
		DWORD format
	);
	bool CreateFromBackBuffer
	(
	);

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTargetView() const
	{
		return m_cpRenderTargetView;
	}


protected:
	/** @brief	The cp render target view. */
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_cpRenderTargetView;
	/** State of the cp depth stencil. */
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_cpRasterizerState;
	std::shared_ptr<BaseTexture2D> m_spTexture2D;
private:
};
