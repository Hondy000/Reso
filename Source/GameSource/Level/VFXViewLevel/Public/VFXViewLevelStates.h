#pragma once
#include "../../../../HarmonyFrameWork/Core/State/Public/IState.h"


class VFXViewMainState
	:
	public IState
{
public:
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
};

