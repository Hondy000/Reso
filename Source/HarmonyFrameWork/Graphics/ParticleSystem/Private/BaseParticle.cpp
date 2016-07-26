#include "..\Public\BaseParticle.h"


IBaseParticle::IBaseParticle()
{
			
	m_velocity = 0;
}

IBaseParticle::~IBaseParticle()
{

}

bool IBaseParticle::Init()
{

	return true;
}

bool IBaseParticle::Update()
{
	UpdateChildTask();
	GetTransform().SetPosition(m_velocity*m_direction + GetTransform().GetPosition());
	SetLife(GetLife() - 1);
	return true;
}

void IBaseParticle::Reset()
{

}

