#pragma once
#include "../../Core/Public/Common.h"

class Timer
{
public:
	Timer()
	{
		restart();
	}
	~Timer() {};
public:
	void  restart()
	{
		m_start = timeGetTime();        // �v���J�n���Ԃ�ۑ�
	}
	DOUBLE  elapsed()    // ���X�^�[�g����̕b����Ԃ�
	{
		DWORD end = timeGetTime();
		return (DOUBLE)(end - m_start) / 1000;
	}
private:
	DWORD    m_start;    //  �v���J�n����
};