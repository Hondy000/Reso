#pragma once
#include "Common.h"
#include "VariableInterface.h"

#ifdef X86
typedef uint32_t GLOBAL_ID;	// �I�u�W�F�N�gID
#endif
#ifdef X64
typedef uint64_t GLOBAL_ID;	// �I�u�W�F�N�gID
#endif
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
	virtual bool Init();


	// Access the GlobalID
	const GLOBAL_ID& GetGlobalID(void) const	{ return(m_globalID);		};
	void SetGlobalID(const GLOBAL_ID& globalID)	{ m_globalID = globalID;	};



protected:
	GLOBAL_ID m_globalID;	// 1�̂̃I�u�W�F�N�g�Ƃ��Ă�ID
};
