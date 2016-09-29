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

	bool Create
	(
		float width,
		float height,
		DWORD format
	);

	void LogConsoleOfCreateDepthStencilTextureDesc(D3D11_TEXTURE2D_DESC _DX11Texture2DDesc);
	void LogConsoleOfCreateDepthStencilViewDesc(D3D11_DEPTH_STENCIL_VIEW_DESC _DX11DepthStencilViewDesc);
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& GetDepthStencilView();
	void SetDepthStencilView(Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& _val);
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& GetDepthStencilState();
	void SetDepthStencilState(Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& _val);

	std::shared_ptr<BaseTexture2D> GetDepthMap() const
	{
		return m_depthMap;
	}

private:
	/** The cp depth stencil view. */
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_cpDepthStencilView;
	/** State of the cp depth stencil. */
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_cpDepthStencilState;
	/** @brief	The depth map. */
	std::shared_ptr<BaseTexture2D> m_depthMap;

};