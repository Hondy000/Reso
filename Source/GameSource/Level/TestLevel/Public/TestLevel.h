#pragma once
#include "../../../../HarmonyFrameWork/Core/Level/Public/LevelInterface.h"

class DemoLevel
	:
	public IBaseLevel
{
public:
	DemoLevel() {};
	~DemoLevel() {};
	bool Init();
	bool Update();

	void Reset();
protected:
private:
};
