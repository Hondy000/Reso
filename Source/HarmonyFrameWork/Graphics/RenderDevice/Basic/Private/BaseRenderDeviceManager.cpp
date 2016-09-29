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
	return m_defaultRenderTarget;
}
std::shared_ptr<BaseDepthStencilBuffer> BaseRenderDeviceManager::GetDefaultDepthStencil(void)
{
	return m_defaultDepthStencilBuffer;
}

std::shared_ptr<BaseRenderTarget> BaseRenderDeviceManager::GetMainRenderTarget(void)
{
	return m_usingRenderTarget;
}

void BaseRenderDeviceManager::SetMainRenderTarget(std::shared_ptr<BaseRenderTarget> _renderTarget)
{
	m_usingRenderTarget = _renderTarget;
}

std::shared_ptr<BaseDepthStencilBuffer> BaseRenderDeviceManager::GetMainUseDepthStencil(void)
{
	return m_usingDepthStencilBuffer;
}

void BaseRenderDeviceManager::SetMainUseDepthStencil(std::shared_ptr<BaseDepthStencilBuffer> _depthStencil)
{
	m_usingDepthStencilBuffer = _depthStencil;
}
