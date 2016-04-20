#pragma once
#include "../../../../HarmonyFrameWork/Core/Level/Public/LevelInterface.h"

class Result
	:
	public IBaseLevel
{
public:
	Result() {};
	~Result() {};

	bool Init();
	bool Update();

	void Reset();
protected:
private:
};