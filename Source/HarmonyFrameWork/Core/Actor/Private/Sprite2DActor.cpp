/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Actor\Private\Sprite2DActor.cpp
 *
 * @brief	Implements the sprite 2D actor class.
 **************************************************************************************************/

#include "..\Public\Sprite2DActor.h"

/**********************************************************************************************//**
 * @fn	Sprite2DActor::Sprite2DActor()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

Sprite2DActor::Sprite2DActor()
{
}

/**********************************************************************************************//**
 * @fn	Sprite2DActor::~Sprite2DActor()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

Sprite2DActor::~Sprite2DActor()
{
}

/**********************************************************************************************//**
 * @fn	bool Sprite2DActor::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool Sprite2DActor::Init()
{
	return Sprite2DObject::Init();
}

/**********************************************************************************************//**
 * @fn	void Sprite2DActor::Reset()
 *
 * @brief	Resets this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void Sprite2DActor::Reset()
{

}

/**********************************************************************************************//**
 * @fn	bool Sprite2DActor::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool Sprite2DActor::Update()
{
	return Sprite2DObject::Update();
}
