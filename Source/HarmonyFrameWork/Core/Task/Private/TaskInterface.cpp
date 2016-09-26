/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Task\Private\TaskInterface.cpp
 *
 * @brief	Implements the task interface class.
 **************************************************************************************************/

#include "../Public/TaskInterface.h"

/**=================================================================================================
 * @fn IBaseTask::~IBaseTask()
 *
 * @brief Finalizes an instance of the IBaseTask class.
 *
 * @author Kazuyuki
 *===============================================================================================**/

IBaseTask::~IBaseTask()
{

}

/**=================================================================================================
 * @fn bool IBaseTask::Init()
 *
 * @brief Initialises this object.
 *
 * @author Kazuyuki
 *
 * @return true if it succeeds, false if it fails.
 *===============================================================================================**/

bool IBaseTask::Init()
{
	m_taskId = std::hash<IBaseTask*>()(this);

	return true;
}

/**=================================================================================================
 * @fn void IBaseTask::UpdateChildTask()
 *
 * @brief Updates the child task.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void IBaseTask::UpdateChildTask()
{
	for (auto it = m_childTaskList.begin();it != m_childTaskList.end();)
{
		if ((*it)->CheckUsageFlag())
		{
			(*it)->Update();
		}
		if ((*it)->GetIsDestroy())
		{
			it = m_childTaskList.erase(it);
			continue;
		}
		it++;
	}
}


void IBaseTask::Reset()
{

}

/**=================================================================================================
 * @fn bool IBaseTask::LoadTaskData(const std::string& path)
 *
 * @brief Loads task data.
 *
 * @author Kazuyuki
 *
 * @param path Full pathname of the file.
 *
 * @return true if it succeeds, false if it fails.
 *===============================================================================================**/

bool IBaseTask::LoadTaskData(const std::string& path)
{
	return false;
}

/**=================================================================================================
 * @fn bool IBaseTask::CheckUsageFlag()
 *
 * @brief Determines if we can check usage flag.
 *
 * @author Kazuyuki
 *
 * @return true if it succeeds, false if it fails.
 *===============================================================================================**/

bool IBaseTask::CheckUsageFlag()
{
	return m_isUsage;
}

/**=================================================================================================
 * @fn bool IBaseTask::CheckDestroy()
 *
 * @brief Determines if we can check destroy.
 *
 * @author Kazuyuki
 *
 * @return true if it succeeds, false if it fails.
 *===============================================================================================**/

bool IBaseTask::CheckDestroy()
{
	return GetIsDestroy();
}

/**=================================================================================================
 * @fn bool IBaseTask::AllowUpdate()
 *
 * @brief Determine if we allow update.
 *
 * @author Kazuyuki
 *
 * @return true if we allow update, false if not.
 *===============================================================================================**/

bool IBaseTask::AllowUpdate()
{
	return true;
}

/**=================================================================================================
 * @fn const IBaseTask::PRIORITY& IBaseTask::GetUpdatePriority(void) const
 *
 * @brief Gets update priority.
 *
 * @author Kazuyuki
 *
 * @return The update priority.
 *===============================================================================================**/

const IBaseTask::PRIORITY& IBaseTask::GetUpdatePriority(void) const
{
	return(m_updatePriority);
}

/**=================================================================================================
 * @fn void IBaseTask::SetUpdatePriority(const PRIORITY& priority)
 *
 * @brief Sets update priority.
 *
 * @author Kazuyuki
 *
 * @param priority The priority.
 *===============================================================================================**/

void IBaseTask::SetUpdatePriority(const PRIORITY& priority)
{
	m_updatePriority = priority;
};

/**=================================================================================================
 * @fn const unsigned long& IBaseTask::GetTaskId(void) const
 *
 * @brief Gets task identifier.
 *
 * @author Kazuyuki
 *
 * @return The task identifier.
 *===============================================================================================**/

const unsigned long& IBaseTask::GetTaskId(void) const
{
	return(m_taskId);
};

/**=================================================================================================
 * @fn void IBaseTask::SetTaskId(const unsigned long& taskId)
 *
 * @brief Sets task identifier.
 *
 * @author Kazuyuki
 *
 * @param taskId Identifier for the task.
 *===============================================================================================**/

void IBaseTask::SetTaskId(const unsigned long& taskId)
{
	m_taskId = taskId;
};

bool IBaseTask::GetIsDestroy() const
{
	return m_isDestroy;
}

void IBaseTask::SetIsDestroy(bool _val)
{
	m_isDestroy = _val;
}

/**=================================================================================================
 * @fn const std::string& IBaseTask::GetTaskName(void) const
 *
 * @brief Gets task name.
 *
 * @author Kazuyuki
 *
 * @return The task name.
 *===============================================================================================**/

const std::string& IBaseTask::GetTaskName(void) const
{
	return m_name;
}

/**=================================================================================================
 * @fn void IBaseTask::SetTaskName(const std::string& name)
 *
 * @brief Sets task name.
 *
 * @author Kazuyuki
 *
 * @param name The name.
 *===============================================================================================**/

void IBaseTask::SetTaskName(const std::string& name)
{
	m_name = name;
}
