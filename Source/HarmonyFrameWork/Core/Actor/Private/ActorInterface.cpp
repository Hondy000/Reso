/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Actor\Private\ActorInterface.cpp
 *
 * @brief	Implements the actor interface class.
 **************************************************************************************************/

#include "../Public/ActorInterface.h"
#include "../../../Graphics/RenderObject/Public/BaseRenderMeshObject.h"

using namespace std;

IActor::IActor()
{
	Init();
};

/**********************************************************************************************//**
 * @fn	IActor::~IActor()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

IActor::~IActor()
{
	for (auto it = m_compornentMap.begin(); it != m_compornentMap.end();it++)
	{
		(*it).second->Destroy();
	}
	m_compornentMap.clear();
}

/**********************************************************************************************//**
 * @fn	bool IActor::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool IActor::Init()
{
	m_transform = (std::make_shared<Transform>());
	
	RegisterVariable("m_transform", m_transform);
	// 初期化タスクを登録


	// 読み込みや初期化
	SortTaskByPriority();
	for (auto it = m_taskList.begin(); it != m_taskList.end();)
	{
		(*it)->Update();
		// タスク消去
		if ((*it)->CheckDestroy())
		{
			it = m_taskList.erase(it);
			continue;
		}
		it++;
	}

	// メインタスクを登録
	return true;
}

/**********************************************************************************************//**
 * @fn	bool IActor::RegisterCompornent(const std::string& compornentName, std::shared_ptr<ICompornent> compornent)
 *
 * @brief	Registers the compornent.
 *
 * @author	Kazuyuki Honda
 *
 * @param	compornentName	Name of the compornent.
 * @param	compornent	  	The compornent.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool IActor::RegisterCompornent(const std::string& compornentName, std::shared_ptr<ICompornent> compornent)
{
	if (compornent->Init())
	{
		compornent->SetTaskName(compornentName);
		pair<string, shared_ptr<ICompornent>> compornentPair;
		compornentPair.first = compornentName;
		compornentPair.second = compornent;
		compornent->SetParentActorGlobalID(IBaseTask::GetTaskId());
		compornent->SetParentActor(shared_from_this());
		m_compornentMap.insert(compornentPair);
		m_taskList.push_back(compornent);
		std::shared_ptr<BaseRenderMeshObject>render = std::dynamic_pointer_cast<BaseRenderMeshObject>(compornent);
		if (render)
		{
			render->Setup();
		}
		return true;
	}
	return false;
}

/**********************************************************************************************//**
 * @fn	void IActor::SortTaskByPriority()
 *
 * @brief	Sort task by priority.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void IActor::SortTaskByPriority()
{
	m_taskList.sort([](shared_ptr<IBaseTask> taskA, shared_ptr<IBaseTask> taskB)
		-> PRIORITY
	{
		return(taskA->GetUpdatePriority() > taskB->GetUpdatePriority());
	});
}

/**********************************************************************************************//**
 * @fn	bool IActor::UpdateAllTask()
 *
 * @brief	Updates all task.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool IActor::UpdateAllTask()
{
	SortTaskByPriority();
	for (auto it = m_taskList.begin(); it != m_taskList.end();)
	{
		(*it)->Update();
		// タスク消去
		if ((*it)->CheckDestroy())	   
		{
			it = m_taskList.erase(it);
			continue;
		}
		it++;
	}
	return true;

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<ICompornent> IActor::GetCompornent(const std::string& name)
 *
 * @brief	Gets a compornent.
 *
 * @author	Kazuyuki Honda
 *
 * @param	name	The name.
 *
 * @return	The compornent.
 **************************************************************************************************/

std::shared_ptr<ICompornent> IActor::GetCompornent(const std::string& name)
{
	auto it = m_compornentMap.find(name);
	if (it != m_compornentMap.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}

}
