#pragma once

#include "..\..\..\HarmonyFrameWork\Core\State\Public\StateHolder.h"
#include "..\..\..\HarmonyFrameWork\Core\Task\Public\TaskInterface.h"
#include "..\..\..\HarmonyFrameWork\Core\Public\Common.h"

class IBaseWeapon
	:
	public 
	virtual IBaseTask,
	public inheritable_enable_shared_from_this<IBaseTask>,
	public IStateHolder
{
public:
	IBaseWeapon();
	virtual~IBaseWeapon();
	bool Init();
	virtual void Use() = 0;
	bool IsEnableUse();
	bool Update();
	void Reset() {};

private:

};
