
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
};

bool Mesh::LoadDiffuseTexture2D(UINT submeshNum, HFString teturePath)
{
	if (m_subMeshArray[submeshNum])
	{
		return m_subMeshArray[submeshNum]->LoadDiffuseTexture2D(teturePath);
	}
	return false;
	
}

