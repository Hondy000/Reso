#include "..\Public\BaseRenderMeshObject.h"
#include "..\..\..\Core\Task\Public\TaskSystem.h"
#include "../../Public/BaseGraphicsCommand.h"
#include "..\..\RenderDevice\Basic\Public\RendererManager.h"
#include "../Public/Mesh.h"
#include "..\..\Shader\Basic\Public\BaseGraphicsShader.h"

bool BaseRenderMeshObject::Setup()
{

	if (m_mesh == nullptr)
	{
		return false;
	}

	GetCommmandArray().resize(m_mesh->GetSubMeshArray().size());
	
	for (int i = 0; i < m_mesh->GetSubMeshArray().size(); i++)
	{
		// マテリアルのシェーダーをセットアップ
		m_mesh->GetSubMeshArray()[i]->GetMaterial()->GetMaterialShader()->CreateAndRegisterGraphicsCommand(shared_from_this(), i);
	}
	return true;
}

bool BaseRenderMeshObject::Update()
{
	return true;
}

bool BaseRenderMeshObject::RenderSubMesh(int elem)
{
	m_mesh->GetSubMeshArray()[elem]->Render();
	return true;
}

const std::shared_ptr<Mesh>& BaseRenderMeshObject::GetMesh(void) const
{
	return(m_mesh);
};

void BaseRenderMeshObject::SetMesh(const std::shared_ptr<Mesh>& mesh)
{
	m_mesh = mesh;
	m_commmandArray.resize(m_mesh->GetSubMeshArray().size());
	mesh->SetParentObject(downcasted_shared_from_this<BaseRenderMeshObject>());
};

void BaseRenderMeshObject::SetSubMeshMaterial(UINT submeshNum, std::shared_ptr<Material> material)
{
	m_mesh->GetSubMeshArray()[submeshNum]->SetMaterial(material);
	m_commmandArray[submeshNum]->SetRenderPriority(m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->GetMaterialShader()->GetPathPriority());
}

const std::shared_ptr<Material>& BaseRenderMeshObject::GetSubMeshMaterial(UINT submeshNum)
{
	return m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial();
}

void BaseRenderMeshObject::SetMaterialDiffuseTexture(UINT submeshNum, std::shared_ptr<IBaseTexture> texture)
{
	m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->SetDiffuseTexture(texture);
}

const std::shared_ptr<IBaseTexture>& BaseRenderMeshObject::GetMaterialDiffuseTexture(UINT submeshNum)
{
	return m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->GetDiffuseTexture();
}

void BaseRenderMeshObject::SetMaterialShader(UINT submeshNum, std::shared_ptr<BaseGraphicsShader> shader)
{
	m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->SetMaterialShader(shader);
	m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->GetMaterialShader()->Setup();
	if (m_commmandArray[submeshNum])
	{
		m_commmandArray[submeshNum]->SetRenderPriority(m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->GetMaterialShader()->GetPathPriority());
	}
}

const std::shared_ptr<BaseGraphicsShader>& BaseRenderMeshObject::GetMaterialShader(UINT submeshNum)
{
	return m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->GetMaterialShader();
}

bool BaseRenderMeshObject::LoadDiffuseTexture2D(UINT submeshNum, HFString teturePath)
{
	if (m_mesh)
	{
		return m_mesh->LoadDiffuseTexture2D(submeshNum, teturePath);
	}
	return false;
}

