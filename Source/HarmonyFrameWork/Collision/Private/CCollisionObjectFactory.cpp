#include "..\Public\CCollisionObjectFactory.h"
#include "..\..\Graphics\Buffer\Public\VertexBuffer.h"
#include "..\..\Graphics\RenderDevice\Basic\Public\RendererManager.h"
#include "..\..\Graphics\RenderObject\Public\Mesh.h"


/**********************************************************************************************//**
 * @fn	HFRESULT CCollisionObjectFactory::CreateOBBObject ( std::shared_ptr<CBaseCollisionObject>& pOut, std::shared_ptr<CDrawObject>& pMaterial, CBaseCollisionObject::BaseCollisionInfoOption* pOption )
 *
 * @brief	Creates obb object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param [in,out]	pOut	 	The out.
 * @param [in,out]	pMaterial	The material.
 * @param [in,out]	pOption  	If non-null, the option.
 *
 * @return	The new obb object.
 **************************************************************************************************/



//std::shared_ptr<BaseCollisionObject> CCollisionObjectFactory::CreateOBBObject(std::vector<std::shared_ptr<SubMesh>>& subMeshArray)
//{
//	D3D11_MAPPED_SUBRESOURCE vertexResource;
//	D3D11_MAPPED_SUBRESOURCE indexResource;
//	HFVECTOR3 maxV, minV;
//	std::vector<HFVECTOR3> positions;
//	std::vector<UINT> indicies;
//
//	for (int j = 0;j< subMeshArray.size();j++)
//	{
//#ifdef DIRECTX11
//		std::vector<std::shared_ptr<VertexBuffer>> vertexBufferArray;
//		DWORD semantics[] = { HF_SEMANTICS_POSITION };
//		subMeshArray[j]->GetVertexBuffers(1, semantics, vertexBufferArray);
//		sRENDER_DEVICE_MANAGER->GetImmediateContext()->Map(vertexBufferArray[0]->Get(),0, D3D11_MAP_READ,0, &vertexResource);
//#endif
//	}
//
//	maxV = positions[0];
//	minV = positions[0];
//	for (int i = 0; i < spMesh->GetMeshData().vertexPositionArray.size(); i++)
//	{
//		if (maxV.x < positions[i].x)
//		{
//			maxV.x = positions[i].x;
//		}
//		if (maxV.y < positions[i].y)
//		{
//			maxV.y = positions[i].y;
//		}
//		if (maxV.z < positions[i].z)
//		{
//			maxV.z = positions[i].z;
//		}
//
//		if (minV.x > positions[i].x)
//		{
//			minV.x = positions[i].x;
//		}
//		if (minV.y > positions[i].y)
//		{
//			minV.y = positions[i].y;
//		}
//		if (minV.z > positions[i].z)
//		{
//			minV.z = positions[i].z;
//		}
//	}
//	HFVECTOR3 size = (maxV - minV) * 0.5;
//	spOBB->SetSize(size);
//	HFVECTOR3 vecArray[3] =
//	{
//		HFVECTOR3(1, 0, 0),
//		HFVECTOR3(0, 1, 0),
//		HFVECTOR3(0, 0, 1)
//	};
//	spOBB->SetDirection(vecArray);
//
//	HFVECTOR3 center = maxV - minV;
//	spOBB->SetBaseCenter(center);
//}


std::shared_ptr<BaseCollisionObject> CCollisionObjectFactory::CreateOBBObject(std::shared_ptr<SubMesh>& subMesh)
{
	std::vector<HFVECTOR3> positions;
	subMesh->GetPositions(positions);
	return nullptr;
}

/**********************************************************************************************//**
 * @fn	void CCollisionObjectFactory::CreatePlaneInfo(const HFVECTOR3 p1, const HFVECTOR3 p2, const HFVECTOR3 p3, CCollisionPlanesObject::PLANE_INFO plane)
 *
 * @brief	Creates plane information.
 *
 * @author	Kazuyuki Honda
 *
 * @param	p1			 	The first HFVECTOR3.
 * @param	p2			 	The second HFVECTOR3.
 * @param	p3			 	The third HFVECTOR3.
 * @param [in,out]	plane	If non-null, the plane.
 **************************************************************************************************/

CollisionPlanesObject::PLANE_INFO CCollisionObjectFactory::CreatePlaneInfo
(
	const HFVECTOR3 p1,
	const HFVECTOR3 p2,
	const HFVECTOR3 p3
	)
{
	CollisionPlanesObject::PLANE_INFO plane;
	HRESULT hr = E_FAIL; // 戻り値
	HFVECTOR3 p1p2;
	HFVECTOR3 p2p3;
	HFVECTOR3 normal;

	p1p2 = p2 - p1;
	p2p3 = p3 - p2;

	normal = HFVec3Cross(p1p2, p2p3); // 外積を求める
	normal = HFVec3Normalize( normal); // 長さを1にしておく
	plane.plane.a = normal.x;
	plane.plane.b = normal.y;
	plane.plane.c = normal.z;
	plane.normal = normal;
	plane.p0 = p1;
	plane.p1 = p2;
	plane.p2 = p3;

	plane.plane.d = -(plane.plane.a * p1.x + plane.plane.b * p1.y + plane.plane.c * p1.z);
	return plane;
}

//std::shared_ptr<BaseCollisionObject> CCollisionObjectFactory::CreateSphereObject
//(
//	std::shared_ptr<BaseCollisionObject>& coll,
//	std::shared_ptr<ShapeObject>& chf_object,
//	BaseCollisionObject::BaseCollisionInfoOption* pOption
//	)
//{
//	HRESULT hr = E_FAIL; // 戻り値
//	std::shared_ptr<CollisionSphereObject> sphere;// = std::shared_ptr<CCollisionSphereObject>(new CCollisionSphereObject);
//	switch (chf_object->GetType())
//	{
//	case ShapeObject::POLYGON_2D:
//	{
//	}
//	break;
//	case ShapeObject::POLYGON_3D:
//
//		break;
//	case ShapeObject::MESH:
//	{
//		std::shared_ptr<MeshShape> spMesh = std::static_pointer_cast<MeshShape>(chf_object);
//		HRESULT hr;
//		HFVECTOR3 maxV, minV;
//		std::vector<HFVECTOR3> positions;
//		std::vector<UINT> indicies;
//		spMesh->GetMeshData().CreatePositionElement(positions); // 頂点情報をメッシュデータから取得
//		spMesh->GetMeshData().CreatePolygonIndex(indicies);
//
//		// 頂点情報が取得できた
//		if (positions.size() > 0)
//		{
//			maxV = positions[0];
//			minV = positions[0];
//			for (UINT i = 0; i < spMesh->GetMeshData().vertexPositionArray.size(); i++)
//			{
//				if (maxV.x < positions[i].x)
//				{
//					maxV.x = positions[i].x;
//				}
//				if (maxV.y < positions[i].y)
//				{
//					maxV.y = positions[i].y;
//				}
//				if (maxV.z < positions[i].z)
//				{
//					maxV.z = positions[i].z;
//				}
//
//				if (minV.x > positions[i].x)
//				{
//					minV.x = positions[i].x;
//				}
//				if (minV.y > positions[i].y)
//				{
//					minV.y = positions[i].y;
//				}
//				if (minV.z > positions[i].z)
//				{
//					minV.z = positions[i].z;
//				}
//			}
//			HFVECTOR3 sizeV;
//			float size;
//			sizeV = maxV - minV;
//			size = sizeV.x;
//			if (size < sizeV.y)
//			{
//				size = sizeV.y;
//			}
//			if (size < sizeV.z)
//			{
//				size = sizeV.z;
//			}
//			sphere->SetSize(size);
//
//			HFVECTOR3 center = maxV + minV;
//			sphere->SetBaseCenter(center);
//		}
//	}
//	break;
//
//	default: break;
//	}
//	coll = sphere;
//	return hr;
//}

std::shared_ptr<BaseCollisionObject> CCollisionObjectFactory::CreateSphereObject(std::shared_ptr<SubMesh>& chf_object, BaseCollisionObject::BaseCollisionInfoOption*)
{
	return nullptr;
}

/**********************************************************************************************//**
 * @fn	void CCollisionObjectFactory::CreatePlanesObject(std::shared_ptr<CBaseCollisionObject>& pOut, std::shared_ptr<CDrawObject>& pMaterial)
 *
 * @brief	Creates planes object.
 *
 * @author	Kazuyuki Honda
 *
 * @param [in,out]	pOut	 	The out.
 * @param [in,out]	pMaterial	The material.
 **************************************************************************************************/

//std::shared_ptr<BaseCollisionObject> CCollisionObjectFactory::CreatePlanesObject
//(
//	std::shared_ptr<RenderObject>& pOutHolder,
//	std::shared_ptr<Mesh>& mesh,
//	BaseCollisionObject::BaseCollisionInfoOption* pOption
//	)
//{
//	std::shared_ptr<CollisionPlanesObject> spPlanes;// = std::shared_ptr<CCollisionPlanesObject>(new CCollisionPlanesObject);
//
//	int i, idx1, idx2, idx0;
//
//	HRESULT hr = E_FAIL; // 戻り値
//
//	//当たり判定用のメッシュを作成
//
//	std::vector<HFVECTOR3> positions;
//	std::vector<UINT> indicies;
//	mesh->GetMeshData().CreatePositionElement(positions);	// 頂点情報をメッシュデータから取得
//	mesh->GetMeshData().CreatePolygonIndex(indicies);
//
//	spPlanes->GetPlaneInfoArray().resize(indicies.size() / 3);
//	for (i = 0; i < spPlanes->GetPlaneInfoArray().size(); i++)
//	{
//		//３頂点をインデックスから特定して頂点データ取得
//		idx0 = i;
//		idx1 = i + 1;
//		idx2 = i + 2;
//		spPlanes->GetPlaneInfoArray()[i] = std::shared_ptr<CollisionPlanesObject::PLANE_INFO>(new CollisionPlanesObject::PLANE_INFO);
//		spPlanes->GetPlaneInfoArray()[i]->p0 = positions[indicies[i * 3 + 0]];
//		spPlanes->GetPlaneInfoArray()[i]->p1 = positions[indicies[i * 3 + 1]];
//		spPlanes->GetPlaneInfoArray()[i]->p2 = positions[indicies[i * 3 + 2]];
//
//		//平面の方程式を求める処理
//		CreatePlaneInfo(
//			&(spPlanes->GetPlaneInfoArray()[i]->p0),
//			&(spPlanes->GetPlaneInfoArray()[i]->p1),
//			&(spPlanes->GetPlaneInfoArray()[i]->p2),
//			(spPlanes->GetPlaneInfoArray()[i]).get(),
//			pOption
//			);
//	}
//	spPlanes->AnalyzeSpaceSize();
//	pOut = spPlanes;
//	hr = S_OK;
//	return hr;
//}

std::shared_ptr<BaseCollisionObject> CCollisionObjectFactory::CreatePlanesObject(std::shared_ptr<SubMesh>& subMesh, BaseCollisionObject::BaseCollisionInfoOption*)
{
	return nullptr;
}

std::shared_ptr<BaseCollisionObject> CCollisionObjectFactory::CreateRayObject(std::shared_ptr<SubMesh>& subMesh, BaseCollisionObject::BaseCollisionInfoOption*)
{
	return nullptr;
}

std::shared_ptr<BaseCollisionObject> CCollisionObjectFactory::CreateCollisionObject(std::shared_ptr<IActor> obj, std::shared_ptr<SubMesh> mesh, BaseCollisionObject::COLLISION_TYPE type)
{
	return nullptr;
}
