#include "..\Public\EmitterActor.h"

EmitterActor::EmitterActor()
{
}

EmitterActor::~EmitterActor()
{
}

bool EmitterActor::Init()
{
	BaseEmitter::Init();
	return true;
}

bool EmitterActor::Update()
{
	return BaseEmitter::Update();
}

void EmitterActor::Reset()
{

}
