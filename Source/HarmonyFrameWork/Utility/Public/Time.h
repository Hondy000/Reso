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
		m_nowTimePoint = m_preTimePoint = std::chrono::system_clock::now(); // �v���J�n����
	}


	float  GetGameDeltaSeconds()    // ���X�^�[�g����̕b����Ԃ�
	{
		return m_timeScale * (std::chrono::duration_cast<std::chrono::seconds>(m_nowTimePoint - m_preTimePoint).count()); //�����ɗv�������Ԃ��~���b�ɕϊ�
	}


	// ���Ԑi�s
	void ProgressionTime()
	{
		m_preTimePoint = m_nowTimePoint;
		m_nowTimePoint = std::chrono::system_clock::now();  // �v���I������
		elapsed =  (std::chrono::duration_cast<std::chrono::nanoseconds>(m_nowTimePoint - m_preTimePoint).count()); //�����ɗv�������Ԃ��~���b�ɕϊ�
	}


	float GetRealityDeltaSeconds()
	{
		return (std::chrono::duration_cast<std::chrono::nanoseconds>(m_nowTimePoint - m_preTimePoint).count()*0.00000001); //�����ɗv�������Ԃ��~���b�ɕϊ�
	}
private:

	std::chrono::system_clock::time_point  m_preTimePoint, m_nowTimePoint;
	float m_preFrameTime;
	float elapsed;
	
	float m_timeScale;		// ���Ԃ̐i�s�{�� 
};