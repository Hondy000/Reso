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


class PlayerMoveState
	:
	public IState
{
public:
	PlayerMoveState() {};
	~PlayerMoveState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
protected:
private:
};

class PlayerStopState
	:
	public IState
{
public:
	PlayerStopState() {};
	~PlayerStopState() {};
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