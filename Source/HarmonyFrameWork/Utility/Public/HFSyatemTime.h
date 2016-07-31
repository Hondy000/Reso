#pragma once
#include "../../Core/Public/Common.h"

#include <chrono>
class HFSyatemTime
{
public:
	HFSyatemTime()
	{
		m_timeScale = 1.0f;
		Start();
	}
	~HFSyatemTime() {};
public:


	static HFSyatemTime* GetInstance()
	{
		static HFSyatemTime instance;
		return &instance;
	}

	void  Start();

	// 時間進行
	void ProgressionTime();

	// 総合経過時間
	float GetTotalDeltaSeconds();

	float GetGameDeltaSeconds();   // スタートからの秒数を返す

	float GetRealityDeltaSeconds();
private:

	std::chrono::system_clock::time_point  m_startTimePoint;
	std::chrono::system_clock::time_point  m_preTimePoint, m_nowTimePoint;	
	float m_timeScale;		// 時間の進行倍率 
};