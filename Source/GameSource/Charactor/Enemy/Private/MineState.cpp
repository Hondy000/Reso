

#include "..\Public\MineState.h"

MineUnBootState::MineUnBootState()
{
}

MineUnBootState::~MineUnBootState()
{
}

void MineUnBootState::Enter()
{

}

void MineUnBootState::Execute()
{

}

void MineUnBootState::Exit()
{

}

std::shared_ptr<IState> MineUnBootState::GetNewState()
{
	return std::make_shared<MineBootState>();
}

MineBootState::MineBootState()
{

}

MineBootState::~MineBootState()
{

}

void MineBootState::Enter()
{

}

void MineBootState::Execute()
{

}

void MineBootState::Exit()
{

}

std::shared_ptr<IState> MineBootState::GetNewState()
{
	return std::make_shared<MineBootState>();
}
