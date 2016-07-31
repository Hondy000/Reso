#pragma once
#include "../../Public/Common.h"

// 更新処理でActor生成するクラス
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