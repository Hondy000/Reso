#include "..\Public\ShadowMapActor.h"
#include "..\..\RenderObject\Public\Mesh.h"
#include <memory>
#include "..\..\Shader\DirectX\ver.11\Public\ShadowMapShader.h"
#include "..\..\RenderObject\Public\SubMesh.h"
#include "..\..\RenderDevice\Basic\Public\RendererManager.h"
#include "..\..\..\Core\Task\Public\TaskSystem.h"

ShadowManager::ShadowManager()
{
	m_shadowMapShader = std::make_shared<ShadowMapShader>();
	m_shadowMapShader->Setup();
}

ShadowManager::~ShadowManager()
{

}

// �e�ɂ��郁�b�V����o�^
bool ShadowManager::RegisterMesh(std::shared_ptr<BaseRenderMeshObject> _renderringObject,std::shared_ptr<Transform> transform)
{
	std::shared_ptr<ShadowRenderObject> shadowRenderObject = std::make_shared<ShadowRenderObject>();
	m_shadowRenderObjectList.push_back(shadowRenderObject);

	// ���b�V�����R�s�[
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
	// �ʒu�����R�s�[
	shadowRenderObject->SetTransform(transform);
	shadowRenderObject->Setup();
	return true;
}

bool ShadowManager::RegisterLight(std::shared_ptr<HFGraphics::BaseLight> spLight)
{

	// �����͖��Ȃ��̂ŃA���I�[�_�[�}�b�v�ŊǗ�
	std::pair<std::shared_ptr<HFGraphics::BaseLight>, std::shared_ptr<RenderShadowMapCommand>> key;
	key.first = spLight;
	key.second = std::make_shared<RenderShadowMapCommand>();   // �V���h�E�}�b�v�����R�}���h�𐶐����ăZ�b�g
	key.second->SetRenderPriority(HF_SHADOW_MAPPING_SHADER);   // �p�X�v���C�I���e�B���Z�b�g
	spLight->GetCommmandArray().push_back(key.second);
	m_shadowMapSet.insert(key);
	auto res = m_shadowMapSet.insert(key);
	if (res.second)
	{
		return false;
	}
	sTASK_SYSTEM->RegisterGraphicsCommand(key.second);			//�@�V���h�E�}�b�v�����R�}���h���V�X�e���ɓo�^

	return true;
}

void ShadowManager::GetShadowMapTextures(std::vector< std::shared_ptr<BaseTexture2D > >& _shadowMapArray)
{
	for (auto it = m_shadowMapSet.begin();it != m_shadowMapSet.end();)
	{
		_shadowMapArray.push_back((*it).second->GetShadowMapTexture());
		it++;
	}
}

RenderShadowMapCommand::RenderShadowMapCommand()
{
	// �V���h�E�������ݗp�̃f�v�X�o�b�t�@����
#ifdef DIRECTX11  

	m_depthBuffer = std::make_shared<DX11DepthStencilView>();
	std::dynamic_pointer_cast<DX11DepthStencilView>(m_depthBuffer)->Create(
		sRENDER_DEVICE_MANAGER
	);
#endif
}

RenderShadowMapCommand::~RenderShadowMapCommand()
{
}

bool RenderShadowMapCommand::Update()
{

	for (auto it = ShadowManager::GetInstance()->GetShadowMapList().begin(); it != ShadowManager::GetInstance()->GetShadowMapList().end();)
	{
		for(INT i = 0;i < (*it)->GetMesh()->GetSubMeshArray().size();i++)
		{
			HFMATRIX world = ((*it)->GetTransform()->GetWorldTransform());
			sRENDER_DEVICE_MANAGER->SetTransform(&world, HFTS_WORLD);

			(*it)->GetMesh()->GetSubMeshArray()[i]->Render();
		}
		
		it++;
	}
	m_shadowMapTexture = sRENDER_DEVICE_MANAGER->GetSRViewFromDepthStencil();
	sRENDER_DEVICE_MANAGER->ClearScreen();
	return true;
}

