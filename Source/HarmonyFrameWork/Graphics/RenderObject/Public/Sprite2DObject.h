#pragma once
#include "StaticMeshObject.h"
#include "../../../Core/Actor/Public/ActorInterface.h"

class Sprite2DObject
	:
	public StaticMeshObject
{
public:
	Sprite2DObject() {};
	virtual ~Sprite2DObject() {};

	BOOL Init();

	BOOL Update();


	void Reset() {};

};
