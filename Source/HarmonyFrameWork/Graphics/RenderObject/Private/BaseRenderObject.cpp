#include "..\Public\BaseRenderObject.h"
#include "..\..\..\Core\Task\Public\TaskSystem.h"
#include "../../Public/RenderCommand.h"
#include "..\..\RenderDevice\Basic\Public\RendererManager.h"
#include "../Public/Mesh.h"
#include "..\..\Shader\Basic\Public\BaseShader.h"


bool BaseRenderObject::Setup()
{

	if (m_mesh == nullptr)
	{
		return false;
	}
	m_commmandArray.resize(m_mesh->GetSubMeshArray().size());
	for (int i = 0; i < m_mesh->GetSubMeshArray().size(); i++)
	{
		std::shared_ptr<RenderCommand> command;
		command = std::shared_ptr<RenderCommand>(new RenderCommand);
		command->SetRenderObject(shared_from_this());
		command->SetRenderMeshElement(i);
		command->SetRenderPriority(m_mesh->GetSubMeshArray()[i]->GetMaterial()->GetMaterialShader()->GetPathPriority());
		TaskSystem::GetInstance()->RegisterRenderCommand(command);
		m_commmandArray[i]= command;			
	}
	return true;
}

bool BaseRenderObject::Update()
{
	return true;
}

bool BaseRenderObject::RenderSubMesh(int elem)
{
	m_mesh->GetSubMeshArray()[elem]->Render();
	return true;
}

const std::shared_ptr<Mesh>& BaseRenderObject::GetMesh(void) const
{
	return(m_mesh);
};

void BaseRenderObject::SetMesh(const std::shared_ptr<Mesh>& mesh)
{
	m_mesh = mesh;
	m_commmandArray.resize(m_mesh->GetSubMeshArray().size());
	mesh->SetParentObject(downcasted_shared_from_this<BaseRenderObject>());
};

void BaseRenderObject::SetSubMeshMaterial(UINT submeshNum, std::shared_ptr<Material> material)
{
	m_mesh->GetSubMeshArray()[submeshNum]->SetMaterial(material);
	m_commmandArray[submeshNum]->SetRenderPriority(m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->GetMaterialShader()->GetPathPriority());
}

const std::shared_ptr<Material>& BaseRenderObject::GetSubMeshMaterial(UINT submeshNum)
{
	return m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial();
}

void BaseRenderObject::SetMaterialDiffuseTexture(UINT submeshNum, std::shared_ptr<IBaseTexture> texture)
{
	m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->SetDiffuseTexture(texture);
}

const std::shared_ptr<IBaseTexture>& BaseRenderObject::GetMaterialDiffuseTexture(UINT submeshNum)
{
	return m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->GetDiffuseTexture();
}

void BaseRenderObject::SetMaterialShader(UINT submeshNum, std::shared_ptr<BaseShader> shader)
{
	m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->SetMaterialShader(shader);
	m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->GetMaterialShader()->Setup();
	if (m_commmandArray[submeshNum])
	{
		m_commmandArray[submeshNum]->SetRenderPriority(m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->GetMaterialShader()->GetPathPriority());
	}
}

const std::shared_ptr<BaseShader>& BaseRenderObject::GetMaterialShader(UINT submeshNum)
{
	return m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->GetMaterialShader();
}

bool BaseRenderObject::LoadDiffuseTexture2D(UINT submeshNum, HFString teturePath)
{
	if (m_mesh)
	{
		return m_mesh->LoadDiffuseTexture2D(submeshNum, teturePath);
	}
	return false;
}

std::vector<std::shared_ptr<RenderCommand>> BaseRenderObject::GetCommmandArray()
{
	return m_commmandArray;
}

