#pragma once
#include "..\..\..\..\HarmonyFramework\Core\State\Public\IState.h"

class ModelViewLevelStartState
	:
	public IState
{
public:
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
};

class ModelViewLevelMainState
	:
	public IState
{
public:
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
};