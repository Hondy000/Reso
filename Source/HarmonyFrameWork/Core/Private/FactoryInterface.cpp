/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Private\FactoryInterface.cpp
 *
 * @brief	Implements the factory interface class.
 **************************************************************************************************/

#include "../Public/FactoryInterface.h"

namespace Factorys
{
	std::list<IObjectFactory*> FactorysManager::m_pFactoryList;
}
