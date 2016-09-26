/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Task\Private\TaskSystem.cpp
 *
 * @brief	Implements the task system class.
 **************************************************************************************************/

#include "../Public/TaskSystem.h"
#include "../../../Graphics/RenderDevice/Basic/Public/RendererManager.h"  
#include "../../../Graphics/Public/BaseGraphicsCommand.h"
#include "../../Actor/Public/ActorInterface.h"
#include "../../../Debug/Public/Debug.h"
#include "../../../Graphics/RenderObject/Public/BaseRenderMeshObject.h"
#include "../../../Input/Public/InputManager.h"
#include "..\..\..\Graphics\Shader\Basic\Public\BaseGraphicsShader.h"

using namespace std;

/**********************************************************************************************//**
 * @fn	bool TaskSystem::RegisterTask(const std::string& name, std::shared_ptr<IBaseTask> task)
 *
 * @brief	Registers the task.
 *
 * @author	Kazuyuki Honda
 *
 * @param	name	The name.
 * @param	task	The task.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool TaskSystem::RegisterTask(const std::string& name, std::shared_ptr<IBaseTask> task)
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
		std::shared_ptr<BaseRenderMeshObject>render = std::dynamic_pointer_cast<BaseRenderMeshObject>(task);
		if(render)
		{
			render->Setup();
		}
		return true;
	}
	return false;
}

bool TaskSystem::RemoveTask(std::shared_ptr<IBaseTask> task)
{
	for (auto it = m_spTaskList.begin(); it != m_spTaskList.end();)
	{
		if (*it == task)
		{
			it = m_spTaskList.erase(it);
			return true;
			continue;
		}
		it++;
	}
	return false;
}


/**********************************************************************************************//**
 * @fn	bool TaskSystem::RegisterRenderCommand(std::shared_ptr<RenderCommand> task)
 *
 * @brief	Registers the render command described by task.
 *
 * @author	Kazuyuki Honda
 *
 * @param	task	The task.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool TaskSystem::RegisterGraphicsCommand(std::shared_ptr<BaseGraphicsCommand> task)
{
	m_spGraphicsCommandList.push_back(task);
	return true;
}

bool TaskSystem::RemoveGraphicsCommand(std::shared_ptr<BaseGraphicsCommand> command)
{
	for (auto it = m_spGraphicsCommandList.begin(); it != m_spGraphicsCommandList.end();)
	{
		if (*it == command)
		{
			it = m_spGraphicsCommandList.erase(it);
			return true;
			continue;
		}
		it++;
	}
	return false;
}

/**********************************************************************************************//**
 * @fn	bool TaskSystem::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/
bool TaskSystem::Update()
{

	m_spTaskList.sort([](const std::shared_ptr<IBaseTask>& commmandA, const std::shared_ptr<IBaseTask>& commmandB)
	{
		// 昇順ソート
		return(commmandA->GetUpdatePriority() < commmandB->GetUpdatePriority());
	});
	UpdateActorsPreviousTransform();
	for (auto it = m_spTaskList.begin(); it != m_spTaskList.end();)
	{
		if ((*it)->CheckUsageFlag())
		{					  
			(*it)->Update();
		}
		if ((*it)->GetIsDestroy())
		{
			it = m_spTaskList.erase(it);
			continue;
		}
		it++;
	}
	return true;
}

/**********************************************************************************************//**
 * @fn	void TaskSystem::UpdateActorsPreviousTransform()
 *
 * @brief	Updates the actors previous transform.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

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
 * @fn	bool TaskSystem::Render()
 *
 * @brief	Renders this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool TaskSystem::Render()
{
	m_spGraphicsCommandList.sort([](const std::shared_ptr<BaseGraphicsCommand>& commmandA,const std::shared_ptr<BaseGraphicsCommand>& commmandB) 
	{
		// 昇順ソート
		return(
			commmandA->GetRenderPriority() 
			<
			commmandB->GetRenderPriority());
	});

	sRENDER_DEVICE_MANAGER->ClearScreen();
	sRENDER_DEVICE_MANAGER->BeginRender();

	for (auto it = m_spGraphicsCommandList.begin(); it != m_spGraphicsCommandList.end(); it++)
	{

		(*it)->Update();
	}
	sRENDER_DEVICE_MANAGER->EndRender();
	return true;
}

/**********************************************************************************************//**
 * @fn	bool TaskSystem::SearchByTaskID(GLOBAL_ID m_id, std::shared_ptr<IBaseTask>&sptask)
 *
 * @brief	Searches for the first task identifier.
 *
 * @author	Kazuyuki Honda
 *
 * @param	m_id		  	The identifier.
 * @param [in,out]	sptask	The sptask.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool TaskSystem::SearchByTaskID(GLOBAL_ID m_id, std::shared_ptr<IBaseTask>&sptask)
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

/**********************************************************************************************//**
 * @fn	bool TaskSystem::SearchByTaskName(const string& name, std::shared_ptr<IBaseTask>sptask)
 *
 * @brief	Searches for the first task name.
 *
 * @author	Kazuyuki Honda
 *
 * @param	name	  	The name.
 * @param	parameter2	The second parameter.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool TaskSystem::SearchByTaskName(const string& name, std::shared_ptr<IBaseTask>sptask)
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

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IBaseTask>TaskSystem::SearchByTaskName(const string& name)
 *
 * @brief	Constructor.
 *
 * @author	Kazuyuki Honda
 *
 * @tparam	IBaseTask	Type of the base task.
 * @param	name	The name.
 **************************************************************************************************/

std::shared_ptr<IBaseTask>TaskSystem::SearchByTaskName(const string& name)
{
	auto resFind = m_spTaskMap.find(name);
	if (resFind != m_spTaskMap.end())
	{
		return resFind->second;
	}
	return nullptr;
}