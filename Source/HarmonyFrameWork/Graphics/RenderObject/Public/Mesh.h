#pragma once	
#include "../../../Core/Public/IBaseObject.h"		 
#include "../../Public/GraphicsTypes.h"
#include "SubMesh.h"

class Mesh
	:
	public IBaseObject,
	public inheritable_enable_shared_from_this<Mesh>
{
public:
	Mesh() {};
	~Mesh() {};

	// Access the SubMeshArray
	std::vector<std::shared_ptr<SubMesh>>& GetSubMeshArray(void)
	{
		return(m_subMeshArray);
	};
	void SetSubMeshArray(const std::vector<std::shared_ptr<SubMesh>>& subMeshArray)
	{
		m_subMeshArray = subMeshArray;
	};

protected:
	std::vector<std::shared_ptr<SubMesh>> m_subMeshArray;
};
