////////////////////////////////////////////////////////////////////////////////
// Filename: deferredshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _DEFERREDSHADERCLASS_H_
#define _DEFERREDSHADERCLASS_H_

#include "../../../Basic/Public/BaseGraphicsShader.h"

struct MeshData;
class BaseRenderMeshObject;

////////////////////////////////////////////////////////////////////////////////
// Class name: DeferredShaderClass
////////////////////////////////////////////////////////////////////////////////
class DeferredShader
	:
	public BaseGraphicsShader
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
	void CreateAndRegisterGraphicsCommand(std::shared_ptr<BaseRenderMeshObject> renderObject, UINT element);
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

#endif