#include "..\Public\BaseRenderObject.h"
#include "..\..\..\Core\Task\Public\TaskSystem.h"
#include "../../Public/RenderCommand.h"
#include "..\..\RenderDevice\Basic\Public\RendererManager.h"
#include "../Public/Mesh.h"

bool BaseRenderObject::Render()
{
	for (int i = 0; i <m_mesh->GetSubMeshArray().size() ;i++)
	{
		m_mesh->GetSubMeshArray()[i]->Render();
	}
	return true;
}

void BaseRenderObject::SetSubMeshMaterial(int submeshNum, std::shared_ptr<Material> material)
{
	m_mesh->GetSubMeshArray()[submeshNum]->SetMaterial(material);
}

const std::shared_ptr<Material>& BaseRenderObject::GetSubMeshMaterial(int submeshNum)
{
	return m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial();
}

void BaseRenderObject::SetMaterialDiffuseTexture(int submeshNum, std::shared_ptr<IBaseTexture> texture)
{
	m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->SetDiffuseTexture(texture);
}

const std::shared_ptr<IBaseTexture>& BaseRenderObject::GetMaterialDiffuseTexture(int submeshNum)
{
	return m_mesh->GetSubMeshArray()[submeshNum]->GetMaterial()->GetDiffuseTexture();
}

