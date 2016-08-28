#include "../Public/Sprite2DObject.h"
#include "../../Public/RenderCommand.h"
#include "../../../Core/Task/Public/TaskSystem.h"
#include "..\Public\Mesh.h"
#include "..\..\Shader\Basic\Public\BaseShader.h"
#include "..\..\..\ResorceManager\Public\BasicMeshManager.h"
#include "..\..\..\ResorceManager\Public\BasicMeshFactory.h"
#include "..\..\Shader\DirectX\ver.11\Public\DefaultSpriteShader.h"


Sprite2DObject::Sprite2DObject()
{
}

Sprite2DObject::~Sprite2DObject()
{

}

bool Sprite2DObject::Init()
{
	if (m_mesh == nullptr)
	{
		SetMesh(BasicMeshManager::GetInstance()->Get(HF_BM_SPRITE, 0, 0, 0));

	}
	if (m_mesh->GetSubMeshArray()[0]->GetMaterial() == nullptr)
	{
		GetMesh()->GetSubMeshArray()[0]->SetMaterial(std::make_shared<Material>());

	}
	if (m_mesh->GetSubMeshArray()[0]->GetMaterial()->GetMaterialShader() == nullptr)
	{
		GetMesh()->GetSubMeshArray()[0]->GetMaterial()->SetMaterialShader(std::make_shared<DefaultSpriteShader>());

	}
	return true;
}

bool Sprite2DObject::Update()
{
	return true;
}

