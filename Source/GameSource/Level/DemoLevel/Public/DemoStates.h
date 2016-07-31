#pragma once
#include "../../../../HarmonyFrameWork/Core/State/Public/IState.h"


class DemoStartState
	:
	public IState
{
public:
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
};

class DemoMainState
	:
	public IState
{
public:
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
};