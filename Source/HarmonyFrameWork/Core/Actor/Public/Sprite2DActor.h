#pragma once
#include "ActorInterface.h"
#include "../../../Graphics/RenderObject/Public/Sprite2DObject.h"

class Sprite2DActor
	:
	public Sprite2DObject,
	public IActor
{
public:
	Sprite2DActor();
	~Sprite2DActor();
	BOOL Init();
	void Reset();

	
	BOOL Update();

private:

};

