/**=================================================================================================
 * @file Source\HarmonyFrameWork\Graphics\ParticleSystem\Public\BaseParticle.h
 *
 * Declares the base particle class.
 *===============================================================================================**/

#pragma once
#include "../../RenderObject/Public/BaseRenderObject.h"

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
	public IBaseTask
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


	Transform GetTransform() const
	{
		return m_transform;
	}

	void SetTransform(Transform _val)
	{
		m_transform = _val;
	}
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

	UINT GetLife() const
	{
		return m_life;
	}
	void SetLife(UINT val)
	{
		m_life = val;
	}
private:
	Transform m_transform;
	float m_velocity;
	HFVECTOR3 m_direction;
	UINT m_life;
};
