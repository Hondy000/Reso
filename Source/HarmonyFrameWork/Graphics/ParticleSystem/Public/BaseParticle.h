/**=================================================================================================
 * @file Source\HarmonyFrameWork\Graphics\ParticleSystem\Public\BaseParticle.h
 *
 * Declares the base particle class.
 *===============================================================================================**/

#pragma once
#include "../../RenderObject/Public/BaseRenderObject.h"

/**=================================================================================================
 * A base particle.
 *
 * @author Kazuyuki
 *===============================================================================================**/

class IBaseParticle
	:
	public IBaseTask
{
public:
	IBaseParticle()
	{
		Init();
	};

	virtual~IBaseParticle()
	{
	};

private:

};
