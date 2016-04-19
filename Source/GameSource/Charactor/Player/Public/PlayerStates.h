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


class PlayerMaxVelocityMoveState
	:
	public IState
{
public:
	PlayerMaxVelocityMoveState() {};
	~PlayerMaxVelocityMoveState() {};
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
	bool m_isChangeStopState;
	bool m_isChangeAcccelerationMoveState;
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

	 /*

class PlayerUnShotState
	:
	public IState
{
public:
	PlayerUnShotState() {};
	~PlayerUnShotState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
protected:
private:
};

class PlayerShotState
	:
	public IState
{
public:
	PlayerShotState() {};
	~PlayerShotState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
protected:
private:
};

class PlayerUseBombState
	:
	public IState
{
public:
	PlayerUseBombState() {};
	~PlayerUseBombState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
protected:
private:
};


class PlayerUnUseBombState
	:
	public IState
{
public:
	PlayerUnUseBombState() {};
	~PlayerUnUseBombState() {};
	void Enter();
	void Execute();
	void Exit();

	std::shared_ptr<IState> GetNewState(void);
protected:
private:
};	   */