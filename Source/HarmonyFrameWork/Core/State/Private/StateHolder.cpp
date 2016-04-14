#include "../Public/StateHolder.h"
#include "../../Task/Public/TaskSystem.h"
#include "../Public/IState.h"

IStateHolder::IStateHolder()
{
}
IStateHolder::~IStateHolder()
{

}

void IStateHolder::UpdateState(std::shared_ptr<IBaseTask> actor)
{
	for (auto it = m_stateList.begin(); it != m_stateList.end(); it++)
	{
		if ((*it)->IsChange())
		{
			(*it)->Exit();
			*it = (*it)->GetNewState();
			(*it)->SetWpTask(actor);
			(*it)->Enter();
		}
		(*it)->Execute();
	}
};

BOOL IStateHolder::RegisterState(std::shared_ptr<IState> state, std::weak_ptr<IBaseTask> actor)
{
	m_stateList.push_back(state);
	state->SetWpTask(actor);
	state->Enter();
	return true;
}
