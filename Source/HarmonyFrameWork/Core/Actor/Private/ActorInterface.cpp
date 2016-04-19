#include "../Public/ActorInterface.h"

using namespace std;
IActor::~IActor()
{
	for (auto it = m_compornentMap.begin(); it != m_compornentMap.end();it++)
	{
		(*it).second->Destroy();
	}
	m_compornentMap.clear();
}

BOOL IActor::Init()
{
	m_transform = std::make_shared<Transform>();
	
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

BOOL IActor::RegisterCompornent(const std::string& compornentName, std::shared_ptr<ICompornent> compornent)
{
	if (compornent->Init())
	{
		pair<string, shared_ptr<ICompornent>> compornentPair;
		compornentPair.first = compornentName;
		compornentPair.second = compornent;
		compornent->SetParentActorGlobalID(IBaseTask::GetTaskId());
		compornent->SetParentActor(shared_from_this());
		m_compornentMap.insert(compornentPair);
		m_taskList.push_back(compornent);
		return true;
	}
	return false;
}

void IActor::SortTaskByPriority()
{
	m_taskList.sort([](shared_ptr<IBaseTask> taskA, shared_ptr<IBaseTask> taskB)
		-> PRIORITY
	{
		return(taskA->GetUpdatePriority() > taskB->GetUpdatePriority());
	});
}

BOOL IActor::UpdateAllTask()
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
