#pragma once
#include "../../../../HarmonyFrameWork/Core/Level/Public/LevelInterface.h"

class Title
	:
	public IBaseLevel
{
public: 
	Title() {};
	~Title() {};
	BOOL Init();
	BOOL Update();

	void Reset();
private:
	
};
