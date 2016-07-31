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
	virtual public IBaseTask   ,
	public inheritable_enable_shared_from_this<BaseRenderObject>
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

	virtual bool RenderSubMesh(int elem);
	


	// Access the Mesh
	const std::shared_ptr<Mesh>& GetMesh(void) const;
	void SetMesh(const std::shared_ptr<Mesh>& mesh);

	void SetSubMeshMaterial(UINT submeshNum, std::shared_ptr<Material> material);
	const std::shared_ptr<Material>& GetSubMeshMaterial(UINT submeshNum);

	void SetMaterialDiffuseTexture(UINT submeshNum,std::shared_ptr<IBaseTexture> texture);
	const std::shared_ptr<IBaseTexture>& GetMaterialDiffuseTexture(UINT submeshNum);

	void SetMaterialShader(UINT submeshNum, std::shared_ptr<BaseShader> shader);
	const std::shared_ptr<BaseShader>& GetMaterialShader(UINT submeshNum);

	bool LoadDiffuseTexture2D(UINT submeshNum, HFString teturePath);

private:
	std::shared_ptr<Mesh> m_mesh;
public:
};



