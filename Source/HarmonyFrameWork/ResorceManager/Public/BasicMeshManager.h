#pragma once
#include "../../Core/Public/Common.h"
class BaseRenderMeshObject;

enum BASIC_MESH_TYPE
{
	HF_BM_SPRITE,			// 四角固定スプライト
	HF_BM_RECTANGLE_SPRITE,	// 多角形スプライト
	HF_BM_QUAD,
	HF_BM_BOX,
	HF_BM_SPHERE
};
class StaticMeshObject;


class BasicMeshManager
{
public:
	BasicMeshManager() {};
	~BasicMeshManager() {};

	static BasicMeshManager* GetInstance()
	{
		static BasicMeshManager instance;
		return &instance;
	}

	std::shared_ptr<Mesh> Get(BASIC_MESH_TYPE meshType, UINT partition1, UINT partition2, UINT partition3);

private:
	std::unordered_map<std::string, std::shared_ptr<Mesh>> m_staticMeshMap;


};
