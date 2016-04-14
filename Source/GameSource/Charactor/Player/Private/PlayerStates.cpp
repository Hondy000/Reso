#include "..\Public\PlayerStates.h"
#include "../../../../HarmonyFrameWork/Core/Task/Public/TaskInterface.h"
#include "../../../../HarmonyFrameWork/Math/Public/Transform.h"
#include "../../../../HarmonyFrameWork/Core/Actor/Public/ActorInterface.h"
#include "../../../../HarmonyFrameWork/Input/Public/InputManager.h"

using namespace std;

#define CAST_PLAYER_ACTOR(task) (dynamic_pointer_cast<PlayerActor>(task))

void PlayerAliveBeingState::Enter()
{

	m_wpTask.lock()->RegisterVariable("m_velocity", 0.0f);
	m_wpTask.lock()->RegisterVariable("m_direction", HFVECTOR3(0,1,1));
	m_wpTask.lock()->RegisterVariable("m_accceleration", 0.002f);
	RegisterState(std::make_shared<PlayerCruiseMoveState>(),m_wpTask.lock());
}

void PlayerAliveBeingState::Execute()
{
	UpdateState(m_wpTask.lock());
}

void PlayerAliveBeingState::Exit()
{

}

std::shared_ptr<IState> PlayerAliveBeingState::GetNewState(void)
{
	return std::make_shared<PlayerDeadBeingState>();
}

void PlayerDeadBeingState::Enter()
{

}

void PlayerDeadBeingState::Execute()
{

}

void PlayerDeadBeingState::Exit()
{

}

std::shared_ptr<IState> PlayerDeadBeingState::GetNewState(void)
{
	return std::make_shared<PlayerDeadBeingState>();
}

void PlayerCruiseMoveState::Enter()
{

}


void PlayerCruiseMoveState::Execute()
{
	/*
	if (*m_wpTask.lock()->GetVariable<FLOAT>("m_velocity")->GetValue() < 5)
	{
		*m_wpTask.lock()->GetVariable<FLOAT>("m_velocity")->GetValue() += *m_wpTask.lock()->GetVariable<FLOAT>("m_accceleration")->GetValue();

	}
	GET_TASK_VARIABLE_VALUE(Transform, "m_transform").SetPosition(
		GET_TASK_VARIABLE_VALUE(Transform, "m_transform").GetPosition() + (GET_TASK_VARIABLE_VALUE(HFVECTOR3, "m_direction") * GET_TASK_VARIABLE_VALUE(FLOAT, "m_velocity"))
		);

	dynamic_pointer_cast<IActor>(m_wpTask.lock())->GetCompornent("class StaticMeshCompornent") ->
		GetVariable<Transform>("m_transform")->GetValue()->SetPosition(
		GET_TASK_VARIABLE_VALUE(Transform,"m_transform").GetPosition() + (GET_TASK_VARIABLE_VALUE(HFVECTOR3,"m_direction") * GET_TASK_VARIABLE_VALUE(FLOAT,"m_velocity"))
		);
	  */
}

void PlayerCruiseMoveState::Exit()
{

}

std::shared_ptr<IState> PlayerCruiseMoveState::GetNewState(void)
{
	return std::make_shared<PlayerAcccelerationMoveState>();
}

void PlayerAcccelerationMoveState::Enter()
{

}

void PlayerAcccelerationMoveState::Execute()
{

}

void PlayerAcccelerationMoveState::Exit()
{

}

std::shared_ptr<IState> PlayerAcccelerationMoveState::GetNewState(void)
{
	return std::make_shared<PlayerCruiseMoveState>();
}

void PlayerDecelerationMoveState::Enter()
{

}

void PlayerDecelerationMoveState::Execute()
{

}

void PlayerDecelerationMoveState::Exit()
{

}

std::shared_ptr<IState> PlayerDecelerationMoveState::GetNewState(void)
{
	return std::make_shared<PlayerDecelerationMoveState>();
}
