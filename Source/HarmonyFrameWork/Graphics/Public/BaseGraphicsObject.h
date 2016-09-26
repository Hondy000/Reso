#pragma once
#include "..\..\Core\Public\IBaseObject.h"

class BaseGraphicsCommand;

class BaseGraphicsObject
	:
	public virtual IBaseObject
{
public:
	BaseGraphicsObject();
	virtual ~BaseGraphicsObject();

	std::vector<std::shared_ptr<BaseGraphicsCommand>>& GetCommmandArray() 
	{
		return m_commmandArray;
	}

	void SetCommmandArray(std::vector<std::shared_ptr<BaseGraphicsCommand>>& _val)
	{
		m_commmandArray = _val;
	}

protected:
	std::vector<std::shared_ptr<BaseGraphicsCommand>> m_commmandArray;

private:
};
