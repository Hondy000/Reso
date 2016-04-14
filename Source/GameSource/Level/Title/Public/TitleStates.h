#pragma once
#include "../../../../HarmonyFrameWork/Core/State/Public/IState.h"

class TitleStartState
	:
	public IState
{
public:
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
};

class TitleChangeTomMainGameState
	:
	public IState
{
public:
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
};