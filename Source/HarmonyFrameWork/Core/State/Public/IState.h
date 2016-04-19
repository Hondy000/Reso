#pragma once
#include "../../Public/Common.h"
#include "../../Public/IBaseObject.h"
#include "StateHolder.h"
#define GET_TASK_VAR_PTR(spTask,typeName,varName)  (spTask->GetVariable<typeName>(varName)->GetValue())
#define GET_TASK_VAR(spTask,typeName,varName)  (*(spTask->GetVariable<typeName>(varName)->GetValue()))

class IBaseTask;

class IState
	:
	public IBaseObject,
	public IStateHolder
{
public:
	IState();
	virtual ~IState();

	virtual void Enter() = 0;
	virtual void Execute() = 0;
	const BOOL IsChange()const
	{
		return m_isChangeState;
	};
	virtual void Exit() = 0;

	virtual std::shared_ptr<IState> GetNewState(void) = 0;
	// Access the WpTask
	const std::weak_ptr<IBaseTask>& GetWpTask(void) const
	{
		return(m_wpTask);
	};
	void SetWpTask(const std::weak_ptr<IBaseTask>& wpTask)
	{
		m_wpTask = wpTask;
	};

protected:
	BOOL m_isChangeState;
	std::weak_ptr<IBaseTask> m_wpTask;
};
