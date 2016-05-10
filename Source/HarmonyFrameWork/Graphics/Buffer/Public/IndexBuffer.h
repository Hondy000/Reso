#pragma once
#include "BaseBuffer.h"

class IndexBuffer
	:
	public BaseBuffer
{
public:
	IndexBuffer(){};
	virtual~IndexBuffer() {};
	bool SetData(void* pIn, size_t dataSize, int count, BaseBuffer::ACCESS_FLAG access_flag);

protected:
};
