/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\GraphicsObject\Basic\CBaseCamera.cpp
 *
 * @brief	Implements the base camera class.
 **************************************************************************************************/

#include "../Public/BaseCamera.h"

#include "../../RenderDevice/Basic/Public/RendererManager.h"

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
	m_cameraPosition = HFVECTOR3(0.0f, 0.0f, -10.0f);
	m_farClip = 1000.0f;
	m_nearClip = 0.1f;
	m_upVector = HFVECTOR3(0.0f, 1.0f, 0.0f);
	m_viewAngle = (FLOAT)HF_PI / 4.0f;;
	m_viewVector = HFVECTOR3(0.0f, 0.00f, 1.0f);
	m_distanceFromFollowTarget = { 0,0,10 };
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
	HFVECTOR3 up, position, lookAt;
	{
		position = m_cameraPosition;
	}

	FLOAT yaw, pitch, roll;
	HFMATRIX rotationMatrix;

	// Setup the std::vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	
	//
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = -1.0f;

	pitch = HFToRadian(m_rotation.x);
	yaw = HFToRadian(m_rotation.y);
	roll = HFToRadian(m_rotation.z);
	
	HFMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	lookAt = position + m_viewVector;
	HFMatrixLookAtLH(&view, &position, &lookAt, &up);

	sRENDER_DEVICE_MANAGER->SetTransform(&view, HFTS_VIEW);

}

void BaseCamera::UpdateProjectionMatrix()
{
	HFMATRIX  proj;

	// “§Ž‹“Š‰e‚ÌÝ’è
	HFMatrixPerspectiveFovLH(
		&proj,
		m_viewAngle,
		m_aspect,
		m_nearClip,
		m_farClip);
	sRENDER_DEVICE_MANAGER->SetTransform(&proj, HFTS_PERSPECTIVE );
}