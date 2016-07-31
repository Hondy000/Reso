#pragma once
#include "../../../../HarmonyFrameWork/Core/Actor/Public/ActorInterface.h"
#include "../../Public/CharactorActor.h"

class PlayerActor
	:
	public CharactorActor
{
public:
	PlayerActor(){};
	~PlayerActor(){};
	bool Init();
	void Reset();
	bool Update();	

private:

};
