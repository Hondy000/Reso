#pragma once
#include "../../../Basic/Public/BaseGraphicsShader.h"

class DeferredShader;

class LineShader
	:
	public BaseGraphicsShader
{
private:
	struct MatrixBufferType
	{
		HFMATRIX wvp;
	};

	struct VERTEX
	{
		HFVECTOR3 pos;
	};

public:
	LineShader();
	LineShader(const LineShader&);
	~LineShader();

	bool Setup();
	void Destroy();

	/**********************************************************************************************//**
	 * @fn	bool PreProcessOfRender(std::shared_ptr<CBaseObject>);
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
	 * @fn	bool Render();
	 *
	 * @brief	Renders this object.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 *
	 * @return	A bool.
	 **************************************************************************************************/

	bool Render();

	bool PostProcessOfRender()
	{
		return S_OK;
	};

private:
	int m_indexCount;
};
