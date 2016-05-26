
#include "..\Public\CollisionSphereObject.h"
#include "..\Public\CollisionPlanesObject.h"
#include "..\..\Public\CollisionAPI.h"

/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Collision\CCollisionSphereObject.cpp
 *
 * @brief	Implements the collision sphere object class.
 **************************************************************************************************/

bool CollisionSphereObject::Collision(std::shared_ptr<BaseCollisionObject> collisionObject)
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
	//				std::shared_ptr<CollisionPlanesObject> planes = std::static_pointer_cast<CollisionPlanesObject>(collisionObject);
	//				HFVECTOR3 point;
	//				float time;
	//				HFVECTOR3 pushBackDistance;
	//				if (isCollisionPlanesAndSphere(planes.get(), this, &point, &pushBackDistance, &time))
	//				{
	//					RegisterCollisionInfo(planes, point, pushBackDistance, time);
	//					return true;
	//				}
	//				break;
	//			}
	//			break;
	//			case OBB:
	//			{
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
	//		std::shared_ptr<CollisionPlanesObject> planes = std::static_pointer_cast<CollisionPlanesObject>(collisionObject);
	//		HFVECTOR3 point;
	//		float time;
	//		HFVECTOR3 pushBackDistance;
	//		if (isCollisionPlanesAndSphere(planes.get(), this, &point, &pushBackDistance, &time))
	//		{
	//			RegisterCollisionInfo(planes, point, pushBackDistance, time);
	//			return true;
	//		}
	//		break;
	//	}
	//	case OBB:
	//	{
	//		std::shared_ptr<CollisionOBBObject> spOBB = std::static_pointer_cast<CollisionOBBObject>(collisionObject);
	//		if (0)
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