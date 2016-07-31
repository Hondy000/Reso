#pragma once
#include "../../../HarmonyFrameWork/Core/Actor/Public/ActorInterface.h"
#include "../../../HarmonyFrameWork/Core/Component/Public/StaticMeshCompornent.h"


class CharactorActor
	:
	public IActor
{
public:
	CharactorActor()
	{
	};
	virtual ~CharactorActor() {};
	bool Init();
	virtual bool Update() = 0;

protected:
};
