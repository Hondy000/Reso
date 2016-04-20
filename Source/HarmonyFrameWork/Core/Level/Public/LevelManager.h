#pragma once
#include "../../Public/Common.h"
#include "LevelInterface.h"
#include "../../Task/Public/TaskInterface.h"

class LevelManager
	:
	public IBaseTask
{
public:
	LevelManager() {};
	~LevelManager(){};
	bool Init();
	bool Update();
	void Reset();

private:
	std::shared_ptr<IBaseLevel> m_spLevel;
};
