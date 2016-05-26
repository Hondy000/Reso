/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Collision\CCollisionSpaceManager.cpp
 *
 * @brief	Implements the collision space manager class.
 **************************************************************************************************/

#include <algorithm>
#include "..\Public\CollisionSpaceManager.h"
#include "..\..\..\Math\Public\HFMath.h"
#include "..\..\CollisionObject\Public\BaseCollisionObject.h"
#include "..\..\Public\CollisionManager.h"

/**********************************************************************************************//**
  * @fn	bool CCollisionSpaceManager::Setup(unsigned int layer,HFVECTOR3 center, HFVECTOR3 size)
  *
  * @brief	Setups.
  *
  * @author	Kazuyuki Honda
  * @date	2015/11/04
  *
  * @param	layer 	The layer.
  * @param	center	The center.
  * @param	size  	The size.
  *
  * @return	true if it succeeds, false if it fails.
  **************************************************************************************************/

bool CollisionSpaceManager::Setup(unsigned int layer, struct HFVECTOR3 center, HFVECTOR3 size)
{
	int num = 0;
	m_center = center;
	m_size = size;
	m_level = layer;
	m_maxCellOfLevel.resize(9);
	m_maxCellOfLevel[0] = 1;
	for (BYTE i = 1; i < 9; i++)
	{
		m_maxCellOfLevel[i] = m_maxCellOfLevel[i - 1] * 8;
	}

	// Levelレベル（0基点）の配列作成
	m_maxCellToatal = (m_maxCellOfLevel[m_level + 1] - 1) / 7;
	m_cellArray.resize(m_maxCellToatal);
	return true;
}

/**********************************************************************************************//**
 * @fn	void CCollisionSpaceManager::CheckCollision(int elem ,std::list<std::shared_ptr<CBaseCollisionObject>> std::list)
 *
 * @brief	Check collision.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	elem	The element.
 * @param	std::list	The std::list.
 **************************************************************************************************/

void CollisionSpaceManager::CheckCollision(int elem, std::list<std::weak_ptr<BaseCollisionObject>>& collisionList)
{
	for (int i = 0; i < 8; i++) {
		int NextElem = elem * 8 + 1 + i;

		if (NextElem < m_maxCellToatal) {
			if (m_cellArray[NextElem] != nullptr)
			{
				m_cellArray[NextElem]->CheckCollision(collisionList);
			}

			//	ChildFlag = true;
			CheckCollision(elem * 8 + 1 + i, collisionList); // 子空間へ
		}
	}
}

/**********************************************************************************************//**
 * @fn	bool CCollisionSpaceManager::Update(void)
 *
 * @brief	Updates this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool CollisionSpaceManager::Update(void)
{
	int cellCount = m_cellArray.size();
	m_cellArray.clear();
	m_cellArray.resize(cellCount);

	// objectの大きさを取得してcellに登録する
	for (auto it = sCOLLISION_MANAGER->GetCollisionObjectList().begin();
	it != sCOLLISION_MANAGER->GetCollisionObjectList().end();
		it++)
	{
		HFVECTOR3 center, halfSize;
		(*it).lock()->GetSpaceSize(&center, &halfSize);
		DWORD serial = FindSerialNumberOfBox(center, halfSize);
		if (serial < m_cellArray.size())
		{
			if (m_cellArray[serial] == nullptr)
			{
				m_cellArray[serial] = std::shared_ptr<CCollisionSpaceCell>(new CCollisionSpaceCell);

				int level = SerialNumberToLevel(serial);
				m_cellArray[serial]->SetLevel(level);
				m_cellArray[serial]->SetSerialNumber(serial);
			}
			m_cellArray[serial]->GetCollisionObjectList().push_back(*it);
		}
	}

	for (int i = 0; i < m_cellArray.size(); i++)
	{
		if (m_cellArray[i])
		{
			// 自空間内で衝突判定
			m_cellArray[i]->CheckCollision(m_cellArray[i]->GetCollisionObjectList());

			// 子の空間で判定
			CheckCollision(i, m_cellArray[i]->GetCollisionObjectList());
		}
	}
	return true;
}

/**********************************************************************************************//**
 * @fn	DWORD CCollisionSpaceManager::FindSerialNumberOfBox(const HFVECTOR3& pCenter, const HFVECTOR3&pHalfSize)
 *
 * @brief	Searches for the first serial number of box.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	pCenter  	The center.
 * @param	pHalfSize	Size of the half.
 *
 * @return	The found serial number of box.
 **************************************************************************************************/

DWORD CollisionSpaceManager::FindSerialNumberOfBox(const HFVECTOR3& pCenter, const HFVECTOR3&pHalfSize)
{
	// 最小の点
	HFVECTOR3 minPoint = pCenter - pHalfSize;

	// 最大の点
	HFVECTOR3 maxPoint = pCenter + pHalfSize;

	// それぞれのMorton番号を求める
	DWORD minMorton = FindMortonNumberOfPoint(minPoint);
	DWORD maxMorton = FindMortonNumberOfPoint(maxPoint);
	DWORD def = minMorton^maxMorton;

	// 空間番号を引き算して
		// 最上位区切りから所属レベルを算出
	unsigned int HiLevel = 0; // = 1;
	unsigned int i;
	for (i = 0; i < m_level; i++)
	{
		DWORD Check = (def >> (i * 3)) & 0x7;
		if (Check != 0)
		{
			HiLevel = i + 1;
		}
	}
	DWORD SpaceNum = maxMorton >> (HiLevel * 3);
	DWORD AddNum = (m_maxCellOfLevel[m_level - HiLevel] - 1) / 7;
	SpaceNum += AddNum;

	if (SpaceNum > m_cellArray.size())
		return 0xffffffff;

	return SpaceNum;
}

/**********************************************************************************************//**
 * @fn	DWORD BitSeparateFor3D(BYTE n)
 *
 * @brief	Bit separate for 3D.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	n	The BYTE to process.
 *
 * @return	A DWORD.
 **************************************************************************************************/

DWORD BitSeparateFor3D(BYTE n)
{
	DWORD s = n;
	s = (s | s << 8) & 0x0000f00f;
	s = (s | s << 4) & 0x000c30c3;
	s = (s | s << 2) & 0x00249249;
	return s;
}

/**********************************************************************************************//**
 * @fn	DWORD CCollisionSpaceManager::FindMortonNumberOfPoint(const HFVECTOR3& pPoint)
 *
 * @brief	Searches for the first morton number of point.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	pPoint	The point.
 *
 * @return	The found morton number of point.
 **************************************************************************************************/

DWORD CollisionSpaceManager::FindMortonNumberOfPoint(const HFVECTOR3& pPoint)
{
	// 最下位レベルでXYZが何番目の部屋の座標にあるか調べる
	HFVECTOR3 minSize = m_size / pow(2, m_level);
	HFVECTOR3 startPoint = m_center - m_size / 2;	// 最小座標
	HFVECTOR3 position;		// 座標ごとの部屋位置
	position.x = (pPoint - startPoint).x / minSize.x;
	position.y = (pPoint - startPoint).y / minSize.y;
	position.z = (pPoint - startPoint).z / minSize.z;

	DWORD numX = BitSeparateFor3D((int)position.x);
	DWORD numY = BitSeparateFor3D((int)position.y);
	DWORD numZ = BitSeparateFor3D((int)position.z);
	return 	(numX | (numY << 1) | (numZ << 2));
}

/**********************************************************************************************//**
 * @fn	void CCollisionSpaceManager::CheckParent(void)
 *
 * @brief	Check parent.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 **************************************************************************************************/

void CollisionSpaceManager::CheckParent(void)
{
	for (auto it = m_cellArray.begin(); it != m_cellArray.end(); it++)
	{
		if (*it != nullptr)
		{
			//	int (*it)->GetSerialNumber();
		}
	}
}