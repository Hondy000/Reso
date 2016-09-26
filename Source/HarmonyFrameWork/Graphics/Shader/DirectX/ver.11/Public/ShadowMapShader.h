#pragma once
#include "..\..\..\Basic\Public\BaseGraphicsShader.h"
#include "..\..\..\..\RenderObject\Public\BaseRenderMeshObject.h"
#include <condition_variable>

class ShadowMapShader
	:
	public BaseGraphicsShader
{
public:
	ShadowMapShader();
	~ShadowMapShader();
	bool Setup();
	void Destroy();
	bool PreProcessOfRender(std::shared_ptr<BaseRenderMeshObject> shape);
	bool PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials);

	bool Render();

	bool PostProcessOfRender() override;
	void CreateAndRegisterGraphicsCommand(std::shared_ptr<BaseRenderMeshObject> renderObject, UINT element);
};
