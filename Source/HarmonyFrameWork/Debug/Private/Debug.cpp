#include "..\Public\Debug.h"				 
#include "..\..\Utility\Public\HFString.h"
#include "../../Core/Public/Common.h"
#include <iosfwd>


			  

FILE*  HFDebug::Debug::m_fp;

HFDebug::Debug::Debug()
{
#ifndef DEBUG
	StartConsole();
#endif

}

HFDebug::Debug::~Debug()
{
#ifndef DEBUG

	// コンソールの文字色を元に戻す
	SetConsoleTextGray();
	// コンソールおしまい
	EndConsole();
#endif
}
void HFDebug::Debug::StartConsole()
{
#ifndef DEBUG
	::AllocConsole();            // コンソール表示
	freopen_s(&m_fp, "CON", "r", stdin);  // 標準入力を割り当てる   
	freopen_s(&m_fp, "CON", "w", stdout);
#endif
}

void HFDebug::Debug::EndConsole()
{
#ifndef DEBUG
	fclose(m_fp);
	::FreeConsole(); // コンソールおしまい		
#endif
}
