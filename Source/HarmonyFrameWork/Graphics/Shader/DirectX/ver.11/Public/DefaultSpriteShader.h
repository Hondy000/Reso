#pragma once
#include "../../../Basic/Public/BaseShader.h"

class DefaultSpriteShader
	:
	public BaseShader
{
public:
	DefaultSpriteShader();
	~DefaultSpriteShader();
	BOOL Setup();
	void Destroy();			

	BOOL PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials);
	/**********************************************************************************************//**
	 * @fn	virtual BOOL CBaseShader::Render() = 0;
	 *
	 * @brief	Renders this object.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 *
	 * @return	A BOOL.
	 **************************************************************************************************/

	BOOL Render();

	/**********************************************************************************************//**
	 * @fn	virtual BOOL CBaseShader::PostRenderProcess() = 0;
	 *
	 * @brief	Posts the render process.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/04
	 *
	 * @return	A BOOL.
	 **************************************************************************************************/

	BOOL PostProcessOfRender() override;


};
