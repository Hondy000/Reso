#include "../Public/TaskSystem.h"
#include "../../../Graphics/RenderDevice/Basic/Public/RendererManager.h"  
#include "../../../Graphics/Public/RenderCommand.h"
#include "../../Actor/Public/ActorInterface.h"

using namespace std;

BOOL TaskSystem::RegisterTask(const std::string& name, std::shared_ptr<IBaseTask> task)
{
	pair<string, shared_ptr<IBaseTask>> key;
	key.first = name;
	key.second = task;
	auto res = m_spTaskMap.insert(key);
	if(res.second)
	{

		m_spTaskList.push_back(task);
		task->Init();
		task->SetTaskName(name);
		return true;
	}
	return false;
}

BOOL TaskSystem::RegisterRenderCommand(std::shared_ptr<RenderCommand> task)
{
	m_spDrawList.push_back(task);
	return true;
}

BOOL TaskSystem::Update()
{
	UpdateActorsPreviousTransform();
	for (auto it = m_spTaskList.begin(); it != m_spTaskList.end();it++)
	{
		(*it)->Update();
	}
	return true;
}

void TaskSystem::UpdateActorsPreviousTransform()
{
	std::vector < std::shared_ptr<IBaseTask>> actorArray;

	SearchGroupByType<IActor>(actorArray);
	for (auto it = actorArray.begin(); it != actorArray.end();it++)
	{
		std::dynamic_pointer_cast<IActor>(*it)
			->SetPreviousTransform(
				std::dynamic_pointer_cast<IActor>(*it)->GetTransform()
				);
	}
}

/**********************************************************************************************//**
 * @fn	BOOL TaskSystem::Render()
 *
 * @brief	Renders this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

BOOL TaskSystem::Render()
{
	m_spDrawList.sort([](const std::shared_ptr<RenderCommand>& commmandA,const std::shared_ptr<RenderCommand>& commmandB) 
	{
		return(commmandA->GetRenderPriority() < commmandB->GetRenderPriority());
	});

	sRENDER_DEVICE_MANAGER->ClearScreen();
	sRENDER_DEVICE_MANAGER->BeginRender();

	for (auto it = m_spDrawList.begin(); it != m_spDrawList.end(); it++)
	{
		//(*it)->Command();
	}
	sRENDER_DEVICE_MANAGER->EndRender();
	m_spDrawList.clear();
	return true;
}

BOOL TaskSystem::SearchByTaskID(DWORD m_id, std::shared_ptr<IBaseTask>sptask)
{
	for (auto it = m_spTaskList.begin(); it != m_spTaskList.end(); it++)
	{
		if ((*it)->GetTaskId() == m_id)
		{
			sptask = *it;
			return true;
		}
	}
	return false;
}

BOOL TaskSystem::SearchByTaskName(const string& name, std::shared_ptr<IBaseTask>sptask)
{
	auto resFind = m_spTaskMap.find(name);
	if (resFind != m_spTaskMap.end())
	{
		sptask = resFind->second;
		return true;
	}
	sptask = nullptr;
	return false;
}


std::shared_ptr<IBaseTask>TaskSystem::SearchByTaskName(const string& name)
{
	auto resFind = m_spTaskMap.find(name);
	if (resFind != m_spTaskMap.end())
	{
		return resFind->second;
	}
	return nullptr;
}