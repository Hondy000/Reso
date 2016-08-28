#pragma once
#include "BaseBuffer.h"
#include "..\..\Public\GraphicsTypes.h"

class VertexBuffer
	:
	public BaseBuffer
{
public:
	VertexBuffer();
	virtual~VertexBuffer();

	bool SetData(void* pIn, size_t dataSize, int count, ACCESS_FLAG access_flag);

	HFGraphics::BufferSemantics GetSemantics(int i) 
	{
		return GetSementicsLayout().m_semanticsArray[i];
	}

	void SetSemantics(int _element,HFGraphics::BufferSemantics _val)
	{
		if(GetSementicsLayout().m_semanticsArray.size() > _element)
		{
			GetSementicsLayout().m_semanticsArray[_element] = _val;
		}
		else
		{
			GetSementicsLayout().m_semanticsArray.resize(_element+1);
			GetSementicsLayout().m_semanticsArray[_element] = _val;
		}
	}

	void SetSemantics(int _element,
		TCHAR* _semanticsName,
		UINT _semanticsIndex,
		UINT _alignedByteOffset,
		HFGraphics::INPUT_CLASSIFICATION _inputSlotClass,
		UINT _instanceDataStepRate)
	{
		if (GetSementicsLayout().m_semanticsArray.size() > _element)
		{
			GetSementicsLayout().m_semanticsArray[_element] = HFGraphics::BufferSemantics
			(
				 _semanticsName,
				_semanticsIndex,
				_alignedByteOffset,
				 _inputSlotClass,
				_instanceDataStepRate
			);
		}
		else
		{
			GetSementicsLayout().m_semanticsArray.resize(_element+1);
			GetSementicsLayout().m_semanticsArray[_element] = HFGraphics::BufferSemantics
			(
				_semanticsName,
				_semanticsIndex,
				_alignedByteOffset,
				_inputSlotClass,
				_instanceDataStepRate
			);
		}
	}


	void AddSemantics(HFGraphics::BufferSemantics _val)
	{
		GetSementicsLayout().m_semanticsArray.push_back(_val);
	}

	const UINT& GetStride() const
	{
		return m_stride;
	}



	HFGraphics::BufferLayout& GetSementicsLayout() 
	{
		return m_sementicsLayout;
	}

	void SetSementicsLayout(HFGraphics::BufferLayout& _val)
	{
		m_sementicsLayout = _val;
	}

protected:
	HFGraphics::BufferLayout  m_sementicsLayout;
	UINT m_stride;
};
