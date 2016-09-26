/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Graphics\Private\RenderCommand.cpp
 *
 * @brief	Implements the render command class.
 **************************************************************************************************/

#include "../Public/BaseGraphicsCommand.h"
#include "../RenderObject/Public/BaseRenderMeshObject.h"
#include "../RenderDevice/Basic/Public/BaseRenderDeviceManager.h"
#include "../RenderDevice/Basic/Public/RendererManager.h"
#include "../RenderObject/Public/SubMesh.h"

/**********************************************************************************************//**
 * @fn	bool RenderCommand::Command()
 *
 * @brief	Commands this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool BaseGraphicsCommand::Update()
{
	return true;
}


void BaseGraphicsCommand::Reset()
{

}

ClearRenderTargetViewComand::ClearRenderTargetViewComand()
{

}

ClearRenderTargetViewComand::~ClearRenderTargetViewComand()
{

}

bool ClearRenderTargetViewComand::Update()
{
	sRENDER_DEVICE_MANAGER->ClearScreen();
	return true;
}

bool RenderMeshCommmand::Update()
{

	UpdateChildTask();
	// 描画オブジェクトのIDからTransformを取得
	sRENDER_DEVICE_MANAGER->SetTransform
	(
		&VariableManagersManager::GetInstance()->GetVariable<Transform>(m_graphicsObject->GetGlobalID(), "m_transform")->GetValue()->GetWorldTransform(),
		HFTS_WORLD
	);
	return m_graphicsObject->RenderSubMesh(m_renderMeshElement);
}

void RenderMeshCommmand::Reset()
{

}

void RenderMeshCommmand::SetRenderObject(const std::shared_ptr<BaseRenderMeshObject> renderObject)
{

	m_graphicsObject = renderObject;
}
