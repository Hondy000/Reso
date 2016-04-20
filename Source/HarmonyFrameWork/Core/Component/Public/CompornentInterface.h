#pragma once
#include "..\..\Task\Public\TaskInterface.h"
#include "../../../Math/Public/Transform.h"

class IActor;
class ICompornent 
	:
	virtual public IBaseTask
{
public:
	ICompornent()
	{

		m_transform = std::make_shared<Transform>();
		RegisterVariable("m_transform", m_transform);
	};
	virtual ~ICompornent() {};
	virtual void Destroy() = 0;

	void SyncPositionWithParent();
	void SyncRotaionWithParent();
	void SyncScaleWithParent();

	// Access the ParentActorGlobalID
	const GLOBAL_ID& GetParentActorGlobalID(void) const					{ return(m_parentActorGlobalID);				};
	void SetParentActorGlobalID(const GLOBAL_ID& parentActorGlobalID)	{ m_parentActorGlobalID = parentActorGlobalID;	};

	// Access the ParentActor
	const std::weak_ptr<IActor>& GetParentActor(void) const { return(m_parentActor); };
	void SetParentActor(const std::weak_ptr<IActor>& parentActor) { m_parentActor = parentActor; };

	// Access the Transform
	const std::shared_ptr<Transform>& GetTransform(void) const		{ return(m_transform);		};
	void SetTransform(const std::shared_ptr<Transform>& transform)	{ m_transform = transform;	};

	// Access the IsSyncPositionWithParent
	bool GetIsSyncPositionWithParent(void) const					{ return(m_isSyncPositionWithParent);						};
	void SetIsSyncPositionWithParent(bool isSyncPositionWithParent)	{ m_isSyncPositionWithParent = isSyncPositionWithParent;	};

	// Access the IsSyncRotationWithParent
	bool GetIsSyncRotationWithParent(void) const					{ return(m_isSyncRotationWithParent);						};
	void SetIsSyncRotationWithParent(bool isSyncRotationWithParent)	{ m_isSyncRotationWithParent = isSyncRotationWithParent;	};

	// Access the IsSyncScaleWithParent
	bool GetIsSyncScaleWithParent(void) const					{ return(m_isSyncScaleWithParent);					};
	void SetIsSyncScaleWithParent(bool isSyncScaleWithParent)	{ m_isSyncScaleWithParent = isSyncScaleWithParent;	};

protected:
	GLOBAL_ID m_parentActorGlobalID;
	std::weak_ptr<IActor> m_parentActor;
	std::shared_ptr<Transform> m_transform;
	bool m_isSyncPositionWithParent;
	bool m_isSyncRotationWithParent;
	bool m_isSyncScaleWithParent;
};
