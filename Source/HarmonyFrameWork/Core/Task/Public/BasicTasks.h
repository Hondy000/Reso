#pragma once


#include "TaskInterface.h"
#include "../../Public/ReflectionSystem.h"

class AddTask
	:
	public IBaseTask
{
public:
	AddTask()
	{
		
	};
	~AddTask()
	{
		
	};

	bool Update()
	{
		return true;
	}

private:
	GLOBAL_ID m_id1;
	GLOBAL_ID m_id2;

	std::string m_typeName1;
	std::string m_typeName2;

	std::string m_variableName1;
	std::string m_variableName2;
};
