#pragma once
#include "../../Math/Public/HFMath.h"	
#include "../../Utility/Public/HFString.h"
#include <string>					
#include <vector>
#include <list>

namespace HFGraphics 
{

// Directx111のシェーダ識別
#define HF_D3D11_VERTEX_SHADER (1)
#define HF_D3D11_HULL_SHADER (HF_D3D11_VERTEX_SHADER << 1)
#define HF_D3D11_DOMAIN_SHADER (HF_D3D11_HULL_SHADER << 1)		
#define HF_D3D11_GEOMETRY_SHADER (HF_D3D11_DOMAIN_SHADER << 1) 
#define HF_D3D11_PIXEL_SHADER (HF_D3D11_GEOMETRY_SHADER << 1)
#define HF_D3D11_COMPUTE_SHADER (HF_D3D11_PIXEL_SHADER << 1)

#define HF_SHADOW_MAPPING_SHADER (0)		
#define HF_POST_SHADOW_MAPPING_SHADER (1)
#define HF_DEFERRED_RENDERING_SHADER ((DWORD_MAX>>1)-1)
#define HF_LIGHTING_PATH_OF_DEFERRED_RENDERING ((DWORD_MAX>>1))
#define HF_POST_DEFERRED_RENDERING_SHADER ((DWORD_MAX>>1)+1)	   
#define HF_FORWARD_RENDERING_SHADER ((DWORD_MAX>>1)+500)					  
#define HF_2D_RENDERING_SHADER ((DWORD_MAX>>1)+5000)


	typedef enum INPUT_CLASSIFICATION
	{
		INPUT_PER_VERTEX_DATA = 0,
		INPUT_PER_INSTANCE_DATA = 1,
	} INPUT_CLASSIFICATION;

	struct BufferSemantics 
	{
		HFString semanticsName;
		UINT semanticsIndex;
		UINT alignedByteOffset;
		INPUT_CLASSIFICATION inputSlotClass;
		UINT instanceDataStepRate;
		BufferSemantics()
		{

		}

		BufferSemantics
		(
			HFString _semanticsName,
			UINT _semanticsIndex,
			UINT _alignedByteOffset,
			INPUT_CLASSIFICATION _inputSlotClass,
			UINT _instanceDataStepRate
		)
			:
			semanticsName(_semanticsName),
			semanticsIndex(_semanticsIndex),
			alignedByteOffset(_alignedByteOffset),
			inputSlotClass(_inputSlotClass),
			instanceDataStepRate(_instanceDataStepRate)
		{
		}
		BufferSemantics
		(
			TCHAR* _semanticsName,
			UINT _semanticsIndex,
			UINT _alignedByteOffset,
			INPUT_CLASSIFICATION _inputSlotClass,
			UINT _instanceDataStepRate
		)
			:
			semanticsName(_semanticsName),
			semanticsIndex(_semanticsIndex),
			alignedByteOffset(_alignedByteOffset),
			inputSlotClass(_inputSlotClass),
			instanceDataStepRate(_instanceDataStepRate)
		{
		}


		bool operator == (BufferSemantics layout)
		{
			if( this->semanticsName == layout.semanticsName &&
				this->semanticsIndex == layout.semanticsIndex &&
				this->alignedByteOffset == layout.alignedByteOffset &&
				this->inputSlotClass == layout.inputSlotClass	)
			{
				return true;
			}
			else
			{
				return false;
			}
		}


		bool operator != (BufferSemantics layout)
		{
			if (this->semanticsName != layout.semanticsName ||
				this->semanticsIndex != layout.semanticsIndex ||
				this->alignedByteOffset != layout.alignedByteOffset ||
				this->inputSlotClass != layout.inputSlotClass)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};

	struct BufferLayout
	{
		std::vector<BufferSemantics> m_semanticsArray;

		bool operator ==(BufferLayout _layout)
		{
			// バッファ内の頂点情報数が一致しているか
			if(m_semanticsArray.size() == _layout.m_semanticsArray.size())
			{

				for (int i = 0;i < m_semanticsArray.size();i++)
				{
					// 頂点情報の一致を確認
					if(m_semanticsArray[i] != _layout.m_semanticsArray[i])
					{
						// 
						return false;
					}
				}
				return true;
			}
			else
			{
				return false;
			}

		}
	};

	struct MeshShaderBufferLayout
	{
		std::vector<BufferLayout> m_bufferLayoutArray;
		void AddBufferLayout(BufferLayout _layout)
		{
			m_bufferLayoutArray.push_back(_layout);
		}

		void AddBufferSemantics(UINT _bufferArrayElement,BufferSemantics _semantics)
		{
			if(m_bufferLayoutArray.size() <= _bufferArrayElement)
			{
				m_bufferLayoutArray.resize(_bufferArrayElement + 1);
			}
			m_bufferLayoutArray[_bufferArrayElement].m_semanticsArray.push_back(_semantics);
	
		}

		void AddBufferSemantics
		(
			UINT _bufferArrayElement,
			TCHAR* _semanticsName,
			UINT _semanticsIndex,
			UINT _alignedByteOffset,
			INPUT_CLASSIFICATION _inputSlotClass,
			UINT _instanceDataStepRate
		)
		{
			if (m_bufferLayoutArray.size() <= _bufferArrayElement)
			{
				m_bufferLayoutArray.resize(_bufferArrayElement + 1);
			}
			m_bufferLayoutArray[_bufferArrayElement].m_semanticsArray.push_back
				(
					HFGraphics::BufferSemantics(
						_semanticsName,
						_semanticsIndex,
						_alignedByteOffset,
						_inputSlotClass,
						_instanceDataStepRate
					)
				);

		}
	};

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
				return HFVECTOR4(ambient.x, ambient.y, ambient.z, transparency);
			}
			break;
			case MATERIAL_ELEMENT::DIFFUSE:
				return HFVECTOR4(diffuse.x, diffuse.y, diffuse.z, transparency);
			case MATERIAL_ELEMENT::SPECULAR:
				return HFVECTOR4(specular.x, specular.y, specular.z, reflectivity);
			case MATERIAL_ELEMENT::EMISSIVE:
				return HFVECTOR4(emissive.x, emissive.y, emissive.z, shininess);
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
		std::vector<uint32_t> indexArray;
		std::vector<MATERIAL> materialArray;
		std::vector<uint32_t> materialIndexArray;

		MAPPING_MODE materialMappingMode;
		REFERENCE_MODE materialReference;

		std::vector<HFVECTOR2> uvArray;
		std::vector<uint32_t> uvIndexArray;

		MAPPING_MODE uvMappingMode;
		REFERENCE_MODE uvReference;
	};

	// バッファに取り込ませるためのサブメッシュデータ
	struct SubMeshData
	{
		std::string name;
		std::vector<HFVECTOR3> vertexPositionArray;
		std::vector<uint32_t> porygonIndexArray;

		std::vector<HFVECTOR3> vertexNormalArray;
		std::vector<HFVECTOR4> biNormalArray;
		std::vector<uint32_t> normalIndexArray;
		MAPPING_MODE normalMappingMode;
		REFERENCE_MODE normalReference;

		std::vector<MATERIAL> materialArray;
		std::vector<uint32_t> materialIndexArray;

		MAPPING_MODE materialMappingMode;
		REFERENCE_MODE materialReference;

		std::vector<HFVECTOR2> uvArray;
		std::vector<uint32_t> uvIndexArray;

		MAPPING_MODE uvMappingMode;
		REFERENCE_MODE uvReference;

		void CreatePolygonIndex(std::vector<uint32_t>&);
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