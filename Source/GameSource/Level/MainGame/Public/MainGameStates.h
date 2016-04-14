#pragma once
#include "../../../../HarmonyFrameWork/Core/State/Public/IState.h"
#include "../../../../HarmonyFrameWork/Utility/Public/Time.h"


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
	std::shared_ptr<Timer> m_popCounter;
	std::shared_ptr<Timer> m_endCounter;

	BOOL m_isChangeEndMain;
};