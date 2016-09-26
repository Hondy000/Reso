#pragma once
#include "..\..\RenderObject\Public\BaseRenderMeshObject.h"
#include "..\..\..\Core\Actor\Public\ActorInterface.h"

class ShadowRenderObject
	:
	public BaseRenderMeshObject,
	public IActor
{
public:
	ShadowRenderObject() {};
	~ShadowRenderObject() {};
	bool Init();
	void Reset() {};
protected:
private:
};

