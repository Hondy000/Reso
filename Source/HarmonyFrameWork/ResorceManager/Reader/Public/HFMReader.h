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
	BOOL Read(const std::string&, const std::shared_ptr<HFGraphics::MeshData>& object);
	//BOOL Load(const std::string& path,const std::shared_ptr<MeshShape>& object);

	BOOL ReadPosition(std::shared_ptr<HFGraphics::SubMeshData> meshData);
	BOOL ReadNormal(std::shared_ptr<HFGraphics::SubMeshData> meshData);
	BOOL ReadUV(std::shared_ptr<HFGraphics::SubMeshData> meshData);
	BOOL ReadMaterial(std::shared_ptr<HFGraphics::SubMeshData> meshData);
	// Access the SrcMesh

	HFGraphics::REFERENCE_MODE StringToReferenceMode(const std::string&);

	HFGraphics::MAPPING_MODE StringToMappingMode(const std::string & str);
	BOOL ReadSubMesh(const std::shared_ptr<HFGraphics::MeshData>& object);
private:
};
