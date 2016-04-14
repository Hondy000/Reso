#pragma once
#include "BaseRenderObject.h"

class StaticMeshObject
	:
	public BaseRenderObject,
	public inheritable_enable_shared_from_this<StaticMeshObject>
{
public:
	StaticMeshObject() {};
	virtual~StaticMeshObject(){};

	BOOL Init()
	{
		return true;
	}

	BOOL Update();



	void Reset(){};


private:

};

