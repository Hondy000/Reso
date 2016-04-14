#include "../../../Utility/Public/StringUtility.h"
#include "../Public/HFMReader.h"
#include "../../../Graphics/RenderObject/Public/SubMesh.h"
using namespace HFGraphics;

BOOL HFMReader::Read(const std::string& filePath, const std::shared_ptr<MeshData>& object)
{
	HRESULT hr = E_FAIL;
	ReadFileBuffer(filePath);
	m_readOffsetIndex = 0;
	std::string syntaxBuffer;
	std::string numString;

	// メッシュの名前
	m_readOffsetIndex = m_buffer.find("MeshName", m_readOffsetIndex) + strlen("MeshName");

	ReadSubMesh(object);

	return S_OK;
}



BOOL HFMReader::ReadPosition(std::shared_ptr<SubMeshData> meshData)
{
	HRESULT hr = false;
	std::string numString;
	// 頂点数
	m_readOffsetIndex = m_buffer.find("VertexCount", m_readOffsetIndex) + strlen("VertexCount");
	if (m_readOffsetIndex != -1)
	{
		int count;

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToInteger(&count, numString);
		meshData->vertexPositionArray.resize(count);
		if (count)
		{
			hr = true;
		}
		else
		{
			hr = false;
			return hr;
		}
	}

	// VERTEX_POSITION
	m_readOffsetIndex = m_buffer.find("Vertices", m_readOffsetIndex) + strlen("Vertices");
	if (m_readOffsetIndex != 0)
	{
		for (DWORD i = 0; i < meshData->vertexPositionArray.size(); i++)
		{
			HFVECTOR3 position;
			FLOAT w;

			UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

			UTILITY::StringToFloat(&position.x, numString);

			UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

			UTILITY::StringToFloat(&position.y, numString);

			UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

			UTILITY::StringToFloat(&position.z, numString);

			UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

			UTILITY::StringToFloat(&w, numString);
			meshData->vertexPositionArray[i] = (position);
		}

		// 読み込みおかしい
		if (meshData->vertexPositionArray.size())
		{
			hr = true;
		}
		else
		{
			hr = false;
			return hr;
		}
	}

	// POLYGON_VERTEX_COUNT
	m_readOffsetIndex = m_buffer.find("VertexIndexCount", m_readOffsetIndex) + strlen("VertexIndexCount");
	if (m_readOffsetIndex != 0)
	{
		int count;

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToInteger(&count, numString);

		meshData->porygonIndexArray.resize(count);

		if (count)
		{
			hr = true;
		}
		else
		{
			hr = false;
			return hr;
		}
	}

	// POLYGON_INDEX
	m_readOffsetIndex = m_buffer.find("PolygonVertexIndex", m_readOffsetIndex) + strlen("PolygonVertexIndex");
	if (m_readOffsetIndex != 0)
	{
		int count;
		for (DWORD i = 0; i < meshData->porygonIndexArray.size(); i++)
		{
			UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

			UTILITY::StringToInteger(&count, numString);

			meshData->porygonIndexArray[i] = (count);
		}
		if (meshData->porygonIndexArray.size())
		{
			hr = true;
		}
		else
		{
			hr = false;
			return hr;
		}
	}
	return hr;
}

BOOL HFMReader::ReadNormal(std::shared_ptr<SubMeshData> meshData)
{
	std::string numString;
	// NORMAL_COUNT
	m_readOffsetIndex = m_buffer.find("NormalCount", m_readOffsetIndex) + strlen("NormalCount");
	if (m_readOffsetIndex != 0)
	{
		int count;

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToInteger(&count, numString);

		meshData->vertexNormalArray.resize(count);
	}

	m_readOffsetIndex = m_buffer.find("NormalMappingMode", m_readOffsetIndex);
	std::string str;
	UTILITY::ExtractionStringBlockFromSentence
		(
			str,
			m_readOffsetIndex,
			m_buffer,
			std::string("\""),
			std::string("\""),
			m_readOffsetIndex
			);

	meshData->normalMappingMode = StringToMappingMode(str);

	m_readOffsetIndex = m_buffer.find("NormalReferenceMode", m_readOffsetIndex) + strlen("NormalReferenceMode");
	UTILITY::ExtractionStringBlockFromSentence
		(
			str,
			m_readOffsetIndex,
			m_buffer,
			std::string("\""),
			std::string("\""),
			m_readOffsetIndex
			);
	meshData->normalReference = StringToReferenceMode(str);

	// VERTEX_NORMAL
	m_readOffsetIndex = m_buffer.find("NormalVector", m_readOffsetIndex) + strlen("NormalVector");
	if (m_readOffsetIndex != 0)
	{
		for (DWORD i = 0; i < meshData->vertexNormalArray.size(); i++)
		{
			HFVECTOR3 normal;

			UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

			UTILITY::StringToFloat(&normal.x, numString);

			UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

			UTILITY::StringToFloat(&normal.y, numString);

			UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

			UTILITY::StringToFloat(&normal.z, numString);
			meshData->vertexNormalArray[i] = (normal);
		}
	}

	m_readOffsetIndex = m_buffer.find("NormalIndexCount", m_readOffsetIndex) + strlen("NormalIndexCount");
	if (m_readOffsetIndex != 0)
	{
		int count;

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToInteger(&count, numString);

		meshData->normalIndexArray.resize(count);
	}

	// 独自インデックスを持っている場合は取得
	m_readOffsetIndex = m_buffer.find("NormalIndex", m_readOffsetIndex) + strlen("NormalIndex");
	if (m_readOffsetIndex != 0)
	{
		for (DWORD i = 0; i < meshData->normalIndexArray.size(); i++)
		{
			int index;

			UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

			UTILITY::StringToInteger(&index, numString);

			meshData->normalIndexArray[i] = (index);
		}
	}

	return false;
}

BOOL HFMReader::ReadUV(std::shared_ptr<SubMeshData> meshData)
{
	std::string numString;

	m_readOffsetIndex = m_buffer.find("UVMappingMode", m_readOffsetIndex) + strlen("UVMappingMode");
	std::string str;
	UTILITY::ExtractionStringBlockFromSentence
		(
			str,
			m_readOffsetIndex,
			m_buffer,
			std::string("\""),
			std::string("\""),
			m_readOffsetIndex
			);

	meshData->uvMappingMode = StringToMappingMode(str);

	m_readOffsetIndex = m_buffer.find("UVReferenceMode", m_readOffsetIndex) + strlen("UVReferenceMode");
	UTILITY::ExtractionStringBlockFromSentence
		(
			str,
			m_readOffsetIndex,
			m_buffer,
			std::string("\""),
			std::string("\""),
			m_readOffsetIndex
			);
	meshData->uvReference = StringToReferenceMode(str);

	m_readOffsetIndex = m_buffer.find("UVCount", m_readOffsetIndex) + strlen("UVCount");
	if (m_readOffsetIndex != 0)
	{
		int count;

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToInteger(&count, numString);

		meshData->uvArray.resize(count);
	}

	m_readOffsetIndex = m_buffer.find("UVIndexCount", m_readOffsetIndex) + strlen("UVIndexCount");
	if (m_readOffsetIndex != 0)
	{
		int count;

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToInteger(&count, numString);

		meshData->uvIndexArray.resize(count);
	}

	// UV_MAP
	m_readOffsetIndex = m_buffer.find("UVPosition", m_readOffsetIndex) + strlen("UVPosition");
	if (m_readOffsetIndex != 0)
	{
		for (DWORD i = 0; i < meshData->uvArray.size(); i++)
		{
			HFVECTOR2 uv;

			UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

			UTILITY::StringToFloat(&uv.x, numString);

			UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

			UTILITY::StringToFloat(&uv.y, numString);

			meshData->uvArray[i] = (uv);
		}
	}

	m_readOffsetIndex = m_buffer.find("UVMapIndex", m_readOffsetIndex) + strlen("UVMapIndex");
	if (m_readOffsetIndex != 0)
	{
		for (DWORD i = 0; i < meshData->uvIndexArray.size(); i++)
		{
			int index;

			UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

			UTILITY::StringToInteger(&index, numString);

			meshData->uvIndexArray[i] = (index);
		}
	}

	return true;
}

BOOL HFMReader::ReadMaterial(std::shared_ptr<SubMeshData> meshData)
{
	std::string numString;
	m_readOffsetIndex = m_buffer.find("MaterialMappingMode", m_readOffsetIndex) + strlen("MaterialMappingMode");
	std::string str;
	UTILITY::ExtractionStringBlockFromSentence
		(
			str,
			m_readOffsetIndex,
			m_buffer,
			std::string("\""),
			std::string("\""),
			m_readOffsetIndex
			);

	meshData->materialMappingMode = StringToMappingMode(str);

	m_readOffsetIndex = m_buffer.find("MaterialReferenceMode", m_readOffsetIndex) + strlen("MaterialReferenceMode");
	UTILITY::ExtractionStringBlockFromSentence
		(
			str,
			m_readOffsetIndex,
			m_buffer,
			std::string("\""),
			std::string("\""),
			m_readOffsetIndex
			);
	meshData->materialReference = StringToReferenceMode(str);

	m_readOffsetIndex = m_buffer.find("MaterialIndexCount", m_readOffsetIndex);
	if (m_readOffsetIndex != 0)
	{
		int count;

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToInteger(&count, numString);

		meshData->materialIndexArray.resize(count);
	}
	m_readOffsetIndex = m_buffer.find("MaterialIndex", m_readOffsetIndex);
	if (m_readOffsetIndex != 0)
	{
		for (DWORD i = 0; i < meshData->materialIndexArray.size(); i++)
		{
			int index;

			UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

			UTILITY::StringToInteger(&index, numString);

			meshData->materialIndexArray[i] = (index);
		}
	}

	// MATERIAL_COUNT
	m_readOffsetIndex = m_buffer.find("MaterialCount", m_readOffsetIndex) + strlen("MaterialCount");
	if (m_readOffsetIndex != 0)
	{
		int count;

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToInteger(&count, numString);
		meshData->materialArray.resize(count);
	}
	// material
	m_readOffsetIndex = m_buffer.find("MaterialInfomation", m_readOffsetIndex) + strlen("MaterialInfomation");

	for (DWORD i = 0; i < meshData->materialArray.size(); i++)
	{
		HFGraphics::MATERIAL mat;

		// number
		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		int number;
		UTILITY::StringToInteger(&number, numString);

		// name
		std::string materialName;
		int progresIndex;
		UTILITY::ExtractionStringBlockFromSentence
			(
				materialName,
				m_readOffsetIndex,
				m_buffer,
				std::string("\""),
				std::string("\""),
				m_readOffsetIndex);

		// amient

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.ambient.x, numString);

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.ambient.y, numString);

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.ambient.z, numString);
		//ambientFileName
		std::string ambientFileName;

		UTILITY::ExtractionStringBlockFromSentence
			(
				ambientFileName,
				m_readOffsetIndex,
				m_buffer,
				std::string("\""),
				std::string("\""),
				m_readOffsetIndex);

		mat.ambientFileName = ambientFileName;

		// diffuse

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.diffuse.x, numString);

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.diffuse.y, numString);

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.diffuse.z, numString);

		//diffuseFileName
		std::string diffuseFileName;

		UTILITY::ExtractionStringBlockFromSentence
			(
				diffuseFileName,
				m_readOffsetIndex,
				m_buffer,
				std::string("\""),
				std::string("\""),
				m_readOffsetIndex);

		mat.diffuseFileName = diffuseFileName;

		// specular
		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.specular.x, numString);

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.specular.y, numString);

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.specular.z, numString);

		//specularFileName
		std::string specularFileName;

		UTILITY::ExtractionStringBlockFromSentence
			(
				specularFileName,
				m_readOffsetIndex,
				m_buffer,
				std::string("\""),
				std::string("\""),
				m_readOffsetIndex);

		mat.specularFileName = specularFileName;

		// emissive
		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.emissive.x, numString);

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.emissive.y, numString);

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.emissive.z, numString);

		//emissiveFileName
		std::string emissiveFileName;

		UTILITY::ExtractionStringBlockFromSentence
			(
				emissiveFileName,
				m_readOffsetIndex,
				m_buffer,
				std::string("\""),
				std::string("\""),
				m_readOffsetIndex);

		mat.emissiveFileName = emissiveFileName;

		// bump
		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.bump.x, numString);

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.bump.y, numString);

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.bump.z, numString);

		//bumpFileName
		std::string bumpFileName;

		UTILITY::ExtractionStringBlockFromSentence
			(
				bumpFileName,
				m_readOffsetIndex,
				m_buffer,
				std::string("\""),
				std::string("\""),
				m_readOffsetIndex);

		mat.bumpFileName = bumpFileName;

		// reflectivity
		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.reflectivity, numString);
		// shininess
		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.shininess, numString);
		// transparency

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToFloat(&mat.transparency, numString);

		meshData->materialArray[i] = (mat);
	}

	return true;
}

HFGraphics::REFERENCE_MODE HFMReader::StringToReferenceMode(const std::string& str)
{
	if ("eDirect" == str)
	{
		return HFGraphics::REFERENCE_MODE::DIRECT;
	}
	else if ("eIndexToDirect" == str)
	{
		return HFGraphics::REFERENCE_MODE::INDEX;
	}
	else
	{
		return HFGraphics::REFERENCE_MODE::INDEX;
	}
}

HFGraphics::MAPPING_MODE HFMReader::StringToMappingMode(const std::string& str)
{
	if ("eByControlPoint" == str)
	{
		return HFGraphics::MAPPING_MODE::BY_CONTROL_POINT;
	}
	else if ("eByPolygonVertex" == str)
	{
		return HFGraphics::MAPPING_MODE::BY_POLYGON_VERTEX;
	}
	else if ("eByPolygon" == str)
	{
		return HFGraphics::MAPPING_MODE::BY_POLYGON;
	}

	else if ("eAllSame" == str)
	{
		return HFGraphics::MAPPING_MODE::ALL_SAME;
	}
}

BOOL HFMReader::ReadSubMesh(const std::shared_ptr<HFGraphics::MeshData>& object)
{
	HRESULT hr = false;
	std::string numString;
	m_readOffsetIndex = m_buffer.find("MeshCount", m_readOffsetIndex) + strlen("MeshCount");
	if (m_readOffsetIndex != -1)
	{
		int count;

		UTILITY::ExtractionNumbersFromString(&numString, &m_readOffsetIndex, &m_buffer, &m_readOffsetIndex);

		UTILITY::StringToInteger(&count, numString);
		object->submeshArray.resize(count);
		
		
		
		for (int i = 0; i < count;i++)
		{
			object->submeshArray[i] = std::make_shared<SubMeshData>();

			ReadPosition(object->submeshArray[i]);
			ReadNormal(object->submeshArray[i]);
			ReadUV(object->submeshArray[i]);
			ReadMaterial(object->submeshArray[i]);
			
		}
		if (count)
		{
			hr = true;
		}
		else
		{
			hr = false;
			return hr;
		}
	}
	return true;
}