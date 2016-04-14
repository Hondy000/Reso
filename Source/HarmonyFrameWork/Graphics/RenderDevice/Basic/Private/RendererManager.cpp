/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\Renderer\Basic\CRendererManager.cpp
 *
 * @brief	Implements the renderer manager class.
 **************************************************************************************************/

#include "../Public/RendererManager.h"		
#ifdef DIRECTX11										
#include "../../DirectX/ver.11//Public/DirectX11RenderDeviceManager.h"
#endif

/**********************************************************************************************//**
  * @fn	CRendererManager::CRendererManager()
  *
  * @brief	Default constructor.
  *
  * @author	Kazuyuki Honda
  * @date	2015/08/02
  **************************************************************************************************/

RendererManager::RendererManager()
{
}

/**********************************************************************************************//**
 * @fn	CRendererManager::~CRendererManager()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 **************************************************************************************************/

RendererManager::~RendererManager()
{
}

/**********************************************************************************************//**
 * @fn	BOOL CRendererManager::Setup(void)
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

BOOL RendererManager::Setup(void)
{
#ifdef DIRECTX11
	m_spRenderDevice = std::shared_ptr<DirectX11RenderDeviceManager>(new DirectX11RenderDeviceManager);

#endif

	return true;
}