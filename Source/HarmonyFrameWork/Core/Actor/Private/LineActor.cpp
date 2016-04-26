
#include "..\Public\LineActor.h"

LineActor::LineActor()
{
	Init();
}

LineActor::~LineActor()
{
}

bool LineActor::Init()
{
	return true;
}

bool LineActor::Update()
{
	return LineObject::Update();
}

void LineActor::Reset()
{

}
