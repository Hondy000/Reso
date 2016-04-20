/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Task\Private\TaskInterface.cpp
 *
 * @brief	Implements the task interface class.
 **************************************************************************************************/

#include "../Public/TaskInterface.h"

/**********************************************************************************************//**
 * @fn	bool IBaseTask::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool IBaseTask::Init()
{
	m_taskId = std::hash<IBaseTask*>()(this);

	return true;
}

/**********************************************************************************************//**
 * @fn	bool IBaseTask::LoadTaskData(const std::string& path)
 *
 * @brief	Loads task data.
 *
 * @author	Kazuyuki Honda
 *
 * @param	path	Full pathname of the file.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool IBaseTask::LoadTaskData(const std::string& path)
{
	return false;
}

