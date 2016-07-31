#pragma once
#include "MaterialFactory.h"
#include "../../Core\Public/FactoryInterface.h"

class ComShaderResourceViewFactory
	:
	Factorys::IComResourceFactory<ID3D11ShaderResourceView>
{
public:
	static ComShaderResourceViewFactory* GetInstance()
	{
		static ComShaderResourceViewFactory instance;
		return &instance;
	}

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Create(Microsoft::WRL::ComPtr<ID3D11Texture2D>);
protected:
private:
};
