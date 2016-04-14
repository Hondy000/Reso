/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Utility\CBaseLoader.cpp
 *
 * @brief	Implements the base loader class.
 **************************************************************************************************/

#include "../../Core/Public/Common.h"
#include "../Public/IBaseReader.h"
#include <fstream>


IBaseReader::IBaseReader()
{
}

BOOL IBaseReader::ReadFileBuffer(const std::string& path)
{

	std::ifstream ifs(path);
	if (ifs.fail())
	{
		return false;
	}
	else
	{
		m_buffer = std::string((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());
	}
}

IBaseReader::~IBaseReader()
{
}