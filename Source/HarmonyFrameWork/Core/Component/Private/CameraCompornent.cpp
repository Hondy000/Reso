/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Component\Private\CameraCompornent.cpp
 *
 * @brief	Implements the camera compornent class.
 **************************************************************************************************/

#include "../Public/CameraCompornent.h"

/**********************************************************************************************//**
 * @fn	CameraCompornent::CameraCompornent()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

CameraCompornent::CameraCompornent()
{

}

/**********************************************************************************************//**
 * @fn	CameraCompornent::~CameraCompornent()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

CameraCompornent::~CameraCompornent()
{

}

/**********************************************************************************************//**
 * @fn	bool CameraCompornent::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool CameraCompornent::Update()
{			  
	return BaseCamera::Update();
}

