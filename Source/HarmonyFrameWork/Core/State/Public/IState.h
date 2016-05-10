#pragma once
#include "../../Public/Common.h"
#include "../../Public/IBaseObject.h"
#include "StateHolder.h"

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
	const bool IsChange()const
	{
		return m_isChangeState;
	}

	bool IsEndState()
	{
		return m_isEndState;
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
	bool m_isChangeState;
	bool m_isEndState;
	std::weak_ptr<IBaseTask> m_wpTask;
};
