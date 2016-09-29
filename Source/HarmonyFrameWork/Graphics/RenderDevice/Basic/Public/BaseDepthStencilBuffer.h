#pragma once				
#include "../../../../Core/Public/Common.h"

class BaseDepthStencilBuffer
{
public:
	BaseDepthStencilBuffer();
	virtual~BaseDepthStencilBuffer();
	
	virtual bool Create
	(
		float width,
		float height,
		DWORD format
	) = 0;
};