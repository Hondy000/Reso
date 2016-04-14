#include "../Public/DemoLevel.h"
#include "../Public/DemoStates.h"
using namespace std;

BOOL DemoLevel::Init()
{
	RegisterState(make_shared<DemoStartState>(), shared_from_this());
	return true;
}

BOOL DemoLevel::Update()
{
	UpdateState(shared_from_this());
	return false;
}

void DemoLevel::Reset()
{
	Init();
}
