#pragma once
#include "../../../Core/Task/Public/TaskInterface.h"
#include "../../../Math/Public/Transform.h"
#include "..\..\Public\BaseGraphicsObject.h"

namespace HFGraphics{
	struct MeshData;
}

class Mesh;
class Material;
class IBaseTexture;
class BaseGraphicsShader;
class BaseGraphicsCommand;


// メッシュやシェーダーを包括し描画に使用するオブジェクト
class BaseRenderMeshObject
	:
	virtual public IBaseTask,
	public BaseGraphicsObject,
	public inheritable_enable_shared_from_this<BaseRenderMeshObject>
{
public:
	BaseRenderMeshObject()
		:
		m_enableRender(true)
	{
	}


	virtual~BaseRenderMeshObject()
	{
	}
	virtual bool Init() = 0;


	virtual bool Setup();


	virtual bool Update();

	virtual bool RenderSubMesh(int elem);
	


	// Access the Mesh
	const std::shared_ptr<Mesh>& GetMesh(void) const;
	void SetMesh(const std::shared_ptr<Mesh>& mesh);

	void SetSubMeshMaterial(UINT submeshNum, std::shared_ptr<Material> material);
	const std::shared_ptr<Material>& GetSubMeshMaterial(UINT submeshNum);

	void SetMaterialDiffuseTexture(UINT submeshNum,std::shared_ptr<IBaseTexture> texture);
	const std::shared_ptr<IBaseTexture>& GetMaterialDiffuseTexture(UINT submeshNum);

	void SetMaterialShader(UINT submeshNum, std::shared_ptr<BaseGraphicsShader> shader);
	const std::shared_ptr<BaseGraphicsShader>& GetMaterialShader(UINT submeshNum);

	bool LoadDiffuseTexture2D(UINT submeshNum, HFString teturePath);
	protected:
	std::shared_ptr<Mesh> m_mesh;
	bool m_enableRender;

public:
};



