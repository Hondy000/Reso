#pragma once
#include "MeshFactory.h"
#include "../../Graphics/RenderObject/Public/StaticMeshObject.h"


enum BASIC_MESH_TYPE;

class BasicMeshFactory
	:
	public Factorys::ObjectFactory
{
private:

	BasicMeshFactory() {};
public:
	~BasicMeshFactory() {};

	static BasicMeshFactory* GetInstance()
	{
		static BasicMeshFactory instance;
		return &instance;
	}


	std::shared_ptr<Mesh> Create(BASIC_MESH_TYPE meshType, UINT partition1, UINT partition2, UINT partition3);

private:
	std::shared_ptr<Mesh> CreateSprite();
	std::shared_ptr<Mesh> CreateRectangleSprite(int rectCount);

	std::shared_ptr<Mesh> CreateQuad(UINT partition1, UINT partition2);
};

