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
#include "../../../../HarmonyFrameWork/Core/Actor/Public/LineActor.h"
#include "..\..\..\..\HarmonyFrameWork\ResorceManager\Public\BasicMeshFactory.h"
#include "..\..\..\..\HarmonyFrameWork\ResorceManager\Public\BasicMeshManager.h"

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
	shared_ptr<StaticMeshActor> mesh = make_shared<StaticMeshActor>();
	shared_ptr<Mesh> spMesh = BasicMeshFactory::GetInstance()->Create(HF_BM_RECTANGLE_SPRITE, 6, 0, 0);
	mesh->SetMesh(spMesh);
	mesh->GetTransform()->SetScale(HFVECTOR3(100, 100, 0));
	mesh->GetTransform()->SetPosition(HFVECTOR3(100, 300, 2000));
	shared_ptr<LineActor> lineRenderer = make_shared<LineActor>();
	TaskSystem::GetInstance()->RegisterTask("lineRenderer",lineRenderer);
	
	HFGraphics::LineData lineData;
	for (int i = 0;i<60;i++)
	{
		lineData.positions.push_back(HFVECTOR3(i * 10 - 300, 0, -300));
		lineData.positions.push_back(HFVECTOR3(i * 10 - 300, 0, 300));
	}

	for (int i = 0; i < 60; i++)
	{
		lineData.positions.push_back(HFVECTOR3(-300, 0, i * 10 - 300));
		lineData.positions.push_back(HFVECTOR3(300, 0, i * 10 - 300));
	}
	lineRenderer->AddLine(lineData);
//	sTASK_SYSTEM->RegisterTask("rect", mesh);
	shared_ptr<CameraActor>	camera = make_shared<CameraActor>(); 
	//camera->SetIs2DCamera(true);
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
