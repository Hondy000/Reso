#pragma once
#include "..\..\..\Basic\Public\BaseShader.h"
class SpecularPhongShader
	:
	public BaseShader
{
private:
	struct MatrixBufferType
	{
		HFMATRIX world;
		HFMATRIX view;
		HFMATRIX projection;
	};



	struct MaterialBufferType
	{
		HFVECTOR4 ambient;
		HFVECTOR4 diffuse;
		HFVECTOR4 emissive;
		HFVECTOR4 specular;
		float power;	
		float range;
		HFVECTOR2 dummy;
	};

	struct VERTEX
	{
		HFVECTOR3 pos;
		HFVECTOR3 normal;
		HFVECTOR2 tex;

		//	HFVECTOR4 ambient;
		//	HFVECTOR4 diffuse;
		//	HFVECTOR4 specular;
		//	HFVECTOR4 emissive;
	};

public:
	SpecularPhongShader();
	SpecularPhongShader(const SpecularPhongShader&);
	~SpecularPhongShader();

	bool Setup();
	void Destroy();

	/**********************************************************************************************//**
																									* @fn	bool PreRenderProcess(std::shared_ptr<BASE_PRAM>);
																									*
																									* @brief	Pre render process.
																									*
																									* @author	Kazuyuki Honda
																									* @date	2015/11/03
																									*
																									* @param	parameter1	The first parameter.
																									*
																									* @return	A bool.
																									**************************************************************************************************/


	bool PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials);
	/**********************************************************************************************//**
																									* @fn	virtual bool Render() = 0;
																									*
																									* @brief	Renders this object.
																									*
																									* @author	Kazuyuki Honda
																									* @date	2015/11/03
																									*
																									* @return	A bool.
																									**************************************************************************************************/

	bool Render();

	bool PostProcessOfRender();
private:

	int m_indexCount;
};
