#include "../Public/Sprite2DObject.h"
#include "../../Public/RenderCommand.h"
#include "../../../Core/Task/Public/TaskSystem.h"
#include "..\Public\Mesh.h"
#include "..\..\Shader\Basic\Public\BaseShader.h"
#include "..\..\..\ResorceManager\Public\BasicMeshManager.h"
#include "..\..\..\ResorceManager\Public\BasicMeshFactory.h"
#include "..\..\Shader\DirectX\ver.11\Public\DefaultSpriteShader.h"


Sprite2DObject::Sprite2DObject()
{
}

Sprite2DObject::~Sprite2DObject()
{

}

bool Sprite2DObject::Init()
{
	m_mesh = BasicMeshManager::GetInstance()->Get(HF_BM_SPRITE, 0, 0, 0);
	m_mesh->GetSubMeshArray()[0]->SetMaterial(std::make_shared<Material>());
	m_mesh->GetSubMeshArray()[0]->GetMaterial()->SetMaterialShader(std::make_shared<DefaultSpriteShader>());
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

