/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Collision\CBaseCollisionObject.h
 *
 * @brief	Declares the base collision object class.
 **************************************************************************************************/

#pragma once
#include "../../../Core/Public/Common.h"
#include "../../Cell/Public/CollisionSpaceCell.h"
#include "..\..\..\Core\Public\IBaseObject.h"


class CollisionSpaceCell;

/**********************************************************************************************//**
 * @class	CHFObject
 *
 * @brief	A chf object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

class IActor;

/**********************************************************************************************//**
 * @class	CBaseCollisionObject
 *
 * @brief	A base collision object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

class BaseCollisionObject
	:
	public IBaseObject,
	public std::enable_shared_from_this<BaseCollisionObject>

	///< .
{
public:
	BaseCollisionObject();
	virtual ~BaseCollisionObject();

	/**********************************************************************************************//**
	 * @enum	COLLISION_TYPE
	 *
	 * @brief	collisionType.
	 **************************************************************************************************/

	enum COLLISION_TYPE
	{
		///< An enum constant representing the other option
		OTHER,
		///< An enum constant representing the ray option
		RAY,
		///< An enum constant representing the sphere option
		SPHERE,
		///< An enum constant representing the obb option
		OBB,
		///< An enum constant representing the plane option
		PLANE,
		///< An enum constant representing the large plane option
		LARGE_PLANE
	};

	/**********************************************************************************************//**
	 * @enum	COLLISION_STATE
	 *
	 * @brief	Values that represent collision states.
	 **************************************************************************************************/

	enum COLLISION_STATE // 衝突状態
	{
		///< An enum constant representing the none option
		NONE,
		///< An enum constant representing the trigger option
		TRIGGER,
		///< An enum constant representing the hold option
		HOLD,
		///< An enum constant representing the release option
		RELEASE
	};

	/**********************************************************************************************//**
	 * @typedef	struct COLLISION_RAY_INFO
	 *
	 * @brief	Ray情報 色々必要になるのでここに定義.
	 **************************************************************************************************/

	typedef struct COLLISION_RAY_INFO
	{
		/**********************************************************************************************//**
		 * @brief	The start point.
		 *
		 * ### summary	@brief	The start point.
		 **************************************************************************************************/

		HFVECTOR3 startPoint;

		/**********************************************************************************************//**
		 * @brief	The direction.
		 *
		 * ### summary	@brief	The direction.
		 **************************************************************************************************/

		HFVECTOR3 direction;
	}CollisionRayInfo, RayInfo;

	/**********************************************************************************************//**
	 * @typedef	struct COLLISION_INFO
	 *
	 * @brief	Defines an alias representing information describing the collision.
	 **************************************************************************************************/

	typedef struct COLLISION_INFO
	{
		// 接触地点
		HFVECTOR3 collisionPoint;
		HFVECTOR3 pushBackDistance;
		// 衝突時間
		float collisionTime;
	}CollisionInfo;

	class BaseCollisionInfoOption
	{
	};

	class RayCollisionInfoOption
		:
		public BaseCollisionInfoOption
	{
		HFVECTOR3 m_positionOffset;
		HFVECTOR3 m_direction;
	};
	/**********************************************************************************************//**
	 * @typedef	std::string CollisionID
	 *
	 * @brief	Defines an alias representing identifier for the collision.
	 **************************************************************************************************/

	typedef std::string CollisionID;

	void SetHolder(std::shared_ptr<IActor> holder)
	{
		m_wpHolder = holder;
	}

	void SetEnableCollisionIDList(std::list<std::string>& enableCollisionIDList)
	{
		m_enableCollisionIDList = enableCollisionIDList;
	};


	void SetCollisionStack(const std::list<std::weak_ptr<BaseCollisionObject>>& collisionStack)
	{
		m_collisionStack = collisionStack;
	};
	void SetId(const std::string& id)
	{
		m_id = id;
	};
	void SetIsPhysical(bool _isPhysical)
	{
		m_isPhysical = _isPhysical;
	};

	void SetIsEnableCollisionIDList(bool _isEnable)
	{
		m_isEnableCollisionIDList = _isEnable;
	};

	void SetBaseCenter(const HFVECTOR3& center)
	{
		m_originCenterPosition = center;
	};

	void SetType(const COLLISION_TYPE& type)
	{
		m_type = type;
	};

	virtual void GetSpaceSize(HFVECTOR3* center, HFVECTOR3* halfSize)
	{

		if (center != nullptr && halfSize != nullptr)
		{
			*center = m_originCenterPosition;
			*halfSize = HFVECTOR3(0, 0, 0);
		}
	};

	// Access the WpHolder
	const std::weak_ptr<IActor>& GetWpHolder(void) const
	{
		return(m_wpHolder);
	};

	// Access the CollisionStack
	std::list<std::weak_ptr<BaseCollisionObject>>& GetCollisionStack(void)
	{
		return(m_collisionStack);
	};

	std::list<std::weak_ptr<BaseCollisionObject>>& GetOldCollisionStack(void)
	{
		return(m_oldCollisionStack);
	};

	bool RegisterCollisionInfo(
		std::shared_ptr<BaseCollisionObject> collisionObject,
		HFVECTOR3 collisionPoint,
		HFVECTOR3 pushBackDistance,
		float collisionTime
		)
	{
		CollisionInfo info;
		// 接触地点
		info.collisionPoint = collisionPoint;

		info.pushBackDistance = pushBackDistance;

		// 衝突時間
		info.collisionTime = collisionTime;

		auto it = m_collisionInfoMap.begin();
		m_collisionInfoMap.find(collisionObject.get());
		// 存在しない
		if (it == m_collisionInfoMap.end())
		{
			std::pair<const BaseCollisionObject*, COLLISION_INFO>pair;
			pair.first = collisionObject.get();
			pair.second = info;
			m_collisionInfoMap.insert(pair);
			return true;
		}
		else
		{
			return false;
		}
	}

	// Access the Id
	const std::string& GetId(void) const
	{
		return(m_id);
	};

	// Access the IsPhysical
	bool GetIsPhysical(void) const
	{
		return(m_isPhysical);
	};

	// Access the IsEnable
	bool GetIsEnableCollisionIDList(void) const
	{
		return(m_isEnableCollisionIDList);
	};

	// Access the EnableCollisionIDList
	std::list<std::string>& GetEnableCollisionIDList(void)
	{
		return(m_enableCollisionIDList);
	};

	// Access the Center
	virtual const HFVECTOR3& GetBaseCenter(void) const
	{
		return(m_originCenterPosition);
	};

	// Access the Type
	const COLLISION_TYPE& GetType(void) const
	{
		return(m_type);
	};

	std::weak_ptr<IActor> GetHolder()
	{
		return m_wpHolder;
	}

	const HFVECTOR3 UpdateCenterPosition(void)const;

	const HFVECTOR3 GetCenter()const
	{
		return m_centerPosition;
	}
	const HFVECTOR3 GetOldPosition()const
	{
		return m_prePosition;
	}

	virtual bool Collision(std::shared_ptr<BaseCollisionObject>) 
	{

		return false;
	};

	virtual void Response(void);

	void PreProcess(void)
	{
		// 古いスタックの削除
		m_oldCollisionStack.clear();

		// 前フレームのスタックを入れ替え
		m_oldCollisionStack = m_collisionStack;
		m_collisionStack.clear();
		Update();
	}

	void PostProcess(void)
	{
		// 位置更新
		m_centerPosition = UpdateCenterPosition();
	}

	COLLISION_STATE BaseCollisionObject::CheckCollisionState(std::shared_ptr<BaseCollisionObject>);

	bool FindCollisionInfo(std::shared_ptr<BaseCollisionObject> partnerCollisionObject, BaseCollisionObject::COLLISION_INFO& info)const;

	bool Update();
	void ClearCollisionInfoMap();



protected:

	/** @brief	The wp holder. */

	std::weak_ptr<IActor>	m_wpHolder;

	/** @brief	The center. */

	// 生成時の中心位置
	HFVECTOR3 m_originCenterPosition;
	HFVECTOR3 m_centerPosition;
	HFVECTOR3 m_prePosition;

	/** @brief	Stack of collisions. */

	std::list<std::weak_ptr<BaseCollisionObject>> m_collisionStack;

	/** @brief	Stack of old collisions. */
	std::list<std::weak_ptr<BaseCollisionObject>> m_oldCollisionStack;

	// 衝突情報マップ
	std::map<const BaseCollisionObject*, CollisionInfo> m_collisionInfoMap;

	/** @brief	The identifier. */

	CollisionID m_id;

	/** @brief	The type. */

	COLLISION_TYPE m_type;

	/** @brief	true if this object is physical. */

	bool m_isPhysical;

	/** @brief	true if this object is enable collision identifier std::list. */

	bool m_isEnableCollisionIDList;

	/** @brief	The mass. */
	float m_mass;

	/** @brief	衝突判定を取るIDリスト. */
	std::list<CollisionID> m_enableCollisionIDList;
	/** @brief	当たったら押し出されるIDリスト. */
	std::list<CollisionID> m_pushedOutCollisionIDList;
};
