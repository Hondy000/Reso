
#include "../Public/TaskInterface.h"

BOOL IBaseTask::Init()
{
	m_taskId = std::hash<IBaseTask*>()(this);

	return true;
}

BOOL IBaseTask::LoadTaskData(const std::string& path)
{
	return false;
}

