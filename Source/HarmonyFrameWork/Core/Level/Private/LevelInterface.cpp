
#include "../Public/LevelInterface.h"

using namespace std;
IBaseLevel::IBaseLevel()
{

}

IBaseLevel::~IBaseLevel()
{

}

BOOL IBaseLevel::Init()
{
	RegisterVariable("m_isChangeLevel", false);
	CreateVariable("m_changeLevelName", typeid(string).name());
	
	return true;
}

BOOL IBaseLevel::IsChangeLevel()
{
	return *GetVariable<BOOL>("m_isChangeLevel")->GetValue();
}

const std::string& IBaseLevel::GetChangeLevelType(void)
{
	return *GetVariable<string>("m_changeLevelName")->GetValue();
}

void IBaseLevel::SetChangeLevelType(const std::string& changeLevelType)
{
	GetVariable<string>("m_changeLevelName")->SetValue(changeLevelType);
}

