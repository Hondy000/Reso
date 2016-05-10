#include "..\Public\BaseParticle.h"


IBaseParticle::IBaseParticle()
{

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
	m_life--;
	return true;
}

void IBaseParticle::Reset()
{

}

