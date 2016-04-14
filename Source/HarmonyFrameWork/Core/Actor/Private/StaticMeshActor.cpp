#include "..\Public\StaticMeshActor.h"
#include "../../../ResorceManager/Public/MeshManager.h"

StaticMeshActor::StaticMeshActor()
{
}

StaticMeshActor::~StaticMeshActor()
{
}

BOOL StaticMeshActor::Init()
{
	return false;
}

BOOL StaticMeshActor::Update()
{
	StaticMeshObject::Update();
	UpdateAllTask();
	return true;
}

void StaticMeshActor::Reset()
{

}


BOOL StaticMeshActor::LoadMesh(const std::string& path)
{
	m_mesh = MeshManager::GetInstance()->Get(path);
	if (m_mesh)
	{
		return S_OK;
	}
	return E_FAIL;
}