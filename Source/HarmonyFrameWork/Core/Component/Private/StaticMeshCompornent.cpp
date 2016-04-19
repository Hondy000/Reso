#include "..\Public\StaticMeshCompornent.h"
#include "..\..\..\ResorceManager\Public\MeshManager.h"
#include "..\..\..\Graphics\RenderObject\Public\StaticMeshObject.h"
#include "..\..\Task\Public\TaskSystem.h"		
#include "..\..\Actor\Public\ActorInterface.h"

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


	shared_ptr<IBaseTask> spTask;
	if (TaskSystem::GetInstance()->SearchByTaskID(this->m_parentActorGlobalID, spTask))
	{
		GetTransform()->SetPosition(dynamic_pointer_cast<IActor>(spTask)->GetTransform()->GetPosition());
		GetTransform()->SetRotation(dynamic_pointer_cast<IActor>(spTask)->GetTransform()->GetRotation());
	}
	StaticMeshObject::Update();
	return true;
}

