#pragma once
#include "BaseCollisionObject.h"

class CollisionOBBObject :
	public BaseCollisionObject
{
public:
	CollisionOBBObject()
	{
		m_type = OBB;
	};
	~CollisionOBBObject() {};
	bool Collision(std::shared_ptr<BaseCollisionObject>);

	// Access the Direction[3]
	const HFVECTOR3* GetDirection(void) const
	{
		return(m_direction);
	};

	const HFVECTOR3 GetDirection(int i) const
	{
		return(m_direction[i]);
	};

	void SetDirection(const HFVECTOR3* direction)
	{
		m_direction[0] = direction[0];
		m_direction[1] = direction[1];
		m_direction[2] = direction[2];
	};

	// Access the Size
	const HFVECTOR3& GetSize(void) const { return(m_size); };
	void SetSize(const HFVECTOR3& size) { m_size = size; };
	void GetSpaceSize(HFVECTOR3* pCenter, HFVECTOR3* pSize)
	{
		*pCenter = m_centerPosition;
		HFVECTOR3 size[3];	// 各方向のサイズ
		float ans[3];
		size[0] = m_size.x * m_direction[0];
		size[1] = m_size.y * m_direction[1];
		size[2] = m_size.z * m_direction[2];
		for (BYTE i = 0; i < 3; i++)
		{
			if (size[i].x > size[i].y && size[i].x > size[i].z)
			{
				ans[i] = size[i].x;
			}
			else if (size[i].y > size[i].z)
			{
				ans[i] = size[i].y;
			}
			else
			{
				ans[i] = size[i].z;
			}
		}

		*pCenter = m_centerPosition;
		*pSize = HFVECTOR3(ans[0], ans[1], ans[2]);
	};

	float GetLength(int i)
	{
		switch (i)
		{
		case 0:
			return m_size.x;
		case 1:
			return m_size.y;
		case 2:
			return m_size.z;
		}
	}

protected:
	HFVECTOR3 m_size;		// 中心から面までの距離
	HFVECTOR3 m_direction[3];	// 方向ベクトル
};
