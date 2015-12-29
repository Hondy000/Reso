#pragma once
#include "Common.h"

typedef uint32_t GLOBAL_ID;	// �I�u�W�F�N�gID
class BaseObject
	
{
public:


	BaseObject()
	{
		m_globalID = std::hash<BaseObject*>()(this);
	}


	virtual ~BaseObject()
	{
	}
	virtual bool Init();


	// Access the GlobalID
	const GLOBAL_ID& GetGlobalID(void) const	{ return(m_globalID);		};
	void SetGlobalID(const GLOBAL_ID& globalID)	{ m_globalID = globalID;	};

protected:
	GLOBAL_ID m_globalID;	// 1�̂̃I�u�W�F�N�g�Ƃ��Ă�ID
};
