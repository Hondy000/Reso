/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Collision\CCollisionObjectFactory.h
 *
 * @brief	Declares the collision object factory class.
 **************************************************************************************************/

#pragma once
#include "../../Core/Public/Common.h"
#include "..\CollisionObject\Public\BaseCollisionObject.h"
#include "..\..\Graphics\RenderObject\Public\SubMesh.h"
#include "..\CollisionObject\Public\CollisionPlanesObject.h"

/**********************************************************************************************//**
  * @def	sCOLLISION_FACTORY
  *
  * @brief	インスタンス所得マクロ
  *
  * @author	Kazuyuki Honda
  *
  * @param	CCollisionObjectFactory::GetInstance()	The collision object factory get instance()
  **************************************************************************************************/

#define sCOLLISION_FACTORY (CCollisionObjectFactory::GetInstance())

  /**********************************************************************************************//**
   * @class	CCollisionObjectFactory
   *
   * @brief	衝突オブジェクトの生成クラス
   *
   * @author	Kazuyuki Honda
   **************************************************************************************************/

class CCollisionObjectFactory
{
public:

	/**********************************************************************************************//**
	 * @fn	CCollisionObjectFactory::~CCollisionObjectFactory()
	 *
	 * @brief	デストラクタ.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	~CCollisionObjectFactory()
	{
	};

	/**********************************************************************************************//**
	 * @fn	static CCollisionObjectFactory* CCollisionObjectFactory::GetInstance()
	 *
	 * @brief	シングルトンのインスタンスを取得.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	null if it fails, else the instance.
	 **************************************************************************************************/

	static CCollisionObjectFactory* GetInstance()
	{
		static CCollisionObjectFactory singleton;
		return &singleton;
	}

	/**********************************************************************************************//**
	 * @fn	bool CCollisionObjectFactory::CreateCollisionObject ( std::shared_ptr<CHFObject>& holder, CBaseCollisionObject::COLLISION_TYPE type );
	 *
	 * @brief	自動衝突オブジェクト生成（オプション無し）.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	holder	ゲーム内で動かすオブジェクト（衝突オブジェクトの保持者）.
	 * @param	type		  	衝突オブジェクトタイプ.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	std::shared_ptr<BaseCollisionObject> CCollisionObjectFactory::CreateCollisionObject
		(
			std::shared_ptr<IActor> obj,
			std::shared_ptr<SubMesh> mesh,
			BaseCollisionObject::COLLISION_TYPE type
			);

public:

	// OBBの衝突オブジェクトの生成
	std::shared_ptr<BaseCollisionObject> CreateOBBObject
		(
			std::shared_ptr<SubMesh>& subMesh
			);




	// 1枚の平面の衝突オブジェクトの生成
	CollisionPlanesObject::PLANE_INFO CreatePlaneInfo(const HFVECTOR3 p1, const HFVECTOR3 p2, const HFVECTOR3 p3);
	
	// 球体の衝突オブジェクトの生成
	std::shared_ptr<BaseCollisionObject> CreateSphereObject
		(
			std::shared_ptr<SubMesh>& chf_object,
			BaseCollisionObject::BaseCollisionInfoOption*
			);

	// 複数の平面の衝突オブジェクトの生成
	std::shared_ptr<BaseCollisionObject> CreatePlanesObject
		(
			std::shared_ptr<SubMesh>& subMesh,
			BaseCollisionObject::BaseCollisionInfoOption*
			);

	// 線の衝突オブジェクトの生成
	std::shared_ptr<BaseCollisionObject> CreateRayObject
		(
			std::shared_ptr<SubMesh>& subMesh,
			BaseCollisionObject::BaseCollisionInfoOption*
			);

private:

	// 隠蔽したコンストラクタ
	CCollisionObjectFactory() {};
};
