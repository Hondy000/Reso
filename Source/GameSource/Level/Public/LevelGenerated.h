#pragma once
#include "../../../HarmonyFrameWork/Core/Public/ReflectionSystem.h"
#include "../DemoLevel/Public/DemoLevel.h"		 	
#include "../VFXViewLevel/Public/VFXViewLevel.h"
#include "../ModelView/Public/ModelViewLevel.h"
#include "../MainGame/Public/MainGame.h"			   
#include "../Title/Public/Title.h"		   	   
#include "../Result/Public/Result.h"	  	   

void LevelGenerated()
{
	ReflectionSystem::GetInstance()->Register(REGISTER_TYPE(VFXViewLevel));
	ReflectionSystem::GetInstance()->Register(REGISTER_TYPE(DemoLevel));
	ReflectionSystem::GetInstance()->Register(REGISTER_TYPE(Title));
	ReflectionSystem::GetInstance()->Register(REGISTER_TYPE(MainGame));
	ReflectionSystem::GetInstance()->Register(REGISTER_TYPE(Result));
	ReflectionSystem::GetInstance()->Register(REGISTER_TYPE(ModelViewLevel));

}
