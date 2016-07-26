#pragma once
#include "../../Core/Public/Common.h"

#include <chrono>
class HFTime
{
public:
	HFTime()
	{
		m_timeScale = 1.0f;
		Start();
	}
	~HFTime() {};
public:


	static HFTime* GetInstance()
	{
		static HFTime instance;
		return &instance;
	}

	void  Start()
	{
		m_nowTimePoint = m_preTimePoint = std::chrono::system_clock::now(); // 計測開始時間
	}


	float  GetGameDeltaSeconds()    // リスタートからの秒数を返す
	{
		return m_timeScale * (std::chrono::duration_cast<std::chrono::seconds>(m_nowTimePoint - m_preTimePoint).count()); //処理に要した時間をミリ秒に変換
	}


	// 時間進行
	void ProgressionTime()
	{
		m_preTimePoint = m_nowTimePoint;
		m_nowTimePoint = std::chrono::system_clock::now();  // 計測終了時間
		elapsed =  (std::chrono::duration_cast<std::chrono::nanoseconds>(m_nowTimePoint - m_preTimePoint).count()); //処理に要した時間をミリ秒に変換
	}


	float GetRealityDeltaSeconds()
	{
		return (std::chrono::duration_cast<std::chrono::nanoseconds>(m_nowTimePoint - m_preTimePoint).count()*0.00000001); //処理に要した時間をミリ秒に変換
	}
private:

	std::chrono::system_clock::time_point  m_preTimePoint, m_nowTimePoint;
	float m_preFrameTime;
	float elapsed;
	
	float m_timeScale;		// 時間の進行倍率 
};