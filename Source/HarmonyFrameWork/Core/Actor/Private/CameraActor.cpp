/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Actor\Private\CameraActor.cpp
 *
 * @brief	Implements the camera actor class.
 **************************************************************************************************/

#include "..\Public\CameraActor.h"

/**********************************************************************************************//**
 * @fn	bool CameraActor::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool CameraActor::Init()
{
	return true;
}

/**********************************************************************************************//**
 * @fn	bool CameraActor::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool CameraActor::Update()
{
	BaseCamera::Update();
	return true;
}

