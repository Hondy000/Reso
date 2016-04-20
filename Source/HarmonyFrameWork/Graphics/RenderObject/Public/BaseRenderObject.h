#pragma once
#include "../../../Core/Task/Public/TaskInterface.h"
#include "../../../Math/Public/Transform.h"

namespace HFGraphics{
	struct MeshData;
}

class Mesh;


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

protected:
	std::shared_ptr<Mesh> m_mesh;
public:
};



