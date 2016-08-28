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


HFVECTOR3 HFGraphics::DirectinalLight::GetPosition()
{
	return pram.position;
}

HFVECTOR4 HFGraphics::DirectinalLight::GetColor()
{
	return pram.color;
}


HFVECTOR4 HFGraphics::DirectinalLight::GetDirection()
{
	return pram.direction;
}

void HFGraphics::DirectinalLight::SetPosition(HFVECTOR3 _position)
{
	pram.position = _position;
}


void HFGraphics::DirectinalLight::SetColor(HFVECTOR4 _color)
{
	pram.color = _color;
}

void HFGraphics::DirectinalLight::SetDirection(HFVECTOR4 _direction)
{
	pram.direction = _direction;
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
