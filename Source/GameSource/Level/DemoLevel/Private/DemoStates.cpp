#include "../Public/DemoStates.h"
#include "../../../Charactor/Player/Public/PlayerActor.h"
#include "../../../../HarmonyFrameWork/Core/Task/Public/TaskSystem.h"
#include "../../../../HarmonyFrameWork/Core/Actor/Public/StaticMeshActor.h"
#include "../../../../HarmonyFrameWork/Graphics/ParticleSystem/Public/BaseEmitter.h"
#include "../../../../HarmonyFrameWork/Core/Actor/Public/CameraActor.h"

using namespace std;


void DemoStartState::Enter( )
{
	shared_ptr<StaticMeshActor> player = make_shared<StaticMeshActor>();
	player->LoadMesh("Resource/Mesh/Sphere.hfm");
	TaskSystem::GetInstance()->RegisterTask("staticmesh",player);
	player->Init();
	shared_ptr<CameraActor>	camera = make_shared<CameraActor>(); 
	TaskSystem::GetInstance()->RegisterTask("camera", camera);

	//shared_ptr<BaseEmitter>emitter = make_shared<BaseEmitter>();
	//emitter->Setup(3,10,HFVECTOR2(10,10),10,"Resource/Texture/DefaultWhite.png");
}

void DemoStartState::Execute( )
{

}

void DemoStartState::Exit( )
{

}

std::shared_ptr<IState> DemoStartState::GetNewState(void)
{
	return std::make_shared<DemoMainState>();
}

void DemoMainState::Enter( )
{

}

void DemoMainState::Execute( )
{

}

void DemoMainState::Exit( )
{

}

std::shared_ptr<IState> DemoMainState::GetNewState(void)
{
	return std::make_shared<DemoMainState>();
}
