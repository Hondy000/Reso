#pragma once
#include "../../Public/Common.h"

// �X�V������Actor��������N���X
class SpawnActor
{
public:
	SpawnActor();
	~SpawnActor();

	bool Init();
	void Reset();
	bool Update();
protected:
private:
	std::string m_typeName;
};