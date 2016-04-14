
#include "../Public/EnemyActor.h"
#include "../Public/EnemyStates.h"

using namespace std;
BOOL EnemyActor::Init()
{
	CharactorActor::Init();
	std::shared_ptr<IState> beingState = make_shared<BasicEnemyAliveBeingState>();
	RegisterState(beingState,shared_from_this());
	return true;
}

BOOL EnemyActor::Update()
{
	UpdateState(shared_from_this());
	UpdateAllTask();
	return true;
}

void EnemyActor::Reset()
{

}

