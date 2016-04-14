#pragma once
#include "../../../../Core/Public/Common.h"
#include "../../../RenderObject/Public/ScreenRenderObject.h"

class DeferredRenderingManager
	:
	public IActor
{
public:
	DeferredRenderingManager();
	~DeferredRenderingManager();

	BOOL Init();
	void Reset();
	BOOL Update();

private:
};
