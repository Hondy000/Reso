#pragma once
#include "TaskInterface.h"		

#define sTASK_SYSTEM (TaskSystem::GetInstance())

class RenderCommand;

class TaskSystem
{
private:
	TaskSystem() {};
public:
	virtual ~TaskSystem() {};

	static TaskSystem* GetInstance()
	{
		static TaskSystem instance;
		return &instance;
	}

	BOOL RegisterTask(const std::string& name, std::shared_ptr<IBaseTask> task);

	BOOL RegisterRenderCommand(std::shared_ptr<RenderCommand> task);

	BOOL Update();


	BOOL Render();

	template<class T> BOOL SearchGroupByType(std::list<std::shared_ptr<T>>typeList)
	{
		for (auto it = m_spTaskList.begin(); it != m_spTaskList.end(); it++)
		{
			std::string typeName = typeid(T).name();
			if (typeid(*it).before(typeid(T)))
			{
				typeList.push_back(*it);
			}
		}
		return false;
	}

	template<class T> BOOL SearchGroupByType(std::vector<std::shared_ptr<IBaseTask>> typeArray)
	{
		for (auto it = m_spTaskList.begin(); it != m_spTaskList.end(); it++)
		{
			std::string typeName = typeid(T).name();
			if (typeid(*it).before(typeid(T)))
			{
				typeArray.push_back(*it);
			}
		}
		return false;
	}

	BOOL SearchByTaskID(DWORD m_id, std::shared_ptr<IBaseTask>sptask);
	BOOL SearchByTaskName(const std::string& name, std::shared_ptr<IBaseTask> sptask);
	std::shared_ptr<IBaseTask> SearchByTaskName(const std::string& name);
private:
	// システム側で前位置を一括更新
	void UpdateActorsPreviousTransform();

	std::list<std::shared_ptr<IBaseTask>> m_spTaskList;
	std::unordered_map<std::string,std::shared_ptr<IBaseTask>> m_spTaskMap;
	std::list<std::shared_ptr<RenderCommand>> m_spDrawList;

};
