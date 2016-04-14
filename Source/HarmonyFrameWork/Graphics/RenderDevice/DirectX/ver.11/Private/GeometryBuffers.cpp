
#include "../../../Basic/Public/RendererManager.h"
#include "../Public/GeometryBuffers.h"
#include "../../../../Texture/Public/BaseTexture2D.h"

/**********************************************************************************************//**
 * @fn	DeferredBuffers::DeferredBuffers()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 **************************************************************************************************/

GeometryBuffers::GeometryBuffers()
{
	int i;
	/*
	for(i=0; i<BUFFER_COUNT; i++)
	{
		m_renderTargetTextureArray[i] = 0;
		m_renderTargetViewArray[i] = 0;
		m_shaderResourceViewArray[i] = 0;
	}

	m_depthStencilBuffer = 0;
	m_depthStencilView = 0;
	*/
}

/**********************************************************************************************//**
 * @fn	DeferredBuffers::DeferredBuffers(const DeferredBuffers& other)
 *
 * @brief	Copy constructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	other	The other.
 **************************************************************************************************/

GeometryBuffers::GeometryBuffers(const GeometryBuffers& other)
{
}

/**********************************************************************************************//**
 * @fn	DeferredBuffers::~DeferredBuffers()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 **************************************************************************************************/

GeometryBuffers::~GeometryBuffers()
{
}

/**********************************************************************************************//**
 * @fn	BOOL DeferredBuffers::Setup(int bufferCount, int textureWidth, int textureHeight, FLOAT screenDepth, FLOAT screenNear)
 *
 * @brief	Setups.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	bufferCount  	Number of buffers.
 * @param	textureWidth 	Width of the texture.
 * @param	textureHeight	Height of the texture.
 * @param	screenDepth  	Depth of the screen.
 * @param	screenNear   	The screen near.
 *
 * @return	A BOOL.
 **************************************************************************************************/

BOOL GeometryBuffers::Setup(int bufferCount, int textureWidth, int textureHeight, FLOAT screenDepth, FLOAT screenNear)
{
	HRESULT hr = E_FAIL;
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	int i;

	m_bufferCount = bufferCount;

	m_renderTargetTextureArray.resize(m_bufferCount);
	m_renderTargetViewArray.resize(m_bufferCount);
	m_shaderResourceViewArray.resize(m_bufferCount);
	for (int i = 0; i < bufferCount; i++)
	{
		m_shaderResourceViewArray[i] = std::shared_ptr<BaseTexture2D>(new BaseTexture2D);
	}

	// Store the width and height of the render texture.
	m_textureWidth = textureWidth;
	m_textureHeight = textureHeight;

	// Initialize the render target texture description.
	ZeroMemory(&textureDesc, sizeof(textureDesc));

	// Setup the render target texture description.
	textureDesc.Width = textureWidth;
	textureDesc.Height = textureHeight;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;



	// Create the render target textures.
	for (i = 0; i < m_bufferCount; i++)
	{
		//hr = sRENDER_DEVICE->CreateTexture2D(&textureDesc, NULL, m_renderTargetTextureArray[i].GetAddressOf());
	
	}

	// Setup the description of the render target view.
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	// Create the render target views.
	for (i = 0; i < m_bufferCount; i++)
	{
		hr = sRENDER_DEVICE_MANAGER->CreateRenderTargetView(m_renderTargetViewArray[i],&HFVECTOR2(textureWidth,textureHeight),DXGI_FORMAT_R32G32B32A32_FLOAT);
		if (FAILED(hr))
		{
			return hr;
		}
	}

	// Setup the description of the shader resource view.
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	// Create the shader resource views.
	for (i = 0; i < m_bufferCount; i++)
	{
		m_shaderResourceViewArray[i]->SetSharderResorceView(sRENDER_DEVICE_MANAGER->GetSRViewFromRTView(m_renderTargetViewArray[i]));
	
		if (FAILED(hr))
		{
			return hr;
		}
	}



	// Setup the viewport for rendering.
	m_viewport.Width = (FLOAT)textureWidth;
	m_viewport.Height = (FLOAT)textureHeight;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0.0f;
	m_viewport.TopLeftY = 0.0f;

	return hr;
}


/**********************************************************************************************//**
 * @fn	void DeferredBuffers::SetRenderTargets(Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext)
 *
 * @brief	Sets render targets.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	deviceContext	Context for the device.
 **************************************************************************************************/

void GeometryBuffers::SetRenderTargets(Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext)
{
	// Bind the render target view array and depth stencil buffer to the output render pipeline.
	deviceContext->OMSetRenderTargets(m_bufferCount, m_renderTargetViewArray.data()->GetAddressOf(), sRENDER_DEVICE_MANAGER->GetCpDepthStencilView().Get());

	// Set the viewport.
	deviceContext->RSSetViewports(1, &m_viewport);

	return;
}

/**********************************************************************************************//**
 * @fn	void DeferredBuffers::ClearRenderTargets(Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext, FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha)
 *
 * @brief	Clears the render targets.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	deviceContext	Context for the device.
 * @param	red			 	The red.
 * @param	green		 	The green.
 * @param	blue		 	The blue.
 * @param	alpha		 	The alpha.
 **************************************************************************************************/

void GeometryBuffers::ClearRenderTargets(Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext, FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha)
{
	FLOAT color[4];
	int i;

	// Setup the color to clear the buffer to.
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	// bufferの数だけクリアする
	for (i = 0; i < m_bufferCount; i++)
	{
		if (m_renderTargetViewArray[i])
		{
			deviceContext->ClearRenderTargetView(m_renderTargetViewArray[i].Get(), color);
		}
	}
	/*
	if (m_depthStencilView)
	{
		// Depthもクリア
		deviceContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	} */
	return;
}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<CBaseTexture> DeferredBuffers::GetShaderResourceView(int view)
 *
 * @brief	Gets shader resource view.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	view	The view.
 *
 * @return	The shader resource view.
 **************************************************************************************************/

std::shared_ptr<BaseTexture2D>& GeometryBuffers::GetShaderResourceView(int view)
{
;
	return m_shaderResourceViewArray[view];
}