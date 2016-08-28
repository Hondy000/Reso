/**********************************************************************************************//**
 * @file	Source\GameSource\Level\MainGame\Private\MainGameStates.cpp
 *
 * @brief	Implements the main game states class.
 **************************************************************************************************/

#include "../Public/MainGameStates.h"
#include "../../../Charactor/Player/Public/PlayerActor.h"
#include "../../../../HarmonyFrameWork/Core/Task/Public/TaskSystem.h"
#include "../../../../HarmonyFrameWork/Graphics/Lighting/Public/LightManager.h"
#include "../Public/MainGame.h"
#include "..\..\..\..\HarmonyFrameWork\Core\Actor\Public\StaticMeshActor.h"
#include "..\..\..\..\HarmonyFrameWork\Core\Public\ReflectionSystem.h"
#include "../../../../HarmonyFrameWork/Utility/Public/HFSyatemTime.h"

using namespace std;

/**********************************************************************************************//**
 * @fn	void MainGameStartState::Enter()
 *
 * @brief	game start.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void MainGameStartState::Enter()
{
	// register reflection
	REGISTER_TYPE(PlayerActor);


	//


	shared_ptr<PlayerActor> player = make_shared<PlayerActor>();
	TaskSystem::GetInstance()->RegisterTask("palyer", player);
	m_wpTask.lock()->RegisterVariable("palyer", player);
	shared_ptr<StaticMeshActor > spStage = make_shared<StaticMeshActor >();
	spStage->LoadMesh("Resource/Mesh/TestStage.hfm");
	TaskSystem::GetInstance()->RegisterTask("stage",spStage);
	
	player->GetTransform()->SetPosition(HFVECTOR3(0, 0, 0));

}

/**********************************************************************************************//**
 * @fn	void MainGameStartState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void MainGameStartState::Execute()
{

}

/**********************************************************************************************//**
 * @fn	void MainGameStartState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void MainGameStartState::Exit()
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> MainGameStartState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

std::shared_ptr<IState> MainGameStartState::GetNewState(void)
{
	return std::make_shared<MainGameMainState>();
}

/**********************************************************************************************//**
 * @fn	void MainGameMainState::Enter()
 *
 * @brief	main.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void MainGameMainState::Enter()
{
	m_popCounter = make_shared<HFSyatemTime>();
	m_endCounter = make_shared<HFSyatemTime>();
}

/**********************************************************************************************//**
 * @fn	void MainGameMainState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void MainGameMainState::Execute()
{

}

/**********************************************************************************************//**
 * @fn	void MainGameMainState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void MainGameMainState::Exit()
{
}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> MainGameMainState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

std::shared_ptr<IState> MainGameMainState::GetNewState(void)
{
	if (m_isChangeEndMain)
	{

		return std::make_shared<MainGameMainState>();
	}
	else
	{
		
		return nullptr;
	}
	
}
