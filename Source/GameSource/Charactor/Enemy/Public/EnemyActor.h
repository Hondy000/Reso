#pragma once
#include "../../Public/CharactorActor.h"

class EnemyActor
	:
	public CharactorActor
{
public:
	EnemyActor() {};
	~EnemyActor() {};

	bool Init();
	bool Update();
	void Reset();

protected:

private:
};
