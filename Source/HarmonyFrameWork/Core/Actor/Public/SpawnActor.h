#pragma once
#include "../../Public/Common.h"

// �X�V������Actor��������N���X
class SpawnActor
{
public:
	SpawnActor();
	~SpawnActor();

	BOOL Init();
	void Reset();
	BOOL Update();
protected:
private:
	std::string m_typeName;
};