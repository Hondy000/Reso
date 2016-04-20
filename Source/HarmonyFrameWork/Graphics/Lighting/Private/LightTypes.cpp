/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\GraphicsObject\Basic\BaseLight.cpp
 *
 * @brief	Implements the base light class.
 **************************************************************************************************/

#include "../Public/LightTypes.h"
#include <cmath>

/**********************************************************************************************//**
 * @fn	FLOAT HFGraphics::BaseLight::GetDistance(HFVECTOR3 pos)
 *
 * @brief	Gets a distance.
 *
 * @author	Kazuyuki Honda
 *
 * @param	pos	The position.
 *
 * @return	The distance.
 **************************************************************************************************/

FLOAT HFGraphics::BaseLight::GetDistance(HFVECTOR3 pos)
{
	return INFINITY;
}

/**********************************************************************************************//**
 * @fn	FLOAT HFGraphics::DirectinalLight::GetDistance(HFVECTOR3 pos)
 *
 * @brief	Gets a distance.
 *
 * @author	Kazuyuki Honda
 *
 * @param	pos	The position.
 *
 * @return	The distance.
 **************************************************************************************************/

FLOAT HFGraphics::DirectinalLight::GetDistance(HFVECTOR3 pos)
{
	FLOAT distance = 0;

	return distance;
}

/**********************************************************************************************//**
 * @fn	FLOAT HFGraphics::PointLight::GetDistance(HFVECTOR3 pos)
 *
 * @brief	Gets a distance.
 *
 * @author	Kazuyuki Honda
 *
 * @param	pos	The position.
 *
 * @return	The distance.
 **************************************************************************************************/

FLOAT HFGraphics::PointLight::GetDistance(HFVECTOR3 pos)
{
	FLOAT distance;
	distance = HFVec3Length(HFVECTOR3(HFVECTOR3(pram.position.x, pram.position.y, pram.position.z) - pos));
	return distance;
}

/**********************************************************************************************//**
 * @fn	FLOAT HFGraphics::SpotLight::GetDistance(HFVECTOR3 pos)
 *
 * @brief	Gets a distance.
 *
 * @author	Kazuyuki Honda
 *
 * @param	pos	The position.
 *
 * @return	The distance.
 **************************************************************************************************/

FLOAT HFGraphics::SpotLight::GetDistance(HFVECTOR3 pos)
{
	FLOAT distance;
	distance = HFVec3Length(HFVECTOR3(HFVECTOR3(pram.position.x, pram.position.y, pram.position.z) - pos));
	return distance;
}
