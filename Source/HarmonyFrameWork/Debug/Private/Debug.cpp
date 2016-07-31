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
	// �R���\�[���̕����F�����ɖ߂�
	SetConsoleTextGray();
	// �R���\�[�������܂�
	EndConsole();
}
void HFDebug::Debug::StartConsole()
{
	::AllocConsole();            // �R���\�[���\��
	freopen_s(&m_fp, "CON", "r", stdin);  // �W�����͂����蓖�Ă�   
	freopen_s(&m_fp, "CON", "w", stdout); 
}

void HFDebug::Debug::EndConsole()
{
	fclose(m_fp);
	::FreeConsole(); // �R���\�[�������܂�
}
