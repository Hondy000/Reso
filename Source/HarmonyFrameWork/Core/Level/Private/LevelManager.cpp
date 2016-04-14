
#include "../Public/LevelManager.h"
#include "../../../../GameSource/Level/Public/LevelGenerated.h"
#include "../../Task/Public/TaskSystem.h"

BOOL LevelManager::Init()
{
	LevelGenerated();
	m_spLevel = std::dynamic_pointer_cast<IBaseLevel>(ReflectionSystem::GetInstance()->Create("class MainGame"));
	TaskSystem::GetInstance()->RegisterTask(typeid(m_spLevel).name(),m_spLevel);
	return false;
}

BOOL LevelManager::Update()
{
	return false;
}

void LevelManager::Reset()
{
}
