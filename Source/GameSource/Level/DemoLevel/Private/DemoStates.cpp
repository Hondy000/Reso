/**********************************************************************************************//**
 * @file	Source\GameSource\Level\DemoLevel\Private\DemoStates.cpp
 *
 * @brief	Implements the demo states class.
 **************************************************************************************************/

#include "../Public/DemoStates.h"
#include "../../../Charactor/Player/Public/PlayerActor.h"
#include "../../../../HarmonyFrameWork/Core/Task/Public/TaskSystem.h"
#include "../../../../HarmonyFrameWork/Core/Actor/Public/StaticMeshActor.h"
#include "../../../../HarmonyFrameWork/Graphics/ParticleSystem/Public/BaseEmitter.h"
#include "../../../../HarmonyFrameWork/Core/Actor/Public/CameraActor.h"

using namespace std;

/**********************************************************************************************//**
 * @fn	void DemoStartState::Enter( )
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void DemoStartState::Enter( )
{
	shared_ptr<StaticMeshActor> player = make_shared<StaticMeshActor>();
	player->LoadMesh("Resource/Mesh/Sphere.hfm");
	TaskSystem::GetInstance()->RegisterTask("staticmesh",player);
	player->Init();
	shared_ptr<CameraActor>	camera = make_shared<CameraActor>(); 
	TaskSystem::GetInstance()->RegisterTask("camera", camera);

	//shared_ptr<BaseEmitter>emitter = make_shared<BaseEmitter>();
	//emitter->Setup(3,10,HFVECTOR2(10,10),10,"Resource/Texture/DefaultWhite.png");
}

/**********************************************************************************************//**
 * @fn	void DemoStartState::Execute( )
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void DemoStartState::Execute( )
{

}

/**********************************************************************************************//**
 * @fn	void DemoStartState::Exit( )
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void DemoStartState::Exit( )
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> DemoStartState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

std::shared_ptr<IState> DemoStartState::GetNewState(void)
{
	return std::make_shared<DemoMainState>();
}

/**********************************************************************************************//**
 * @fn	void DemoMainState::Enter( )
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void DemoMainState::Enter( )
{

}

/**********************************************************************************************//**
 * @fn	void DemoMainState::Execute( )
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void DemoMainState::Execute( )
{

}

/**********************************************************************************************//**
 * @fn	void DemoMainState::Exit( )
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void DemoMainState::Exit( )
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> DemoMainState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

std::shared_ptr<IState> DemoMainState::GetNewState(void)
{
	return std::make_shared<DemoMainState>();
}
