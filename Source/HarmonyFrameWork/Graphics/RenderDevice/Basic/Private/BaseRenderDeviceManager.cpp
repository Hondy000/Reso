/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\Renderer\Basic\CBaseRenderDeviceManager.cpp
 *
 * @brief	Implements the base render device manager class.
 **************************************************************************************************/

#include "../Public/BaseRenderDeviceManager.h"

/**********************************************************************************************//**
  * @fn	CBaseRenderDeviceManager::CBaseRenderDeviceManager()
  *
  * @brief	Default constructor.
  *
  * @author	Kazuyuki Honda
  * @date	2015/11/04
  **************************************************************************************************/

BaseRenderDeviceManager::BaseRenderDeviceManager()
{
	// �Ǘ��s��z��̏�����
	m_transformArray.resize(HFTS_MAX);
};