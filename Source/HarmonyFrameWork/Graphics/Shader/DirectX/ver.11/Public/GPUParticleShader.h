#pragma once
#include "..\..\..\Basic\Public\BaseGraphicsShader.h"

class GPUParticleShader
	:
	public BaseGraphicsShader
{
private:

public:

	/**=================================================================================================
	* @fn ParticleShader();
	*
	* @brief Initializes a new instance of the ParticleShader class.
	*
	* @author Kazuyuki
	*===============================================================================================**/

	GPUParticleShader();

	/**=================================================================================================
	* @fn ParticleShader(const ParticleShader&);
	*
	* @brief Initializes a new instance of the ParticleShader class.
	*
	* @author Kazuyuki
	*
	* @param parameter1 The first parameter.
	*===============================================================================================**/

	GPUParticleShader(const GPUParticleShader&);

	/**=================================================================================================
	* @fn ~ParticleShader();
	*
	* @brief Finalizes an instance of the ParticleShader class.
	*
	* @author Kazuyuki
	*===============================================================================================**/

	~GPUParticleShader();

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

	bool PreProcessOfRender(std::shared_ptr<SubMesh> mesh, std::shared_ptr<Material>materials);

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

	bool PostProcessOfRender();

	void CreateAndRegisterGraphicsCommand(std::shared_ptr<BaseRenderMeshObject> renderObject, UINT element);
private:
	/** @brief Number of indexes. */
	int m_instanceCount;
};