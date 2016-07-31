#pragma once
#include "../../Core/Public/Common.h"
#include "CCollisionObjectFactory.h"

#define sCOLLISION_MANAGER (CollisionManager::GetInstance())

class CollisionSpaceManager;

class CollisionManager
{
public:
	~CollisionManager()
	{
		m_collisionObjectList.clear();
	};

	// Access the CollisionObjectList
	const std::list<std::weak_ptr<BaseCollisionObject>>& GetCollisionObjectList(void) const
	{
		return(m_collisionObjectList);
	};

	static CollisionManager* GetInstance(void)
	{
		static CollisionManager singleton;
		return &singleton;
	}

	bool SetupCollisionSpace(const DWORD& level, const HFVECTOR3& center, const HFVECTOR3& size);

	void UpdateCollisionInfo();

	bool RegisterCollisionObject(std::weak_ptr<BaseCollisionObject>);
	void EraseCollisionObject(std::shared_ptr<BaseCollisionObject>);
	void Response();
private:
	CollisionManager() {};
	std::list<std::weak_ptr<BaseCollisionObject>> m_collisionObjectList;
	std::shared_ptr<CollisionSpaceManager> m_spSpaceManager;
	std::shared_ptr<CCollisionObjectFactory> m_spFactory;
};


