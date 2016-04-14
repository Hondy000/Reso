#pragma once
#include "..\..\..\..\HarmonyFrameWork\Core\State\Public\IState.h"

class PlayerAliveBeingState
	:
	public IState
{
public:
	PlayerAliveBeingState() {};
	~PlayerAliveBeingState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
protected:
private:
};

class PlayerDeadBeingState
	:
	public IState
{
public:
	PlayerDeadBeingState() {};
	~PlayerDeadBeingState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
protected:
private:
};


class PlayerCruiseMoveState
	:
	public IState
{
public:
	PlayerCruiseMoveState() {};
	~PlayerCruiseMoveState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
protected:
private:
};

class PlayerAcccelerationMoveState
	:
	public IState
{
public:
	PlayerAcccelerationMoveState() {};
	~PlayerAcccelerationMoveState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
protected:
private:
};		   
class PlayerDecelerationMoveState
	:
	public IState
{
public:
	PlayerDecelerationMoveState() {};
	~PlayerDecelerationMoveState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
protected:
private:
};