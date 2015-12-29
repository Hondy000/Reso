#include "../../Public/Task/TaskSystem.h"


bool TaskSystem::Update()
{
	for (auto it = m_spTaskList.begin(); it != m_spTaskList.end();it++)
	{
		(*it)->Update();
	}
	return true;
}

bool TaskSystem::Draw()
{
	for (auto it = m_spTaskList.begin(); it != m_spTaskList.end(); it++)
	{
		(*it)->Update();
	}
	return true;
}
