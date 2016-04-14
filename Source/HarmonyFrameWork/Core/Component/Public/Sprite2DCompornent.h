#pragma once
#include "../../../Graphics/RenderObject/Public/Sprite2DObject.h"

class Sprite2DCompornent
	:
	virtual public ICompornent,
	virtual public Sprite2DObject
{
public:
	Sprite2DCompornent();
	~Sprite2DCompornent();

	BOOL Init();
	void Reset();
	BOOL Update();

	void Destroy();

private:

};

