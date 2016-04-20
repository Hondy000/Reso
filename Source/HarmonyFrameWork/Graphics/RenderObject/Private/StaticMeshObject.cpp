
#include "../Public/StaticMeshObject.h"
#include "../../../ResorceManager/Public/MeshFactory.h"
#include "../../../ResorceManager/Public/MeshManager.h"
#include "../../Public/RenderCommand.h"
#include "../../../Core/Task/Public/TaskSystem.h"
#include "../Public/SubMesh.h"
#include "../../Matetial/Public/Material.h"
#include "../../Shader/Basic/Public/BaseShader.h"

bool StaticMeshObject::Update()
{

	for (int i = 0; i < m_mesh->GetSubMeshArray().size();i++)
	{
		std::shared_ptr<RenderCommand> command;
		command = std::shared_ptr<RenderCommand>(new RenderCommand);
		command->SetRenderObject(shared_from_this());
		command->SetRenderMeshElement(i);
		command->SetRenderPriority(m_mesh->GetSubMeshArray()[i]->GetMaterial()->GetMaterialShader()->GetPathPriority());
		TaskSystem::GetInstance()->RegisterRenderCommand(command);
	}
	return true;
}
