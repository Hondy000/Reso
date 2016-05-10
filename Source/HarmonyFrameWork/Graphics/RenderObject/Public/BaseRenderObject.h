#pragma once
#include "../../../Core/Task/Public/TaskInterface.h"
#include "../../../Math/Public/Transform.h"

namespace HFGraphics{
	struct MeshData;
}

class Mesh;
class Material;
class IBaseTexture;
class BaseShader;
class BaseRenderObject
	:
	virtual public IBaseTask
{
public:
	BaseRenderObject()
	{
	}


	virtual~BaseRenderObject()
	{
	}
	virtual bool Init() = 0;


	virtual bool Setup()
	{
		return S_OK;
	};


	virtual bool Update() = 0;

	virtual bool Render();
	


	// Access the Mesh
	const std::shared_ptr<Mesh>& GetMesh(void) const
	{
		return(m_mesh);
	};
	void SetMesh(const std::shared_ptr<Mesh>& mesh)
	{
		m_mesh = mesh;
	};

	void SetSubMeshMaterial(UINT submeshNum, std::shared_ptr<Material> material);
	const std::shared_ptr<Material>& GetSubMeshMaterial(UINT submeshNum);

	void SetMaterialDiffuseTexture(UINT submeshNum,std::shared_ptr<IBaseTexture> texture);
	const std::shared_ptr<IBaseTexture>& GetMaterialDiffuseTexture(UINT submeshNum);

	void SetMaterialShader(UINT submeshNum, std::shared_ptr<BaseShader> shader);
	const std::shared_ptr<BaseShader>& GetMaterialShader(UINT submeshNum);

	bool LoadDiffuseTexture2D(UINT submeshNum, HFString teturePath);

protected:
	std::shared_ptr<Mesh> m_mesh;
public:
};



