/**********************************************************************************************//**
 * @file	Source\GameSource\Charactor\Enemy\Private\EnemyStates.cpp
 *
 * @brief	Implements the enemy states class.
 **************************************************************************************************/

#include "../Public/EnemyStates.h"
#include "../Public/EnemyActor.h"

using namespace std;

/**********************************************************************************************//**
 * @def	CAST_ENEMY_ACTOR(task) (dynamic_pointer_cast<EnemyActor>(task))
 *
 * @brief	A macro that defines cast enemy actor.
 *
 * @author	Kazuyuki Honda
 *
 * @param	task	The task.
 **************************************************************************************************/

#define CAST_ENEMY_ACTOR(task) (dynamic_pointer_cast<EnemyActor>(task))

/**********************************************************************************************//**
 * @fn	void BasicEnemyAliveBeingState::Enter()
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void BasicEnemyAliveBeingState::Enter()
{
	CAST_STATIC_MESH_COMPORNENT(
		CAST_ENEMY_ACTOR(m_wpTask.lock())->GetCompornent(typeid(StaticMeshCompornent).name()))->LoadMesh("Resource/Mesh/Sphere.hfm");
	RegisterState(std::make_shared<BasicEnemyWaitActionState>(), m_wpTask.lock());
	RegisterState(std::make_shared<BasicEnemyWaitMoveState>(), m_wpTask.lock());
	(m_wpTask.lock())->RegisterVariable("hitpoint", 100.0f);
}

/**********************************************************************************************//**
 * @fn	void BasicEnemyAliveBeingState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void BasicEnemyAliveBeingState::Execute()
{
	UpdateState(m_wpTask.lock());
	if(m_wpTask.lock()->GetVariable<FLOAT>("hitpoint")->GetValue() <= 0)
	{
		m_isChangeState = true;
	}


}

/**********************************************************************************************//**
 * @fn	void BasicEnemyAliveBeingState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void BasicEnemyAliveBeingState::Exit()
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> BasicEnemyAliveBeingState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

std::shared_ptr<IState> BasicEnemyAliveBeingState::GetNewState(void)
{
	return std::make_shared<BasicEnemyDeadBeingState>();
}

/**********************************************************************************************//**
 * @fn	void BasicEnemyDeadBeingState::Enter()
 *
 * @brief	Ž€–S.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void BasicEnemyDeadBeingState::Enter()
{

}

/**********************************************************************************************//**
 * @fn	void BasicEnemyDeadBeingState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void BasicEnemyDeadBeingState::Execute()
{

}

/**********************************************************************************************//**
 * @fn	void BasicEnemyDeadBeingState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void BasicEnemyDeadBeingState::Exit()
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> BasicEnemyDeadBeingState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

std::shared_ptr<IState> BasicEnemyDeadBeingState::GetNewState(void)
{
	return std::make_shared<BasicEnemyAliveBeingState>();
}

/**********************************************************************************************//**
 * @fn	void BasicEnemyWaitActionState::Enter()
 *
 * @brief	’âŽ~.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void BasicEnemyWaitActionState::Enter()
{

}

/**********************************************************************************************//**
 * @fn	void BasicEnemyWaitActionState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void BasicEnemyWaitActionState::Execute()
{

}

/**********************************************************************************************//**
 * @fn	void BasicEnemyWaitActionState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void BasicEnemyWaitActionState::Exit()
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> BasicEnemyWaitActionState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

std::shared_ptr<IState> BasicEnemyWaitActionState::GetNewState(void)
{
	return std::make_shared<BasicEnemyWaitActionState>();
}

/**********************************************************************************************//**
 * @fn	void BasicEnemyWaitMoveState::Enter()
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void BasicEnemyWaitMoveState::Enter()
{

}

/**********************************************************************************************//**
 * @fn	void BasicEnemyWaitMoveState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void BasicEnemyWaitMoveState::Execute()
{

}

/**********************************************************************************************//**
 * @fn	void BasicEnemyWaitMoveState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void BasicEnemyWaitMoveState::Exit()
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> BasicEnemyWaitMoveState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

std::shared_ptr<IState> BasicEnemyWaitMoveState::GetNewState(void)
{
	return std::make_shared<BasicEnemyStraightMoveState>();
}

/**********************************************************************************************//**
 * @fn	void BasicEnemyStraightMoveState::Enter()
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void BasicEnemyStraightMoveState::Enter()
{

}

/**********************************************************************************************//**
 * @fn	void BasicEnemyStraightMoveState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void BasicEnemyStraightMoveState::Execute()
{

}

/**********************************************************************************************//**
 * @fn	void BasicEnemyStraightMoveState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void BasicEnemyStraightMoveState::Exit()
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> BasicEnemyStraightMoveState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

std::shared_ptr<IState> BasicEnemyStraightMoveState::GetNewState(void)
{
	return std::make_shared<BasicEnemyWaitMoveState>();
}
