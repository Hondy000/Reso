#pragma once
#include "../../../../HarmonyFrameWork/Core/State/Public/IState.h"


class Level1EnemyArrivalState
	:
	public IState
{
public:
	Level1EnemyArrivalState() {};
	~Level1EnemyArrivalState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
private:

};

class Level1EnemyAliveBeingState
	:
	public IState
{
public:
	Level1EnemyAliveBeingState() {};
	~Level1EnemyAliveBeingState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
private:

};



class Level1EnemyDeadBeingState
	:
	public IState
{
public:
	Level1EnemyDeadBeingState() {};
	~Level1EnemyDeadBeingState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
private:

};





class Level1EnemyWaitMoveState
	:
	public IState
{
public:
	Level1EnemyWaitMoveState() {};
	~Level1EnemyWaitMoveState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
private:
};




class Level1EnemyMoveState
	:
	public IState
{
public:
	Level1EnemyMoveState() {};
	~Level1EnemyMoveState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
private:
};
