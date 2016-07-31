#pragma once
#include "../../Core/Public/FactoryInterface.h"
#include "../../Graphics/Matetial/Public/Material.h"

class MaterialFactory
	:
	Factorys::ExternalResourceFactory<Material>
{
	MaterialFactory()
	{
		
	};

	~MaterialFactory()
	{

	}

	std::shared_ptr<Material> Create(const std::string& path);

};
