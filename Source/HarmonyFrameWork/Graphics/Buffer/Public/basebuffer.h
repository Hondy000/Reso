#pragma once
#include "../../../Core/Public/IBaseObject.h"


class BaseBuffer :
	public IBaseObject
{
public:
	enum class ACCESS_FLAG
	{
		WRITEONLY,
		READONLY,
		WRITEANDREAD,
	};

	enum class BIND_FLAG
	{
		VERTEX_BUFFER,
		INDEX_BUFFER,
		CONSTANT_BUFFER,
		OTHER,
	};


	// ReSharper disable once CppPossiblyUninitializedMember
	BaseBuffer()
	{
	};
	virtual~BaseBuffer()
	{
	};
	virtual BOOL SetData(void* pIn, size_t, int count, ACCESS_FLAG) = 0;
	virtual BOOL GetData(void* pOut, size_t);
	virtual ACCESS_FLAG GetAccessFlag(void)
	{
		return m_accessFlag;
	};
	virtual BIND_FLAG GetBindsFlag(void) { return BIND_FLAG::OTHER; };

	virtual int GetDataCount()
	{
		return m_dataCount;
	};

#ifdef DIRECTX9
#endif

#ifdef DIRECTX11
	ID3D11Buffer* Get()
	{
		return m_cpBuffer.Get();
	}

	virtual D3D11_BIND_FLAG GetD311BindFlag(BIND_FLAG flag);
	DWORD GetD311AccessFlag(BaseBuffer::ACCESS_FLAG flag);
	ID3D11Buffer** GetAddressOf()
	{
		return m_cpBuffer.GetAddressOf();
	}

	virtual Microsoft::WRL::ComPtr<ID3D11Buffer>&GetBuffer()
	{
		return m_cpBuffer;
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_cpBuffer;
#endif
				  
	int m_dataCount;
	ACCESS_FLAG m_accessFlag;

};
