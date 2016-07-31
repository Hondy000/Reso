
#include "..\Public\CollisionManager.h"
#include "..\Cell\Public\CollisionSpaceManager.h"

bool CollisionManager::SetupCollisionSpace(const DWORD& level, const HFVECTOR3& center, const HFVECTOR3& size)
{
	m_spSpaceManager = std::shared_ptr<CollisionSpaceManager>(new CollisionSpaceManager);
	m_spSpaceManager->Setup(level, center, size);
	return true;
}

/**********************************************************************************************//**
 * @fn	void CCollisionManager::UpdateCollisionInfo()
 *
 * @brief	Updates the collision information.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 **************************************************************************************************/

void CollisionManager::UpdateCollisionInfo()
{
	for (auto it = m_collisionObjectList.begin(); it != m_collisionObjectList.end(); it++)
	{
		(*it).lock()->PreProcess();
	}

	m_spSpaceManager->Update();
	Response();
	for (auto it = m_collisionObjectList.begin(); it != m_collisionObjectList.end(); it++)
	{
		(*it).lock()->PostProcess();
	}
}

/**********************************************************************************************//**
 * @fn	bool CCollisionManager::RegisterCollisionObject(std::shared_ptr<CBaseCollisionObject>& obj)
 *
 * @brief	Registers the collision object described by obj.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param [in,out]	obj	The object.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool CollisionManager::RegisterCollisionObject(std::weak_ptr<BaseCollisionObject> obj)
{
	m_collisionObjectList.push_back(obj);
	return true;
}


/**********************************************************************************************//**
 * @fn	void CCollisionManager::EraseCollisionObject(std::shared_ptr<CBaseCollisionObject>& obj)
 *
 * @brief	Erase collision object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param [in,out]	obj	The object.
 **************************************************************************************************/

void CollisionManager::EraseCollisionObject(std::shared_ptr<BaseCollisionObject> obj)
{
	for (auto it = m_collisionObjectList.begin(); it != m_collisionObjectList.end();)
	{
		if (obj == it->lock())
		{
			it = m_collisionObjectList.erase(it);

			continue;
		}

		it++;
	}
}

/**********************************************************************************************//**
 * @fn	void CCollisionManager::Response(void)
 *
 * @brief	Responses this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 **************************************************************************************************/

void CollisionManager::Response(void)
{
	for (auto it = m_collisionObjectList.begin(); it != m_collisionObjectList.end(); it++)
	{
		(*it).lock()->Response();
	}
	for (auto it = m_collisionObjectList.begin(); it != m_collisionObjectList.end(); it++)
	{
		(*it).lock()->ClearCollisionInfoMap();
	}
}