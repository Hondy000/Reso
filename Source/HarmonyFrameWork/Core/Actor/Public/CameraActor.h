#pragma once
#include "ActorInterface.h"
#include "..\..\..\Graphics\Camera\Public\BaseCamera.h"

class CameraActor
	:
	virtual public IActor,
	public BaseCamera
{
public:
	CameraActor() {};
	~CameraActor() {};

	bool Init();
	void Reset() {};
	bool Update();


protected:
private:
};