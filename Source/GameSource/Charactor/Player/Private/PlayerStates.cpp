/**********************************************************************************************//**
 * @file	Source\GameSource\Charactor\Player\Private\PlayerStates.cpp
 *
 * @brief	Implements the player states class.
 **************************************************************************************************/

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

/**********************************************************************************************//**
 * @def	GET_PLAYER_ACTOR
 *
 * @brief	A macro that defines get player actor.
 *
 * @author	Kazuyuki Honda
 *
 * @param	std::dynamic_pointer_cast<PlayerActor>(m_wpTask.lock()	The standard dynamic pointer
 * 																	cast.
 **************************************************************************************************/

/**=================================================================================================
 * A macro that defines get player actor.
 *
 * @author Kazuyuki
 *
 * @param std::dynamic_pointer_cast<PlayerActor>(m_wpTask.lock() The standard dynamic pointer cast.
 *===============================================================================================**/

#define GET_PLAYER_ACTOR (std::dynamic_pointer_cast<PlayerActor>(m_wpTask.lock()))

/**********************************************************************************************//**
 * @fn	void PlayerAliveBeingState::Enter()
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Enters this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerAliveBeingState::Enter()
{

	m_wpTask.lock()->RegisterVariable("m_valueOfTurn", 0.6f);
	m_wpTask.lock()->RegisterVariable("m_velocity", 0.0f);
	m_wpTask.lock()->RegisterVariable("m_direction", HFVECTOR3(0,0,0));
	m_wpTask.lock()->RegisterVariable("m_accceleration", 0.005f);
	m_wpTask.lock()->RegisterVariable("m_deceleration", 0.006f);
	m_wpTask.lock()->RegisterVariable("m_maxVelocity", 0.3f);
	m_wpTask.lock()->RegisterVariable<IBaseWeapon,MachineGun>("m_weapon", make_shared<MachineGun>());
	RegisterState(std::make_shared<PlayerStopState>(), m_wpTask.lock());
	RegisterState(std::make_shared<PlayerUnShotState>(), m_wpTask.lock());
	RegisterState(std::make_shared<PlayerUnUseBombState>(), m_wpTask.lock());
	//IBaseWeapon test;
	sTASK_SYSTEM->RegisterTask
	(
		"playerWeapon",
		GET_PLAYER_ACTOR->GetVariable<IBaseWeapon>("m_weapon")->GetValue()
	);

}

void PlayerAliveBeingState::Execute()
{
	UpdateState(m_wpTask.lock());
}

/**********************************************************************************************//**
 * @fn	void PlayerAliveBeingState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void PlayerAliveBeingState::Exit()
{

}

/**=================================================================================================
 * Gets new state.
 *
 * @author Kazuyuki
 *
 * @return The new state.
 *===============================================================================================**/

std::shared_ptr<IState> PlayerAliveBeingState::GetNewState(void)
{
	return std::make_shared<PlayerDeadBeingState>();
}

/**********************************************************************************************//**
 * @fn	void PlayerDeadBeingState::Enter()
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void PlayerDeadBeingState::Enter()
{

}

/**********************************************************************************************//**
 * @fn	void PlayerDeadBeingState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Executes this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerDeadBeingState::Execute()
{

}

/**********************************************************************************************//**
 * @fn	void PlayerDeadBeingState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Exits this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerDeadBeingState::Exit()
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> PlayerDeadBeingState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

/**=================================================================================================
 * Gets new state.
 *
 * @author Kazuyuki
 *
 * @return The new state.
 *===============================================================================================**/

std::shared_ptr<IState> PlayerDeadBeingState::GetNewState(void)
{
	return std::make_shared<PlayerDeadBeingState>();
}

/**********************************************************************************************//**
 * @fn	void PlayerMaxVelocityMoveState::Enter()
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Enters this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerMaxVelocityMoveState::Enter()
{

}

/**********************************************************************************************//**
 * @fn	void PlayerMaxVelocityMoveState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Executes this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

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

	DirectX::SimpleMath::Quaternion q =
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(vec1, HFToRadian(GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_velocity") * 25));
	

							 
	GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").SetQuaternionRotation(
		HFQUATERNION(q)
		*
		GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").GetQuaternionRotation()
	);
}

/**********************************************************************************************//**
 * @fn	void PlayerMaxVelocityMoveState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Exits this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerMaxVelocityMoveState::Exit()
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> PlayerMaxVelocityMoveState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

/**=================================================================================================
 * Gets new state.
 *
 * @author Kazuyuki
 *
 * @return The new state.
 *===============================================================================================**/

std::shared_ptr<IState> PlayerMaxVelocityMoveState::GetNewState(void)
{
	return std::make_shared<PlayerDecelerationMoveState>();
}

/**********************************************************************************************//**
 * @fn	void PlayerAcccelerationMoveState::Enter()
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Enters this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerAcccelerationMoveState::Enter()
{

}
/**=================================================================================================
 * @fn void PlayerAcccelerationMoveState::Execute()
 *
 * @brief Executes this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

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

	DirectX::SimpleMath::Quaternion q =
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(vec1, HFToRadian(GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_velocity") * 25));



	GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").SetQuaternionRotation(
		HFQUATERNION(q)
		*
		GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").GetQuaternionRotation()
	);
}

/**********************************************************************************************//**
 * @fn	void PlayerAcccelerationMoveState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Exits this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerAcccelerationMoveState::Exit()
{
}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> PlayerAcccelerationMoveState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

/**=================================================================================================
 * Gets new state.
 *
 * @author Kazuyuki
 *
 * @return The new state.
 *===============================================================================================**/

std::shared_ptr<IState> PlayerAcccelerationMoveState::GetNewState(void)
{
	return std::make_shared<PlayerMaxVelocityMoveState>();
}

/**=================================================================================================
 * @fn void PlayerDecelerationMoveState::Enter()
 *
 * @brief Enters this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerDecelerationMoveState::Enter()
{

}


/**=================================================================================================
 * @fn void PlayerDecelerationMoveState::Execute()
 *
 * @brief Executes this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

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

	DirectX::SimpleMath::Quaternion q =
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(vec1, HFToRadian(GET_TASK_VAR(m_wpTask.lock(), FLOAT, "m_velocity") * 25));



	GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").SetQuaternionRotation(
		HFQUATERNION(q)
		*
		GET_TASK_VAR(m_wpTask.lock(), Transform, "m_transform").GetQuaternionRotation()
	);
}

/**********************************************************************************************//**
 * @fn	void PlayerDecelerationMoveState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Exits this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerDecelerationMoveState::Exit()
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> PlayerDecelerationMoveState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

/**=================================================================================================
 * Gets new state.
 *
 * @author Kazuyuki
 *
 * @return The new state.
 *===============================================================================================**/

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

/**********************************************************************************************//**
 * @fn	void PlayerStopState::Enter()
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Enters this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerStopState::Enter()
{
	GET_TASK_VAR(m_wpTask.lock(), HFVECTOR3, "m_direction") = HFVECTOR3(0, 0, 0);
}

/**********************************************************************************************//**
 * @fn	void PlayerStopState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Executes this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

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

/**********************************************************************************************//**
 * @fn	void PlayerStopState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Exits this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerStopState::Exit()
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> PlayerStopState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

/**=================================================================================================
 * Gets new state.
 *
 * @author Kazuyuki
 *
 * @return The new state.
 *===============================================================================================**/

std::shared_ptr<IState> PlayerStopState::GetNewState(void)
{
	return std::make_shared<PlayerAcccelerationMoveState>();
}

/**********************************************************************************************//**
 * @fn	void PlayerUnShotState::Enter()
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Enters this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerUnShotState::Enter()
{

}

/**********************************************************************************************//**
 * @fn	void PlayerUnShotState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Executes this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerUnShotState::Execute()
{
	if (sINPUT->IsHoldMouse(HFM_LEFT))
	{
		if (
			GET_TASK_VAR_PTR(m_wpTask.lock(), IBaseWeapon, "m_weapon")->IsEnableUse()
			)
		{
			m_isChangeState = true;
		}
	}
}

/**********************************************************************************************//**
 * @fn	void PlayerUnShotState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Exits this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerUnShotState::Exit()
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> PlayerUnShotState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

/**=================================================================================================
 * Gets new state.
 *
 * @author Kazuyuki
 *
 * @return The new state.
 *===============================================================================================**/

std::shared_ptr<IState> PlayerUnShotState::GetNewState(void)
{
	return std::make_shared<PlayerShotState>();
}

/**********************************************************************************************//**
 * @fn	void PlayerShotState::Enter()
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Enters this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerShotState::Enter()
{

}

/**=================================================================================================
 * @fn void PlayerShotState::Execute()
 *
 * @brief Executes this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerShotState::Execute()
{
	GET_TASK_VAR_PTR(m_wpTask.lock(), IBaseWeapon, "m_weapon")->Use();
	m_isChangeState = true;
}

/**=================================================================================================
 * @fn void PlayerShotState::Exit()
 *
 * @brief Exits this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerShotState::Exit()
{

}

/**=================================================================================================
 * @fn std::shared_ptr<IState> PlayerShotState::GetNewState(void)
 *
 * @brief Gets new state.
 *
 * @author Kazuyuki
 *
 * @return The new state.
 *===============================================================================================**/

std::shared_ptr<IState> PlayerShotState::GetNewState(void)
{
	return std::make_shared<PlayerUnShotState>();

}

/**********************************************************************************************//**
 * @fn	void PlayerUseBombState::Enter()
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Enters this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerUseBombState::Enter()
{

}

/**********************************************************************************************//**
 * @fn	void PlayerUseBombState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Executes this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerUseBombState::Execute()
{

}

/**********************************************************************************************//**
 * @fn	void PlayerUseBombState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Exits this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerUseBombState::Exit()
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> PlayerUseBombState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

/**=================================================================================================
 * Gets new state.
 *
 * @author Kazuyuki
 *
 * @return The new state.
 *===============================================================================================**/

std::shared_ptr<IState> PlayerUseBombState::GetNewState(void)
{
	return std::make_shared<PlayerUseBombState>();
}

/**********************************************************************************************//**
 * @fn	void PlayerUnUseBombState::Enter()
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Enters this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerUnUseBombState::Enter()
{

}

/**********************************************************************************************//**
 * @fn	void PlayerUnUseBombState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Executes this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerUnUseBombState::Execute()
{

}

/**********************************************************************************************//**
 * @fn	void PlayerUnUseBombState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

/**=================================================================================================
 * Exits this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void PlayerUnUseBombState::Exit()
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> PlayerUnUseBombState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

/**=================================================================================================
 * Gets new state.
 *
 * @author Kazuyuki
 *
 * @return The new state.
 *===============================================================================================**/

std::shared_ptr<IState> PlayerUnUseBombState::GetNewState(void)
{
	return std::make_shared<PlayerUnUseBombState>();
}
		  