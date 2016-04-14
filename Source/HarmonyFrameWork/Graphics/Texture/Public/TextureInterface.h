#pragma once
#include "../../../Core/Public/IBaseObject.h"

class IBaseTexture
	:
	public IBaseObject
{
public:
	IBaseTexture() {};
	virtual ~IBaseTexture() {};
#ifdef DIRECTX11

	virtual BOOL CreateShaderResource()
	{

		return E_FAIL;//;Factorys::ComShaderRenderViewFactory::GetInstance()->CreateShaderResourceView(m_cpTexture, m_cpSharderResorceView);

	};


	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSharderResorceView()
	{
		return m_cpSharderResorceView;
	}

	void SetSharderResorceView(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& val)
	{
		m_cpSharderResorceView = val;
	}

#endif



	// Access the Name
	const std::string& GetName(void) const	{ return(m_name);	};
	void SetName(const std::string& name)	{ m_name = name;	};

protected:


	std::string m_name;
#ifdef DIRECTX11
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cpSharderResorceView;	// シェーダリソースビュー
#endif

};