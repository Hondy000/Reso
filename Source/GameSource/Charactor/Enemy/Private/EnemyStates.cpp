#include "../Public/EnemyStates.h"
#include "../Public/EnemyActor.h"

using namespace std;

#define CAST_ENEMY_ACTOR(task) (dynamic_pointer_cast<EnemyActor>(task))


void BasicEnemyAliveBeingState::Enter()
{
	CAST_STATIC_MESH_COMPORNENT(
		CAST_ENEMY_ACTOR(m_wpTask.lock())->GetCompornent(typeid(StaticMeshCompornent).name()))->LoadMesh("Resource/Mesh/Sphere.hfm");
	RegisterState(std::make_shared<BasicEnemyWaitActionState>(), m_wpTask.lock());
	RegisterState(std::make_shared<BasicEnemyWaitMoveState>(), m_wpTask.lock());
	(m_wpTask.lock())->RegisterVariable("hitpoint", 100.0f);
}

void BasicEnemyAliveBeingState::Execute()
{
	UpdateState(m_wpTask.lock());
	if(m_wpTask.lock()->GetVariable<FLOAT>("hitpoint")->GetValue() <= 0)
	{
		m_isChangeState = true;
	}


}

void BasicEnemyAliveBeingState::Exit()
{

}

std::shared_ptr<IState> BasicEnemyAliveBeingState::GetNewState(void)
{
	return std::make_shared<BasicEnemyDeadBeingState>();
}




// Ž€–S
void BasicEnemyDeadBeingState::Enter()
{

}

void BasicEnemyDeadBeingState::Execute()
{

}

void BasicEnemyDeadBeingState::Exit()
{

}

std::shared_ptr<IState> BasicEnemyDeadBeingState::GetNewState(void)
{
	return std::make_shared<BasicEnemyAliveBeingState>();
}

// ’âŽ~

void BasicEnemyWaitActionState::Enter()
{

}

void BasicEnemyWaitActionState::Execute()
{

}

void BasicEnemyWaitActionState::Exit()
{

}

std::shared_ptr<IState> BasicEnemyWaitActionState::GetNewState(void)
{
	return std::make_shared<BasicEnemyWaitActionState>();
}

void BasicEnemyWaitMoveState::Enter()
{

}

void BasicEnemyWaitMoveState::Execute()
{

}

void BasicEnemyWaitMoveState::Exit()
{

}

std::shared_ptr<IState> BasicEnemyWaitMoveState::GetNewState(void)
{
	return std::make_shared<BasicEnemyStraightMoveState>();
}

void BasicEnemyStraightMoveState::Enter()
{

}

void BasicEnemyStraightMoveState::Execute()
{

}

void BasicEnemyStraightMoveState::Exit()
{

}

std::shared_ptr<IState> BasicEnemyStraightMoveState::GetNewState(void)
{
	return std::make_shared<BasicEnemyWaitMoveState>();
}
