#pragma once
#include "Common.h"
#include "VariableInterface.h"

typedef uint32_t GLOBAL_ID;	// オブジェクトID
class IBaseObject
	
{
public:


	IBaseObject()
	{
		m_globalID = std::hash<IBaseObject*>()(this);
	}


	virtual ~IBaseObject()
	{
	}
	virtual BOOL Init();


	// Access the GlobalID
	const GLOBAL_ID& GetGlobalID(void) const	{ return(m_globalID);		};
	void SetGlobalID(const GLOBAL_ID& globalID)	{ m_globalID = globalID;	};



protected:
	GLOBAL_ID m_globalID;	// 1個体のオブジェクトとしてのID
};
