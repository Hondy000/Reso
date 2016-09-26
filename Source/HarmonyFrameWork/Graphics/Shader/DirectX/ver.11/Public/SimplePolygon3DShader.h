/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\Shader\DirectX\ver.11\SimplePolygon3DShader.h
 *
 * @brief	Declares the simple polygon 3D shader class.
 **************************************************************************************************/

#pragma once
#include "../../../Basic/Public/BaseGraphicsShader.h"

/**********************************************************************************************//**
  * @class	SimplePolygon3DShader SimplePolygon3DShader.h
  * 			Source\HarmonyFrame\Graphics\Shader\DirectX\ver.11\SimplePolygon3DShader.h
  *
  * @brief	A simple polygon 3D shader.
  *
  * @author	Kazuyuki Honda
  * @date	2015/11/05
  **************************************************************************************************/

class SimplePolygon3DShader
	:
	public BaseGraphicsShader
{
public:

	SimplePolygon3DShader() {};
	~SimplePolygon3DShader()
	{

	}

	/**********************************************************************************************//**
	 * @fn	virtual bool Setup();
	 *
	 * @brief	初期化.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 *
	 * @return	A bool.
	 **************************************************************************************************/

	virtual bool Setup();
	virtual void Destroy();

	bool PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials);
	/**********************************************************************************************//**


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
	void CreateAndRegisterGraphicsCommand(std::shared_ptr<BaseRenderMeshObject> renderObject, UINT element);
};
