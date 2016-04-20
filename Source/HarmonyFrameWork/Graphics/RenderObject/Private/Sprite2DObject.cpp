#include "../Public/Sprite2DObject.h"
#include "../../Public/RenderCommand.h"
#include "../../../Core/Task/Public/TaskSystem.h"
#include "..\Public\Mesh.h"
#include "..\..\Shader\Basic\Public\BaseShader.h"


bool Sprite2DObject::Init()
{
	

	return true;
}

bool Sprite2DObject::Update()
{

	std::shared_ptr<RenderCommand> command;
	command = std::shared_ptr<RenderCommand>(new RenderCommand);
	command->SetRenderObject(StaticMeshObject::shared_from_this());
	command->SetRenderPriority(m_mesh->GetSubMeshArray()[0]->GetMaterial()->GetMaterialShader()->GetPathPriority());

	TaskSystem::GetInstance()->RegisterRenderCommand(command);
	return true;
}

