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

	// ���Ԑi�s
	void ProgressionTime();

	// �����o�ߎ���
	float GetTotalDeltaSeconds();

	float GetGameDeltaSeconds();   // �X�^�[�g����̕b����Ԃ�

	float GetRealityDeltaSeconds();
private:

	std::chrono::system_clock::time_point  m_startTimePoint;
	std::chrono::system_clock::time_point  m_preTimePoint, m_nowTimePoint;	
	float m_timeScale;		// ���Ԃ̐i�s�{�� 
};