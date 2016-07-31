#include "../Public/HFSyatemTime.h"

void HFSyatemTime::Start()
{
	m_startTimePoint = m_nowTimePoint = m_preTimePoint = std::chrono::system_clock::now(); // 計測開始時間
}
// リスタートからのゲーム内の秒数を返す
float HFSyatemTime::GetGameDeltaSeconds()
{
	return m_timeScale * (std::chrono::duration_cast<std::chrono::seconds>(m_nowTimePoint - m_preTimePoint).count()); //処理に要した時間をミリ秒に変換
}

// 時間進行
void HFSyatemTime::ProgressionTime()
{
	m_preTimePoint = m_nowTimePoint;
	m_nowTimePoint = std::chrono::system_clock::now();  // 計測終了時間
}


float HFSyatemTime::GetTotalDeltaSeconds()
{
	return (std::chrono::duration_cast<std::chrono::nanoseconds>(m_startTimePoint - m_preTimePoint).count()*0.00000001); //処理に要した時間をミリ秒に変換

}

float HFSyatemTime::GetRealityDeltaSeconds()
{
	return (std::chrono::duration_cast<std::chrono::nanoseconds>(m_nowTimePoint - m_preTimePoint).count()*0.00000001); //処理に要した時間をミリ秒に変換
}
