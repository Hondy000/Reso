#include "..\Public\DX11DepthStencilView.h"
#include "..\..\..\..\..\Debug\Public\Debug.h"
#include "..\..\..\Basic\Public\RendererManager.h"

DX11DepthStencilView::DX11DepthStencilView()
{

}

DX11DepthStencilView::~DX11DepthStencilView()
{

}

Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DX11DepthStencilView::Create(
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

	CONSOLE_LOG(_T("�[�x�o�b�t�@�r���[�쐬 �J�n\n"));


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

	// �[�x�X�e���V���r���[���쐬								

	// CreateDepthStencilView
	hr = sRENDER_DEVICE->CreateDepthStencilView(m_depthMap->GetCpTexture().Get(), &descDSV, m_cpDepthStencilView.GetAddressOf());
	if (FAILED(hr)) goto EXIT;

	CONSOLE_LOG(_T("�[�x�o�b�t�@�r���[�쐬"), _T(""), _T("����\n"));

	hr = S_OK;

EXIT:

	return m_cpDepthStencilView;
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
