#pragma once
#include "../../Core/Public/Common.h"


interface IPosition
{

protected:
	std::shared_ptr<Variable<HFVECTOR3>> m_position;		// 現在位置

public:
	IPosition()
	{
		m_position = std::make_shared<Variable<HFVECTOR3>>();
		m_position->SetValue(HFVECTOR3());
	}
	virtual ~IPosition() {};

	virtual void SetPositionX(FLOAT x) = 0;
	virtual void SetPositionY(FLOAT y) = 0;
	virtual void SetPositionZ(FLOAT z) = 0;
	virtual void SetPosition(FLOAT x, FLOAT y, FLOAT z) = 0;
	virtual void SetPosition(HFVECTOR3 _position) = 0;

	virtual FLOAT GetPositionX() = 0;
	virtual FLOAT GetPositionY() = 0;
	virtual FLOAT GetPositionZ() = 0;
	virtual HFVECTOR3 GetPosition() = 0;

	virtual HFMATRIX GetTranslationMatrix() = 0;

};

// 回転インターフェース
interface IRotation
{

protected:
	HFVECTOR3 m_rotation;		// オイラー角

public:
	IRotation()
		:
		m_rotation(HFVECTOR3(0, 0, 0))
	{

	}
	virtual ~IRotation() {};

	virtual void SetRotationX(const FLOAT& x) = 0;
	virtual void SetRotationY(const FLOAT& y) = 0;
	virtual void SetRotationZ(const FLOAT& z) = 0;
	virtual void SetRotation(const FLOAT& x, const FLOAT& y, const FLOAT& z) = 0;
	virtual void SetRotation(const HFVECTOR3& _rotation) = 0;

	virtual const FLOAT& GetRotationX()const = 0;
	virtual const FLOAT& GetRotationY()const = 0;
	virtual const FLOAT& GetRotationZ()const = 0;
	virtual const HFVECTOR3& GetRotation()const = 0;

	virtual HFMATRIX GetRotationMatrixX()const = 0;
	virtual HFMATRIX GetRotationMatrixY()const = 0;
	virtual HFMATRIX GetRotationMatrixZ()const = 0;
};

// 拡縮インターフェース
interface IScale
{

protected:
	HFVECTOR3 m_scale;		// 拡縮

public:
	IScale()
		:
		m_scale(HFVECTOR3(1, 1, 1))
	{

	}
	virtual ~IScale() {};

	virtual void SetScaleX(const FLOAT& _scale) = 0;
	virtual void SetScaleY(const FLOAT& _scale) = 0;
	virtual void SetScaleZ(const FLOAT& _scale) = 0;
	virtual void SetScale(const FLOAT& x, const FLOAT& y, const FLOAT& z) = 0;
	virtual void SetScale(const HFVECTOR3& _scale) = 0;


	virtual const FLOAT& GetScaleX(void)const = 0;
	virtual const FLOAT& GetScaleY(void)const = 0;
	virtual const FLOAT& GetScaleZ(void)const = 0;
	virtual const HFVECTOR3& GetScale(void)const = 0;

	virtual HFMATRIX GetScalingMatrix()const = 0;

};






class Transform
	:
	public IPosition,
	public IRotation,
	public IScale
{
public:
	Transform()
	{
		if (m_position->GetValue())
		{
			m_position->SetValue(HFVECTOR3(0, 0, 0));
		}
	};
	~Transform(){};

	void SetPositionX(FLOAT x)
	{
		m_position->SetValue(HFVECTOR3(x, m_position->GetValue()->y, m_position->GetValue()->z));
	};
	
	void SetPositionY(FLOAT y)
	{
		m_position->SetValue(HFVECTOR3(m_position->GetValue()->x, y, m_position->GetValue()->z));
	};

	void SetPositionZ(FLOAT z)
	{
		m_position->SetValue(HFVECTOR3(m_position->GetValue()->x, m_position->GetValue()->y,z));
	};
	
	void SetPosition(FLOAT x, FLOAT y, FLOAT z)
	{
		m_position->SetValue(HFVECTOR3(x, y, z));
	};

	void SetPosition(HFVECTOR3 _position)
	{
		m_position->SetValue(_position);
	};

	FLOAT GetPositionX()
	{
		return m_position->GetValue()->x;
	};
	FLOAT GetPositionY()
	{
		return m_position->GetValue()->y;
	};
	FLOAT GetPositionZ()
	{
		return m_position->GetValue()->z;
	};
	HFVECTOR3 GetPosition()
	{
		return *m_position->GetValue();
	};

	HFMATRIX GetTranslationMatrix()
	{
		HFMATRIX trans;
		HFMatrixTranslation(&trans, m_position->GetValue()->x, m_position->GetValue()->y, m_position->GetValue()->z);
		return trans;
	};

	void SetRotationX(const FLOAT& x)
	{
		m_rotation.x = x;
	};

	void SetRotationY(const FLOAT& y)
	{
		m_rotation.y = y;
	};

	void SetRotationZ(const FLOAT& z)
	{
		m_rotation.z = z;
	};

	void SetRotation(const FLOAT& x, const FLOAT& y, const FLOAT& z)
	{
		m_rotation.x = x;
		m_rotation.y = y;
		m_rotation.z = z;
	};
	void SetRotation(const HFVECTOR3& _rotation)
	{
		m_rotation = _rotation;
	};

	const FLOAT& GetRotationX()const
	{
		return m_rotation.x;
	};
	const FLOAT& GetRotationY()const
	{
		return m_rotation.y;
	};
	const FLOAT& GetRotationZ()const
	{
		return m_rotation.z;
	};
	const HFVECTOR3& GetRotation()const
	{
		return m_rotation;
	};

	HFMATRIX GetRotationMatrixX()const
	{
		HFMATRIX rotationX;
		HFMatrixRotationX(&rotationX,HFToRadian(m_rotation.x));
		return rotationX;
	};

	HFMATRIX GetRotationMatrixY()const
	{
		HFMATRIX rotationY;
		HFMatrixRotationY(&rotationY, HFToRadian(m_rotation.y));
		return rotationY;
	};

	HFMATRIX GetRotationMatrixZ()const
	{
		HFMATRIX rotationZ;
		HFMatrixRotationZ(&rotationZ, HFToRadian(m_rotation.z));
		return rotationZ;
	};

	void SetScaleX(const FLOAT& x)
	{
		m_scale.x = x;
	};

	void SetScaleY(const FLOAT& y)
	{
		m_scale.y = y;
	};

	void SetScaleZ(const FLOAT& z)
	{
		m_scale.z = z;
	};

	void SetScale(const FLOAT& x, const FLOAT& y, const FLOAT& z)
	{
		m_scale.x = x;
		m_scale.y = y;
		m_scale.z = z;
	};

	void SetScale(const HFVECTOR3& _scale)
	{
		m_scale = _scale;
	};


	const FLOAT& GetScaleX(void)const
	{
		return m_scale.x;
	};
	const FLOAT& GetScaleY(void)const
	{
		return m_scale.y;
	};
	const FLOAT& GetScaleZ(void)const
	{
		return m_scale.z;
	};
	const HFVECTOR3& GetScale(void)const
	{
		return m_scale;
	};

	HFMATRIX GetScalingMatrix()const
	{
		HFMATRIX scale;
		HFMatrixScaling(&scale, m_scale.x, m_scale.y, m_scale.z);
		return scale;
	};


	HFMATRIX GetWorldTransform()
	{
		HFMATRIX wolrd;
		wolrd = GetScalingMatrix() * GetRotationMatrixZ() * GetRotationMatrixY() * GetRotationMatrixX() * GetTranslationMatrix();
		return wolrd;
	};

private:

};
