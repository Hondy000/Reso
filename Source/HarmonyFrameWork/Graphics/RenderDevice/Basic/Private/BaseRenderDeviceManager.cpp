/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\Renderer\Basic\CBaseRenderDeviceManager.cpp
 *
 * @brief	Implements the base render device manager class.
 **************************************************************************************************/

#include "../Public/BaseRenderDeviceManager.h"

/**********************************************************************************************//**
 * @fn	BaseRenderDeviceManager::BaseRenderDeviceManager()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 **************************************************************************************************/
/**
 * Default constructor.
 *
 * @author Kazuyuki
 * @date 2016/09/25
 */
BaseRenderDeviceManager::BaseRenderDeviceManager()
{
	// ŠÇ—s—ñ”z—ñ‚Ì‰Šú‰»
	m_transformArray.resize(HFTS_MAX);
};

std::shared_ptr<BaseRenderTarget> BaseRenderDeviceManager::GetDefaultRenderTarget(void)
{

}

std::shared_ptr<BaseRenderTarget> BaseRenderDeviceManager::GetMainRenderTarget(void)
{
	return std::shared_ptr<BaseRenderTarget>();
}

void BaseRenderDeviceManager::SetMainRenderTarget(std::shared_ptr<BaseRenderTarget> _renderTarget)
{

}

std::shared_ptr<BaseDepthStencilBuffer> BaseRenderDeviceManager::GetMainDepthStencil(void)
{

}

void BaseRenderDeviceManager::SetMainDepthStencil(std::shared_ptr<BaseDepthStencilBuffer> _depthStencil)
{

}
