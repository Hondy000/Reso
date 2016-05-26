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
  * @brief	�C���X�^���X�����}�N��
  *
  * @author	Kazuyuki Honda
  *
  * @param	CCollisionObjectFactory::GetInstance()	The collision object factory get instance()
  **************************************************************************************************/

#define sCOLLISION_FACTORY (CCollisionObjectFactory::GetInstance())

  /**********************************************************************************************//**
   * @class	CCollisionObjectFactory
   *
   * @brief	�Փ˃I�u�W�F�N�g�̐����N���X
   *
   * @author	Kazuyuki Honda
   **************************************************************************************************/

class CCollisionObjectFactory
{
public:

	/**********************************************************************************************//**
	 * @fn	CCollisionObjectFactory::~CCollisionObjectFactory()
	 *
	 * @brief	�f�X�g���N�^.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	~CCollisionObjectFactory()
	{
	};

	/**********************************************************************************************//**
	 * @fn	static CCollisionObjectFactory* CCollisionObjectFactory::GetInstance()
	 *
	 * @brief	�V���O���g���̃C���X�^���X���擾.
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
	 * @brief	�����Փ˃I�u�W�F�N�g�����i�I�v�V���������j.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param [in,out]	holder	�Q�[�����œ������I�u�W�F�N�g�i�Փ˃I�u�W�F�N�g�̕ێ��ҁj.
	 * @param	type		  	�Փ˃I�u�W�F�N�g�^�C�v.
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

	// OBB�̏Փ˃I�u�W�F�N�g�̐���
	std::shared_ptr<BaseCollisionObject> CreateOBBObject
		(
			std::shared_ptr<SubMesh>& subMesh
			);




	// 1���̕��ʂ̏Փ˃I�u�W�F�N�g�̐���
	CollisionPlanesObject::PLANE_INFO CreatePlaneInfo(const HFVECTOR3 p1, const HFVECTOR3 p2, const HFVECTOR3 p3);
	
	// ���̂̏Փ˃I�u�W�F�N�g�̐���
	std::shared_ptr<BaseCollisionObject> CreateSphereObject
		(
			std::shared_ptr<SubMesh>& chf_object,
			BaseCollisionObject::BaseCollisionInfoOption*
			);

	// �����̕��ʂ̏Փ˃I�u�W�F�N�g�̐���
	std::shared_ptr<BaseCollisionObject> CreatePlanesObject
		(
			std::shared_ptr<SubMesh>& subMesh,
			BaseCollisionObject::BaseCollisionInfoOption*
			);

	// ���̏Փ˃I�u�W�F�N�g�̐���
	std::shared_ptr<BaseCollisionObject> CreateRayObject
		(
			std::shared_ptr<SubMesh>& subMesh,
			BaseCollisionObject::BaseCollisionInfoOption*
			);

private:

	// �B�������R���X�g���N�^
	CCollisionObjectFactory() {};
};
