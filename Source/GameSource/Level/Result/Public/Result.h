#pragma once
#include "../../../../HarmonyFrameWork/Core/Level/Public/LevelInterface.h"

class Result
	:
	public IBaseLevel
{
public:
	Result() {};
	~Result() {};

	BOOL Init();
	BOOL Update();

	void Reset();
protected:
private:
};