/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\Renderer\Basic\CRendererManager.cpp
 *
 * @brief	Implements the renderer manager class.
 **************************************************************************************************/

#include "../../../Public/Renderer/Basic/RendererManager.h"

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
 * @fn	bool CRendererManager::Setup(void)
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool RendererManager::Setup(void)
{
#ifdef DIRECTX11
	m_spRenderDevice = std::shared_ptr<DirectX11RenderDeviceManager>(new DirectX11RenderDeviceManager);

#endif

	return true;
}