#pragma once
#include "../../../Core/Public/Common.h"

class CollisionManager;
class CCollisionSpaceCell;
class BaseCollisionObject;

class CollisionSpaceManager
{
public:
	CollisionSpaceManager() {};
	~CollisionSpaceManager() {};

	bool Setup(void);
	bool Setup(unsigned int layer, HFVECTOR3 center, HFVECTOR3 size);
	void CheckCollision(int elem, std::list<std::weak_ptr<BaseCollisionObject>>& collisionList);
	bool Update(void);

	DWORD FindMortonNumberOfPoint(const HFVECTOR3& pCenter);
	void CheckParent();
	DWORD FindSerialNumberOfBox(const HFVECTOR3& pCenter, const HFVECTOR3&pHalfSize);

	int SerialNumberToLevel(DWORD morton)
	{
		int level = 0;
		for (DWORD i = 0; i < m_maxCellOfLevel.size(); i++)
		{
			if (m_maxCellOfLevel[i] > morton)
			{
				level = (i - 1);
			}
		}
		return level;
	}
private:
	std::vector< std::shared_ptr<CCollisionSpaceCell> >m_cellArray;
	UINT m_level;
	HFVECTOR3 m_size;
	HFVECTOR3 m_center;
	std::vector<DWORD> m_maxCellOfLevel;
	DWORD  m_maxCellToatal;
	std::list<std::shared_ptr<BaseCollisionObject>> m_collisionStack;
};
