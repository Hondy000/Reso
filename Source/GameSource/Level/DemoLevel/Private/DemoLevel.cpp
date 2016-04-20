/**********************************************************************************************//**
 * @file	Source\GameSource\Level\DemoLevel\Private\DemoLevel.cpp
 *
 * @brief	Implements the demo level class.
 **************************************************************************************************/

#include "../Public/DemoLevel.h"
#include "../Public/DemoStates.h"
using namespace std;

/**********************************************************************************************//**
 * @fn	bool DemoLevel::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool DemoLevel::Init()
{
	RegisterState(make_shared<DemoStartState>(), shared_from_this());
	return true;
}

/**********************************************************************************************//**
 * @fn	bool DemoLevel::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool DemoLevel::Update()
{
	UpdateState(shared_from_this());
	return false;
}

/**********************************************************************************************//**
 * @fn	void DemoLevel::Reset()
 *
 * @brief	Resets this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void DemoLevel::Reset()
{
	Init();
}
