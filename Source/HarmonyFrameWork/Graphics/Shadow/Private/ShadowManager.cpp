#include "..\Public\ShadowManager.h"
#include "..\..\RenderObject\Public\Mesh.h"
#include <memory>
#include "..\..\Shader\DirectX\ver.11\Public\ShadowMapShader.h"
#include "..\..\RenderObject\Public\SubMesh.h"

ShadowManager::ShadowManager()
{
	m_shadowMapShader = std::make_shared<ShadowMapShader>();
	m_shadowMapShader->Setup();
}

ShadowManager::~ShadowManager()
{

}

bool ShadowManager::Register(std::shared_ptr<BaseRenderObject> _renderringObject,std::shared_ptr<Transform> transform)
{
	std::shared_ptr<ShadowRenderObject> shadowRenderObject = std::make_shared<ShadowRenderObject>();
	m_shadowMapList.push_back(shadowRenderObject);

	shadowRenderObject->SetMesh(std::make_shared<Mesh>());
	shadowRenderObject->GetMesh()->GetSubMeshArray().resize(_renderringObject->GetMesh()->GetSubMeshArray().size());
	for (int i = 0;i < shadowRenderObject->GetMesh()->GetSubMeshArray().size();i++)
	{
		shadowRenderObject->GetMesh()->GetSubMeshArray()[i] = std::make_shared<SubMesh>();
		shadowRenderObject->GetMesh()->GetSubMeshArray()[i]->SetMaterial(std::make_shared<Material>());
		shadowRenderObject->GetMesh()->GetSubMeshArray()[i]->SetIndexBuffer(_renderringObject->GetMesh()->GetSubMeshArray()[i]->GetIndexBuffer());
		shadowRenderObject->GetMesh()->GetSubMeshArray()[i]->SetVertexBuffers(_renderringObject->GetMesh()->GetSubMeshArray()[i]->GetVertexBuffers());

		shadowRenderObject->GetMesh()->GetSubMeshArray()[i]->SetIndexCount(_renderringObject->GetMesh()->GetSubMeshArray()[i]->GetIndexCount());
		shadowRenderObject->GetMesh()->GetSubMeshArray()[i]->GetMaterial()->SetMaterialShader(m_shadowMapShader);

	}
	shadowRenderObject->SetTransform(transform);
	shadowRenderObject->Setup();
	return true;
}

bool ShadowManager::Update()
{
	for (auto it = m_shadowMapList.begin();it != m_shadowMapList.end();it++)
	{
		(*it)->Update();
	}
	return true;
}

