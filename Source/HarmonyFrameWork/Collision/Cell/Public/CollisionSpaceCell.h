#pragma once
#include "../../CollisionObject/Public/BaseCollisionObject.h"

class BaseCollisionObject;

class CCollisionSpaceCell
{
public:
	CCollisionSpaceCell()
	{
	};

	~CCollisionSpaceCell()
	{
	};

	// Access the CollisionObjectList
	std::list<std::weak_ptr<BaseCollisionObject>>& GetCollisionObjectList(void)
	{
		return(m_collisionObjectList);
	};

	void SetCollisionObjectList(const std::list<std::weak_ptr<BaseCollisionObject>>& collisionObjectList)
	{
		m_collisionObjectList = collisionObjectList;
	};

	// Access the SerialNumber
	int GetSerialNumber(void) const
	{
		return(m_serialNumber);
	};

	void SetSerialNumber(int serialNumber)
	{
		m_serialNumber = serialNumber;
	};

	// Access the Layer
	int GetLevel(void) const
	{
		return(m_level);
	};

	void SetLevel(int layer)
	{
		m_level = layer;
	};

	// Access the Size
	const HFVECTOR3& GetSize(void) const
	{
		return(m_size);
	};

	void SetSize(const HFVECTOR3& size)
	{
		m_size = size;
	};

	// Access the ChildeCell
	const std::list<std::shared_ptr< CCollisionSpaceCell>>& GetChildeCell(void) const
	{
		return(m_childeCell);
	};

	void SetChildeCell(const std::list<std::shared_ptr< CCollisionSpaceCell>>& childeCell)
	{
		m_childeCell = childeCell;
	};

	void CheckCollision(std::list<std::weak_ptr<BaseCollisionObject>>&);

private:
	HFVECTOR3 m_size;
	std::list<std::shared_ptr< CCollisionSpaceCell>>	m_childeCell;
	int m_serialNumber;
	int m_level;
	std::list<std::weak_ptr<BaseCollisionObject>> m_collisionObjectList;
};
