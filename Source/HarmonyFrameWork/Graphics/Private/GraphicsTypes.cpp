/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Graphics\Private\GraphicsTypes.cpp
 *
 * @brief	Implements the graphics types class.
 **************************************************************************************************/

#include "../Public/GraphicsTypes.h"

namespace HFGraphics 
{
	void SubMeshData::CreatePolygonIndex(std::vector<uint32_t>& indices)
	{
		if (uvIndexArray.size() != porygonIndexArray.size())
		{
			indices = porygonIndexArray;
			return;
		}
		// インデックス頂点ごとに情報が必要
		// 頂点はインデックスで展開済みなのでインデックスは0から順番
		indices.resize(porygonIndexArray.size());
		for (int i = 0; i < porygonIndexArray.size(); i++)
		{
			indices[i] = i;
		}
	}

	/**********************************************************************************************//**
																									* @fn	const std::vector<HFVECTOR3>& MESH_BASE_DATA::CreatePositionElement()
																									*
																									* @brief	Creates position element.
																									*
																									* @author	Kazuyuki Honda
																									* @date	2015/11/04
																									*
																									* @return	The new position element.
																									**************************************************************************************************/

	void SubMeshData::CreatePositionElement(std::vector<HFVECTOR3>& positions)
	{
		if (uvIndexArray.size() != porygonIndexArray.size())
		{
			positions = this->vertexPositionArray;
			return;
		}
		// インデックス頂点ごとに情報が必要
		positions.resize(porygonIndexArray.size());
		for (int i = 0; i < porygonIndexArray.size(); i++)
		{
			positions[i] = vertexPositionArray[porygonIndexArray[i]];
		}
	}

	/**********************************************************************************************//**
																									* @fn	const std::vector<HFVECTOR2>& MESH_BASE_DATA::CreateTexElement()
																									*
																									* @brief	Creates tex element.
																									*
																									* @author	Kazuyuki Honda
																									* @date	2015/11/04
																									*
																									* @return	The new tex element.
																									**************************************************************************************************/

	void SubMeshData::CreateTexElement(std::vector<HFVECTOR2>& texcoords)
	{
		switch (uvMappingMode)
		{
			// 頂点単位で割当
		case MAPPING_MODE::BY_CONTROL_POINT:
		{
			switch (uvReference)
			{
			case REFERENCE_MODE::DIRECT:

				texcoords.resize(vertexPositionArray.size());
				for (int i = 0; i < texcoords.size(); i++)
				{
					texcoords[i] = uvArray[normalIndexArray[i]];
				}
				break;
			case REFERENCE_MODE::INDEX:
				texcoords.resize(vertexPositionArray.size());
				for (int i = 0; i < texcoords.size(); i++)
				{
					texcoords[i] = uvArray[uvIndexArray[i]];
				}
				break;
			default:
				break;
			}
			break;
		}
		// ポリゴンで扱う頂点ごとに法線1つ割当(同じ位置情報でもポリゴンごとに変える)
		case MAPPING_MODE::BY_POLYGON_VERTEX:
		{
			switch (uvReference)
			{
				// 直接法線を取得
			case REFERENCE_MODE::DIRECT:
				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				texcoords.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < uvArray.size(); i++)
				{
					texcoords[i] = uvArray[i];
				}
				break;
				// インデックスを見て法線を取得
			case REFERENCE_MODE::INDEX:

				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				texcoords.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));

				// 元の配列が同数ならインデックスは不要

				for (int i = 0; i < uvArray.size(); i++)
				{
					texcoords[i] = uvArray[i];
				}

				break;
			default:
				break;
			}
			break;
		}
		// ポリゴン単位
		case MAPPING_MODE::BY_POLYGON:
		{
			switch (uvReference)
			{					// 直接法線を取得
			case REFERENCE_MODE::DIRECT:
				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				texcoords.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < uvArray.size(); i++)
				{
					for (int j = 0; j < 3; j++)
					{
						texcoords[i] = uvArray[i];
					}
				}
				break;
				// インデックスを見て法線を取得
			case REFERENCE_MODE::INDEX:

				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				texcoords.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < uvIndexArray.size(); i++)
				{
					for (int j = 0; j < 3; j++)
					{
						texcoords[i * 3 + j] = uvArray[uvIndexArray[i]];
					}
				}
				break;
			default:
				break;
			}
			break;
		}
		// メッシュ全体
		case MAPPING_MODE::ALL_SAME:
		{
			switch (uvReference)
			{					// 直接法線を取得
			case REFERENCE_MODE::DIRECT:
				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				texcoords.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < uvArray.size(); i++)
				{
					texcoords[i] = uvArray[i];
				}
				break;
				// インデックスを見て法線を取得
			case REFERENCE_MODE::INDEX:

				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				texcoords.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < uvIndexArray.size(); i++)
				{
					texcoords[i] = uvArray[uvIndexArray[i]];
				}
				break;
			default:
				break;
			}
		}
		default:
			break;
		}
	}

	/**********************************************************************************************//**
																									* @fn	const std::vector<HFVECTOR3>& MESH_BASE_DATA::CreateNormalElement()
																									*
																									* @brief	Creates normal element.
																									*
																									* @author	Kazuyuki Honda
																									* @date	2015/11/04
																									*
																									* @return	The new normal element.
																									**************************************************************************************************/

	void SubMeshData::CreateNormalElement(std::vector<HFVECTOR3>& normals)
	{
		switch (normalMappingMode)
		{
			// 頂点単位で割当
		case MAPPING_MODE::BY_CONTROL_POINT:
		{
			switch (normalReference)
			{
			case REFERENCE_MODE::DIRECT:
				// 位置情報がインデックスによって展開済み
				if (uvIndexArray.size() != porygonIndexArray.size())
				{
					normals = vertexNormalArray;
					return;
				}
				// インデックス頂点ごとに情報が必要
				normals.resize(porygonIndexArray.size());
				for (int i = 0; i < porygonIndexArray.size(); i++)
				{
					normals[i] = vertexNormalArray[porygonIndexArray[i]];
				}
				break;
			case REFERENCE_MODE::INDEX:
				normals.resize(vertexPositionArray.size());
				for (int i = 0; i < normals.size(); i++)
				{
					normals[i] = vertexNormalArray[normalIndexArray[i]];
				}
				break;
			default:
				break;
			}
			break;
		}
		// ポリゴンで扱う頂点ごとに法線1つ割当(同じ位置情報でもポリゴンごとに変える)
		case MAPPING_MODE::BY_POLYGON_VERTEX:
		{
			switch (normalReference)
			{
				// 直接法線を取得
			case REFERENCE_MODE::DIRECT:
				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				normals.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < vertexNormalArray.size(); i++)
				{
					normals[i] = vertexNormalArray[i];
				}
				break;
				// インデックスを見て法線を取得
			case REFERENCE_MODE::INDEX:

				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				normals.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < normalIndexArray.size(); i++)
				{
					normals[i] = vertexNormalArray[normalIndexArray[i]];
				}
				break;
			default:
				break;
			}
			break;
		}
		// ポリゴン単位
		case MAPPING_MODE::BY_POLYGON:
		{
			switch (normalReference)
			{					// 直接法線を取得
			case REFERENCE_MODE::DIRECT:
				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				normals.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < vertexNormalArray.size(); i++)
				{
					for (int j = 0; j < 3; j++)
					{
						normals[i] = vertexNormalArray[i];
					}
				}
				break;
				// インデックスを見て法線を取得
			case REFERENCE_MODE::INDEX:

				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				normals.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < normalIndexArray.size(); i++)
				{
					for (int j = 0; j < 3; j++)
					{
						normals[i * 3 + j] = vertexNormalArray[normalIndexArray[i]];
					}
				}
				break;
			default:
				break;
			}
			break;
		}
		// メッシュ全体
		case MAPPING_MODE::ALL_SAME:
		{
			switch (normalReference)
			{					// 直接法線を取得
			case REFERENCE_MODE::DIRECT:
				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				normals.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < vertexNormalArray.size(); i++)
				{
					normals[i] = vertexNormalArray[i];
				}
				break;
				// インデックスを見て法線を取得
			case REFERENCE_MODE::INDEX:

				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				normals.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < normalIndexArray.size(); i++)
				{
					normals[i] = vertexNormalArray[normalIndexArray[i]];
				}
				break;
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
	}

	/**********************************************************************************************//**
	 * @fn	void SubMeshData::CreateMaterialVec4Element(std::vector<HFVECTOR4>& materials, MATERIAL_ELEMENT elem)
	 *
	 * @brief	Creates material std::vector 4 element.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/04
	 *
	 * @param [in,out]	materials	The materials.
	 * @param	elem			 	The element.
	 **************************************************************************************************/

	void SubMeshData::CreateMaterialVec4Element(std::vector<HFVECTOR4>& materials, MATERIAL_ELEMENT elem)
	{
		switch (materialMappingMode)
		{
			// 頂点単位で割当
		case MAPPING_MODE::BY_CONTROL_POINT:
		{
			switch (materialReference)
			{
			case REFERENCE_MODE::INDEX:
				materials.resize(vertexPositionArray.size());
				for (int i = 0; i < materials.size(); i++)
				{
					materials[i] = materialArray[materialIndexArray[i]].GetVec4Element(elem);
				}
			default:
				break;
			}
			break;
		}
		// ポリゴンで扱う頂点ごとに法線1つ割当(同じ位置情報でもポリゴンごとに変える)
		case MAPPING_MODE::BY_POLYGON_VERTEX:
		{
			switch (materialReference)
			{
				// 直接法線を取得
			case REFERENCE_MODE::DIRECT:
				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				materials.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < materialArray.size(); i++)
				{
					//	materials[i] = vertexNormalArray[i];
				}
				break;
				// インデックスを見て法線を取得
			case REFERENCE_MODE::INDEX:

				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				materials.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < materialArray.size(); i++)
				{
					materials[i] = materialArray[materialIndexArray[i]].GetVec4Element(elem);
				}
				break;
			default:
				break;
			}
			break;
		}
		// ポリゴン単位
		case MAPPING_MODE::BY_POLYGON:
		{
			switch (materialReference)
			{					// 直接法線を取得
			case REFERENCE_MODE::DIRECT:
				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				materials.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < porygonIndexArray.size() / 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						materials[i] = materialArray[materialIndexArray[i]].GetVec4Element(elem);
					}
				}
				break;
				// インデックスを見て法線を取得
			case REFERENCE_MODE::INDEX:

				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				materials.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < porygonIndexArray.size() / 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						materials[i + j * 3] = materialArray[materialIndexArray[i]].GetVec4Element(elem);
					}
				}
				break;
			default:
				break;
			}
			break;
		}
		// メッシュ全体
		case MAPPING_MODE::ALL_SAME:
		{
			switch (materialReference)
			{					// 直接法線を取得
			case REFERENCE_MODE::DIRECT:
				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				materials.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < materials.size(); i++)
				{
					//	materials[i] = vertexNormalArray[i];
				}
				break;
				// インデックスを見て法線を取得
			case REFERENCE_MODE::INDEX:

				// DirectXは頂点単位でしかインデックスは持てないので位置情報に合わせる
				materials.resize(max(vertexPositionArray.size(), porygonIndexArray.size()));		   //
				for (int i = 0; i < materials.size(); i++)
				{
					materials[i] = materialArray[materialIndexArray[0]].GetVec4Element(elem);
				}
				break;
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
	}
}
