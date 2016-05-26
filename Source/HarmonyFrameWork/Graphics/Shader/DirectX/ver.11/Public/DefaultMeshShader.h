#pragma once
#include "../../../Basic/Public/BaseShader.h"
#include "..\..\..\..\Public\GraphicsTypes.h"

class DefaultMeshShader
	:
	public BaseShader
{
public:
	DefaultMeshShader()
	{
		m_pathPriority = HF_POST_DEFERRED_RENDERING_SHADER;
	};

	~DefaultMeshShader()
	{

	}
	virtual bool Setup();
	virtual void Destroy();

	bool PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material> materials);

	/**********************************************************************************************//**
	 * @fn	virtual bool Render();
	 *
	 * @brief	Renders this object.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 *
	 * @return	A bool.
	 **************************************************************************************************/

	virtual bool Render();

	/**********************************************************************************************//**
	 * @fn	virtual bool PostProcessOfRender();
	 *
	 * @brief	Posts the render process.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/04
	 *
	 * @return	A bool.
	 **************************************************************************************************/

	virtual bool PostProcessOfRender();
};
