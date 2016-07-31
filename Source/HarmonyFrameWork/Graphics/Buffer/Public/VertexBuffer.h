#pragma once
#include "BaseBuffer.h"

class VertexBuffer
	:
	public BaseBuffer
{
public:
	VertexBuffer();
	virtual~VertexBuffer();

	bool SetData(void* pIn, size_t dataSize, int count, ACCESS_FLAG access_flag);

	DWORD GetSemantics() const
	{
		return m_semantics;
	}

	void SetSemantics(DWORD _val)
	{
		m_semantics = _val;
	}

	const UINT& GetStride() const
	{
		return m_stride;
	}


protected:
	DWORD m_semantics;
	UINT m_stride;
};
