#pragma once
#include "..\..\RenderObject\Public\BaseRenderObject.h"
#include "..\..\..\Core\Actor\Public\ActorInterface.h"

class ShadowRenderObject
	:
	public BaseRenderObject,
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

