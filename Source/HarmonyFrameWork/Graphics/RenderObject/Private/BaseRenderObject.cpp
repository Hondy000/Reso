#include "..\Public\BaseRenderObject.h"
#include "..\..\..\Core\Task\Public\TaskSystem.h"
#include "../../Public/RenderCommand.h"
#include "..\..\RenderDevice\Basic\Public\RendererManager.h"
#include "../Public/Mesh.h"

BOOL BaseRenderObject::Render()
{
	for (int i = 0; i <m_mesh->GetSubMeshArray().size() ;i++)
	{
		m_mesh->GetSubMeshArray()[i]->Render();
	}
	return true;
}

