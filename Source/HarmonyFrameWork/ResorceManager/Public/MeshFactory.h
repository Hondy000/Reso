#pragma once
#include "../../Core/Public/FactoryInterface.h"					 
#include "../../Graphics/Public/GraphicsTypes.h"
#include "../../Graphics/RenderObject/Public/Mesh.h"
class BaseRenderObject;
struct HFGraphics::MeshData;


class MeshFactory
	:
	public Factorys::ExternalResourceFactory<Mesh>
{		   
private:
	MeshFactory() {};
public:			  
	static MeshFactory* GetInstance()
	{
		static MeshFactory instance;
		return &instance;
	}
	std::shared_ptr<Mesh> Create(const std::string & path);
	void PartitionSubMesh(std::shared_ptr<HFGraphics::MeshData>);
private:
};
