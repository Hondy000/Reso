/**********************************************************************************************//**
 * @file	Source\GameSource\Charactor\Private\CharactorActor.cpp
 *
 * @brief	Implements the charactor class.
 **************************************************************************************************/

#include "../Public/CharactorActor.h"

using namespace std;

/**********************************************************************************************//**
 * @fn	bool CharactorActor::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool CharactorActor::Init()
{
	if(IActor::Init())
	{
		shared_ptr<StaticMeshCompornent> staticMesh = make_shared<StaticMeshCompornent>();
		RegisterCompornent(typeid(StaticMeshCompornent).name(), staticMesh);
	}
	return true;
}

