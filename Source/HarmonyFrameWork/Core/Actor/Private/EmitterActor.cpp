#include "..\Public\EmitterActor.h"

EmitterActor::EmitterActor()
{
	Init();
}

EmitterActor::~EmitterActor()
{
}

bool EmitterActor::Init()
{
	return true;
}

bool EmitterActor::Update()
{
	return BaseEmitter::Update();
}

void EmitterActor::Reset()
{

}
