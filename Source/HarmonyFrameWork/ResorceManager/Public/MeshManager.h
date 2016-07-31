#pragma once
#include "../../Core/Public/ManagerInterface.h"
#include "MeshFactory.h"

class Mesh;
class MeshManager
	:
	public GeneralResourceManager<Mesh>
{
private:
	MeshManager() {};

public:
	static MeshManager* GetInstance()
	{
		static MeshManager instance;
		return &instance;
	}

private:

	std::shared_ptr<Mesh>  RequestCreate(const std::string& path)
	{
		return MeshFactory::GetInstance()->Create(path);
	}
};


