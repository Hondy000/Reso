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
#include "..\..\..\..\HarmonyFrameWork\Graphics\Shadow\Public\ShadowMapActor.h"
#include "..\..\..\..\HarmonyFrameWork\Graphics\RenderDevice\DirectX\ver.11\Public\GeometryBuffers.h"
#include "..\..\..\..\HarmonyFrameWork\Graphics\Shader\DirectX\ver.11\Public\DefaultSpriteShader.h"

using namespace std;
void ModelViewLevelStartState::Enter()
{


	shared_ptr<HFGraphics::DirectinalLight> directionalLight = make_shared<HFGraphics::DirectinalLight>();
	directionalLight->SetDirection(HFVECTOR4(0, -1, 0, 1));
	
	HFGraphics::LightManager::GetInstance()->Register(directionalLight);
	int num = 0;
	for (int i = 0; i < 4;i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				num++;
				shared_ptr<StaticMeshActor> phongSpecularMesh = make_shared<StaticMeshActor>();
				phongSpecularMesh->LoadMesh("Resource/Mesh/Sphere.hfm");
				phongSpecularMesh->SetMaterialShader(0, std::make_shared<DeferredShader>());
				phongSpecularMesh->GetSubMeshMaterial(0)->SetDiffuse(HFVECTOR4(0.9, 0.8, 0.8, 1));
				phongSpecularMesh->GetSubMeshMaterial(0)->SetAmbient(HFVECTOR4(0.2, 0.2, 0.10, 1));
				phongSpecularMesh->GetSubMeshMaterial(0)->SetSpecular(HFVECTOR4(1, 1, 0.4, 1.0));
				//phongSpecularMesh->SetMaterialShader(0, std::make_shared<SpecularPhongShader>());

				phongSpecularMesh->GetTransform()->SetPosition(HFVECTOR3(i * 5, j * 5,  k * 5));
				sTASK_SYSTEM->RegisterTask(std::string("model") + std::to_string(num) , phongSpecularMesh);
				phongSpecularMesh->LoadDiffuseTexture2D(0, "Resource/Texture/XA-20_Razorback_Strike_Fighter_P01.png");
				
				ShadowManager::GetInstance()->RegisterMesh(phongSpecularMesh,phongSpecularMesh->GetTransform());

			}
		}
	}


	shared_ptr<HFGraphics::DirectinalLight> dLight = make_shared<HFGraphics::DirectinalLight>();

	dLight->SetDirection(HFVECTOR4(0, -1, 1, 0));
	dLight->SetPosition(HFVECTOR3(0, 50, 0));
	dLight->SetColor(HFVECTOR4(1,1,1,1));

	HFGraphics::LightManager::GetInstance()->Register(dLight);

	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 1; k++)
			{
				num++;
				shared_ptr<HFGraphics::SpotLight> point = make_shared<HFGraphics::SpotLight>();
				HFGraphics::SPOT_LIGHT_PRAM par;
				point->SetRange(10);
				point->SetFalloff(10);
				point->SetAtttention(10);
				point->SetColor(HFVECTOR4(1, 1, 1, 1));
				point->SetDirection(HFVECTOR4(0, 0, 1, 0)); 
				point->SetPosition(HFVECTOR4(5*j, 0, 0,0));

				point->SetPHI(HFToRadian(12));
				HFGraphics::LightManager::GetInstance()->Register(point);
			}
		}
	}
	//sTASK_SYSTEM->RegisterTask("simpleMesh", simpleMesh);

	shared_ptr<StaticMeshActor> colorSprite = make_shared<StaticMeshActor>();
	shared_ptr<Mesh> spMesh = BasicMeshFactory::GetInstance()->Create(HF_BM_RECTANGLE_SPRITE, 3, 0, 0);
	colorSprite->SetMesh(spMesh);
	colorSprite->GetTransform()->SetScale(HFVECTOR3(100, 100, 0));
	colorSprite->GetTransform()->SetPosition(HFVECTOR3(-100, -100, 2000));
	shared_ptr<LineActor> lineRenderer = make_shared<LineActor>();

	HFGraphics::LineData lineData;
	for (int i = 0; i < 60; i++)
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

	TaskSystem::GetInstance()->RegisterTask("lineRenderer", lineRenderer);
	shared_ptr<Sprite2DActor> monotoneSprite = make_shared<Sprite2DActor>();

	//	sTASK_SYSTEM->RegisterTask("rect", colorSprite);
	shared_ptr < CameraActor>	camera2D = make_shared<CameraActor>();
	shared_ptr < CameraActor>	camera3D = make_shared<CameraActor>();
	camera3D->SetCameraPosition(HFVECTOR3(0, 10, -10));
	camera2D->SetIs2DCamera(true);
	TaskSystem::GetInstance()->RegisterTask("2Dcamera", camera2D);
	TaskSystem::GetInstance()->RegisterTask("3Dcamera", camera3D);


	// デバッグ 

	// アルベド表示スプライト
	std::shared_ptr<Sprite2DActor> sprite0 = std::make_shared<Sprite2DActor>();
	
	sprite0->GetTransform()->SetScale(100, 100, 0);
	sprite0->GetTransform()->SetPosition(-100, -100, 0);
	
	sprite0->SetMaterialDiffuseTexture(0,sRENDER_DEVICE_MANAGER->GetGeometryBuffer()->GetShaderResourceView(0));

	TaskSystem::GetInstance()->RegisterTask("sprite0", sprite0);


	// アルベド表示スプライト
	std::shared_ptr<Sprite2DActor> sprite1 = std::make_shared<Sprite2DActor>();


	sprite1->GetTransform()->SetScale(100, 100, 0);
	sprite1->GetTransform()->SetPosition(-300, -100, 0);

	sprite1->SetMaterialDiffuseTexture(0, sRENDER_DEVICE_MANAGER->GetGeometryBuffer()->GetShaderResourceView(1));

	TaskSystem::GetInstance()->RegisterTask("sprite1", sprite1);


	std::shared_ptr<Sprite2DActor> sprite2 = std::make_shared<Sprite2DActor>();


	sprite2->GetTransform()->SetScale(100, 100, 0);
	sprite2->GetTransform()->SetPosition(-500, -100, 0);

	sprite2->SetMaterialDiffuseTexture(0, sRENDER_DEVICE_MANAGER->GetGeometryBuffer()->GetShaderResourceView(2));

	TaskSystem::GetInstance()->RegisterTask("sprite2", sprite2);


	std::shared_ptr<Sprite2DActor> sprite3 = std::make_shared<Sprite2DActor>();


	sprite3->GetTransform()->SetScale(100, 100, 0);
	sprite3->GetTransform()->SetPosition(-700, -100, 0);

	sprite3->SetMaterialDiffuseTexture(0, sRENDER_DEVICE_MANAGER->GetGeometryBuffer()->GetShaderResourceView(3));

	TaskSystem::GetInstance()->RegisterTask("sprite3", sprite3);

	std::shared_ptr<Sprite2DActor> sprite4 = std::make_shared<Sprite2DActor>();


	sprite4->GetTransform()->SetScale(100, 100, 0);
	sprite4->GetTransform()->SetPosition(-900, -100, 0);

	sprite4->SetMaterialDiffuseTexture(0, ShadowManager::GetInstance()->GetShadowMapTextureOfDirectionalight());

	TaskSystem::GetInstance()->RegisterTask("sprite4", sprite4);

	// 地面生成
	std::shared_ptr<StaticMeshActor> groundMesh = std::make_shared<StaticMeshActor>();
	groundMesh->SetMesh(BasicMeshFactory::GetInstance()->Create(HF_BM_QUAD, 0, 0, 0));
	groundMesh->SetMaterialShader(0, std::make_shared<DeferredShader>());
	groundMesh->GetTransform()->SetEulerDegAngles(90,0,0);
	groundMesh->GetTransform()->SetScale(HFVECTOR3(20, 20, 20));
	groundMesh->GetTransform()->SetPosition(HFVECTOR3(0, -2, 0));
	groundMesh->SetMaterialDiffuseTexture(0,Texture2DManager::GetInstance()->Get("Resource/Texture/DefaultWhite.png"));
	groundMesh->GetSubMeshMaterial(0)->SetDiffuse(HFVECTOR4(0.5f, 0.5f, 0.5f, 1));
	groundMesh->GetSubMeshMaterial(0)->SetSpecular(HFVECTOR4(0.5f, 0.5f, 0.5f, 1));
	sTASK_SYSTEM->RegisterTask("groundMesh", groundMesh);
}

void ModelViewLevelStartState::Execute()
{
	static UINT meshNum = 0;
	static UINT shaderNum = 0;

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
