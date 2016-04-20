/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Graphics\Private\RenderCommand.cpp
 *
 * @brief	Implements the render command class.
 **************************************************************************************************/

#include "../Public/RenderCommand.h"
#include "../RenderObject/Public/BaseRenderObject.h"
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

bool RenderCommand::Command()
{
	sRENDER_DEVICE_MANAGER->SetTransform
		(
		&VariableManagersManager::GetInstance()->GetVariable<Transform>(m_renderObject->GetGlobalID(), "m_transform")->GetValue()->GetWorldTransform(),
		HFTS_WORLD
			);
	return m_renderObject->Render();	
}

/**********************************************************************************************//**
 * @fn	void RenderCommand::SetRenderObject(const std::shared_ptr<BaseRenderObject> renderObject)
 *
 * @brief	Sets render object.
 *
 * @author	Kazuyuki Honda
 *
 * @param	renderObject	The render object.
 **************************************************************************************************/

void RenderCommand::SetRenderObject(const std::shared_ptr<BaseRenderObject> renderObject)
{
	m_renderObject = renderObject;
};