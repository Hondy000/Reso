/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\State\Private\StateHolder.cpp
 *
 * @brief	Implements the state holder class.
 **************************************************************************************************/

#include "../Public/StateHolder.h"
#include "../../Task/Public/TaskSystem.h"
#include "../Public/IState.h"

/**********************************************************************************************//**
 * @fn	IStateHolder::IStateHolder()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

IStateHolder::IStateHolder()
{
}

/**********************************************************************************************//**
 * @fn	IStateHolder::~IStateHolder()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

IStateHolder::~IStateHolder()
{

}

/**********************************************************************************************//**
 * @fn	void IStateHolder::UpdateState(std::shared_ptr<IBaseTask> actor)
 *
 * @brief	Updates the state described by actor.
 *
 * @author	Kazuyuki Honda
 *
 * @param	actor	The actor.
 **************************************************************************************************/

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

/**********************************************************************************************//**
 * @fn	bool IStateHolder::RegisterState(std::shared_ptr<IState> state, std::weak_ptr<IBaseTask> actor)
 *
 * @brief	Registers the state.
 *
 * @author	Kazuyuki Honda
 *
 * @param	state	The state.
 * @param	actor	The actor.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool IStateHolder::RegisterState(std::shared_ptr<IState> state, std::weak_ptr<IBaseTask> actor)
{
	m_stateList.push_back(state);
	state->SetWpTask(actor);
	state->Enter();
	return true;
}
