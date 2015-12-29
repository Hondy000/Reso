#pragma once
#include "TaskInterface.h"

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

	bool Update();

	bool Draw();


private:
	std::list<std::shared_ptr<IBaseTask>> m_spTaskList;

};
