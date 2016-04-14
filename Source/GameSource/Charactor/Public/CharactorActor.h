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
	BOOL Init();
	virtual BOOL Update() = 0;

protected:
};
