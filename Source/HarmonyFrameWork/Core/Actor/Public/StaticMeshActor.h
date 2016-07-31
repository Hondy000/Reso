#pragma once
#include "ActorInterface.h"
#include "../../../Graphics/RenderObject/Public/StaticMeshObject.h"	
#define CAST_STATIC_MESH_ACTOR(ptr) (std::dynamic_pointer_cast<StaticMeshActor>(ptr))

class StaticMeshActor
	:
	public IActor,
	virtual public StaticMeshObject
{
public:
	StaticMeshActor();
	~StaticMeshActor();
	bool Init();
	bool Update();
	void Reset();
	bool LoadMesh(const std::string& path);
protected:
private:
};
