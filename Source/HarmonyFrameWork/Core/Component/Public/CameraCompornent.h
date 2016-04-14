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
	BOOL Init()
	{
		return true;
	};
	void Reset() {};
	BOOL Update();

private:
};
