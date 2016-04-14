#pragma once
#include "../../Task/Public/TaskInterface.h"
#include "../../State/Public/StateHolder.h"

class IBaseLevel
	:
	virtual public IBaseTask,
	public IStateHolder,
	public inheritable_enable_shared_from_this<IBaseLevel>
{
protected:
	IBaseLevel();
public:
	virtual ~IBaseLevel();
	BOOL Init();
	virtual BOOL Update() = 0;
	BOOL IsChangeLevel();

	const std::string& GetChangeLevelType(void);

private:
	void SetChangeLevelType(const std::string& changeLevelType);
};
