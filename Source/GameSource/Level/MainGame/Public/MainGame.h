#pragma once
#include "../../../../HarmonyFrameWork/Core/Level/Public/LevelInterface.h"
#include "../../../Charactor/Enemy/Public/EnemyActor.h"
#include "../../../Charactor/Player/Public/PlayerActor.h"

class MainGame
	:
	public IBaseLevel
{
public:
	MainGame()
	{
		
	};
	~MainGame()
	{

	}
	BOOL Init();
	BOOL Update();

	void Reset();
private:
	

};
