/**********************************************************************************************//**
 * @file	Source\GameSource\Weapon\Public\IBaseBullet.h
 *
 * @brief	Declares the IBaseBullet interface.
 **************************************************************************************************/

#pragma once
#include "..\..\..\HarmonyFrameWork\Graphics\ParticleSystem\Public\BaseParticle.h"

/**********************************************************************************************//**
 * @class	IBaseBullet IBaseBullet.h Source\GameSource\Weapon\Public\IBaseBullet.h
 *
 * @brief	A base bullet.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

class IBaseBullet
	:
	public IBaseParticle 
{
public:
	IBaseBullet();
	~IBaseBullet();

private:

};  /*!< . */
