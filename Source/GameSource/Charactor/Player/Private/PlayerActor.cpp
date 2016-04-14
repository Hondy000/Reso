#include "../Public/PlayerActor.h"
#include "../../../../HarmonyFrameWork/Core/Component/Public/StaticMeshCompornent.h"
#include "../../../../HarmonyFrameWork/Core/Task/Public/TaskSystem.h"
#include "../../../../HarmonyFrameWork/Core/Component/Public/CameraCompornent.h"
#include "../Public/PlayerStates.h"

using namespace std;

BOOL PlayerActor::Init()
{
	CharactorActor::Init();
	shared_ptr<CameraCompornent> cameraCompornent = make_shared<CameraCompornent>();
	RegisterCompornent(typeid(CameraCompornent).name() , cameraCompornent);
	auto it = m_compornentMap.find(typeid(StaticMeshCompornent).name());
	if(it != m_compornentMap.end())
	{
		if(dynamic_pointer_cast<StaticMeshCompornent>(it->second)->LoadMesh("Resource/Mesh/Sphere.hfm"))
		{
		}
		dynamic_pointer_cast<StaticMeshCompornent>(it->second)->GetTransform()->SetPosition(0, 0, 0);

	}

	RegisterState(std::make_shared<PlayerAliveBeingState>(),shared_from_this());
	return true;
}

BOOL PlayerActor::Update()
{
	static FLOAT rot = 0;
	rot += 0.01;
	auto it = m_compornentMap.find(typeid(StaticMeshCompornent).name());
	if (it != m_compornentMap.end())
	{
		dynamic_pointer_cast<StaticMeshCompornent>(it->second)->GetTransform()->SetRotation(0,rot, 0);
	}
	UpdateState(shared_from_this());
	UpdateAllTask();
	

	return true;

}

void PlayerActor::Reset()
{

}
