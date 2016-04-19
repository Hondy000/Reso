////////////////////////////////////////////////////////////////////////////////
// Filename: deferredshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _DEFERREDSHADERCLASS_H_
#define _DEFERREDSHADERCLASS_H_

#include "../../../Basic/Public/BaseShader.h"

struct MeshData;
class BaseRenderObject;

////////////////////////////////////////////////////////////////////////////////
// Class name: DeferredShaderClass
////////////////////////////////////////////////////////////////////////////////
class DeferredShader
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
	DeferredShader();
	DeferredShader(const DeferredShader&);
	~DeferredShader();

	BOOL Setup();
	void Destroy();

	/**********************************************************************************************//**
	 * @fn	BOOL PreRenderProcess(std::shared_ptr<BASE_PRAM>);
	 *
	 * @brief	Pre render process.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 *
	 * @param	parameter1	The first parameter.
	 *
	 * @return	A BOOL.
	 **************************************************************************************************/


	BOOL PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials);
	/**********************************************************************************************//**
	 * @fn	virtual BOOL Render() = 0;
	 *
	 * @brief	Renders this object.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 *
	 * @return	A BOOL.
	 **************************************************************************************************/

	BOOL Render();

	BOOL PostProcessOfRender();
private:

	int m_indexCount;
};

#endif