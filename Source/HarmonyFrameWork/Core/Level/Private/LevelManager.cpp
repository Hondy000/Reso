/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Level\Private\LevelManager.cpp
 *
 * @brief	Implements the level manager class.
 **************************************************************************************************/

#include "../Public/LevelManager.h"
#include "../../../../GameSource/Level/Public/LevelGenerated.h"
#include "../../Task/Public/TaskSystem.h"

/**********************************************************************************************//**
 * @fn	bool LevelManager::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool LevelManager::Init()
{
	LevelGenerated();
	m_spLevel = std::dynamic_pointer_cast<IBaseLevel>(ReflectionSystem::GetInstance()->Create("class ModelViewLevel"));
	TaskSystem::GetInstance()->RegisterTask(typeid(m_spLevel).name(),m_spLevel);
	return false;
}

/**********************************************************************************************//**
 * @fn	bool LevelManager::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool LevelManager::Update()
{
	return false;
}

/**********************************************************************************************//**
 * @fn	void LevelManager::Reset()
 *
 * @brief	Resets this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void LevelManager::Reset()
{
}
