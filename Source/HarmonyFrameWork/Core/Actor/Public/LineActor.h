#pragma once
#include "ActorInterface.h"
#include "..\..\..\Graphics\RenderObject\Public\LineObject.h"

class LineActor
	:
	public IActor ,
	public LineObject
{
public:
	LineActor();
	~LineActor();
	bool Init();
	bool Update();
	void Reset();
private:

};
