#pragma once
#include "../../../../HarmonyFrameWork/Core/Level/Public/LevelInterface.h"

class VFXViewLevel
	:
	public IBaseLevel
{
public:
	VFXViewLevel() {};
	~VFXViewLevel() {};
	bool Init();
	bool Update();

	void Reset();
protected:
private:
};
