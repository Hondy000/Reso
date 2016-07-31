#pragma once
#include "MaterialFactory.h"

class ComTexture2DFactory
	:
	public Factorys::IComResourceFactory<ID3D11Texture2D>
{
public:
	static ComTexture2DFactory* GetInstance()
	{
		static ComTexture2DFactory instance;
		return &instance;
	}

	Microsoft::WRL::ComPtr<ID3D11Texture2D> Create(const std::string& path);
protected:
private:
};
