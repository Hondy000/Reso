#pragma once
#include <fstream>
#include "../../../IO/Public/IBaseReader.h"
#include "../../../Graphics/Public/GraphicsTypes.h"

class HFMReader :
	public BaseReader<HFGraphics::MeshData>
{
public:
	HFMReader()
	{
	};

	~HFMReader()
	{
	};
	bool Read(const std::string&, const std::shared_ptr<HFGraphics::MeshData>& object);
	//bool Load(const std::string& path,const std::shared_ptr<MeshShape>& object);

	bool ReadPosition(std::shared_ptr<HFGraphics::SubMeshData> meshData);
	bool ReadNormal(std::shared_ptr<HFGraphics::SubMeshData> meshData);
	bool ReadUV(std::shared_ptr<HFGraphics::SubMeshData> meshData);
	bool ReadMaterial(std::shared_ptr<HFGraphics::SubMeshData> meshData);
	// Access the SrcMesh

	HFGraphics::REFERENCE_MODE StringToReferenceMode(const std::string&);

	HFGraphics::MAPPING_MODE StringToMappingMode(const std::string & str);
	bool ReadSubMesh(const std::shared_ptr<HFGraphics::MeshData>& object);
private:
};
