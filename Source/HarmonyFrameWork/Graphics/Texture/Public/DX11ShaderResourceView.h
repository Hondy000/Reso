#pragma once
#include "../../../Core/Public/Common.h"

class DX11ShaderResourceView
{
public:
	DX11ShaderResourceView();
	~DX11ShaderResourceView();


	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetShaderResourceView() const
	{
		return m_shaderResourceView;
	}

	void SetShaderResourceView(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _val)
	{
		m_shaderResourceView = _val;
	}

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;

};
