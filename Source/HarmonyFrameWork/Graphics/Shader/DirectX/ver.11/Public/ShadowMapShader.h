#pragma once
#include "..\..\..\Basic\Public\BaseShader.h"
#include "..\..\..\..\RenderObject\Public\BaseRenderObject.h"
#include <condition_variable>

class ShadowMapShader
	:
	public BaseShader
{
public:
	ShadowMapShader();
	~ShadowMapShader();
	bool Setup();
	void Destroy();
	bool PreProcessOfRender(std::shared_ptr<BaseRenderObject> shape);
	bool PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials);

	bool Render();

	bool PostProcessOfRender() override;


};
