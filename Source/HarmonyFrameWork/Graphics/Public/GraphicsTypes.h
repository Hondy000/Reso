#pragma once
#include "../../Math/Public/HFMath.h"
#include <string>					
#include <vector>
#include <list>

namespace HFGraphics 
{
#define HF_SEMANTICS_POSITION (1)
#define HF_SEMANTICS_NORMAL (HF_SEMANTICS_POSITION << 1)
#define HF_SEMANTICS_TEXCOORD0 (HF_SEMANTICS_NORMAL << 1)
#define HF_SEMANTICS_DIFFUSE (HF_SEMANTICS_TEXCOORD0 << 1)
#define HF_SEMANTICS_AMBIENT (HF_SEMANTICS_DIFFUSE << 1)	  
#define HF_SEMANTICS_SPECULAR (HF_SEMANTICS_AMBIENT << 1)
#define HF_SEMANTICS_EMISSIVE (HF_SEMANTICS_SPECULAR << 1)	 
#define HF_SEMANTICS_MATRIX0 (HF_SEMANTICS_EMISSIVE << 1)

// Directx111のシェーダ識別
#define HF_D3D11_VERTEX_SHADER (1)
#define HF_D3D11_HULL_SHADER (HF_D3D11_VERTEX_SHADER << 1)
#define HF_D3D11_DOMAIN_SHADER (HF_D3D11_HULL_SHADER << 1)		
#define HF_D3D11_GEOMETRY_SHADER (HF_D3D11_DOMAIN_SHADER << 1) 
#define HF_D3D11_PIXEL_SHADER (HF_D3D11_GEOMETRY_SHADER << 1)
#define HF_D3D11_COMPUTE_SHADER (HF_D3D11_PIXEL_SHADER << 1)

#define HF_DEFERRED_RENDERING_SHADER (0)
#define HF_LIGHTING_PATH_OF_DEFERRED_RENDERING ((DWORD_MAX>>1))
#define HF_POST_DEFERRED_RENDERING_SHADER ((DWORD_MAX>>1)+1)	   
#define HF_FORWARD_RENDERING_SHADER ((DWORD_MAX>>1)+500)					  
#define HF_2D_RENDERING_SHADER ((DWORD_MAX>>1)+5000)


	enum class MAPPING_MODE
	{
		BY_CONTROL_POINT,	// 頂点単位
		BY_POLYGON_VERTEX,	// ポリゴンで指定されるインデックス単位で割当
		BY_POLYGON,			// ポリゴン単位で割当
		ALL_SAME,	// 全てに割当
	};

	enum class REFERENCE_MODE
	{
		DIRECT,				// 位置インデックスに依存
		INDEX,				// 独自のインデックスに依存
	};

	enum class MATERIAL_ELEMENT
	{
		AMBIENT,
		DIFFUSE,
		SPECULAR,
		EMISSIVE,
	};

	typedef struct MATERIAL
	{

		HFVECTOR3 ambient;
		HFVECTOR3 diffuse;
		HFVECTOR3 specular;
		HFVECTOR3 emissive;
		HFVECTOR3 bump;
		FLOAT reflectivity;	  // 反射率
		FLOAT shininess;	  // 輝度
		FLOAT transparency;	  // 透明度
		std::string ambientFileName;
		std::string diffuseFileName;
		std::string specularFileName;
		std::string emissiveFileName;
		std::string bumpFileName;

		HFVECTOR4 GetVec4Element(MATERIAL_ELEMENT elem)
		{
			switch (elem)
			{
			case MATERIAL_ELEMENT::AMBIENT:
			{
				return HFVECTOR4(ambient, transparency);
			}
			break;
			case MATERIAL_ELEMENT::DIFFUSE:
				return HFVECTOR4(diffuse, transparency);
			case MATERIAL_ELEMENT::SPECULAR:
				return HFVECTOR4(ambient, reflectivity);
			case MATERIAL_ELEMENT::EMISSIVE:
				return HFVECTOR4(specular, shininess);
			default: break;
			}
		}
	};


	struct LineData
	{
		std::vector<HFVECTOR3> positions;
	};

	struct LineDataEx
		:
		public LineData
	{
		std::vector<UINT> indexArray;
		std::vector<MATERIAL> materialArray;
		std::vector<UINT> materialIndexArray;

		MAPPING_MODE materialMappingMode;
		REFERENCE_MODE materialReference;

		std::vector<HFVECTOR2> uvArray;
		std::vector<UINT> uvIndexArray;

		MAPPING_MODE uvMappingMode;
		REFERENCE_MODE uvReference;
	};

	struct SubMeshData
	{
		std::string name;
		std::vector<HFVECTOR3> vertexPositionArray;
		std::vector<UINT> porygonIndexArray;

		std::vector<HFVECTOR3> vertexNormalArray;
		std::vector<UINT> normalIndexArray;
		MAPPING_MODE normalMappingMode;
		REFERENCE_MODE normalReference;

		std::vector<MATERIAL> materialArray;
		std::vector<UINT> materialIndexArray;

		MAPPING_MODE materialMappingMode;
		REFERENCE_MODE materialReference;

		std::vector<HFVECTOR2> uvArray;
		std::vector<UINT> uvIndexArray;

		MAPPING_MODE uvMappingMode;
		REFERENCE_MODE uvReference;

		void CreatePolygonIndex(std::vector<UINT>&);
		void CreatePositionElement(std::vector<HFVECTOR3>&);

		void CreateNormalElement(std::vector<HFVECTOR3>&);

		void CreateMaterialVec4Element(std::vector<HFVECTOR4>&, MATERIAL_ELEMENT);

		void CreateTexElement(std::vector<HFVECTOR2>&);
	};

	struct MeshData
	{

		std::string name;
		std::vector<std::shared_ptr<SubMeshData>> submeshArray;

	};
};