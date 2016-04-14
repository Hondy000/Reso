#pragma once
#include "../../DemoLevel/Public/DemoLevel.h"

class ModelViewLevel
	:
	public IBaseLevel
{
public:
	ModelViewLevel();
	~ModelViewLevel();
	
	BOOL Init();

	BOOL Update();

	void Reset();

private:

};

