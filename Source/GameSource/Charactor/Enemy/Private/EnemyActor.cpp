/**********************************************************************************************//**
 * @file	Source\GameSource\Charactor\Enemy\Private\EnemyActor.cpp
 *
 * @brief	Implements the enemy actor class.
 **************************************************************************************************/

#include "../Public/EnemyActor.h"
#include "../Public/Level1EnemyStates.h"

using namespace std;

/**********************************************************************************************//**
 * @fn	bool EnemyActor::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool EnemyActor::Init()
{
	CharactorActor::Init();
	std::shared_ptr<IState> beingState = make_shared<Level1EnemyAliveBeingState>();
	RegisterState(beingState,shared_from_this());
	return true;
}

/**********************************************************************************************//**
 * @fn	bool EnemyActor::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool EnemyActor::Update()
{
	UpdateState(shared_from_this());
	UpdateAllTask();
	return true;
}

/**********************************************************************************************//**
 * @fn	void EnemyActor::Reset()
 *
 * @brief	Resets this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void EnemyActor::Reset()
{

}

