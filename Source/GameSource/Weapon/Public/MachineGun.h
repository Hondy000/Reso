#pragma once

#include "IBaseWeapon.h"

class MachineGun
	:
	public IBaseWeapon
{
public:
	MachineGun(){};
	~MachineGun(){};

	void Use();
	bool Init();

private:

};
