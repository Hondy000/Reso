/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Level\Private\LevelInterface.cpp
 *
 * @brief	Implements the level interface class.
 **************************************************************************************************/

#include "../Public/LevelInterface.h"

using namespace std;

/**********************************************************************************************//**
 * @fn	IBaseLevel::IBaseLevel()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

IBaseLevel::IBaseLevel()
{

}

/**********************************************************************************************//**
 * @fn	IBaseLevel::~IBaseLevel()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

IBaseLevel::~IBaseLevel()
{

}

/**********************************************************************************************//**
 * @fn	bool IBaseLevel::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool IBaseLevel::Init()
{
	RegisterVariable("m_isChangeLevel", false);
	CreateVariable("m_changeLevelName", typeid(string).name());
	
	return true;
}

/**********************************************************************************************//**
 * @fn	bool IBaseLevel::IsChangeLevel()
 *
 * @brief	Query if this object is change level.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if change level, false if not.
 **************************************************************************************************/

bool IBaseLevel::IsChangeLevel()
{
	return *GetVariable<bool>("m_isChangeLevel")->GetValue();
}

/**********************************************************************************************//**
 * @fn	const std::string& IBaseLevel::GetChangeLevelType(void)
 *
 * @brief	Gets change level type.
 *
 * @author	Kazuyuki Honda
 *
 * @return	The change level type.
 **************************************************************************************************/

const std::string& IBaseLevel::GetChangeLevelType(void)
{
	return *GetVariable<string>("m_changeLevelName")->GetValue();
}

/**********************************************************************************************//**
 * @fn	void IBaseLevel::SetChangeLevelType(std::string& changeLevelType)
 *
 * @brief	Sets change level type.
 *
 * @author	Kazuyuki Honda
 *
 * @param [in,out]	changeLevelType	Type of the change level.
 **************************************************************************************************/

void IBaseLevel::SetChangeLevelType(std::string& changeLevelType)
{
	GetVariable<string>("m_changeLevelName")->SetValue(&changeLevelType);
}

