#pragma once
#include "../../Core/Public/ManagerInterface.h"
#include "../../Graphics/Shader/Basic/Public/BaseShader.h"
#include "Texture2DFactory.h"

#define sTEXTURE2D_MANAGER (Texture2DManager::GetInstance())

class Texture2DManager
	:
	public GeneralResourceManager<BaseTexture2D>
{
public:

	static Texture2DManager* GetInstance()
	{
		static Texture2DManager instance;
		return &instance;
	}

private:

	std::shared_ptr<BaseTexture2D> RequestCreate(const std::string& path);
};
