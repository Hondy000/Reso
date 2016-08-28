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

	// �R���\�[���̕����F�����ɖ߂�
	SetConsoleTextGray();
	// �R���\�[�������܂�
	EndConsole();
#endif
}
void HFDebug::Debug::StartConsole()
{
#ifndef DEBUG
	::AllocConsole();            // �R���\�[���\��
	freopen_s(&m_fp, "CON", "r", stdin);  // �W�����͂����蓖�Ă�   
	freopen_s(&m_fp, "CON", "w", stdout);
#endif
}

void HFDebug::Debug::EndConsole()
{
#ifndef DEBUG
	fclose(m_fp);
	::FreeConsole(); // �R���\�[�������܂�		
#endif
}
