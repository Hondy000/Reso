/**=================================================================================================
 * @file Source\HarmonyFrameWork\Graphics\ParticleSystem\Public\BaseParticle.h
 *
 * Declares the base particle class.
 *===============================================================================================**/

#pragma once
#include "../../RenderObject/Public/BaseRenderMeshObject.h"

/**=================================================================================================
 * @class IBaseParticle BaseParticle.h
 * Source\HarmonyFrameWork\Graphics\ParticleSystem\Public\BaseParticle.h
 *
 * @brief A base particle.
 *
 * @author Kazuyuki
 *
 * @sa IBaseTask
 *===============================================================================================**/

class IBaseParticle
	:
	public IBaseTask,
	public TransformHolder
{
public:
	IBaseParticle();

	virtual~IBaseParticle();

	/**=================================================================================================
	 * @fn bool Init();
	 *
	 * @brief Initialises this object.
	 *
	 * @author Kazuyuki
	 *
	 * @return true if it succeeds, false if it fails.
	 *===============================================================================================**/

	bool Init();

	/**=================================================================================================
	 * @fn bool Update() ;
	 *
	 * @brief Updates this object.
	 *
	 * @author Kazuyuki
	 *
	 * @return true if it succeeds, false if it fails.
	 *===============================================================================================**/

	bool Update();

	/**=================================================================================================
	 * @fn void Reset();
	 *
	 * @brief Resets this object.
	 *
	 * @author Kazuyuki
	 *===============================================================================================**/

	void Reset();

	float GetVelocity() const
	{
		return m_velocity;
	}
	void SetVelocity(float val)
	{
		m_velocity = val;
	}
	HFVECTOR3 GetDirection() const
	{
		return m_direction;
	}
	void SetDirection(HFVECTOR3 val)
	{
		m_direction = val;
	}

	float GetLife() const
	{
		return m_life;
	}
	void SetLife(float val)
	{
		m_life = val;
	}

	HFColor GetColor() const
	{
		return m_color;
	}

	void SetColor(HFColor _val)
	{
		m_color = _val;
	}

private:
	float m_velocity;
	HFVECTOR3 m_direction;
	float m_life;
	HFColor m_color;
};
