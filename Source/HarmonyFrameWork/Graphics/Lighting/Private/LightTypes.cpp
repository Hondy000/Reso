/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\GraphicsObject\Basic\BaseLight.cpp
 *
 * @brief	Implements the base light class.
 **************************************************************************************************/

#include "../Public/LightTypes.h"
#include <cmath>

FLOAT HFGraphics::BaseLight::GetDistance(HFVECTOR3 pos)
{
	return INFINITY;
}



FLOAT HFGraphics::DirectinalLight::GetDistance(HFVECTOR3 pos)
{
	FLOAT distance = 0;

	return distance;
}


FLOAT HFGraphics::PointLight::GetDistance(HFVECTOR3 pos)
{
	FLOAT distance;
	distance = HFVec3Length(HFVECTOR3(HFVECTOR3(pram.position.x, pram.position.y, pram.position.z) - pos));
	return distance;
}


FLOAT HFGraphics::SpotLight::GetDistance(HFVECTOR3 pos)
{
	FLOAT distance;
	distance = HFVec3Length(HFVECTOR3(HFVECTOR3(pram.position.x, pram.position.y, pram.position.z) - pos));
	return distance;
}
