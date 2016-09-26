
#include "..\Public\Mesh.h"
#include "..\..\..\Utility\Public\HFString.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

// Access the SubMeshArray
std::vector<std::shared_ptr<SubMesh>>& Mesh::GetSubMeshArray(void)
{
	return(m_subMeshArray);
};

void Mesh::SetSubMeshArray(const std::vector<std::shared_ptr<SubMesh>>& subMeshArray)
{
	m_subMeshArray = subMeshArray;
	for (int i = 0; i < m_subMeshArray.size();i++)
	{
		m_subMeshArray[i]->SetParentMesh(shared_from_this());
	}
};

bool Mesh::LoadDiffuseTexture2D(UINT submeshNum, HFString teturePath)
{
	if (m_subMeshArray[submeshNum])
	{
		return m_subMeshArray[submeshNum]->LoadDiffuseTexture2D(teturePath);
	}
	return false;
	
}

std::weak_ptr<BaseRenderMeshObject> Mesh::GetParentObject() const
{
	return m_parentObject;
}

void Mesh::SetParentObject(std::shared_ptr<BaseRenderMeshObject>& _val)
{
	m_parentObject = _val;
}

