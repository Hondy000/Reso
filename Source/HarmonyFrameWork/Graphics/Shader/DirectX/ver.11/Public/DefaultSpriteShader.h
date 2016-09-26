#pragma once
#include "../../../Basic/Public/BaseGraphicsShader.h"

class DefaultSpriteShader
	:
	public BaseGraphicsShader
{
public:
	DefaultSpriteShader();
	~DefaultSpriteShader();
	bool Setup();
	void Destroy();			

	bool PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials);
	/**********************************************************************************************//**
	 * @fn	virtual bool CBaseShader::Render() = 0;
	 *
	 * @brief	Renders this object.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 *
	 * @return	A bool.
	 **************************************************************************************************/

	bool Render();

	/**********************************************************************************************//**
	 * @fn	virtual bool CBaseShader::PostRenderProcess() = 0;
	 *
	 * @brief	Posts the render process.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/04
	 *
	 * @return	A bool.
	 **************************************************************************************************/

	bool PostProcessOfRender() override;
	void CreateAndRegisterGraphicsCommand(std::shared_ptr<BaseRenderMeshObject> renderObject, UINT element);
};
