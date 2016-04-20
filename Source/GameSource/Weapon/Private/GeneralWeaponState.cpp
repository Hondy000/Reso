/**********************************************************************************************//**
 * @file	Source\GameSource\Weapon\Private\GeneralWeaponState.cpp
 *
 * @brief	Implements the general weapon state class.
 **************************************************************************************************/

#include "../Public/GeneralWeaponState.h"

/**********************************************************************************************//**
 * @fn	GeneralWeaponUnUseState::GeneralWeaponUnUseState()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

GeneralWeaponUnUseState::GeneralWeaponUnUseState()
{
	
}

/**********************************************************************************************//**
 * @fn	GeneralWeaponUnUseState::~GeneralWeaponUnUseState()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

GeneralWeaponUnUseState::~GeneralWeaponUnUseState()
{

}

/**********************************************************************************************//**
 * @fn	void GeneralWeaponUnUseState::Enter()
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void GeneralWeaponUnUseState::Enter()
{

}

/**********************************************************************************************//**
 * @fn	void GeneralWeaponUnUseState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void GeneralWeaponUnUseState::Execute()
{

}

/**********************************************************************************************//**
 * @fn	void GeneralWeaponUnUseState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void GeneralWeaponUnUseState::Exit()
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> GeneralWeaponUnUseState::GetNewState()
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

std::shared_ptr<IState> GeneralWeaponUnUseState::GetNewState()
{
	return std::make_shared<GeneralWeaponUseState>();
}

/**********************************************************************************************//**
 * @fn	GeneralWeaponUseState::GeneralWeaponUseState()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

GeneralWeaponUseState::GeneralWeaponUseState()
{

}

/**********************************************************************************************//**
 * @fn	GeneralWeaponUseState::~GeneralWeaponUseState()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

GeneralWeaponUseState::~GeneralWeaponUseState()
{

}

/**********************************************************************************************//**
 * @fn	void GeneralWeaponUseState::Enter()
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void GeneralWeaponUseState::Enter()
{

}

/**********************************************************************************************//**
 * @fn	void GeneralWeaponUseState::Execute()
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void GeneralWeaponUseState::Execute()
{

	m_isChangeState = true;
}

/**********************************************************************************************//**
 * @fn	void GeneralWeaponUseState::Exit()
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void GeneralWeaponUseState::Exit()
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> GeneralWeaponUseState::GetNewState()
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

std::shared_ptr<IState> GeneralWeaponUseState::GetNewState()
{
	return std::make_shared<GeneralWeaponUnUseState>();
}
