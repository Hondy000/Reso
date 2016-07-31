#pragma once
#include "../../Public/Common.h"
#include "../../Public/IBaseObject.h"

class IState;
class IBaseTask;

class IStateHolder
{
public:
	IStateHolder();
	virtual~IStateHolder();

	virtual void UpdateState(std::shared_ptr<IBaseTask> actor);

	bool RegisterState(std::shared_ptr<IState> state,std::weak_ptr<IBaseTask> actor);
protected:
	std::list<std::shared_ptr<IState>> m_stateList;
};
