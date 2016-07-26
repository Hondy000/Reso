/**********************************************************************************************//**
 * @file	Source\GameSource\Level\DemoLevel\Private\DemoStates.cpp
 *
 * @brief	Implements the demo states class.
 **************************************************************************************************/

#include "../Public/VFXViewLevelStates.h"
#include "../../../Charactor/Player/Public/PlayerActor.h"
#include "../../../../HarmonyFrameWork/Core/Task/Public/TaskSystem.h"
#include "../../../../HarmonyFrameWork/Core/Actor/Public/StaticMeshActor.h"
#include "../../../../HarmonyFrameWork/Graphics/ParticleSystem/Public/BaseEmitter.h"
#include "../../../../HarmonyFrameWork/Core/Actor/Public/CameraActor.h"
#include "../../../../HarmonyFrameWork/Core/Actor/Public/LineActor.h"
#include "..\..\..\..\HarmonyFrameWork\ResorceManager\Public\BasicMeshFactory.h"
#include "..\..\..\..\HarmonyFrameWork\ResorceManager\Public\BasicMeshManager.h"
#include "..\..\..\..\HarmonyFrameWork\Core\Actor\Public\Sprite2DActor.h"
#include "..\..\..\..\HarmonyFrameWork\ResorceManager\Public\Texture2DManager.h"
#include "..\..\..\..\HarmonyFrameWork\Graphics\Shader\DirectX\ver.11\Public\SepiaTextureShader.h"
#include "..\..\..\..\HarmonyFrameWork\Graphics\Shader\DirectX\ver.11\Public\MonotoneTextureShader.h"
#include "..\..\..\..\HarmonyFrameWork\Graphics\RenderDevice\Basic\Public\RendererManager.h"
#include "..\..\..\..\HarmonyFrameWork\Core\Actor\Public\EmitterActor.h"
#include "..\..\..\..\HarmonyFrameWork\Collision\Public\CCollisionObjectFactory.h"
#include "..\..\..\..\HarmonyFrameWork\Graphics\Lighting\Public\LightManager.h"
#include "../../../../HarmonyFrameWork/Input/Public/InputManager.h"

using namespace std;

/**********************************************************************************************//**
 * @fn	void VFXViewMainState::Enter( )
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void VFXViewMainState::Enter( )
{
	shared_ptr<HFGraphics::DirectinalLight> directionalLight = make_shared<HFGraphics::DirectinalLight>();
	HFGraphics::DIRECTIONAL_LIGHT_PRAM pram;
	pram.color = HFVECTOR4(1, 1, 1, 1);
	pram.direction = HFVECTOR4(1, -1, 1, 0);
	directionalLight->SetPram(pram);
	HFGraphics::LightManager::GetInstance()->Register(directionalLight);

	// create camera
	shared_ptr < CameraActor>	camera2D = make_shared<CameraActor>();
	shared_ptr < CameraActor>	camera3D = make_shared<CameraActor>();
	camera3D->SetCameraPosition(HFVECTOR3(0, 0, -50));
	camera2D->SetIs2DCamera(true);
	TaskSystem::GetInstance()->RegisterTask("2Dcamera", camera2D);
	TaskSystem::GetInstance()->RegisterTask("3Dcamera", camera3D);


	// create grid
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

	shared_ptr<EmitterActor>emitter = make_shared<EmitterActor>();

	//CCollisionObjectFactory::GetInstance()->CreateOBBObject(lineRenderer->GetMesh()->GetSubMeshArray()[0]);
	emitter->Setup();
	emitter->SetMaxParticle(300);
	sTASK_SYSTEM->RegisterTask("emitter", emitter);
}

/**********************************************************************************************//**
 * @fn	void VFXViewMainState::Execute( )
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void VFXViewMainState::Execute( )
{
	shared_ptr < CameraActor>	camera3D = dynamic_pointer_cast<CameraActor> (sTASK_SYSTEM->SearchByTaskName("3Dcamera"));
	if (sINPUT->IsHoldKeyboard(DIK_SPACE))
	{
		camera3D->SetCameraPosition(camera3D->GetCameraPosition() + HFVECTOR3(0, 0.1, 0));
	}
	if (sINPUT->IsHoldKeyboard(DIK_LSHIFT))
	{
		camera3D->SetCameraPosition(camera3D->GetCameraPosition() - HFVECTOR3(0, 0.1, 0));
	}
	if (sINPUT->IsHoldKeyboard(DIK_RIGHT))
	{
		camera3D->SetCameraPosition(camera3D->GetCameraPosition() + HFVECTOR3(0.1, 0, 0));
	}
	if (sINPUT->IsHoldKeyboard(DIK_LEFT))
	{
		camera3D->SetCameraPosition(camera3D->GetCameraPosition() - HFVECTOR3(0.1, 0, 0));
	}
	if (sINPUT->IsHoldKeyboard(DIK_UP))
	{
		camera3D->SetCameraPosition(camera3D->GetCameraPosition() + HFVECTOR3(0, 0, 0.1));
	}
	if (sINPUT->IsHoldKeyboard(DIK_DOWN))
	{
		camera3D->SetCameraPosition(camera3D->GetCameraPosition() - HFVECTOR3(0, 0, 0.1));
	}
}

/**********************************************************************************************//**
 * @fn	void VFXViewMainState::Exit( )
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void VFXViewMainState::Exit( )
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> VFXViewMainState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

std::shared_ptr<IState> VFXViewMainState::GetNewState(void)
{
	return std::make_shared<VFXViewMainState>();
}

