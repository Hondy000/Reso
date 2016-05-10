#pragma once

#include "../../Core/Public/Common.h"
class Mesh;
class ParticleFactory
{
private:
	ParticleFactory();
public:
	~ParticleFactory();

	static ParticleFactory* GetInstance()
	{
		static ParticleFactory instance;
		return &instance;
	};
	std::shared_ptr<Mesh> GetQuadParticle(UINT particleNum);
private:

};

