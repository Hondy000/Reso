#pragma once


#include "../../../Core/Public/Common.h"
#include "../../../Core/Task/Public/TaskInterface.h"


struct CameraInfomation
{
	FLOAT m_aspect;							// �A�X�y�N�g��
	FLOAT m_nearClip;						// �j�A�N���b�v
	FLOAT m_farClip;						// �t�@�[�N���b�v
	FLOAT m_viewAngle;						// ����p

	HFVECTOR3 m_upVector;					// �J�����̏�x�N�g��
	HFVECTOR3 m_cameraPosition;				// �J�����ʒu
	HFVECTOR3 m_distanceFromFollowTarget;	// �Ǐ]�I�u�W�F�N�g�Ƃ̋���
	HFVECTOR3 m_viewVector;					// ���_�x�N�g��
	HFVECTOR3 m_rotation;
};

class BaseCamera 
{
protected:
public:
	BaseCamera();

	virtual~BaseCamera() {};

	BOOL Init(void);

	void Reset() {};
	// Access the Aspect
	FLOAT GetAspect(void) const
	{
		return(m_aspect);
	};
	void SetAspect(FLOAT aspect)
	{
		m_aspect = aspect;
	};

	// Access the NearClip
	FLOAT GetNearClip(void) const
	{
		return(m_nearClip);
	};

	void SetNearClip(FLOAT nearClip)
	{
		m_nearClip = nearClip;
	};

	// Access the FarClip
	FLOAT GetFarClip(void) const
	{
		return(m_farClip);
	};

	void SetFarClip(FLOAT farClip)
	{
		m_farClip = farClip;
	};

	// Access the ViewAngle
	FLOAT GetViewAngle(void) const
	{
		return(m_viewAngle);
	};
	void SetViewAngle(FLOAT viewAngle)
	{
		m_viewAngle = viewAngle;
	};

	// Access the UpVector
	const HFVECTOR3& GetUpVector(void) const
	{
		return(m_upVector);
	};
	void SetUpVector(const HFVECTOR3& upVector)
	{
		m_upVector = upVector;
	};

	// Access the CameraPosition
	const HFVECTOR3& GetCameraPosition(void) const
	{
		return(m_cameraPosition);
	};
	void SetCameraPosition(const HFVECTOR3& cameraPosition)
	{
		m_cameraPosition = cameraPosition;
	};

	// Access the ViewPosition
	const HFVECTOR3& GetViewVector(void) const
	{
		return(m_viewVector);
	};
	void SetViewVector(const HFVECTOR3& viewPosition)
	{
		m_viewVector = viewPosition;
	};

	BOOL Update(void);
	virtual void UpdateViewMatrix();
	virtual void UpdateProjectionMatrix();

	// Access the Rotation
	const HFVECTOR3& GetRotation(void) const
	{
		return(m_rotation);
	};

	// Access the Rotation
	const HFVECTOR3& GetDistanceFromTarget(void) const
	{
		return(m_distanceFromFollowTarget);
	};

	void SetRotation(const HFVECTOR3& rotation)
	{
		m_rotation = rotation;
	};

	void SetDistanceFromFollowTarget(HFVECTOR3 vec)
	{
		m_distanceFromFollowTarget = vec;
	}

	void SetIsView(BOOL flag)
	{
		isView = flag;
	}

	void SetIsFollow(BOOL flag)
	{
		isFollow = flag;
	}

protected:
	FLOAT m_aspect;
	FLOAT m_nearClip;
	FLOAT m_farClip;
	FLOAT m_viewAngle;

	HFVECTOR3 m_upVector;
	HFVECTOR3 m_cameraPosition;
	HFVECTOR3 m_distanceFromFollowTarget;	// �Ǐ]�Ώۂ���̋���
	HFVECTOR3 m_viewVector;	// ���_�x�N�g��
	HFVECTOR3 m_rotation;

	/** @brief	�Ǐ]�I�u�W�F�N�g�̈ʒu�I�t�Z�b�g. */
	HFVECTOR3 m_followObjectOffset;
	/** @brief	�����I�u�W�F�N�g�̈ʒu�I�t�Z�b�g. */
	HFVECTOR3 m_viewObjectOffset;

	/** @brief	�J�������I�u�W�F�N�g��Ǐ]���邩�̃t���O. */
	BOOL isFollow;
	/** @brief	�J�����̃I�u�W�F�N�g�𒆎~���邩�̃t���O. */
	BOOL isView;
};
