/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Graphics\RenderObject\Public\StaticMeshObject.h
 *
 * @brief	Declares the static mesh object class.
 **************************************************************************************************/

#pragma once
#include "BaseRenderObject.h"

/**********************************************************************************************//**
 * @class	StaticMeshObject StaticMeshObject.h
 * 			Source\HarmonyFrameWork\Graphics\RenderObject\Public\StaticMeshObject.h
 *
 * @brief	A static mesh object.
 *
 * @author	Kazuyuki Honda
 *
 * @sa	BaseRenderObject
 * @sa	inheritable_enable_shared_from_this&lt;StaticMeshObject&gt;
 **************************************************************************************************/

class StaticMeshObject
	:
	public BaseRenderObject,
	public inheritable_enable_shared_from_this<StaticMeshObject>
{
public:
	StaticMeshObject() {};

	/**********************************************************************************************//**
	 * @fn	virtual~StaticMeshObject()
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	virtual~StaticMeshObject(){};

	bool Init()
	{
		return true;
	}

	bool Update();



	void Reset(){};


private:

};

