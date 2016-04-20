#pragma once
#include "../../../Core/Public/IBaseObject.h"
#include "TextureInterface.h"


class BaseTexture2D
	:
	public IBaseTexture
{
public:
	BaseTexture2D()
	{
	};

	virtual ~BaseTexture2D()
	{
	};

	std::string GetName()
	{
		return m_name;
	}

	virtual bool Load(const std::string& path)
	{
		return E_FAIL;
	}

	// Access the CpTexture
	const Microsoft::WRL::ComPtr<ID3D11Texture2D>& GetCpTexture(void) const		{ return(m_cpTexture);		};
	void SetCpTexture(const Microsoft::WRL::ComPtr<ID3D11Texture2D>& cpTexture)	{ m_cpTexture = cpTexture;	};

protected:
#ifdef DIRECTX11
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_cpTexture;
#endif // DIRECTX11

};
