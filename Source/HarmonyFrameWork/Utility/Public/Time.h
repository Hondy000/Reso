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
		m_start = timeGetTime();        // 計測開始時間を保存
	}
	DOUBLE  elapsed()    // リスタートからの秒数を返す
	{
		DWORD end = timeGetTime();
		return (DOUBLE)(end - m_start) / 1000;
	}
private:
	DWORD    m_start;    //  計測開始時間
};