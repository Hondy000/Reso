#pragma once
#include "../Task/TaskInterface.h"

class ILevel
	:
	public IBaseTask
{
protected:
	ILevel() {};
public:
	virtual ~ILevel() {};
	virtual bool Update() = 0;
	

private:
};
