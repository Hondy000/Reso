/***********************************************************************************************
 * @file Source\HarmonyFrameWork\Graphics\Camera\Public\CameraManager.h
 *
 * Declares the camera manager class.
 *************************************************************************************************/

#pragma once
#include "BaseCamera.h"
#include <memory>

/***********************************************************************************************
 * Manager for cameras.
 *
 * @author Kazuyuki
 *************************************************************************************************/

class CameraManager
{
private:

	/** The setting camera. */
	std::shared_ptr<BaseCamera> m_settingCamera;

	CameraManager() {};

public:
	~CameraManager(){}

	/***********************************************************************************************
	 * Gets the instance.
	 *
	 * @author Kazuyuki
	 *
	 * @return null if it fails, else the instance.
	 *************************************************************************************************/

	static CameraManager* GetInstance()
	{
		static CameraManager instance;
		return &instance;
	}
	std::shared_ptr<BaseCamera> GetSettingCamera() const
	{
		return m_settingCamera;
	}

	/***********************************************************************************************
	 * Sets setting camera.
	 *
	 * @author Kazuyuki
	 *
	 * @param _val The value.
	 *************************************************************************************************/

	void SetSettingCamera(std::shared_ptr<BaseCamera> _val)
	{
		m_settingCamera = _val;
	}

private:

};
