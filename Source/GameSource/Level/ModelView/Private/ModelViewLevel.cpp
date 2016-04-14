#include "../Public/ModelViewLevel.h"
#include "../../../../HarmonyFrameWork/Core/Task/Public/TaskSystem.h"
#include "../../../../HarmonyFrameWork/Core/Actor/Public/StaticMeshActor.h"

using namespace std;
ModelViewLevel::ModelViewLevel()
{
}

ModelViewLevel::~ModelViewLevel()
{
}

BOOL ModelViewLevel::Init()
{
	shared_ptr<StaticMeshActor> actor = shared_ptr<StaticMeshActor>(new StaticMeshActor);
	TaskSystem::GetInstance()->RegisterTask("staticmesh", actor);
	
		actor->LoadMesh("Resource/Mesh/Sphere.hfm");
	return true;
}

BOOL ModelViewLevel::Update()
{
	UpdateState(shared_from_this());
	return true;
}

void ModelViewLevel::Reset()
{

}
