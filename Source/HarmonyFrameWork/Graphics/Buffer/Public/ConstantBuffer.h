﻿#pragma once
#include "BaseBuffer.h"

class ConstantBuffer
	:
	public BaseBuffer
{
public:
	ConstantBuffer();
	virtual~ConstantBuffer() ;
	BOOL SetData(void* pIn, size_t dataSize, int count, ACCESS_FLAG access_flag);
protected:
};
