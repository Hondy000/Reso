/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Private\ReflectionSystem.cpp
 *
 * @brief	Implements the reflection system class.
 **************************************************************************************************/

#include "../Public/ReflectionSystem.h"

/**********************************************************************************************//**
 * @fn	void ReflectionSystem::Remove(const std::string& typeName)
 *
 * @brief	Removes the given typeName.
 *
 * @author	Kazuyuki Honda
 *
 * @param	typeName	The type name to remove.
 **************************************************************************************************/

void ReflectionSystem::Remove(const std::string& typeName)
{

	auto it = m_builderMap.find(typeName);
	if (it != m_builderMap.end())
	{
		m_builderMap.erase(it);
	}
}
