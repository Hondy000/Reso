/*
#include "..\Public\IBaseWeapon.h"
#include "..\..\..\HarmonyFrameWork\Core\State\Public\IState.h"


IBaseWeapon::IBaseWeapon()
{
}


bool IBaseWeapon::IsEnableUse()
{
	if(
	GET_TASK_VAR(shared_from_this(),int,"m_coolTime")
		<=
		0
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

IBaseWeapon::~IBaseWeapon()
{
} */