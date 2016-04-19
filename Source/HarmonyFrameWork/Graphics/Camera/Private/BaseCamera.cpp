/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\GraphicsObject\Basic\CBaseCamera.cpp
 *
 * @brief	Implements the base camera class.
 **************************************************************************************************/

#include "../Public/BaseCamera.h"

#include "../../RenderDevice/Basic/Public/RendererManager.h"
#include "..\..\..\Core\Actor\Public\ActorInterface.h"

/**********************************************************************************************//**
  * @fn	BOOL CBaseCamera::Setup(void)
  *
  * @brief	Gets the setup.
  *
  * @author	Kazuyuki Honda
  * @date	2015/11/04
  *
  * @return	A BOOL.
  **************************************************************************************************/


BaseCamera::BaseCamera()
{
	Init();
}

BOOL BaseCamera::Init(void)
{
	HRESULT hr = E_FAIL;
	m_aspect = sRENDER_DEVICE_MANAGER->GetScreenSize().x / sRENDER_DEVICE_MANAGER->GetScreenSize().y;
	m_cameraPosition = HFVECTOR3(0.0f, 10.0f, 20.0f);
	m_farClip = 1000.0f;
	m_nearClip = 0.1f;
	m_upVector = HFVECTOR3(0.0f, 1.0f, 0.0f);
	m_viewAngle = (FLOAT)HF_PI / 4.0f;;
	m_viewVector = HFVECTOR3(0.0f, 0.00f, 1.0f);
	m_distanceFromFollowTarget = { 0,10,20 };
	m_rotation.x = (0);
	m_rotation.y = (0);
	m_rotation.z = (0);
	return true;
}

/**********************************************************************************************//**
 * @fn	BOOL CBaseCamera::Draw(void)
 *
 * @brief	Draws this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

BOOL BaseCamera::Update(void)
{
	HFMATRIX view, proj;

	UpdateViewMatrix();
	UpdateProjectionMatrix();

	return true;
}

void BaseCamera::UpdateViewMatrix()
{
	HFMATRIX view;	
	HFVECTOR3  position, lookAt;
	
	FLOAT yaw, pitch, roll;
	HFMATRIX rotationMatrix;

	pitch = HFToRadian(m_rotation.x);
	yaw = HFToRadian(m_rotation.y);
	roll = HFToRadian(m_rotation.z);
	
	HFMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	if (m_wpFollowObject.lock() != nullptr)
	{
		// オブジェクトがセットされている	
		if (typeid(m_wpFollowObject.lock()).before(typeid(IActor)))
		{
			m_cameraPosition =
				std::dynamic_pointer_cast<IActor>(m_wpFollowObject.lock())->GetTransform()->GetPosition()
				+
				m_distanceFromFollowTarget;
		}else
		{

			m_cameraPosition =
				std::dynamic_pointer_cast<ICompornent>(m_wpFollowObject.lock())->GetTransform()->GetPosition()
				+
				m_distanceFromFollowTarget;
		}
	}



	if (m_wpViewObject.lock() != nullptr)
	{


		// オブジェクトがセットされている	
		if (typeid(m_wpViewObject.lock()).before(typeid(IActor)))
		{
			lookAt =
				
				std::dynamic_pointer_cast<IActor>(m_wpViewObject.lock())->GetTransform()->GetPosition()
				;
		}
		else
		{

			lookAt =

				std::dynamic_pointer_cast<IActor>(m_wpViewObject.lock())->GetTransform()->GetPosition()
				
				;
		}
	}

	HFMatrixLookAtLH(&view, &m_cameraPosition, &lookAt, &m_upVector);

	sRENDER_DEVICE_MANAGER->SetTransform(&view, HFTS_VIEW);

}

void BaseCamera::UpdateProjectionMatrix()
{
	HFMATRIX  proj;

	// 透視投影の設定
	HFMatrixPerspectiveFovLH(
		&proj,
		m_viewAngle,
		m_aspect,
		m_nearClip,
		m_farClip);
	sRENDER_DEVICE_MANAGER->SetTransform(&proj, HFTS_PERSPECTIVE );
}

void BaseCamera::SetFollowObject(std::shared_ptr<IBaseTask> _val)
{
	if (typeid(GetFollowObject()).before(typeid(IActor)))
	{
		m_wpFollowObject = _val;
	}
	else if (typeid(GetFollowObject()).before(typeid(ICompornent)))
	{
		m_wpFollowObject = _val;
	}
	else
	{
		m_wpFollowObject.reset();
	}
}

void BaseCamera::SetViewObject(std::shared_ptr<IBaseTask> _val)
{
	
	if (typeid(GetFollowObject()).before(typeid(IActor)))
	{
		m_wpViewObject = _val;
	}
	else if (typeid(GetFollowObject()).before(typeid(ICompornent)))
	{
		m_wpViewObject = _val;
	}
	else
	{
		m_wpFollowObject.reset();
	}
	
}
