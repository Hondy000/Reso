#pragma once

#include "../../../HarmonyFramework/Core/State/Public/IState.h"

/**********************************************************************************************//**
 * @class	GeneralWeaponUnUseState GeneralWeaponState.h
 * 			Source\GameSource\Weapon\Public\GeneralWeaponState.h
 *
 * @brief	A general weapon un use state.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

class GeneralWeaponUnUseState
	:
	public IState
{
public:
	GeneralWeaponUnUseState();
	~GeneralWeaponUnUseState();
	void Enter();
	void Execute();
	void Exit();
	std::shared_ptr<IState> GetNewState();
private:

};

class GeneralWeaponUseState
	:
	public IState
{
public:
	GeneralWeaponUseState();
	~GeneralWeaponUseState();
	void Enter();
	void Execute();
	void Exit();
	std::shared_ptr<IState> GetNewState();
private:

};