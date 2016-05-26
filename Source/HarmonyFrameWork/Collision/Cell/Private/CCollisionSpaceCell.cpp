/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Collision\CCollisionSpaceCell.cpp
 *
 * @brief	Implements the collision space cell class.
 **************************************************************************************************/


#include "..\Public\CollisionSpaceCell.h"

/**********************************************************************************************//**
  * @fn	void CCollisionSpaceCell::CheckCollision(std::list<std::shared_ptr<CBaseCollisionObject>>& collisionList)
  *
  * @brief	Check collision.
  *
  * @author	Kazuyuki Honda
  * @date	2015/11/04
  *
  * @param [in,out]	collisionList	List of collisions.
  **************************************************************************************************/

void CCollisionSpaceCell::CheckCollision(std::list<std::weak_ptr<BaseCollisionObject>>& collisionList)
{
	// 所属するオブジェクトとの衝突を検証
	for (auto it1 = m_collisionObjectList.begin(); it1 != m_collisionObjectList.end(); it1++)
	{
		auto it2 = collisionList.begin();
		for (; it2 != collisionList.end(); it2++)
		{
			if (it1->lock().get() != it2->lock().get() && it1->lock()->Collision((*it2).lock()))
			{
				//
				(*it1).lock()->GetCollisionStack().push_back(*it2);
				(*it2).lock()->GetCollisionStack().push_back(*it1);
			}
		}
	}
}