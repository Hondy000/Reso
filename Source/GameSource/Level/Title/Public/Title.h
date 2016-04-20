#pragma once
#include "../../../../HarmonyFrameWork/Core/Level/Public/LevelInterface.h"

class Title
	:
	public IBaseLevel
{
public: 
	Title() {};
	~Title() {};
	bool Init();
	bool Update();

	void Reset();
private:
	
};
