#pragma once	
#include "../../../Core/Public/IBaseObject.h"		 
#include "../../Public/GraphicsTypes.h"
#include "SubMesh.h"
class BaseRenderMeshObject;

class Mesh
	:
	public IBaseObject,
	public inheritable_enable_shared_from_this<Mesh>
{
public:
	Mesh();
	~Mesh();

	// Access the SubMeshArray
	std::vector<std::shared_ptr<SubMesh>>& GetSubMeshArray(void);

	void SetSubMeshArray(const std::vector<std::shared_ptr<SubMesh>>& subMeshArray);

	bool LoadDiffuseTexture2D(UINT submeshNum,HFString teturePath);


	std::weak_ptr<BaseRenderMeshObject> GetParentObject() const;

	void SetParentObject(std::shared_ptr<BaseRenderMeshObject>& _val);

protected:
	std::vector<std::shared_ptr<SubMesh>> m_subMeshArray;
	std::weak_ptr<BaseRenderMeshObject> m_parentObject;
};

