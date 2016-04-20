#pragma once
#include "BaseBuffer.h"

class IndexBuffer
	:
	public BaseBuffer
{
public:
	IndexBuffer(){};
	virtual~IndexBuffer() {};
	bool SetData(void* pIn, size_t dataSize, int count, BaseBuffer::ACCESS_FLAG access_flag) ;

	// Access the IndexCount
	int GetIndexCount(void) const
	{
		return(m_indexCount);
	};
	void SetIndexCount(int indexCount)
	{
		m_indexCount = indexCount;
	};

protected:
	int m_indexCount;
};
