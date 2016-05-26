/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Collision\CBaseCollisionObject.cpp
 *
 * @brief	Implements the base collision object class.
 **************************************************************************************************/


/**********************************************************************************************//**
  * @fn	CBaseCollisionObject::CBaseCollisionObject()
  *
  * @brief	Default constructor.
  *
  * @author	Kazuyuki Honda
  * @date	2015/08/02
  **************************************************************************************************/

#include "..\Public\BaseCollisionObject.h"
#include "..\..\..\Core\Actor\Public\ActorInterface.h"

BaseCollisionObject::BaseCollisionObject()
{
	m_type = OTHER;
}

/**********************************************************************************************//**
 * @fn	CBaseCollisionObject::~CBaseCollisionObject()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 **************************************************************************************************/

BaseCollisionObject::~BaseCollisionObject()
{
}

/**********************************************************************************************//**
 * @fn	HFVECTOR3 CBaseCollisionObject::GetCenter(void)
 *
 * @brief	Collisions the given parameter 1.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @return	true if it succeeds, false if it fails.
 *
 * ### param	parameter1	The first parameter.
 **************************************************************************************************/

const HFVECTOR3 BaseCollisionObject::UpdateCenterPosition(void)const
{
	HFVECTOR3 center;
	HFMATRIX matAns, matHolder;
	HFMatrixTranslation(&matAns, m_originCenterPosition.x,
		m_originCenterPosition.y,
		m_originCenterPosition.z);
//	matHolder = m_wpHolder.lock()->GetVariable<Transform>("Tra")->m_value->GetWorldTransform();
	matAns *= matHolder;
	center.x = matAns._41;
	center.y = matAns._42;
	center.z = matAns._43;
	//return m_wpHolder.lock()->GetComponent<Transform>()->GetPosition();
	return HFVECTOR3(0, 0, 0);
}


/**********************************************************************************************//**
 * @fn	void CBaseCollisionObject::Response()
 *
 * @brief	Responses this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 **************************************************************************************************/

void BaseCollisionObject::Response()
{
	// TRIGGERとHOLDのチェック
	for (auto it = m_collisionStack.begin(); it != m_collisionStack.end(); it++)
	{
		COLLISION_STATE state = CheckCollisionState((*it).lock());
		if (TRIGGER == state)
		{
			//m_wpHolder.lock()->ResponseTrigerCollision((*it).lock()->GetHolder(), shared_from_this(), (*it).lock());
		}

		if (HOLD == state || TRIGGER == state)
		{
			//m_wpHolder.lock()->ResponseHoldCollision((*it).lock()->GetHolder(), shared_from_this(), (*it).lock());
		}
	}

	// RELEASEのチェック
	for (auto it = m_oldCollisionStack.begin(); it != m_oldCollisionStack.end(); it++)
	{
		COLLISION_STATE state = CheckCollisionState((*it).lock());
		if (RELEASE == state)
		{
			//m_wpHolder.lock()->ResponseTrigerCollision((*it).lock()->GetHolder(), shared_from_this(), (*it).lock());
		}
	}
}

/**********************************************************************************************//**
 * @fn	CBaseCollisionObject::COLLISION_STATE CBaseCollisionObject::CheckCollisionState(std::shared_ptr<CBaseCollisionObject> sp)
 *
 * @brief	Check collision state.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	sp	The sp.
 *
 * @return	A CBaseCollisionObject::COLLISION_STATE.
 **************************************************************************************************/

BaseCollisionObject::COLLISION_STATE BaseCollisionObject::CheckCollisionState(std::shared_ptr<BaseCollisionObject> sp)
{
	bool lastest = false, old = false;
	for (auto it = m_collisionStack.begin(); it != m_collisionStack.end(); it++)
	{
		if ((*it).lock() == sp)
		{
			lastest = true;
		}
	}

	for (auto it = m_oldCollisionStack.begin(); it != m_oldCollisionStack.end(); it++)
	{
		if ((*it).lock() == sp)
		{
			old = true;
		}
	}
	if (lastest & !old)
	{
		return TRIGGER;
	}

	if (lastest & old)
	{
		return HOLD;
	}

	if (!lastest & old)
	{
		return HOLD;
	}
	return NONE;
}

bool BaseCollisionObject::FindCollisionInfo(std::shared_ptr<BaseCollisionObject> partnerCollisionObject, BaseCollisionObject::COLLISION_INFO& info)const
{
	auto it = m_collisionInfoMap.find(partnerCollisionObject.get());
	if (it != m_collisionInfoMap.end())
	{
		info = it->second;
		return true;
	}
	else
	{
		return false;
	}
}

bool BaseCollisionObject::Update()
{
	m_prePosition = m_centerPosition;
	m_centerPosition = UpdateCenterPosition();
	return true;
}

void BaseCollisionObject::ClearCollisionInfoMap()
{
	m_collisionInfoMap.clear();
}