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
	BOOL Init();
	BOOL Update();
	void Reset();
	BOOL LoadMesh(const std::string& path);
protected:
private:
};
