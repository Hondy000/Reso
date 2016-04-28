/**********************************************************************************************//**
																								* @file	Source\GameSource\Level\VFXViewLevel\Private\VFXViewLevel.cpp
																								*
																								* @brief	Implements the demo level class.
																								**************************************************************************************************/

#include "../Public/VFXViewLevel.h"
#include "../Public/VFXViewLevelStates.h"
using namespace std;

/**********************************************************************************************//**
																								* @fn	bool VFXViewLevel::Init()
																								*
																								* @brief	Initialises this object.
																								*
																								* @author	Kazuyuki Honda
																								*
																								* @return	true if it succeeds, false if it fails.
																								**************************************************************************************************/

bool VFXViewLevel::Init()
{
	RegisterState(make_shared<VFXViewMainState>(), shared_from_this());
	return true;
}

/**********************************************************************************************//**
																								* @fn	bool VFXViewLevel::Update()
																								*
																								* @brief	Updates this object.
																								*
																								* @author	Kazuyuki Honda
																								*
																								* @return	true if it succeeds, false if it fails.
																								**************************************************************************************************/

bool VFXViewLevel::Update()
{
	UpdateState(shared_from_this());
	return false;
}

/**********************************************************************************************//**
																								* @fn	void VFXViewLevel::Reset()
																								*
																								* @brief	Resets this object.
																								*
																								* @author	Kazuyuki Honda
																								**************************************************************************************************/

void VFXViewLevel::Reset()
{
	Init();
}
