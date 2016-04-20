/**********************************************************************************************//**
 * @file	Source\GameSource\Level\ModelView\Private\ModelViewLevel.cpp
 *
 * @brief	Implements the model view level class.
 **************************************************************************************************/

#include "../Public/ModelViewLevel.h"
#include "../../../../HarmonyFrameWork/Core/Task/Public/TaskSystem.h"
#include "../../../../HarmonyFrameWork/Core/Actor/Public/StaticMeshActor.h"

using namespace std;

/**********************************************************************************************//**
 * @fn	ModelViewLevel::ModelViewLevel()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

ModelViewLevel::ModelViewLevel()
{
}

/**********************************************************************************************//**
 * @fn	ModelViewLevel::~ModelViewLevel()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

ModelViewLevel::~ModelViewLevel()
{
}

/**********************************************************************************************//**
 * @fn	bool ModelViewLevel::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool ModelViewLevel::Init()
{
	shared_ptr<StaticMeshActor> actor = shared_ptr<StaticMeshActor>(new StaticMeshActor);
	TaskSystem::GetInstance()->RegisterTask("staticmesh", actor);
	
		actor->LoadMesh("Resource/Mesh/Sphere.hfm");
	return true;
}

/**********************************************************************************************//**
 * @fn	bool ModelViewLevel::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool ModelViewLevel::Update()
{
	UpdateState(shared_from_this());
	return true;
}

/**********************************************************************************************//**
 * @fn	void ModelViewLevel::Reset()
 *
 * @brief	Resets this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void ModelViewLevel::Reset()
{

}
