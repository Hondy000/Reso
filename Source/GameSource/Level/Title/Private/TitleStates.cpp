
#include "../Public/TitleStates.h"


void TitleStartState::Enter( )
{
}

void TitleStartState::Execute( )
{

}

void TitleStartState::Exit( )
{

}

std::shared_ptr<IState> TitleStartState::GetNewState(void)
{
	return {std::make_shared<TitleStartState>()};
}

void TitleChangeTomMainGameState::Enter( )
{

}


void TitleChangeTomMainGameState::Execute( )
{

}

void TitleChangeTomMainGameState::Exit( )
{

}

std::shared_ptr<IState> TitleChangeTomMainGameState::GetNewState(void)
{
	return{ std::make_shared<TitleStartState>() };
}
