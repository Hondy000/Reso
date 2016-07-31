#include "../Public/HFSyatemTime.h"

void HFSyatemTime::Start()
{
	m_startTimePoint = m_nowTimePoint = m_preTimePoint = std::chrono::system_clock::now(); // �v���J�n����
}
// ���X�^�[�g����̃Q�[�����̕b����Ԃ�
float HFSyatemTime::GetGameDeltaSeconds()
{
	return m_timeScale * (std::chrono::duration_cast<std::chrono::seconds>(m_nowTimePoint - m_preTimePoint).count()); //�����ɗv�������Ԃ��~���b�ɕϊ�
}

// ���Ԑi�s
void HFSyatemTime::ProgressionTime()
{
	m_preTimePoint = m_nowTimePoint;
	m_nowTimePoint = std::chrono::system_clock::now();  // �v���I������
}


float HFSyatemTime::GetTotalDeltaSeconds()
{
	return (std::chrono::duration_cast<std::chrono::nanoseconds>(m_startTimePoint - m_preTimePoint).count()*0.00000001); //�����ɗv�������Ԃ��~���b�ɕϊ�

}

float HFSyatemTime::GetRealityDeltaSeconds()
{
	return (std::chrono::duration_cast<std::chrono::nanoseconds>(m_nowTimePoint - m_preTimePoint).count()*0.00000001); //�����ɗv�������Ԃ��~���b�ɕϊ�
}
