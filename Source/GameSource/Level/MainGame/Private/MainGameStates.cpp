/**********************************************************************************************//**
 * @file	Source\GameSource\Level\MainGame\Private\MainGameStates.cpp
 *
 * @brief	Implements the main game states class.
 **************************************************************************************************/

#include "../Public/MainGameStates.h"
#include "../../../Charactor/Player/Public/PlayerActor.h"
#include "../../../../HarmonyFrameWork/Core/Task/Public/TaskSystem.h"
#include "../../../../HarmonyFrameWork/Graphics/Lighting/Public/LightManager.h"
#include "../../../Charactor/Enemy/Public/EnemyActor.h"
#include "../Public/MainGame.h"
#include "..\..\..\..\HarmonyFrameWork\Core\Actor\Public\StaticMeshActor.h"
#include "..\..\..\Charactor\Enemy\Public\Level1EnemyStates.h"
#include "..\..\..\Charactor\Enemy\Public\MineState.h"
#include "..\..\..\..\HarmonyFrameWork\Core\Public\ReflectionSystem.h"

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
	REGISTER_TYPE(EnemyActor);
	REGISTER_TYPE(Level1EnemyAliveBeingState);
	REGISTER_TYPE(MineUnBootState);


	//


	shared_ptr<PlayerActor> player = make_shared<PlayerActor>();
	TaskSystem::GetInstance()->RegisterTask("palyer", player);
	m_wpTask.lock()->RegisterVariable("palyer", player);
	shared_ptr<StaticMeshActor > spStage = make_shared<StaticMeshActor >();
	spStage->LoadMesh("Resource/Mesh/TestStage.hfm");
	TaskSystem::GetInstance()->RegisterTask("stage",spStage);
	
	player->GetTransform()->SetPosition(HFVECTOR3(0, 0, 0));

	std::list<std::shared_ptr<EnemyActor>> m_manageEnemyList;
	m_wpTask.lock()->RegisterVariable("enemyList", m_manageEnemyList);
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
	m_popCounter = make_shared<HFTime>();
	m_endCounter = make_shared<HFTime>();
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

	if(m_popCounter->GetGameDeltaSeconds() >= 5)
	{
		shared_ptr<EnemyActor> actor = make_shared<EnemyActor>();
		
		actor->GetTransform()->SetPosition(HFVECTOR3(0, 0, -100));

		TaskSystem::GetInstance()->RegisterTask("enemy",actor);
		m_wpTask.lock()->GetVariable<list<shared_ptr<EnemyActor>>>("enemyList")->GetValue()->push_back(actor);
		m_popCounter->Start();
	}
	if(m_endCounter->GetGameDeltaSeconds() > 60)
	{
		m_isChangeEndMain = true;
		m_isChangeState = true;
	}
	

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
