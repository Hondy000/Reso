#pragma once
#include "..\..\..\..\HarmonyFrameWork\Core\State\Public\IState.h"

class MineUnBootState
	:
	public IState
{
public:
	MineUnBootState();
	~MineUnBootState();

	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState();

private:

};

class MineBootState
	:
	public IState
{
public:
	MineBootState();
	~MineBootState();

	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState();

private:

};
