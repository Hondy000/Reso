#pragma once
#include "../../Public/CharactorActor.h"

class EnemyActor
	:
	public CharactorActor
{
public:
	EnemyActor() {};
	~EnemyActor() {};

	BOOL Init();
	BOOL Update();
	void Reset();

protected:

private:
};
