#include "..\Public\Debug.h"				 
#include "..\..\Utility\Public\HFString.h"
#include "../../Core/Public/Common.h"
#include <iosfwd>


			  

FILE*  HFDebug::Debug::m_fp;

HFDebug::Debug::Debug()
{
	StartConsole();

}

HFDebug::Debug::~Debug()
{
	// コンソールの文字色を元に戻す
	SetConsoleTextGray();
	// コンソールおしまい
	EndConsole();
}
void HFDebug::Debug::StartConsole()
{
	::AllocConsole();            // コンソール表示
	freopen_s(&m_fp, "CON", "r", stdin);  // 標準入力を割り当てる   
	freopen_s(&m_fp, "CON", "w", stdout); 
}

void HFDebug::Debug::EndConsole()
{
	fclose(m_fp);
	::FreeConsole(); // コンソールおしまい
}
