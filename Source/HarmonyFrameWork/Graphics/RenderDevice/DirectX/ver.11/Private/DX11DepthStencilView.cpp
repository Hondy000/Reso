#include "..\Public\DX11DepthStencilView.h"
#include "..\..\..\..\..\Debug\Public\Debug.h"
#include "..\..\..\Basic\Public\RendererManager.h"

DX11DepthStencilView::DX11DepthStencilView()
{

}

DX11DepthStencilView::~DX11DepthStencilView()
{

}

bool DX11DepthStencilView::Create(
	float width, 
	float height,
	DWORD format
)
{

	HRESULT hr = E_FAIL;


	DXGI_SWAP_CHAIN_DESC desc;
	hr = sRENDER_DEVICE_MANAGER->GetSpSwapChain()->GetCpSwapChain()->GetDesc(&desc);

	// D3D11_TEXTURE2D_DESC
	D3D11_TEXTURE2D_DESC descDS;

	// D3D11_DEPTH_STENCIL_VIEW_DESC
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;

	//if (m_SwapChain == NULL) goto EXIT;
																
	CONSOLE_LOG("�f�v�X�X�e���V�� �쐬 �J�n\n");


	// �X���b�v�`�F�[���̐ݒ���擾����

	::ZeroMemory(&descDS, sizeof(D3D11_TEXTURE2D_DESC));
	descDS.Width = desc.BufferDesc.Width;   // �o�b�N�o�b�t�@�Ɠ����ɂ���B
	descDS.Height = desc.BufferDesc.Height;  // �o�b�N�o�b�t�@�Ɠ����ɂ���B
	descDS.MipLevels = 1;                            // �~�b�v�}�b�v���쐬���Ȃ�
	descDS.ArraySize = 1;                            // �e�N�X�`���[�̔z��
	descDS.Format = DXGI_FORMAT_R32_TYPELESS;       // �t�H�[�}�b�g
	descDS.SampleDesc.Count = desc.SampleDesc.Count;   // �o�b�N�o�b�t�@�Ɠ����ɂ���B
	descDS.SampleDesc.Quality = desc.SampleDesc.Quality; // �o�b�N�o�b�t�@�Ɠ����ɂ���B
	descDS.Usage = D3D11_USAGE_DEFAULT;          // GPU �ɂ��ǂݎ�肨��я������݃A�N�Z�X��K�v�Ƃ��郊�\�[�X�B

												 //   descDS.BindFlags          = D3D11_BIND_DEPTH_STENCIL;     // �X�e���V���o�b�t�@
	descDS.BindFlags = D3D11_BIND_DEPTH_STENCIL |    // �[�x�X�e���V���o�b�t�@�Ƃ��č쐬����
		D3D11_BIND_SHADER_RESOURCE;   // �V�F�[�_�[���\�[�X�r���[�Ƃ��č쐬����
	descDS.CPUAccessFlags = 0;                            // CPU �A�N�Z�X���s�v�B
	descDS.MiscFlags = 0;                            // ���̑��̃t���O���ݒ肵�Ȃ��B

	LogConsoleOfCreateDepthStencilTextureDesc(descDS);

	// �[�x�o�b�t�@�p�̃e�N�X�`���[�쐬
	// CreateTexture2D
	m_depthMap = std::make_shared<BaseTexture2D>();

	hr = sRENDER_DEVICE->CreateTexture2D(&descDS, NULL, m_depthMap->GetCpTexture().GetAddressOf());
	if (FAILED(hr)) goto EXIT;

	::ZeroMemory(&descDSV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

	// �e�N�X�`���[�쐬���Ɏw�肵���t�H�[�}�b�g�ƌ݊���������A�[�x�X�e���V���r���[�Ƃ��Ďw��ł���t�H�[�}�b�g���w�肷��
	//   descDSV.Format = descDS.Format;
	switch (descDS.Format)
	{
		// 8�r�b�g�t�H�[�}�b�g�͎g�p�ł��Ȃ��H
	case DXGI_FORMAT_R8_TYPELESS:
		descDSV.Format = DXGI_FORMAT_R8_UNORM;
		break;
	case DXGI_FORMAT_R16_TYPELESS:
		descDSV.Format = DXGI_FORMAT_D16_UNORM;
		break;
	case DXGI_FORMAT_R32_TYPELESS:
		descDSV.Format = DXGI_FORMAT_D32_FLOAT;
		break;
	case DXGI_FORMAT_R24G8_TYPELESS:
		descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		break;
	default:
		descDSV.Format = descDS.Format;
	}

	// �}���`�T���v�����g�p���Ă���ꍇ
	if (desc.SampleDesc.Count > 1)
	{
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	}

	// �}���`�T���v�����g�p���Ă��Ȃ��ꍇ
	else
	{
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	}

	descDSV.Texture2D.MipSlice = 0;

	
	LogConsoleOfCreateDepthStencilViewDesc(descDSV);
	// �[�x�X�e���V���r���[���쐬								

	// CreateDepthStencilView
	hr = sRENDER_DEVICE->CreateDepthStencilView(m_depthMap->GetCpTexture().Get(), &descDSV, m_cpDepthStencilView.GetAddressOf());
	if (FAILED(hr))
	{
		CONSOLE_LOG("�f�v�X�X�e���V�� �쐬 ���s\n");
		return false;
	}

	CONSOLE_LOG("�f�v�X�X�e���V�� �쐬 ����\n");

	hr = S_OK;

EXIT:

	return true;
}

void DX11DepthStencilView::LogConsoleOfCreateDepthStencilTextureDesc(D3D11_TEXTURE2D_DESC _DX11Texture2DDesc)
{

	CONSOLE_LOG("=====DepthStencil Texture Status=====\n");
	CONSOLE_LOG("Width = ", _DX11Texture2DDesc.Width,"\n");
	CONSOLE_LOG("Height = ", _DX11Texture2DDesc.Height, "\n");
	CONSOLE_LOG("MipLevels = ", _DX11Texture2DDesc.MipLevels, "\n");
	CONSOLE_LOG("ArraySize = ", _DX11Texture2DDesc.ArraySize, "\n");
	CONSOLE_LOG("Format(DXGI_FORMAT) = ",_DX11Texture2DDesc.Format, "\n");
	CONSOLE_LOG("BinFlags = ", _DX11Texture2DDesc.BindFlags, "\n");
	CONSOLE_LOG("CPUAccessFlags = ", _DX11Texture2DDesc.CPUAccessFlags, "\n");
	CONSOLE_LOG("Usage(D3D11_USAGE) = ", _DX11Texture2DDesc.Usage, "\n");
	CONSOLE_LOG("SampleDesc.Count = ", _DX11Texture2DDesc.SampleDesc.Count, "\n");
	CONSOLE_LOG("SampleDesc.Quality = ", _DX11Texture2DDesc.SampleDesc.Quality, "\n");
	CONSOLE_LOG("=====================================\n");
}


void DX11DepthStencilView::LogConsoleOfCreateDepthStencilViewDesc(D3D11_DEPTH_STENCIL_VIEW_DESC _DX11DepthStencilViewDesc)
{
	CONSOLE_LOG("==================DepthStencil View Status==================\n");
	CONSOLE_LOG("Flags = ", _DX11DepthStencilViewDesc.Flags, "\n");
	CONSOLE_LOG("Format(DXGI_FORMAT) = ", (_DX11DepthStencilViewDesc.Format), "\n");
	CONSOLE_LOG("ViewDimension = ", (_DX11DepthStencilViewDesc.ViewDimension), "\n\n");

	CONSOLE_LOG("Texture1D MipSlice = ", _DX11DepthStencilViewDesc.Texture1D.MipSlice, "\n\n");

	CONSOLE_LOG("Texture1DArray ArraySize = ", _DX11DepthStencilViewDesc.Texture1DArray.ArraySize, "\n");
	CONSOLE_LOG("Texture1DArray FirstArraySlice = ", _DX11DepthStencilViewDesc.Texture1DArray.FirstArraySlice, "\n");
	CONSOLE_LOG("Texture1DArray MipSlice = ", _DX11DepthStencilViewDesc.Texture1DArray.MipSlice, "\n\n");

	CONSOLE_LOG("Texture2D MipSlice = ", _DX11DepthStencilViewDesc.Texture2D.MipSlice, "\n\n");

	CONSOLE_LOG("Texture2DArray ArraySize = ", _DX11DepthStencilViewDesc.Texture2DArray.ArraySize, "\n");
	CONSOLE_LOG("Texture2DArray FirstArraySlice = ", _DX11DepthStencilViewDesc.Texture2DArray.FirstArraySlice, "\n");
	CONSOLE_LOG("Texture2DArray MipSlice = ", _DX11DepthStencilViewDesc.Texture2DArray.MipSlice, "\n\n");

	CONSOLE_LOG("Texture2DMS UnusedField_NothingToDefine = ", _DX11DepthStencilViewDesc.Texture2DMS.UnusedField_NothingToDefine, "\n\n");

	CONSOLE_LOG("Texture2DMSArray ArraySize = ", _DX11DepthStencilViewDesc.Texture2DMSArray.ArraySize, "\n");
	CONSOLE_LOG("Texture2DMSArray FirstArraySlice = ", _DX11DepthStencilViewDesc.Texture2DMSArray.FirstArraySlice, "\n");

	CONSOLE_LOG("==============================================================\n");
}


Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& DX11DepthStencilView::GetDepthStencilView()
{
	return m_cpDepthStencilView;
}

void DX11DepthStencilView::SetDepthStencilView(Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& _val)
{
	m_cpDepthStencilView = _val;
}


Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& DX11DepthStencilView::GetDepthStencilState()
{
	return m_cpDepthStencilState;
}

void DX11DepthStencilView::SetDepthStencilState(Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& _val)
{
	m_cpDepthStencilState = _val;
}
