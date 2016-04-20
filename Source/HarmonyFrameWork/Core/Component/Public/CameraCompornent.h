#pragma once
#include "../../../Graphics/Camera/Public/BaseCamera.h"
#include "CompornentInterface.h"

class CameraCompornent
	:
	public ICompornent,
	public BaseCamera
{
public:
	CameraCompornent();
	~CameraCompornent();
	void Destroy() {};
	bool Init()
	{
		return true;
	};
	void Reset() {};
	bool Update();

private:
};
