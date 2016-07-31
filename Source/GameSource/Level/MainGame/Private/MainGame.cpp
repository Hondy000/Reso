/**********************************************************************************************//**
 * @file	Source\GameSource\Level\MainGame\Private\MainGame.cpp
 *
 * @brief	Implements the main game class.
 **************************************************************************************************/

#include "../Public/MainGame.h"
#include "../../../Charactor/Player/Public/PlayerActor.h"
#include "../../../../HarmonyFrameWork/Core/Task/Public/TaskSystem.h"
#include "../Public/MainGameStates.h"

using namespace std;

/**********************************************************************************************//**
 * @fn	bool MainGame::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool MainGame::Init()
{
	RegisterState(make_shared<MainGameStartState>(),shared_from_this());
	return true;
}

/**********************************************************************************************//**
 * @fn	bool MainGame::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool MainGame::Update()
{
	UpdateState(shared_from_this());
	return false;
}

/**********************************************************************************************//**
 * @fn	void MainGame::Reset()
 *
 * @brief	Resets this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void MainGame::Reset()
{
	Init();
}
