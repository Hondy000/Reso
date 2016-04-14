#pragma once
#include "../../../Basic/Public/BaseShader.h"

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
	virtual BOOL Setup();
	virtual void Destroy();

	BOOL PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material> materials);

	/**********************************************************************************************//**
	 * @fn	virtual BOOL Render();
	 *
	 * @brief	Renders this object.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 *
	 * @return	A BOOL.
	 **************************************************************************************************/

	virtual BOOL Render();

	/**********************************************************************************************//**
	 * @fn	virtual BOOL PostProcessOfRender();
	 *
	 * @brief	Posts the render process.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/04
	 *
	 * @return	A BOOL.
	 **************************************************************************************************/

	virtual BOOL PostProcessOfRender();
};
