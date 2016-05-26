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
#include "..\..\..\..\HarmonyFrameWork\Core\Actor\Public\Sprite2DActor.h"
#include "..\..\..\..\HarmonyFrameWork\ResorceManager\Public\Texture2DManager.h"
#include "..\..\..\..\HarmonyFrameWork\Graphics\Shader\DirectX\ver.11\Public\SepiaTextureShader.h"
#include "..\..\..\..\HarmonyFrameWork\Graphics\Shader\DirectX\ver.11\Public\MonotoneTextureShader.h"
#include "..\..\..\..\HarmonyFrameWork\Graphics\RenderDevice\Basic\Public\RendererManager.h"
#include "..\..\..\..\HarmonyFrameWork\Graphics\Shader\DirectX\ver.11\Public\DefaultMeshShader.h"
#include "..\..\..\..\HarmonyFrameWork\Input\Public\InputManager.h"
#include "..\..\..\..\HarmonyFrameWork\Graphics\Shader\DirectX\ver.11\Public\SpecularPhongShader.h"

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

	shared_ptr<StaticMeshActor> phongSpecularMesh = make_shared<StaticMeshActor>();
	phongSpecularMesh->LoadMesh("Resource/Mesh/Lod.hfm");
	phongSpecularMesh->SetMaterialShader(0, std::make_shared<SpecularPhongShader>());

	sTASK_SYSTEM->RegisterTask("model", phongSpecularMesh);
	phongSpecularMesh->LoadDiffuseTexture2D(0, "Resource/Texture/DefaultGray.png");


	//sTASK_SYSTEM->RegisterTask("simpleMesh", simpleMesh);

	shared_ptr<StaticMeshActor> colorSprite = make_shared<StaticMeshActor>();
	shared_ptr<Mesh> spMesh = BasicMeshFactory::GetInstance()->Create(HF_BM_RECTANGLE_SPRITE, 3, 0, 0);
	colorSprite->SetMesh(spMesh);
	colorSprite->GetTransform()->SetScale(HFVECTOR3(100, 100, 0));
	colorSprite->GetTransform()->SetPosition(HFVECTOR3(-100, -100, 2000));
	shared_ptr<LineActor> lineRenderer = make_shared<LineActor>();
	TaskSystem::GetInstance()->RegisterTask("lineRenderer",lineRenderer);
	shared_ptr<Sprite2DActor> monotoneSprite = make_shared<Sprite2DActor>();
	/*
	TaskSystem::GetInstance()->RegisterTask("monotoneSprite", monotoneSprite); 
	monotoneSprite->GetTransform()->SetScale(150, 150, 0);
	monotoneSprite->GetTransform()->SetPosition(-300, -600, 0);
	monotoneSprite->GetSubMeshMaterial(0)->SetMaterialShader(std::make_shared<MonotoneTextureShader>());
	monotoneSprite->SetMaterialDiffuseTexture(0, Texture2DManager::GetInstance()->Get("C:/Users/Kazuyuki/Desktop/miyamori_aoi_by_kuvshinov_ilya-d9wx7c1.jpg"));
	*/

	/*
	shared_ptr<Sprite2DActor> spiaSprite = make_shared<Sprite2DActor>();
	TaskSystem::GetInstance()->RegisterTask("spiaSprite", spiaSprite);
	spiaSprite->GetTransform()->SetScale(150, 150, 0);
	spiaSprite->GetTransform()->SetPosition(-450, -450, 0);
	spiaSprite->GetSubMeshMaterial(0)->SetMaterialShader(std::make_shared<SepiaTextureShader>());
	spiaSprite->SetMaterialDiffuseTexture(0, Texture2DManager::GetInstance()->Get("C:/Users/Kazuyuki/Desktop/miyamori_aoi_by_kuvshinov_ilya-d9wx7c1.jpg"));
	*/
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
//	sTASK_SYSTEM->RegisterTask("rect", colorSprite);
	shared_ptr < CameraActor>	camera2D = make_shared<CameraActor>();
	shared_ptr < CameraActor>	camera3D = make_shared<CameraActor>();
	camera3D->SetCameraPosition(HFVECTOR3(0, 10, -10));
	camera2D->SetIs2DCamera(true);
	TaskSystem::GetInstance()->RegisterTask("2Dcamera", camera2D);
	TaskSystem::GetInstance()->RegisterTask("3Dcamera", camera3D);

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
	shared_ptr < CameraActor>	camera3D = dynamic_pointer_cast<CameraActor> (sTASK_SYSTEM->SearchByTaskName("3Dcamera"));
	
	shared_ptr < StaticMeshActor>	mesh = dynamic_pointer_cast<StaticMeshActor> (sTASK_SYSTEM->SearchByTaskName("model"));

	if(sINPUT->IsHoldKeyboard(DIK_SPACE))
	{
		camera3D->SetCameraPosition(camera3D->GetCameraPosition() + HFVECTOR3(0, 0.1, 0));
	}
	if (sINPUT->IsHoldKeyboard(DIK_LSHIFT))
	{
		camera3D->SetCameraPosition(camera3D->GetCameraPosition() - HFVECTOR3(0, 0.1, 0));
	}		
	if (sINPUT->IsHoldKeyboard(DIK_RIGHT))
	{
		camera3D->SetCameraPosition(camera3D->GetCameraPosition() + HFVECTOR3(0.1,0,  0));
	}
	if (sINPUT->IsHoldKeyboard(DIK_LEFT))
	{
		camera3D->SetCameraPosition(camera3D->GetCameraPosition() - HFVECTOR3(0.1,0,  0));
	}
	if (sINPUT->IsHoldKeyboard(DIK_UP))
	{
		camera3D->SetCameraPosition(camera3D->GetCameraPosition() + HFVECTOR3(0, 0,0.1 ));
	}
	if (sINPUT->IsHoldKeyboard(DIK_DOWN))
	{
		camera3D->SetCameraPosition(camera3D->GetCameraPosition() - HFVECTOR3(0, 0,0.1));
	}

	if (sINPUT->IsHoldKeyboard(DIK_W))
	{
		mesh->GetTransform()->SetEulerDegAngles(mesh->GetTransform()->GetEulerDegAngles() + HFVECTOR3(5, 0, 0));
	}
	if (sINPUT->IsHoldKeyboard(DIK_S))
	{
		mesh->GetTransform()->SetEulerDegAngles(mesh->GetTransform()->GetEulerDegAngles() - HFVECTOR3(5, 0, 0));
	}
	if (sINPUT->IsHoldKeyboard(DIK_A))
	{
		mesh->GetTransform()->SetEulerDegAngles(mesh->GetTransform()->GetEulerDegAngles() + HFVECTOR3(0, 0, 5));
	}
	if (sINPUT->IsHoldKeyboard(DIK_D))
	{
		mesh->GetTransform()->SetEulerDegAngles(mesh->GetTransform()->GetEulerDegAngles() - HFVECTOR3(0, 0, 5));
	}

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
