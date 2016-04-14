/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\Shader\DirectX\ver.11\SimplePolygon3DShader.h
 *
 * @brief	Declares the simple polygon 3D shader class.
 **************************************************************************************************/

#pragma once
#include "../../../Basic/Public/BaseShader.h"

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
	public BaseShader
{
public:

	SimplePolygon3DShader() {};
	~SimplePolygon3DShader()
	{

	}

	/**********************************************************************************************//**
	 * @fn	virtual BOOL Setup();
	 *
	 * @brief	初期化.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 *
	 * @return	A BOOL.
	 **************************************************************************************************/

	virtual BOOL Setup();
	virtual void Destroy();

	BOOL PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials);
	/**********************************************************************************************//**


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
