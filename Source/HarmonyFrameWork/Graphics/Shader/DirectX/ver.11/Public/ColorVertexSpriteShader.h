#pragma once
#include "..\..\..\Basic\Public\BaseGraphicsShader.h"

class ColorVertexShader
	:
	public BaseGraphicsShader
{
public:
	ColorVertexShader();
	~ColorVertexShader();
	bool Setup();
	void Destroy();

	bool PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials);

	/***********************************************************************************************
	 * Renders this object.
	 *
	 * @author Kazuyuki Honda
	 * @date 2015/11/03
	 *
	 * @return A bool.
	 *************************************************************************************************/

	bool Render();

	/***********************************************************************************************
	 * Posts the render process.
	 *
	 * @author Kazuyuki Honda
	 * @date 2015/11/04
	 *
	 * @return A bool.
	 *************************************************************************************************/

	bool PostProcessOfRender() override;

	/***********************************************************************************************
	 * シェーダを実行するグラフィックスコマンドを生成し登録.
	 *
	 * @author Kazuyuki
	 *
	 * @param parameter1 The first parameter.
	 *
	 * @return true if it succeeds, false if it fails.
	 *************************************************************************************************/

	virtual void CreateAndRegisterGraphicsCommand(std::shared_ptr<BaseRenderMeshObject> renderObject, UINT element);


};
