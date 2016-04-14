#include "../Public/RenderCommand.h"
#include "../RenderObject/Public/BaseRenderObject.h"
#include "../RenderDevice/Basic/Public/BaseRenderDeviceManager.h"
#include "../RenderDevice/Basic/Public/RendererManager.h"
#include "../RenderObject/Public/SubMesh.h"

BOOL RenderCommand::Command()
{
	sRENDER_DEVICE_MANAGER->SetTransform
		(
		&VariableManagersManager::GetInstance()->GetVariable<Transform>(m_renderObject->GetGlobalID(), "m_transform")->GetValue()->GetWorldTransform(),
		HFTS_WORLD
			);
	return m_renderObject->Render();	
}

void RenderCommand::SetRenderObject(const std::shared_ptr<BaseRenderObject> renderObject)
{
	m_renderObject = renderObject;
};