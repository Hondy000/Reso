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
	bool Init();
	bool Update();

	void Reset();
private:
	

};
