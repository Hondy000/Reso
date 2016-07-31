#pragma once
#include "../../Core/Public/Common.h"


interface IPosition
{

protected:
	HFVECTOR3 m_position;		// 現在位置

public:
	IPosition()
		:
		m_position(HFVECTOR3(0, 0, 0))
	{
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
	HFQUATERNION m_rotation;		

public:
	IRotation()
		:
		m_rotation(0, 0, 0,1)
	{

	}
	virtual ~IRotation() {};

	virtual void SetRotationX(const FLOAT& x) = 0;
	virtual void SetRotationY(const FLOAT& y) = 0;
	virtual void SetRotationZ(const FLOAT& z) = 0;
	virtual void SetEulerRadAngles(const FLOAT x, const FLOAT y, const FLOAT z) = 0;
	virtual void SetEulerRadAngles(const HFVECTOR3 _rotation) = 0;

	virtual const FLOAT& GetQuaternionRotationX()const = 0;
	virtual const FLOAT& GetQuaternionRotationY()const = 0;
	virtual const FLOAT& GetQuaternionRotationZ()const = 0;
	virtual const HFVECTOR3& GetEulerRadAngles()const = 0;

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
	};
	~Transform(){};

	void SetPositionX(FLOAT x);
	
	void SetPositionY(FLOAT y);

	void SetPositionZ(FLOAT z);
	
	void SetPosition(FLOAT x, FLOAT y, FLOAT z);

	void SetPosition(HFVECTOR3 _position);

	FLOAT GetPositionX();
	FLOAT GetPositionY();
	FLOAT GetPositionZ();
	HFVECTOR3 GetPosition();

	HFMATRIX GetTranslationMatrix();

	void SetRotationX(const FLOAT& x);

	void SetRotationY(const FLOAT& y);

	void SetRotationZ(const FLOAT& z);
	void SetQuaternionRotation(HFQUATERNION q);

	void SetEulerRadAngles(const FLOAT x, const FLOAT y, const FLOAT z);
	void SetEulerRadAngles(const HFVECTOR3 _rotation);

	void SetEulerDegAngles(const FLOAT x, const FLOAT y, const FLOAT z);
	void SetEulerDegAngles( HFVECTOR3 _rotation);
	const FLOAT& GetQuaternionRotationX()const;
	const FLOAT& GetQuaternionRotationY()const;
	const FLOAT& GetQuaternionRotationZ()const;
	const FLOAT& GetQuaternionRotationW()const;
	HFQUATERNION GetQuaternionRotation();
	const HFVECTOR3& GetEulerRadAngles()const;
	const HFVECTOR3& GetEulerDegAngles() const;
	HFMATRIX GetRotationMatrixX()const;

	HFMATRIX GetRotationMatrixY()const;

	HFMATRIX GetRotationMatrixZ()const;

	HFMATRIX GetRotationMatrix();
	void SetScaleX(const FLOAT& x);

	void SetScaleY(const FLOAT& y);

	void SetScaleZ(const FLOAT& z);

	void SetScale(const FLOAT& x, const FLOAT& y, const FLOAT& z);

	void SetScale(const HFVECTOR3& _scale);


	const FLOAT& GetScaleX(void)const;
	const FLOAT& GetScaleY(void)const;
	const FLOAT& GetScaleZ(void)const;
	const HFVECTOR3& GetScale(void)const;

	HFMATRIX GetScalingMatrix()const;


	HFMATRIX GetWorldTransform();

private:

};
