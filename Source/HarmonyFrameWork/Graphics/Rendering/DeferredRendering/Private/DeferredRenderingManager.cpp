#include "..\Public\DeferredRenderingManager.h"
#include "../../../../ResorceManager/Public/BasicMeshFactory.h"
#include "../../../Shader/DirectX/ver.11/Public/LightShaderOfDeferredRender.h"
#include "../../../../ResorceManager/Public/BasicMeshManager.h"
#include "../../../../Core/Component/Public/Sprite2DCompornent.h"

using namespace std;

DeferredRenderingManager::DeferredRenderingManager()
{

}

DeferredRenderingManager::~DeferredRenderingManager()
{

}

BOOL DeferredRenderingManager::Init()
{
	shared_ptr<Sprite2DCompornent> m_screenRenderObject = shared_ptr<Sprite2DCompornent>(new Sprite2DCompornent);
	m_screenRenderObject->SetMesh(BasicMeshManager::GetInstance()->Get(HF_BM_SPRITE, 0, 0, 0));
	std::shared_ptr<LightShaderOfDeferredRender> lightingshader = shared_ptr<LightShaderOfDeferredRender>(new LightShaderOfDeferredRender);
	RegisterCompornent("m_screenRenderObject", m_screenRenderObject);
	lightingshader->Setup();
	m_screenRenderObject->GetMesh()->GetSubMeshArray()[0]->GetMaterial()->SetMaterialShader(lightingshader);

	return true;
}

void DeferredRenderingManager::Reset()
{

}

BOOL DeferredRenderingManager::Update()
{					
	UpdateAllTask();
	return true;
}
