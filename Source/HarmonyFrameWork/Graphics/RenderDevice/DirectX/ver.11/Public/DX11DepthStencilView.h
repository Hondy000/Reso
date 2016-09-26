/***********************************************************************************************
 * @file Source\HarmonyFrameWork\Graphics\RenderDevice\DirectX\ver.11\Public\DX11DepthStencilView.h
 *
 * Declares the dx 11 depth stencil view class.
 *************************************************************************************************/

#pragma once
#include "..\..\..\Basic\Public\BaseDepthStencilBuffer.h"	   
#include "../../../../../Core/Public/Common.h"
#include "..\..\..\..\Texture\Public\BaseTexture2D.h"

/***********************************************************************************************
 * A dx 11 depth stencil view.
 *
 * @author Kazuyuki
 *
 * @sa BaseDepthStencilBuffer
 *************************************************************************************************/

class DX11DepthStencilView
	:

	/***********************************************************************************************
	 * Gets the buffer for base depth stencil data.
	 *
	 * @value .
	 *************************************************************************************************/

	public BaseDepthStencilBuffer
{
public:
	DX11DepthStencilView();
	~DX11DepthStencilView();

	static Microsoft::WRL::ComPtr<ID3D11DepthStencilView> Create(
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthStencilView,
		std::shared_ptr<BaseTexture2D> _depthMap,
		DXGI_SWAP_CHAIN_DESC desc,
		float width,
		float height,
		DWORD format
	);

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& GetDepthStencilView();
	void SetDepthStencilView(Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& _val);
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& GetDepthStencilState();
	void SetDepthStencilState(Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& _val);
private:
	/** The cp depth stencil view. */
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_cpDepthStencilView;
	/** State of the cp depth stencil. */
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_cpDepthStencilState;
	std::shared_ptr<BaseTexture2D> m_depthMap;

};