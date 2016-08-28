#pragma once
#include "ActorInterface.h"
#include "..\..\..\Graphics\ParticleSystem\Public\BaseEmitter.h"

class EmitterActor
	:
	public IActor,
	public virtual BaseEmitter
{
public:
	EmitterActor();
	~EmitterActor();
	bool Init();
	bool Update();
	void Reset();
private:

};
