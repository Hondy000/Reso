#include "..\Public\CameraActor.h"

BOOL CameraActor::Init()
{
	return true;
}

BOOL CameraActor::Update()
{
	BaseCamera::Update();
	return true;
}

