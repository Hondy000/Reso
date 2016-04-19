#include "..\Public\PlayerStates.h"
#include "..\Public\PlayerActor.h"
#include "../../../../HarmonyFrameWork/Core/Task/Public/TaskInterface.h"
#include "../../../../HarmonyFrameWork/Math/Public/Transform.h"
#include "../../../../HarmonyFrameWork/Core/Actor/Public/ActorInterface.h"
#include "../../../../HarmonyFrameWork/Input/Public/InputManager.h"
#include "..\..\..\Weapon\Public\IBaseWeapon.h"
#include "..\..\..\..\HarmonyFrameWork\Core\Task\Public\TaskSystem.h"
#include "..\..\..\Weapon\Public\MachineGun.h"

using namespace std;

//#define GET_PLAYER_ACTOR (std::dynamic_pointer_cast<PlayerActor>(m_wpTask.lock()))

//#define GET_PLAYER_ACTOR (std::dynamic_pointer_cast<PlayerActor>(m_wpTask.lock()))

void PlayerAliveBeingState::Enter()
{

	m_wpTask.lock()->RegisterVariable("m_valueOfTurn", 0.6f);
	m_wpTask.lock()->RegisterVariable("m_velocity", 0.0f);
	m_wpTask.lock()->RegisterVariable("m_direction", HFVECTOR3(0,0,0));
	m_wpTask.lock()->RegisterVariable("m_accceleration", 0.002f);
	m_wpTask.lock()->RegisterVariable("m_deceleration", 0.002f);
	m_wpTask.lock()->RegisterVariable("m_maxVelocity", 0.2f);
	//m_wpTask.lock()->RegisterVariable<IbaseWeapon>("m_weapon", make_shared<MachineGun>());
	RegisterState(std::make_shared<PlayerStopState>(), m_wpTask.lock());
	//RegisterState(std::make_shared<PlayerUnShotState>(), m_wpTask.lock());
	//RegisterState(std::make_shared<PlayerUnUseBombState>(), m_wpTask.lock());
	
	/*
	sTASK_SYSTEM->RegisterTask
	(
		"playerWeapon",
		GET_PLAYER_ACTOR->GetVariable<IBaseWeapon>("m_weapon")
		->downcasted_shared_from_this<IBaseTask>()
	);*/

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

void PlayerMaxVelocityMoveState::Enter()
{

}


void PlayerMaxVelocityMoveState::Execute()
{
	if(sINPUT->IsHoldKeyboard(DIK_W))
	{
		GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction").z += 
			GET_TASK_VAR(m_wpTask.lock(), float, "m_valueOfTurn");
	}
	if (sINPUT->IsHoldKeyboard(DIK_S))
	{
		GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction").z -=
			GET_TASK_VAR(m_wpTask.lock(), float, "m_valueOfTurn");

	}
	if (sINPUT->IsHoldKeyboard(DIK_A))
	{
		GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction").x +=
			GET_TASK_VAR(m_wpTask.lock(), float, "m_valueOfTurn");

	}
	if (sINPUT->IsHoldKeyboard(DIK_D))
	{
		GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction").x -=
			GET_TASK_VAR(m_wpTask.lock(), float, "m_valueOfTurn");
	}

	// ê≥ãKâª
	GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction") = HFVec3Normalize(GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction"));


	GET_TASK_VAR(m_wpTask.lock(),Transform, "m_transform").SetPosition(
		GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").GetPosition() +
		(
			GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction") * 
			GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_velocity")
			)
		);



	if (!sINPUT->IsHoldKeyboard(DIK_W)
		&&
		!sINPUT->IsHoldKeyboard(DIK_A)
		&&
		!sINPUT->IsHoldKeyboard(DIK_S)
		&&
		!sINPUT->IsHoldKeyboard(DIK_D)
		)
	{
		m_isChangeState = true;
	}
	HFVECTOR3 vec1, vec2;
	vec2 = HFVECTOR3(0, 1, 0);
	vec1 = HFVec3Cross(GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction"), vec2);
	HFMATRIX rot = DirectX::SimpleMath::Matrix::CreateFromAxisAngle(vec1, HFToRadian(10));

	HFVECTOR3 rotVec = HFMatrixEulerAngles(rot);
	rotVec.x = HFToDegree(rotVec.x);
	rotVec.y = HFToDegree(rotVec.y);
	rotVec.z = HFToDegree(rotVec.z);

	GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").SetRotation(
		GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").GetRotation()
		+ rotVec*GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_velocity")
	);
}

void PlayerMaxVelocityMoveState::Exit()
{

}

std::shared_ptr<IState> PlayerMaxVelocityMoveState::GetNewState(void)
{
	return std::make_shared<PlayerDecelerationMoveState>();
}

void PlayerAcccelerationMoveState::Enter()
{

}

void PlayerAcccelerationMoveState::Execute()
{
	if (sINPUT->IsHoldKeyboard(DIK_W))
	{
		GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction").z +=
			GET_TASK_VAR(m_wpTask.lock(), float, "m_valueOfTurn");
	}
	if (sINPUT->IsHoldKeyboard(DIK_S))
	{
		GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction").z -=
			GET_TASK_VAR(m_wpTask.lock(), float, "m_valueOfTurn");

	}
	if (sINPUT->IsHoldKeyboard(DIK_A))
	{
		GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction").x +=
			GET_TASK_VAR(m_wpTask.lock(), float, "m_valueOfTurn");

	}
	if (sINPUT->IsHoldKeyboard(DIK_D))
	{
		GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction").x -=
			GET_TASK_VAR(m_wpTask.lock(), float, "m_valueOfTurn");
	}

	// ê≥ãKâª
	GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction") = HFVec3Normalize(GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction"));

	if (GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_velocity") <= GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_maxVelocity"))
	{

		GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_velocity") +=
			GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_accceleration");
		
		if (GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_velocity") 
			> GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_maxVelocity"))
		{
			m_isChangeState = true;
			GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_velocity") = GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_maxVelocity");
			
		}
	}

	GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").SetPosition(
		GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").GetPosition()
		+
		GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction")
		*
		GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_velocity")
			);

	if (!sINPUT->IsHoldKeyboard(DIK_W)
		&&
		!sINPUT->IsHoldKeyboard(DIK_A)
		&&
		!sINPUT->IsHoldKeyboard(DIK_S)
		&&
		!sINPUT->IsHoldKeyboard(DIK_D)
		)
	{
		m_isChangeState = true;
	}
	HFVECTOR3 vec1, vec2;
	vec2 = HFVECTOR3(0, 1, 0);
	vec1 = HFVec3Cross(GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction"), vec2);
	HFMATRIX rot = DirectX::SimpleMath::Matrix::CreateFromAxisAngle(vec1, HFToRadian(10));

	HFVECTOR3 rotVec = HFMatrixEulerAngles(rot);
	rotVec.x = HFToDegree(rotVec.x);
	rotVec.y = HFToDegree(rotVec.y);
	rotVec.z = HFToDegree(rotVec.z);

	GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").SetRotation(
		GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").GetRotation()
		+ rotVec*GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_velocity")
	);


}

void PlayerAcccelerationMoveState::Exit()
{
}

std::shared_ptr<IState> PlayerAcccelerationMoveState::GetNewState(void)
{
	return std::make_shared<PlayerMaxVelocityMoveState>();
}

void PlayerDecelerationMoveState::Enter()
{

}

void PlayerDecelerationMoveState::Execute()
{
	GET_TASK_VAR(m_wpTask.lock(), float, "m_velocity")
		-=
		GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_deceleration");


	GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").SetPosition(
		GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").GetPosition()
		+
		GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction")
		*
		GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_velocity")
		);

	// à⁄ìÆÉLÅ[Ç™âüÇ≥ÇÍÇΩ
	if (sINPUT->IsHoldKeyboard(DIK_W)
		||
		sINPUT->IsHoldKeyboard(DIK_A)
		||
		sINPUT->IsHoldKeyboard(DIK_S)
		||
		sINPUT->IsHoldKeyboard(DIK_D)
		)
	{
		// ëJà⁄
		m_isChangeState = true;
		m_isChangeAcccelerationMoveState = true;
	}
	// maxà»è„
	if (GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_velocity")
			<= 0)
	{
		GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_velocity") = 0;
		// ëJà⁄
		m_isChangeState = true;
		m_isChangeStopState = true;
	}
	HFVECTOR3 vec1, vec2;
	vec2 = HFVECTOR3(0, 1, 0);
	vec1 = HFVec3Cross(GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction"), vec2);
	HFMATRIX rot = DirectX::SimpleMath::Matrix::CreateFromAxisAngle(vec1, HFToRadian(10));

	HFVECTOR3 rotVec = HFMatrixEulerAngles(rot);
	rotVec.x = HFToDegree(rotVec.x);
	rotVec.y = HFToDegree(rotVec.y);
	rotVec.z = HFToDegree(rotVec.z);

	GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").SetRotation(
		GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").GetRotation()
		+ rotVec*GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_velocity")
	);
}

void PlayerDecelerationMoveState::Exit()
{

}

std::shared_ptr<IState> PlayerDecelerationMoveState::GetNewState(void)
{
	if (m_isChangeStopState)
	{
		return std::make_shared<PlayerStopState>();
	}

	if (m_isChangeAcccelerationMoveState)
	{
		return std::make_shared<PlayerAcccelerationMoveState>();
	}
}


void PlayerStopState::Enter()
{
	GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction") = HFVECTOR3(0, 0, 0);
}

void PlayerStopState::Execute()
{
	if (sINPUT->IsHoldKeyboard(DIK_W)
		||
		sINPUT->IsHoldKeyboard(DIK_A)
		||
		sINPUT->IsHoldKeyboard(DIK_S)
		||
		sINPUT->IsHoldKeyboard(DIK_D)
		)
	{
		m_isChangeState = true;
	}
	

}

void PlayerStopState::Exit()
{

}

std::shared_ptr<IState> PlayerStopState::GetNewState(void)
{
	return std::make_shared<PlayerAcccelerationMoveState>();
}

void PlayerUnShotState::Enter()
{

}

void PlayerUnShotState::Execute()
{
	if (sINPUT->IsHoldMouse(HFM_LEFT))
	{
// 		if (
// 			GET_TASK_VAR_PTR(m_wpTask.lock(), IBaseWeapon, "m_weapon")->IsEnableUse()
// 			)
// 		{
// 			m_isChangeState = true;
// 		}
	}
}

void PlayerUnShotState::Exit()
{

}

std::shared_ptr<IState> PlayerUnShotState::GetNewState(void)
{
	return std::make_shared<PlayerShotState>();
}

void PlayerShotState::Enter()
{

}

void PlayerShotState::Execute()
{
// 	GET_TASK_VAR_PTR(m_wpTask.lock(), IBaseWeapon, "m_weapon")->Use();
// 	m_isChangeState = true;
}

void PlayerShotState::Exit()
{

}

std::shared_ptr<IState> PlayerShotState::GetNewState(void)
{
	return std::make_shared<PlayerUnShotState>();

}

void PlayerUseBombState::Enter()
{

}

void PlayerUseBombState::Execute()
{

}

void PlayerUseBombState::Exit()
{

}

std::shared_ptr<IState> PlayerUseBombState::GetNewState(void)
{
	return std::make_shared<PlayerUseBombState>();
}

void PlayerUnUseBombState::Enter()
{

}

void PlayerUnUseBombState::Execute()
{

}

void PlayerUnUseBombState::Exit()
{

}

std::shared_ptr<IState> PlayerUnUseBombState::GetNewState(void)
{
	return std::make_shared<PlayerUnUseBombState>();
}
		  