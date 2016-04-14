#include "../Public/MainGameStates.h"
#include "../../../Charactor/Player/Public/PlayerActor.h"
#include "../../../../HarmonyFrameWork/Core/Task/Public/TaskSystem.h"
#include "../../../../HarmonyFrameWork/Graphics/Lighting/Public/LightManager.h"
#include "../../../Charactor/Enemy/Public/EnemyActor.h"
#include "../Public/MainGame.h"

using namespace std;


// game start
void MainGameStartState::Enter()
{
	//shared_ptr<PlayerActor> player = make_shared<PlayerActor>();
	//TaskSystem::GetInstance()->RegisterTask("palyer", player);
	//m_wpTask.lock()->RegisterVariable("palyer", player);
	//player->GetTransform()->SetPosition(HFVECTOR3(0, 0, 50));

	std::list<std::shared_ptr<EnemyActor>> m_manageEnemyList;
	m_wpTask.lock()->RegisterVariable("enemyList", m_manageEnemyList);
}

void MainGameStartState::Execute()
{

}

void MainGameStartState::Exit()
{

}

std::shared_ptr<IState> MainGameStartState::GetNewState(void)
{
	return std::make_shared<MainGameMainState>();
}



// main

void MainGameMainState::Enter()
{
	m_popCounter = make_shared<Timer>();
	m_endCounter = make_shared<Timer>();
}

void MainGameMainState::Execute()
{

	if(m_popCounter->elapsed() >= 5000)
	{
		shared_ptr<EnemyActor> actor = make_shared<EnemyActor>();
		
		actor->GetTransform()->SetPosition(HFVECTOR3(0, 0, -100));

		TaskSystem::GetInstance()->RegisterTask("enemy",actor);
		m_wpTask.lock()->GetVariable<list<shared_ptr<EnemyActor>>>("enemyList")->GetValue()->push_back(actor);
		m_popCounter->restart();
	}
	if(m_endCounter->elapsed() > 600000)
	{
		m_isChangeEndMain = true;
		m_isChangeState = true;
	}
	

}

void MainGameMainState::Exit()
{
}

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
