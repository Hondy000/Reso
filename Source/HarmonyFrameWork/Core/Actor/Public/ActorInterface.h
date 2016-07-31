#pragma once
#include "../../Task/Public/TaskInterface.h"
#include "../../State/Public/StateHolder.h"
#include "../../Component/Public/CompornentInterface.h"
#include "../../../Math/Public/Transform.h"

class IActor
	:
	virtual public IBaseTask,
	public IStateHolder,
	public inheritable_enable_shared_from_this<IActor>
{
protected:		
	IActor();
public:
	virtual ~IActor();		

	bool Init();
	bool RegisterCompornent(const std::string& compornentName, std::shared_ptr<ICompornent> compornent);
	void SortTaskByPriority();
	bool UpdateAllTask();
	// Access the Transform
	const std::shared_ptr< Transform>& GetTransform(void) const
	{
		return(m_transform);
	};
	void SetTransform(const std::shared_ptr< Transform>& transform)	{ m_transform = transform;	};

	// Access the PreviousTransform
	const std::shared_ptr<Transform>& GetPreviousTransform(void) const { return(m_previousTransform); };
	void SetPreviousTransform(const std::shared_ptr<Transform>& previousTransform) { m_previousTransform = previousTransform; };

	std::shared_ptr<ICompornent> GetCompornent(const std::string& name);


protected:
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<Transform> m_previousTransform;
	std::unordered_map<std::string, std::shared_ptr<ICompornent>> m_compornentMap;
	std::list<std::shared_ptr<IBaseTask>> m_taskList;

};
