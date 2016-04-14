#include "..\Public\PlayerStates.h"
#include "../../../../HarmonyFrameWork/Core/Task/Public/TaskInterface.h"
#include "../../../../HarmonyFrameWork/Math/Public/Transform.h"
#include "../../../../HarmonyFrameWork/Core/Actor/Public/ActorInterface.h"
#include "../../../../HarmonyFrameWork/Input/Public/InputManager.h"

using namespace std;

#define CAST_PLAYER_ACTOR(task) (dynamic_pointer_cast<PlayerActor>(task))

void PlayerAliveBeingState::Enter()
{
	RegisterState(std::make_shared<PlayerMoveState>(),m_wpTask.lock());
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

void PlayerMoveState::Enter()
{

}


void PlayerMoveState::Execute()
{
	HFVECTOR3 moveDirection;
	if(sINPUT->IsHoldKeyboard(DIK_W))
	{
		moveDirection.z += 1;
	}
	if (sINPUT->IsHoldKeyboard(DIK_A))
	{
		moveDirection.x -= 1;
	}
	if (sINPUT->IsHoldKeyboard(DIK_S))
	{
		moveDirection.z -= 1;
	}
	if (sINPUT->IsHoldKeyboard(DIK_D))
	{
		moveDirection.x += 1;
	}

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

void PlayerMoveState::Exit()
{

}

std::shared_ptr<IState> PlayerMoveState::GetNewState(void)
{
	return std::make_shared<PlayerStopState>();
}

void PlayerStopState::Enter()
{

}

void PlayerStopState::Execute()
{

}

void PlayerStopState::Exit()
{

}

std::shared_ptr<IState> PlayerStopState::GetNewState(void)
{
	return std::make_shared<PlayerMoveState>();
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
	return std::make_shared<PlayerStopState>();
}
