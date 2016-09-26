#pragma once
#include "..\..\..\Basic\Public\BaseGraphicsShader.h"

class FowardDiffuseOnlyMeshShader
	:
	public BaseGraphicsShader
{
public:
	FowardDiffuseOnlyMeshShader();
	~FowardDiffuseOnlyMeshShader();

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
	void CreateAndRegisterGraphicsCommand(std::shared_ptr<BaseRenderMeshObject> renderObject, UINT element);
private:

};
