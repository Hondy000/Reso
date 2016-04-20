/**********************************************************************************************//**
 * @file	Source\GameSource\Charactor\Player\Private\PlayerActor.cpp
 *
 * @brief	Implements the player actor class.
 **************************************************************************************************/

#include "../Public/PlayerActor.h"
#include "../../../../HarmonyFrameWork/Core/Component/Public/StaticMeshCompornent.h"
#include "../../../../HarmonyFrameWork/Core/Task/Public/TaskSystem.h"
#include "../../../../HarmonyFrameWork/Core/Component/Public/CameraCompornent.h"
#include "../Public/PlayerStates.h"

using namespace std;

/**********************************************************************************************//**
 * @fn	bool PlayerActor::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool PlayerActor::Init()
{
	CharactorActor::Init();
	shared_ptr<CameraCompornent> cameraCompornent = make_shared<CameraCompornent>();
	RegisterCompornent(typeid(CameraCompornent).name() , cameraCompornent);
	cameraCompornent->SetDistanceFromFollowTarget(HFVECTOR3(0, 75, 0));
	cameraCompornent->SetViewObjectOffset(HFVECTOR3(0, 1, 0));
	cameraCompornent->SetUpVector(HFVECTOR3(0, 0, 1));
	cameraCompornent->SetFollowObject(shared_from_this());
	cameraCompornent->SetViewObject(shared_from_this());

	auto it = m_compornentMap.find(typeid(StaticMeshCompornent).name());
	if(it != m_compornentMap.end())
	{
		if(dynamic_pointer_cast<StaticMeshCompornent>(it->second)->LoadMesh("Resource/Mesh/PlayerSphere.hfm"))
		{
		}
		dynamic_pointer_cast<StaticMeshCompornent>(it->second)->GetTransform()->SetPosition(0, 0, 0);

	}

	RegisterState(std::make_shared<PlayerAliveBeingState>(),shared_from_this());
	return true;
}

/**********************************************************************************************//**
 * @fn	bool PlayerActor::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool PlayerActor::Update()
{
	UpdateState(shared_from_this());
	UpdateAllTask();
	

	return true;

}

/**********************************************************************************************//**
 * @fn	void PlayerActor::Reset()
 *
 * @brief	Resets this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void PlayerActor::Reset()
{

}
