#pragma once
#include "CompornentInterface.h"
#include "..\..\..\Graphics\RenderObject\Public\StaticMeshObject.h"

#define CAST_STATIC_MESH_COMPORNENT(compornent) (std::dynamic_pointer_cast<StaticMeshCompornent>(compornent))



class StaticMeshCompornent
	:
	public ICompornent,
	public StaticMeshObject
{
public: 
	StaticMeshCompornent() {};
	~StaticMeshCompornent() {};
	void Destroy(){};
	BOOL Init();
	void Reset() {};
	BOOL LoadMesh(const std::string& path);
	BOOL Update();

private:
};

