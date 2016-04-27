/**********************************************************************************************//**
 * @file	Source\GameSource\Charactor\Enemy\Private\EnemyStates.cpp
 *
 * @brief	Implements the enemy states class.
 **************************************************************************************************/

#include "../Public/Level1EnemyStates.h"
#include "../Public/EnemyActor.h"
#include "..\..\..\..\HarmonyFrameWork\Core\Task\Public\TaskSystem.h"

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

void Level1EnemyAliveBeingState::Enter()
{
	CAST_STATIC_MESH_COMPORNENT(
		CAST_ENEMY_ACTOR(m_wpTask.lock())->GetCompornent(typeid(StaticMeshCompornent).name()))->LoadMesh("Resource/Mesh/Level1Enenmy.hfm");
	RegisterState(std::make_shared<Level1EnemyWaitMoveState>(), m_wpTask.lock());
	(m_wpTask.lock())->RegisterVariable("hitpoint", 100.0f);
	GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_playerPosition")
		= std::dynamic_pointer_cast<IActor>(sTASK_SYSTEM->SearchByTaskName("player"))->GetTransform()->GetPosition();
}

/**********************************************************************************************//**
 * @fn	void BasicEnemyAliveBeingState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void Level1EnemyAliveBeingState::Execute()
{
	UpdateState(m_wpTask.lock());
	// player position update
	GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_playerPosition")
		= std::dynamic_pointer_cast<IActor>(sTASK_SYSTEM->SearchByTaskName("player"))->GetTransform()->GetPosition();

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

void Level1EnemyAliveBeingState::Exit()
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

std::shared_ptr<IState> Level1EnemyAliveBeingState::GetNewState(void)
{
	return std::make_shared<Level1EnemyDeadBeingState>();
}

/**********************************************************************************************//**
 * @fn	void BasicEnemyDeadBeingState::Enter()
 *
 * @brief	Ž€–S.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void Level1EnemyDeadBeingState::Enter()
{

}

/**********************************************************************************************//**
 * @fn	void BasicEnemyDeadBeingState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void Level1EnemyDeadBeingState::Execute()
{

}

/**********************************************************************************************//**
 * @fn	void BasicEnemyDeadBeingState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void Level1EnemyDeadBeingState::Exit()
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

std::shared_ptr<IState> Level1EnemyDeadBeingState::GetNewState(void)
{
	return std::make_shared<Level1EnemyDeadBeingState>();
}


/**********************************************************************************************//**
 * @fn	void BasicEnemyWaitMoveState::Enter()
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void Level1EnemyWaitMoveState::Enter()
{

}

/**********************************************************************************************//**
 * @fn	void BasicEnemyWaitMoveState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void Level1EnemyWaitMoveState::Execute()
{

}

/**********************************************************************************************//**
 * @fn	void BasicEnemyWaitMoveState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void Level1EnemyWaitMoveState::Exit()
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

std::shared_ptr<IState> Level1EnemyWaitMoveState::GetNewState(void)
{
	return std::make_shared<Level1EnemyMoveState>();
}

void Level1EnemyMoveState::Enter()
{

}

void Level1EnemyMoveState::Execute()
{

	HFVECTOR3 direction = 
	HFVec3Normalize(
		GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_playerPosition")
		-
		GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").GetPosition()
	);

}

void Level1EnemyMoveState::Exit()
{

}

std::shared_ptr<IState> Level1EnemyMoveState::GetNewState(void)
{
	return std::make_shared<Level1EnemyWaitMoveState>();
}

void Level1EnemyArrivalState::Enter()
{

}

void Level1EnemyArrivalState::Execute()
{

}
void Level1EnemyArrivalState::Exit()
{

}

std::shared_ptr<IState> Level1EnemyArrivalState::GetNewState(void)
{
	return std::make_shared<Level1EnemyArrivalState>();
}
