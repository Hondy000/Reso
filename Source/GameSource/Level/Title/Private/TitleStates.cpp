/**********************************************************************************************//**
 * @file	Source\GameSource\Level\Title\Private\TitleStates.cpp
 *
 * @brief	Implements the title states class.
 **************************************************************************************************/

#include "../Public/TitleStates.h"

/**********************************************************************************************//**
 * @fn	void TitleStartState::Enter( )
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void TitleStartState::Enter( )
{
}

/**********************************************************************************************//**
 * @fn	void TitleStartState::Execute( )
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void TitleStartState::Execute( )
{

}

/**********************************************************************************************//**
 * @fn	void TitleStartState::Exit( )
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void TitleStartState::Exit( )
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> TitleStartState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

std::shared_ptr<IState> TitleStartState::GetNewState(void)
{
	return {std::make_shared<TitleStartState>()};
}

/**********************************************************************************************//**
 * @fn	void TitleChangeTomMainGameState::Enter( )
 *
 * @brief	Enters this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void TitleChangeTomMainGameState::Enter( )
{

}

/**********************************************************************************************//**
 * @fn	void TitleChangeTomMainGameState::Execute( )
 *
 * @brief	Executes this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void TitleChangeTomMainGameState::Execute( )
{

}

/**********************************************************************************************//**
 * @fn	void TitleChangeTomMainGameState::Exit( )
 *
 * @brief	Exits this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void TitleChangeTomMainGameState::Exit( )
{

}

/**********************************************************************************************//**
 * @fn	std::shared_ptr<IState> TitleChangeTomMainGameState::GetNewState(void)
 *
 * @brief	Gets new state.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The new state.
 **************************************************************************************************/

std::shared_ptr<IState> TitleChangeTomMainGameState::GetNewState(void)
{
	return{ std::make_shared<TitleStartState>() };
}
