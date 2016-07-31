#pragma once
#include "../../../../HarmonyFrameWork/Core/State/Public/IState.h"
#include "../../../../HarmonyFrameWork/Utility/Public/HFSyatemTime.h"


class MainGameStartState
	:
	public IState
{
public:
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
};

class MainGameMainState
	:
	public IState
{
public:
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
private:
	std::shared_ptr<HFSyatemTime> m_popCounter;
	std::shared_ptr<HFSyatemTime> m_endCounter;

	bool m_isChangeEndMain;
};


class MainGameCheckScoreState
	:
	public IState
{
public:
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
private:
	std::shared_ptr<HFSyatemTime> m_popCounter;
	std::shared_ptr<HFSyatemTime> m_endCounter;

	bool m_isChangeEndMain;
};

class MainGameLevelupState
	:
	public IState
{
public:
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
private:
	bool m_isChangeEndMain;
};


class MainGameTimeupState
	:
	public IState
{
public:
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
private:
	bool m_isChangeEndMain;
};