#pragma once
#include "../../Public/Common.h"

// 更新処理でActor生成するクラス
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