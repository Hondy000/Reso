#pragma once
#include "../../DemoLevel/Public/DemoLevel.h"

class ModelViewLevel
	:
	public IBaseLevel
{
public:
	ModelViewLevel();
	~ModelViewLevel();
	
	bool Init();

	bool Update();

	void Reset();

private:

};

