/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Actor\Private\StaticMeshActor.cpp
 *
 * @brief	Implements the static mesh actor class.
 **************************************************************************************************/

#include "..\Public\StaticMeshActor.h"
#include "../../../ResorceManager/Public/MeshManager.h"

/**********************************************************************************************//**
 * @fn	StaticMeshActor::StaticMeshActor()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

StaticMeshActor::StaticMeshActor()
{
}

/**********************************************************************************************//**
 * @fn	StaticMeshActor::~StaticMeshActor()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

StaticMeshActor::~StaticMeshActor()
{
}

/**********************************************************************************************//**
 * @fn	bool StaticMeshActor::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool StaticMeshActor::Init()
{
	return true;
}

/**********************************************************************************************//**
 * @fn	bool StaticMeshActor::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool StaticMeshActor::Update()
{
	StaticMeshObject::Update();
	UpdateAllTask();
	return true;
}

/**********************************************************************************************//**
 * @fn	void StaticMeshActor::Reset()
 *
 * @brief	Resets this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void StaticMeshActor::Reset()
{

}

/**********************************************************************************************//**
 * @fn	bool StaticMeshActor::LoadMesh(const std::string& path)
 *
 * @brief	Loads a mesh.
 *
 * @author	Kazuyuki Honda
 *
 * @param	path	Full pathname of the file.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool StaticMeshActor::LoadMesh(const std::string& path)
{
	m_mesh = MeshManager::GetInstance()->Get(path);
	if (m_mesh)
	{
		return S_OK;
	}
	return E_FAIL;
}