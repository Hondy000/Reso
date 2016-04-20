#pragma once
#include "../../../../HarmonyFrameWork/Core/State/Public/IState.h"

class BasicEnemyAliveBeingState
	:
	public IState
{
public:
	BasicEnemyAliveBeingState() {};
	~BasicEnemyAliveBeingState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
private:

};



class BasicEnemyStartState
	:
	public IState
{
public:
	BasicEnemyStartState() {};
	~BasicEnemyStartState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
private:

};


class BasicEnemyWaitActionState
	:
	public IState
{
public:
	BasicEnemyWaitActionState() {};
	~BasicEnemyWaitActionState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
private:
	bool m_isChangeAttakState;
};


class BasicEnemyAttackActionState
	:
	public IState
{
public:
	BasicEnemyAttackActionState() {};
	~BasicEnemyAttackActionState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
private:
	bool m_isDeadState;
};




class BasicEnemyWaitMoveState
	:
	public IState
{
public:
	BasicEnemyWaitMoveState() {};
	~BasicEnemyWaitMoveState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
private:
};



class BasicEnemyStraightMoveState
	:
	public IState
{
public:
	BasicEnemyStraightMoveState() {};
	~BasicEnemyStraightMoveState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
private:
};


class BasicEnemyDeadBeingState
	:
	public IState
{
public:
	BasicEnemyDeadBeingState() {};
	~BasicEnemyDeadBeingState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
};
