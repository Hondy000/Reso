#pragma once
#include "BaseCollisionObject.h"
class CollisionPlanesObject
	:
	public BaseCollisionObject
{
public:
	CollisionPlanesObject()
	{
		m_type = PLANE;
	};
	virtual ~CollisionPlanesObject()
	{
		m_planeInfoArray.clear();
	};

	// �n�`�f�[�^�̖ʂ̕��������
	class PLANE_INFO
	{
	public:
		PLANE_INFO()
		{
		}
		virtual ~PLANE_INFO()
		{
		}

		HFVECTOR3 GetCenter(void)
		{
			HFVECTOR3 center = { 0,0,0 };
			center += p0 + p1 + p2;
			center /= 3;
			return 	center;
		}
		HFPLANE	plane;				//���ʂ̕�����
		HFVECTOR3	p0, p1, p2;		//���_���W
		HFVECTOR3	normal;
	};

	bool Collision(std::shared_ptr<BaseCollisionObject>);

	void AnalyzeSpaceSize(void)
	{
		HFVECTOR3 max, min;
		for (auto it = m_planeInfoArray.begin(); it != m_planeInfoArray.end(); it++)
		{
			// �ő��T��
			if (max.x < (*it)->p0.x)
			{
				max.x = (*it)->p0.x;
			}
			if (max.x < (*it)->p1.x)
			{
				max.x = (*it)->p1.x;
			}
			if (max.y < (*it)->p2.y)
			{
				max.y = (*it)->p2.y;
			}
			if (max.y < (*it)->p0.y)
			{
				max.y = (*it)->p0.y;
			}
			if (max.y < (*it)->p1.y)
			{
				max.y = (*it)->p1.y;
			}
			if (max.y < (*it)->p2.y)
			{
				max.y = (*it)->p2.y;
			}
			if (max.y < (*it)->p2.y)
			{
				max.y = (*it)->p2.y;
			}
			if (max.z < (*it)->p0.z)
			{
				max.z = (*it)->p0.z;
			}
			if (max.z < (*it)->p1.z)
			{
				max.z = (*it)->p1.z;
			}
			if (max.z < (*it)->p2.z)
			{
				max.z = (*it)->p2.z;
			}
		}
		min = max;
		for (auto it = m_planeInfoArray.begin(); it != m_planeInfoArray.end(); it++)
		{
			// �ŏ������߂�
			if (min.x > (*it)->p0.x)
			{
				min.x = (*it)->p0.x;
			}
			if (min.x > (*it)->p1.x)
			{
				min.x = (*it)->p1.x;
			}
			if (min.y > (*it)->p2.y)
			{
				min.y = (*it)->p2.y;
			}
			if (min.y > (*it)->p0.y)
			{
				min.y = (*it)->p0.y;
			}
			if (min.y > (*it)->p1.y)
			{
				min.y = (*it)->p1.y;
			}
			if (min.y > (*it)->p2.y)
			{
				min.y = (*it)->p2.y;
			}
			if (min.y > (*it)->p2.y)
			{
				min.y = (*it)->p2.y;
			}
			if (min.z > (*it)->p0.z)
			{
				min.z = (*it)->p0.z;
			}
			if (min.z > (*it)->p1.z)
			{
				min.z = (*it)->p1.z;
			}
			if (min.z > (*it)->p2.z)
			{
				min.z = (*it)->p2.z;
			}
		}
		// �T�C�Y
		m_spaceSize = max - min;
	}

	void GetSpaceSize(HFVECTOR3* center, HFVECTOR3* halfSize)
	{
		*center = GetCenter();
		*halfSize = m_spaceSize*0.5;
	}

	std::vector<std::shared_ptr<PLANE_INFO>>& GetPlaneInfoArray(void);
	int GetPlaneCount()
	{
		return m_planeInfoArray.size();
	}

protected:

	std::vector<std::shared_ptr<PLANE_INFO>>		m_planeInfoArray;
	HFVECTOR3 m_spaceSize;
};