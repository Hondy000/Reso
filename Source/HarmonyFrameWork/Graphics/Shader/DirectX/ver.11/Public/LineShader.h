#pragma once
#include "../../../Basic/Public/BaseShader.h"

class DeferredShader;

class LineShader
	:
	public BaseShader
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

	BOOL Setup();
	void Destroy();

	/**********************************************************************************************//**
	 * @fn	BOOL PreProcessOfRender(std::shared_ptr<CBaseObject>);
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
	 * @fn	BOOL Render();
	 *
	 * @brief	Renders this object.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/03
	 *
	 * @return	A BOOL.
	 **************************************************************************************************/

	BOOL Render();

	BOOL PostProcessOfRender()
	{
		return S_OK;
	};

private:
	int m_indexCount;
};
