/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Collision\COBBCollisionObject.cpp
 *
 * @brief	Implements the cobb collision object class.
 **************************************************************************************************/

#include "../Public/OBBCollisionObject.h"
#include "../../Public/CollisionAPI.h"

 /**********************************************************************************************//**
  * @fn	bool CollisionOBBObject::Collision(std::shared_ptr<CBaseCollisionObject> collisionObject)
  *
  * @brief	Collisions the given collision object.
  *
  * @author	Kazuyuki Honda
  * @date	2015/11/04
  *
  * @param	collisionObject	The collision object.
  *
  * @return	true if it succeeds, false if it fails.
  **************************************************************************************************/

bool CollisionOBBObject::Collision(std::shared_ptr<BaseCollisionObject> collisionObject)
{
	//for (auto it = m_enableCollisionIDList.begin(); it != m_enableCollisionIDList.end(); it++)
	//{
	//	if (collisionObject->GetId() == *it)
	//	{
	//		switch (collisionObject->GetType())
	//		{
	//		case RAY:
	//		{
	//			std::shared_ptr<CollisionOBBObject> spOBB = std::static_pointer_cast<CollisionOBBObject>(collisionObject);
	//			if (isCollisionOfOBBandOBB(this, spOBB.get()))
	//			{
	//				return true;
	//			}
	//		}
	//		break;
	//		case SPHERE:
	//			return true;
	//			break;
	//		case OBB:
	//			return true;
	//			break;
	//		case PLANE:
	//			return true;
	//			break;
	//		default:
	//			return true;
	//			break;
	//		}
	//	}
	//}
	return false;
}