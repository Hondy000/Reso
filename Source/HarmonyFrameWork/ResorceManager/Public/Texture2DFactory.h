#pragma once
#include "../../Core/Public/FactoryInterface.h"
#include "../../Graphics/Texture/Public/TextureInterface.h"
#include "../../Graphics/Texture/Public/BaseTexture2D.h"

class Texture2DFactory
	:
	Factorys::ExternalResourceFactory<BaseTexture2D>
{
public:
	Texture2DFactory();
	~Texture2DFactory();

	static Texture2DFactory* GetInstance()
	{
		static Texture2DFactory instance;
		return &instance;
	}

	std::shared_ptr<BaseTexture2D> Create(const std::string& psth);

private:

};
