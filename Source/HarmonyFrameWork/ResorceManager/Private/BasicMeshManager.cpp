
#include "../../Graphics/RenderObject/Public/BaseRenderObject.h"
#include "../Public/BasicMeshFactory.h"
#include "../Public/BasicMeshManager.h"

std::shared_ptr<Mesh> BasicMeshManager::Get(BASIC_MESH_TYPE meshType, UINT partition1, UINT partition2, UINT partition3)
{
	return BasicMeshFactory::GetInstance()->Create(meshType,partition1,partition2,partition3);
}

