#pragma once
#include "../../../Basic/Public/BaseShader.h"

class DefaultSpriteShader
	:
	public BaseShader
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


};
