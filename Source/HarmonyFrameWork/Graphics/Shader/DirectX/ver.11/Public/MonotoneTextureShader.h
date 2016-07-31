/**=================================================================================================
* @file Source\HarmonyFrameWork\Graphics\Shader\DirectX\ver.11\Public\SepiaTextureShader.h
*
* @brief Declares the sepia texture shader class.
*===============================================================================================**/

#pragma once
#include "../../../Basic/Public/BaseShader.h"

class MonotoneTextureShader
	:
	public BaseShader
{
public:
	MonotoneTextureShader();
	~MonotoneTextureShader();

	/**=================================================================================================
	* @fn bool Setup();
	*
	* @brief Setups this object.
	*
	* @author Kazuyuki
	*
	* @return true if it succeeds, false if it fails.
	*===============================================================================================**/

	bool Setup();

	/**=================================================================================================
	* @fn void Destroy();
	*
	* @brief Destroys this object.
	*
	* @author Kazuyuki
	*===============================================================================================**/

	void Destroy();

	/**=================================================================================================
	* @fn bool PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials);
	*
	* @brief Pre process of render.
	*
	* @author Kazuyuki
	*
	* @param shape		 The shape.
	* @param parameter2 The second parameter.
	*
	* @return true if it succeeds, false if it fails.
	*===============================================================================================**/

	bool PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials);

	/**=================================================================================================
	* @fn bool Render();
	*
	* @brief Renders this object.
	*
	* @author Kazuyuki
	*
	* @return true if it succeeds, false if it fails.
	*===============================================================================================**/

	bool Render();

	/**=================================================================================================
	* @fn bool PostProcessOfRender() override;
	*
	* @brief Posts the process of render.
	*
	* @author Kazuyuki
	*
	* @return true if it succeeds, false if it fails.
	*===============================================================================================**/

	bool PostProcessOfRender() override;


};
