#include "..\Public\StaticMeshCompornent.h"
#include "..\..\..\ResorceManager\Public\MeshManager.h"
#include "..\..\..\Graphics\RenderObject\Public\StaticMeshObject.h"

using namespace std;

BOOL StaticMeshCompornent::Init()
{
	return true;
};

BOOL StaticMeshCompornent::LoadMesh(const string& path)
{
	m_mesh = MeshManager::GetInstance()->Get(path);
	return S_OK;

}

BOOL StaticMeshCompornent::Update()
{

	StaticMeshObject::Update();
	return true;
}

