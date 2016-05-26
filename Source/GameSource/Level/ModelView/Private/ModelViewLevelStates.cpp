#include "..\Public\ModelViewLevelStates.h"	  
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
#include "..\..\..\..\HarmonyFrameWork\Graphics\Lighting\Public\LightManager.h"
#include "..\..\..\..\HarmonyFrameWork\Graphics\Shader\DirectX\ver.11\Public\DeferredShader.h"
#include "..\..\..\..\HarmonyFrameWork\Graphics\Shader\DirectX\ver.11\Public\ForwardDiffuseOnlyMeshShader.h"
#include "..\..\..\..\HarmonyFrameWork\Graphics\Shader\DirectX\ver.11\Public\SpecularPerVertexShader.h"

using namespace std;
void ModelViewLevelStartState::Enter()
{
	shared_ptr<HFGraphics::DirectinalLight> directionalLight = make_shared<HFGraphics::DirectinalLight>();
	HFGraphics::DIRECTIONAL_LIGHT_PRAM pram;
	pram.color = HFVECTOR4(1, 1, 1, 1);
	pram.direction = HFVECTOR4(1, -1, 1, 0);
	directionalLight->SetPram(pram);
	HFGraphics::LightManager::GetInstance()->Register(directionalLight);
	shared_ptr<StaticMeshActor> phongSpecularMesh = make_shared<StaticMeshActor>();
	phongSpecularMesh->LoadMesh("Resource/Mesh/Sphere.hfm");
	phongSpecularMesh->SetMaterialShader(0, std::make_shared<SpecularPhongShader>());
	phongSpecularMesh->GetSubMeshMaterial(0)->SetDiffuse(HFVECTOR4(0.9, 0.8, 0.3, 1));
	phongSpecularMesh->GetSubMeshMaterial(0)->SetAmbient(HFVECTOR4(0.0, 0.0, 0.00, 1));
	phongSpecularMesh->GetSubMeshMaterial(0)->SetSpecular(HFVECTOR4(1, 1, 0.4, 1.0));
	//phongSpecularMesh->SetMaterialShader(0, std::make_shared<SpecularPhongShader>());

	sTASK_SYSTEM->RegisterTask("model", phongSpecularMesh);
	phongSpecularMesh->LoadDiffuseTexture2D(0, "Resource/Texture/XA-20_Razorback_Strike_Fighter_P01.png");


	//sTASK_SYSTEM->RegisterTask("simpleMesh", simpleMesh);

	shared_ptr<StaticMeshActor> colorSprite = make_shared<StaticMeshActor>();
	shared_ptr<Mesh> spMesh = BasicMeshFactory::GetInstance()->Create(HF_BM_RECTANGLE_SPRITE, 3, 0, 0);
	colorSprite->SetMesh(spMesh);
	colorSprite->GetTransform()->SetScale(HFVECTOR3(100, 100, 0));
	colorSprite->GetTransform()->SetPosition(HFVECTOR3(-100, -100, 2000));
	shared_ptr<LineActor> lineRenderer = make_shared<LineActor>();
	TaskSystem::GetInstance()->RegisterTask("lineRenderer", lineRenderer);
	shared_ptr<Sprite2DActor> monotoneSprite = make_shared<Sprite2DActor>();

	HFGraphics::LineData lineData;
	for (int i = 0; i<60; i++)
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

void ModelViewLevelStartState::Execute()
{
	static UINT meshNum = 0;
	static UINT shaderNum = 0;

	shared_ptr < CameraActor>	camera3D = dynamic_pointer_cast<CameraActor> (sTASK_SYSTEM->SearchByTaskName("3Dcamera"));

	shared_ptr < StaticMeshActor>	mesh = dynamic_pointer_cast<StaticMeshActor> (sTASK_SYSTEM->SearchByTaskName("model"));

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

	if (sINPUT->IsHoldKeyboard(DIK_W))
	{
		mesh->GetTransform()->SetEulerDegAngles(mesh->GetTransform()->GetEulerDegAngles() + HFVECTOR3(0, 0, 1));
	}
	if (sINPUT->IsHoldKeyboard(DIK_S))
	{
		mesh->GetTransform()->SetEulerDegAngles(mesh->GetTransform()->GetEulerDegAngles() - HFVECTOR3(0, 0, 1));
	}
	if (sINPUT->IsHoldKeyboard(DIK_A))
	{
		mesh->GetTransform()->SetEulerDegAngles(mesh->GetTransform()->GetEulerDegAngles() + HFVECTOR3(0, 1, 0));
	}
	if (sINPUT->IsHoldKeyboard(DIK_D))
	{
		mesh->GetTransform()->SetEulerDegAngles(mesh->GetTransform()->GetEulerDegAngles() - HFVECTOR3(0, 1, 0));
	}

	if (sINPUT->IsTriggerKeyboard(DIK_1))
	{
		++meshNum %= 2;
		switch(meshNum)
		{
		case 0:
			mesh->LoadMesh("Resource/Mesh/Sphere.hfm");
			break;
		case 1:
			mesh->LoadMesh("Resource/Mesh/Lod.hfm");
			break;
		}
		mesh->GetSubMeshMaterial(0)->SetDiffuse(HFVECTOR4(0.9, 0.8, 0.3, 1));
		mesh->GetSubMeshMaterial(0)->SetAmbient(HFVECTOR4(0.0, 0.0, 0.00, 1));
		mesh->GetSubMeshMaterial(0)->SetSpecular(HFVECTOR4(1, 1, 0.4, 1.0));
		mesh->LoadDiffuseTexture2D(0, "Resource/Texture/XA-20_Razorback_Strike_Fighter_P01.png");



	}
	if (sINPUT->IsTriggerKeyboard(DIK_2))
	{
		++shaderNum %= 3;
		switch (shaderNum)
		{
		case 0:														
			mesh->SetMaterialShader(0, std::make_shared<FowardDiffuseOnlyMeshShader>());
			break;
		case 1:
			mesh->SetMaterialShader(0, std::make_shared<SpecularPerVertexShader>());
			break;
		case 2:
			mesh->SetMaterialShader(0, std::make_shared<SpecularPhongShader>());
			break;
		
		}
	}


	
}

void ModelViewLevelStartState::Exit()
{

}

std::shared_ptr<IState> ModelViewLevelStartState::GetNewState(void)
{
	return std::make_shared<ModelViewLevelMainState>();
}

void ModelViewLevelMainState::Enter()
{

}

void ModelViewLevelMainState::Execute()
{

}

void ModelViewLevelMainState::Exit()
{

}

std::shared_ptr<IState> ModelViewLevelMainState::GetNewState(void)
{
	return std::make_shared<ModelViewLevelMainState>();
}
