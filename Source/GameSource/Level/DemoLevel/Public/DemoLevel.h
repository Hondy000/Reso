#pragma once
#include "../../../../HarmonyFrameWork/Core/Level/Public/LevelInterface.h"

class DemoLevel
	:
	public IBaseLevel
{
public:
	DemoLevel() {};
	~DemoLevel() {};
	BOOL Init();
	BOOL Update();

	void Reset();
protected:
private:
};
