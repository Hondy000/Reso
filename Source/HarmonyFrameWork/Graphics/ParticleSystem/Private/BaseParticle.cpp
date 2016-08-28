#include "..\Public\BaseParticle.h"
#include "..\..\..\Utility\Public\HFSyatemTime.h"


IBaseParticle::IBaseParticle()
	:
	m_velocity(0), m_life(0.0f), m_direction(HFVECTOR3(0, 0, 0))
{
	Init();
}

IBaseParticle::~IBaseParticle()
{

}

bool IBaseParticle::Init()
{
	m_life = 0.0f;
	return true;
}

bool IBaseParticle::Update()
{
	if(0 < m_life)
	{
		m_transform->SetPosition(m_velocity*m_direction + m_transform->GetPosition());

		UpdateChildTask();
		m_life -= HFSyatemTime::GetInstance()->GetGameDeltaSeconds();
	}
	else 
	{
		m_color.A(0);
	}
	return true;
}

void IBaseParticle::Reset()
{

}

