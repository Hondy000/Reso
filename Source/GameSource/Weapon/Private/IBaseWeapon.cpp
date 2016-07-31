/**********************************************************************************************//**
 * @file	Source\GameSource\Weapon\Private\IBaseWeapon.cpp
 *
 * @brief	Declares the IBaseWeapon interface.
 **************************************************************************************************/

#include "..\Public\IBaseWeapon.h"
#include "..\..\..\HarmonyFrameWork\Core\State\Public\IState.h"
#include "..\..\..\HarmonyFrameWork\Core\Actor\Public\ActorInterface.h"

/**********************************************************************************************//**
 * @fn	IBaseWeapon::IBaseWeapon()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

IBaseWeapon::IBaseWeapon()
{
	// 基本変数のセット
	Init();
}

/**********************************************************************************************//**
 * @fn	bool IBaseWeapon::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool IBaseWeapon::Init()
{
	RegisterVariable<int>("m_coolTime", 0);
	RegisterVariable<IActor>("m_holder", nullptr);

	return true;
}

/**********************************************************************************************//**
 * @fn	bool IBaseWeapon::IsEnableUse()
 *
 * @brief	Query if this object is enable use.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if enable use, false if not.
 **************************************************************************************************/

bool IBaseWeapon::IsEnableUse()
{
	if (
		GET_TASK_VAR(shared_from_this(), int, "m_coolTime")
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

/**********************************************************************************************//**
 * @fn	IBaseWeapon::~IBaseWeapon()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

IBaseWeapon::~IBaseWeapon()
{
}

/**********************************************************************************************//**
 * @fn	bool IBaseWeapon::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool IBaseWeapon::Update()
{
	this->UpdateState(shared_from_this());
	
	return true;
}