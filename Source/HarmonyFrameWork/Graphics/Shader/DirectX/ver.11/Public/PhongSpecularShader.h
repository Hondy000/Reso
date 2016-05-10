#pragma once
#include "../../../Basic/Public/BaseShader.h"

/**********************************************************************************************//**
																								* @class	PhongSpecularShader PhongSpecularShader.h
																								* 			Source\HarmonyFrame\Graphics\Shader\DirectX\ver.11\PhongSpecularShader.h
																								*
																								* @brief	A simple polygon 3D shader.
																								*
																								* @author	Kazuyuki Honda
																								* @date	2015/11/05
																								**************************************************************************************************/

class PhongSpecularShader
	:
	public BaseShader
{
public:

	PhongSpecularShader() {};
	~PhongSpecularShader()
	{

	}

	/**********************************************************************************************//**
																									* @fn	virtual bool Setup();
																									*
																									* @brief	èâä˙âª.
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

};
