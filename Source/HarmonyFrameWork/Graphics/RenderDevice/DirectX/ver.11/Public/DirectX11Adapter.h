#pragma once
#include "../../../../../Core/Public/Common.h"
class DirectX11Adapter
{
public:
	DirectX11Adapter();
	~DirectX11Adapter();

	BOOL Setup(void);

	// �A�_�v�^�[�̎擾
	Microsoft::WRL::ComPtr<IDXGIAdapter> GetAdapter(void) const
	{
		return(m_cpAdapter);
	};

	// �A�_�v�^�[�̍쐬
	BOOL CreateAdapter(void);

	// �A�_�v�^�[�̃����[�X
	void ReleaseAdapter(void);

protected:

	Microsoft::WRL::ComPtr<IDXGIAdapter>           m_cpAdapter;                 // �A�_�v�^�[
};
