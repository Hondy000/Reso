#pragma once
#include "../../../../Core/Public/Common.h"

class BaseRenderDeviceManager;

#ifdef DIRECTX11
#include "../../DirectX/ver.11/Public/DirectX11RenderDeviceManager.h"
#define sRENDER_DEVICE_MANAGER (std::static_pointer_cast<DirectX11RenderDeviceManager>(RendererManager::GetInstance()->GetSpRenderDevice()))
#define sRENDER_DEVICE ((sRENDER_DEVICE_MANAGER)->GetDevice())
#endif

class RendererManager
{
public:
	virtual ~RendererManager();

	static RendererManager* GetInstance(void)
	{
		static RendererManager singleton;
		return &singleton;
	}

	BOOL Setup(void);

	// Access the UpRenderDevice
	const std::shared_ptr<BaseRenderDeviceManager>& GetSpRenderDevice(void) const
	{
		return(m_spRenderDevice);
	};

private:
	RendererManager();
	std::shared_ptr<BaseRenderDeviceManager>m_spRenderDevice;
};
