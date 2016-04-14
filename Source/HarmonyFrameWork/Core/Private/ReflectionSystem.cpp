
#include "../Public/ReflectionSystem.h"

void ReflectionSystem::Remove(const std::string& typeName)
{

	auto it = m_builderMap.find(typeName);
	if (it != m_builderMap.end())
	{
		m_builderMap.erase(it);
	}
}
