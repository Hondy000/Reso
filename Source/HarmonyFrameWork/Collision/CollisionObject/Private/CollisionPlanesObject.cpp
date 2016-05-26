/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Collision\CCollisionPlanesObject.cpp
 *
 * @brief	Implements the collision planes object class.
 **************************************************************************************************/

#include "..\Public\CollisionPlanesObject.h"
#include "..\Public\CollisionSphereObject.h"
#include "..\..\Public\CollisionAPI.h"

/**********************************************************************************************//**
  * @fn	std::vector<std::shared_ptr<CCollisionPlanesObject::PLANE_INFO>>& CCollisionPlanesObject::GetPlaneInfoArray()
  *
  * @brief	Gets plane information array.
  *
  * @author	Kazuyuki Honda
  * @date	2015/11/04
  *
  * @return	The plane information array.
  **************************************************************************************************/

std::vector<std::shared_ptr<CollisionPlanesObject::PLANE_INFO>>& CollisionPlanesObject::GetPlaneInfoArray()
{
	return m_planeInfoArray;
}

/**********************************************************************************************//**
 * @fn	bool CCollisionPlanesObject::Collision(std::shared_ptr<CBaseCollisionObject> collisionObject)
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

bool CollisionPlanesObject::Collision(std::shared_ptr<BaseCollisionObject> collisionObject)
{
	//if (m_isEnableCollisionIDList) {
	//	for (auto it = m_enableCollisionIDList.begin(); it != m_enableCollisionIDList.end(); it++)
	//	{
	//		if (collisionObject->GetId() == *it)
	//		{
	//			switch (collisionObject->GetType())
	//			{
	//			case RAY:
	//			{
	//			}
	//			break;
	//			case SPHERE:
	//			{
	//				std::shared_ptr<CollisionSphereObject> sphere = std::static_pointer_cast<CollisionSphereObject>(collisionObject);
	//				HFVECTOR3 point;
	//				float time;
	//				HFVECTOR3 pushBackDistance;
	//				if (isCollisionPlanesAndSphere(this, sphere.get(), &point, &pushBackDistance, &time))
	//				{
	//					RegisterCollisionInfo(sphere, point, pushBackDistance, time);
	//					sphere->RegisterCollisionInfo(shared_from_this(), point, pushBackDistance, time);
	//					return true;
	//				}
	//			}
	//			break;
	//			case OBB:
	//			{
	//				std::shared_ptr<CollisionOBBObject> spOBB = std::static_pointer_cast<CollisionOBBObject>(collisionObject);
	//				if (isCollisionOfPlanesAndOBB(this, spOBB.get()))
	//				{
	//					return true;
	//				}
	//				return false;
	//			}
	//			break;
	//			case PLANE:
	//				return false;
	//				break;
	//			default:
	//				return false;
	//				break;
	//			}
	//		}
	//	}
	//}
	//else
	//{
	//	switch (collisionObject->GetType())
	//	{
	//	case RAY:
	//	{
	//	}
	//	break;
	//	case SPHERE:
	//	{
	//		std::shared_ptr<CollisionSphereObject> sphere = std::static_pointer_cast<CollisionSphereObject>(collisionObject);
	//		HFVECTOR3 point;
	//		float time;
	//		HFVECTOR3 pushBackDistance;
	//		if (isCollisionPlanesAndSphere(this, sphere.get(), &point, &pushBackDistance, &time))
	//		{
	//			RegisterCollisionInfo(sphere, point, pushBackDistance, time);
	//			sphere->RegisterCollisionInfo(shared_from_this(), point, pushBackDistance, time);
	//			return true;
	//		}
	//		break;
	//	}
	//	case OBB:
	//	{
	//		std::shared_ptr<CollisionOBBObject> spOBB = std::static_pointer_cast<CollisionOBBObject>(collisionObject);
	//		if (isCollisionOfPlanesAndOBB(this, spOBB.get()))
	//		{
	//			return true;
	//		}
	//	}
	//	break;
	//	case PLANE:
	//		return false;
	//		break;
	//	default:
	//		return false;
	//		break;
	//	}
	//}
	return false;
}