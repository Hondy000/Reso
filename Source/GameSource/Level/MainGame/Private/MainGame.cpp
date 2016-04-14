#include "../Public/MainGame.h"
#include "../../../Charactor/Player/Public/PlayerActor.h"
#include "../../../../HarmonyFrameWork/Core/Task/Public/TaskSystem.h"
#include "../Public/MainGameStates.h"

using namespace std;

BOOL MainGame::Init()
{
	RegisterState(make_shared<MainGameStartState>(),shared_from_this());
	return true;
}

BOOL MainGame::Update()
{
	UpdateState(shared_from_this());
	return false;
}

void MainGame::Reset()
{
	Init();
}
