/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Component\Private\StaticMeshCompornent.cpp
 *
 * @brief	Implements the static mesh compornent class.
 **************************************************************************************************/

#include "..\Public\StaticMeshCompornent.h"
#include "..\..\..\ResorceManager\Public\MeshManager.h"
#include "..\..\..\Graphics\RenderObject\Public\StaticMeshObject.h"
#include "..\..\Task\Public\TaskSystem.h"		
#include "..\..\Actor\Public\ActorInterface.h"

using namespace std;

/**********************************************************************************************//**
 * @fn	bool StaticMeshCompornent::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool StaticMeshCompornent::Init()
{
	return true;
};

/**********************************************************************************************//**
 * @fn	bool StaticMeshCompornent::LoadMesh(const string& path)
 *
 * @brief	Loads a mesh.
 *
 * @author	Kazuyuki Honda
 *
 * @param	path	Full pathname of the file.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool StaticMeshCompornent::LoadMesh(const string& path)
{
	m_mesh = MeshManager::GetInstance()->Get(path);
	return S_OK;

}

/**********************************************************************************************//**
 * @fn	bool StaticMeshCompornent::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool StaticMeshCompornent::Update()
{


	shared_ptr<IBaseTask> spTask;
	if (TaskSystem::GetInstance()->SearchByTaskID(this->m_parentActorGlobalID, spTask))
	{
		GetTransform()->SetPosition(dynamic_pointer_cast<IActor>(spTask)->GetTransform()->GetPosition());
		GetTransform()->SetQuaternionRotation(dynamic_pointer_cast<IActor>(spTask)->GetTransform()->GetQuaternionRotation());
	}
	StaticMeshObject::Update();
	return true;
}

