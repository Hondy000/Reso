	   	#include "..\Public\Transform.h"

void Transform::SetPositionX(FLOAT x)
	{
		m_position=(HFVECTOR3(x, m_position.y, m_position.z));
	};
	
	void Transform::SetPositionY(FLOAT y)
	{
		m_position=(HFVECTOR3(m_position.x, y, m_position.z));
	};

	void Transform::SetPositionZ(FLOAT z)
	{
		m_position=(HFVECTOR3(m_position.x, m_position.y,z));
	};
	
	void Transform::SetPosition(FLOAT x, FLOAT y, FLOAT z)
	{
		m_position=(HFVECTOR3(x, y, z));
	};

	void Transform::SetPosition(HFVECTOR3 _position)
	{
		m_position=(_position);
	};

	FLOAT Transform::GetPositionX()
	{
		return m_position.x;
	};
	FLOAT Transform::GetPositionY()
	{
		return m_position.y;
	};
	FLOAT Transform::GetPositionZ()
	{
		return m_position.z;
	};
	HFVECTOR3 Transform::GetPosition()
	{
		return m_position;
	};

	HFMATRIX Transform::GetTranslationMatrix()
	{
		HFMATRIX trans;
		HFMatrixTranslation(&trans, m_position.x, m_position.y, m_position.z);
		return trans;
	};

	void Transform::SetRotationX(const FLOAT& x)
	{
		m_rotation.x = x;
	};

	void Transform::SetRotationY(const FLOAT& y)
	{
		m_rotation.y = y;
	};

	void Transform::SetRotationZ(const FLOAT& z)
	{
		m_rotation.z = z;
	};

	void Transform::SetQuaternionRotation(HFQUATERNION q)
	{
		m_rotation = q;
	}

	void Transform::SetEulerRadAngles(const FLOAT x, const FLOAT y, const FLOAT z)
	{
		m_rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(z, y, x);

	};
	void Transform::SetEulerRadAngles(const HFVECTOR3 _rotation)
	{
		m_rotation =  DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(_rotation.z, _rotation.y, _rotation.x);
		
	};
	void Transform::SetEulerDegAngles(const FLOAT x, const FLOAT y, const FLOAT z)
	{
		m_rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(HFToRadian(z), HFToRadian(y), HFToRadian(x));

	};
	void Transform::SetEulerDegAngles(HFVECTOR3 _rotation)
	{
		if (_rotation.x>360)
		{
			_rotation.x -= 360;

		}
		else if(_rotation.x< -360)
		{
			_rotation.x += 360;
			
		}
		if (_rotation.y > 360)
		{
			_rotation.y -= 360;

		}
		else if (_rotation.y < -360)
		{
			_rotation.y += 360;

		}
		if (_rotation.z > 360)
		{
			_rotation.z -= 360;

		}
		else if (_rotation.z < -360)
		{
			_rotation.z += 360 ;

		}
		using namespace DirectX::SimpleMath;
		Quaternion q1 = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), HFToRadian(_rotation.x));
		Quaternion q2 = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(Vector3(0, 1, 0), HFToRadian(_rotation.y));
		Quaternion q3 = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), HFToRadian(_rotation.z));

		m_rotation = q1;

	};
	const FLOAT& Transform::GetQuaternionRotationX()const
	{
		return m_rotation.x;
	};
	const FLOAT& Transform::GetQuaternionRotationY()const
	{
		return m_rotation.y;
	};
	const FLOAT& Transform::GetQuaternionRotationZ()const
	{
		return m_rotation.z;
	};
	const FLOAT& Transform::GetQuaternionRotationW()const
	{
		return m_rotation.w;
	};
	HFQUATERNION Transform::GetQuaternionRotation()
	{
		return m_rotation;
	};
	const HFVECTOR3& Transform::GetEulerRadAngles()const
	{
		HFMATRIX mat = DirectX::SimpleMath::Matrix::CreateFromQuaternion((DirectX::SimpleMath::Quaternion&)m_rotation);
		HFVECTOR3 outVec = HFMatrixEulerAngles(mat);
		return outVec;
	};

	const HFVECTOR3& Transform::GetEulerDegAngles()const
	{
		HFMATRIX mat = DirectX::SimpleMath::Matrix::CreateFromQuaternion((DirectX::SimpleMath::Quaternion&)m_rotation);
		HFVECTOR3 outVec = HFMatrixEulerAngles(mat);
		outVec.x = HFToDegree(outVec.x);
		outVec.y = HFToDegree(outVec.y);
		outVec.z = HFToDegree(outVec.z);
		return outVec;
	};
	HFMATRIX Transform::GetRotationMatrixX()const
	{
		HFMATRIX rotationX;
		HFMATRIX mat = DirectX::SimpleMath::Matrix::CreateFromQuaternion((DirectX::SimpleMath::Quaternion&)m_rotation);
		HFVECTOR3 outVec = HFMatrixEulerAngles(mat);
		HFMatrixRotationX(&rotationX,HFToRadian(outVec.x));
		return rotationX;
	};

	HFMATRIX Transform::GetRotationMatrixY()const
	{
		HFMATRIX rotationY;
		HFMATRIX mat = DirectX::SimpleMath::Matrix::CreateFromQuaternion((DirectX::SimpleMath::Quaternion&)m_rotation);
		HFVECTOR3 outVec = HFMatrixEulerAngles(mat);
		HFMatrixRotationY(&rotationY, HFToRadian(outVec.y));
		return rotationY;
	};

	HFMATRIX Transform::GetRotationMatrixZ()const
	{
		HFMATRIX rotationZ;
		HFMATRIX mat = DirectX::SimpleMath::Matrix::CreateFromQuaternion((DirectX::SimpleMath::Quaternion&)m_rotation);
		HFVECTOR3 outVec = HFMatrixEulerAngles(mat);
		HFMatrixRotationZ(&rotationZ, HFToRadian(outVec.z));
		return rotationZ;
	};

	HFMATRIX Transform::GetRotationMatrix()
	{
		DirectX::SimpleMath::Quaternion q = m_rotation;
		q.Normalize();
		m_rotation = q;
		HFMATRIX mat = DirectX::SimpleMath::Matrix::CreateFromQuaternion((DirectX::SimpleMath::Quaternion&)m_rotation);
		
		HFVECTOR3 outVec = HFMatrixEulerAngles(mat);
		return mat;
	};

	void Transform::SetScaleX(const FLOAT& x)
	{
		m_scale.x = x;
	};

	void Transform::SetScaleY(const FLOAT& y)
	{
		m_scale.y = y;
	};

	void Transform::SetScaleZ(const FLOAT& z)
	{
		m_scale.z = z;
	};

	void Transform::SetScale(const FLOAT& x, const FLOAT& y, const FLOAT& z)
	{
		m_scale.x = x;
		m_scale.y = y;
		m_scale.z = z;
	};

	void Transform::SetScale(const HFVECTOR3& _scale)
	{
		m_scale = _scale;
	};


	const FLOAT& Transform::GetScaleX(void)const
	{
		return m_scale.x;
	};
	const FLOAT& Transform::GetScaleY(void)const
	{
		return m_scale.y;
	};
	const FLOAT& Transform::GetScaleZ(void)const
	{
		return m_scale.z;
	};
	const HFVECTOR3& Transform::GetScale(void)const
	{
		return m_scale;
	};

	HFMATRIX Transform::GetScalingMatrix()const
	{
		HFMATRIX scale;
		HFMatrixScaling(&scale, m_scale.x, m_scale.y, m_scale.z);
		return scale;
	};


	HFMATRIX Transform::GetWorldTransform()
	{
		HFMATRIX wolrd;
		wolrd = Transform::GetScalingMatrix() * Transform::GetRotationMatrix() * Transform::GetTranslationMatrix();
		return wolrd;
	};
