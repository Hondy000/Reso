#pragma once
#include "BaseCollisionObject.h"
#include "..\..\..\Core\Component\Public\CompornentInterface.h"

class CollisionSphereObject
	:
	public BaseCollisionObject
{
public:
	CollisionSphereObject()
	{
		m_type = SPHERE;
		m_size = 10;
	}

	virtual~CollisionSphereObject()
	{
	}
	class SphereCollisionInfoOption
		:
		public BaseCollisionInfoOption
	{
		HFVECTOR3 m_positionOffset;
		float m_sizeOffset;
	};

	bool Collision(std::shared_ptr<BaseCollisionObject> object);

	void SetSize(float _size)
	{
		m_size = _size;
	}

	const float GetSize(void) const
	{
		return m_size;
	}

	virtual void GetSpaceSize(HFVECTOR3* center, HFVECTOR3* halfSize)
	{
		*center = GetCenter();
		*halfSize = HFVECTOR3(m_size*0.5, m_size*0.5, m_size*0.5);
	};

protected:
	float m_size;
};

class CollisionSphereComponent
	:
	virtual public ICompornent,
	virtual public CollisionSphereObject
{
public:
	CollisionSphereComponent() {};
	~CollisionSphereComponent() {};
	bool Init() { return true; }
};