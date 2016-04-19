#pragma once


#include "../../../Core/Public/Common.h"
#include "../../../Core/Task/Public/TaskInterface.h"


struct CameraInfomation
{
	FLOAT m_aspect;							// アスペクト比
	FLOAT m_nearClip;						// ニアクリップ
	FLOAT m_farClip;						// ファークリップ
	FLOAT m_viewAngle;						// 視野角

	HFVECTOR3 m_upVector;					// カメラの上ベクトル
	HFVECTOR3 m_cameraPosition;				// カメラ位置
	HFVECTOR3 m_distanceFromFollowTarget;	// 追従オブジェクトとの距離
	HFVECTOR3 m_viewVector;					// 視点ベクトル
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


	std::weak_ptr<IBaseTask> GetFollowObject() const
	{
		return m_wpFollowObject;
	}

	void SetFollowObject(std::shared_ptr<IBaseTask> _val);


	std::weak_ptr<IBaseTask> GetViewObject() const
	{
		return m_wpViewObject;
	}

	void SetViewObject(std::shared_ptr<IBaseTask> _val);


	HFVECTOR3 GetViewObjectOffset() const
	{
		return m_viewObjectOffset;
	}

	void SetViewObjectOffset(HFVECTOR3 _val)
	{
		m_viewObjectOffset = _val;
	}

protected:
	FLOAT m_aspect;
	FLOAT m_nearClip;
	FLOAT m_farClip;
	FLOAT m_viewAngle;

	HFVECTOR3 m_upVector;
	HFVECTOR3 m_cameraPosition;
	HFVECTOR3 m_viewVector;	// 視点ベクトル
	HFVECTOR3 m_rotation;

	/** @brief	追従オブジェクトの位置オフセット. */
	HFVECTOR3 m_distanceFromFollowTarget;
	/** @brief	注視オブジェクトのオフセット. */
	HFVECTOR3 m_viewObjectOffset;

	/** @brief	カメラがオブジェクトを追従するかのフラグ. */
	BOOL isFollow;
	/** @brief	カメラのオブジェクトを中止するかのフラグ. */
	BOOL isView;
	std::weak_ptr<IBaseTask> m_wpFollowObject;
	std::weak_ptr<IBaseTask> m_wpViewObject;
};
