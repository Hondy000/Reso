/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\Renderer\DirectX\ver.11\CDirectX11RenderDeviceManager.cpp
 *
 * @brief	Implements the direct x coordinate 11 render device manager class.
 **************************************************************************************************/

#include <fstream>
#include "../../../../Public/GraphicsTypes.h"
#include "../Public/DirectX11RenderDeviceManager.h"
#include "../Public/GeometryBuffers.h"
#include "../../../../../Utility/Public/StringUtility.h"
#include "../../../Basic/Public/RendererManager.h"
#include "..\..\..\..\..\Utility\Public\HFString.h"
#include "..\..\..\..\..\Platform\Windows\BaseWindow.h"
using namespace std;	
using namespace Microsoft::WRL;

/**********************************************************************************************//**
 * @fn	CDirectX11RenderDeviceManager::CDirectX11RenderDeviceManager()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 **************************************************************************************************/

DirectX11RenderDeviceManager::DirectX11RenderDeviceManager()
{
}

/**********************************************************************************************//**
 * @fn	CDirectX11RenderDeviceManager::~CDirectX11RenderDeviceManager()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 **************************************************************************************************/

DirectX11RenderDeviceManager::~DirectX11RenderDeviceManager()
{
	m_cpRenderTargetView.Reset();
	m_cpD3DDebug.Reset();
	m_cpDepthStencilView.Reset();
	m_cpImmediateContext.Reset();
	m_cpD3DDevice.Reset();
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::Setup(void)
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	A long.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::Setup(void)
{
	HRESULT hr = S_OK;

	// �������m��
	m_spAdapter = std::shared_ptr<DirectX11Adapter>(new DirectX11Adapter);
	m_spSwapChain = std::shared_ptr<DirectX11SwapChain>(new DirectX11SwapChain);

	m_spSwapChain->SetWpAdapter(m_spAdapter);

	// �\�����[�h���L�q���邽�߂̍\���́B
	// DXGI_MODE_DESC
	// �f�B�X�v���C���[�h���Œ�őI������ꍇ�̃T���v���R�[�h
	::ZeroMemory(&m_displayMode, sizeof(m_displayMode));
	m_displayMode.Width = 1280;
	m_displayMode.Height = 720;
	m_displayMode.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_displayMode.RefreshRate.Numerator = 60;
	m_displayMode.RefreshRate.Denominator = 1;

	// �f�B�X�v���C���[�h�ꗗ���擾����B
	// �擾�����l�̓N���X�����ɕێ������B
	hr = GetDisplayMode();
	if (FAILED(hr))
	{
		::MessageBox(NULL, _T("�f�B�X�v���C���[�h�擾�G���["), _T("�������G���["), MB_OK);
	}

	// �Ƃ肠�����ŏ��Ɍ��������f�B�X�v���C���[�h��I������
	//CopyMemory(&m_displayMode, &m_DisplayModeDesc[m_DisplayModeDesc.size()-1], sizeof(DXGI_MODE_DESC));

	m_screenSize.x = m_displayMode.Width;
	m_screenSize.y = m_displayMode.Height;
	InitD3D11(&m_displayMode, true, true, true, true);	
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::InitD3D11( DXGI_MODE_DESC* pDisplayMode, bool Windowed, bool DirectX11Only, bool MultisampleEnabled, bool UseDepthBuffer )
 *
 * @brief	�E�B���h�E�̍쐬 ����� Direct3D�̏�����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pDisplayMode	If non-null, the display mode.
 * @param	Windowed				true if windowed.
 * @param	DirectX11Only			true to direct x coordinate 11 only.
 * @param	MultisampleEnabled  	true to enable, false to disable the multisample.
 * @param	UseDepthBuffer			true to use depth buffer.
 *
 * @return	A hResult.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::InitD3D11(
	DXGI_MODE_DESC* pDisplayMode,
	bool Windowed,
	bool DirectX11Only,
	bool MultisampleEnabled,
	bool UseDepthBuffer
	)
{
	HRESULT hr = E_FAIL;
		   
	WindowManager::GetInstance()->CreateMainWindow(false);
	m_UseDepthBuffer = UseDepthBuffer;

	// �A�_�v�^�[���擾�B
	hr = m_spAdapter->CreateAdapter();
	if (FAILED(hr)) goto EXIT;

	// �f�o�C�X�̍쐬
	hr = CreateDevice(DirectX11Only);
	if (FAILED(hr)) goto EXIT;
	m_hWnd = WindowManager::GetInstance()->GetMainWindow()->GetHWND();
	m_spSwapChain->SetCpDevice(m_cpD3DDevice);

	// �X���b�v�`�F�[���̍쐬
	hr = m_spSwapChain->CreateSwapChain(pDisplayMode, MultisampleEnabled,m_hWnd);
	if (FAILED(hr)) goto EXIT;

	// �����_�����O�^�[�Q�b�g�r���[�̍쐬
	hr = CreateRenderTargetView();
	if (FAILED(hr)) goto EXIT;

	// �[�x�X�e���V���r���[�̍쐬
	hr = CreateDepthStencilView();
	if (FAILED(hr)) goto EXIT;

	// �^�[�Q�b�g�r���[�̐ݒ�
	m_cpImmediateContext->OMSetRenderTargets(1,
		m_cpRenderTargetView.GetAddressOf(),
		m_cpDepthStencilView.Get());

	// �r���[�|�[�g�쐬
	hr = CreateViewport();
	if (FAILED(hr)) goto EXIT;

	// �\�����[�h�̎����؊����𖳌��ɂ���B
	// �����؊�����L���ɂ���ꍇ�͂��̊֐����R�����g�A�E�g����B
	// �������R�����g�A�E�g�����ꍇ�A�����N�����t���X�N���[�����[�h�ɂ����Ƃ����������삵�Ă���Ȃ��B
	hr = SetWindowAssociation();
	if (FAILED(hr)) goto EXIT;

	// �f�t�H���g�̃��X�^���C�U��ݒ肷��
	hr = SetDefaultRasterize();
	if (FAILED(hr)) goto EXIT;

	// �f�t�H���g�̐[�x�X�e���V���X�e�[�g��ݒ肷��
	hr = SetDefaultDepthStencilState();
	if (FAILED(hr)) goto EXIT;

	// �E�B���h�E�쐬��X���b�v�`�F�[���̏��������ɂ̓E�B���h�E���[�h�ō쐬����B
	// ����N�����t���X�N���[���ɂ���ꍇ�́A�������I����ɕ\�����[�h��ύX����悤�ɂ���B
	if (Windowed == FALSE)
	{
		hr = ChangeWindowMode();
		if (FAILED(hr))
		{
			goto EXIT;
		}
	}					 

	// Geometry�o�b�t�@�̏�����
	SetupGeometryBuffer();

	OutputMsg(_T("����������"), _T(""), _T("(^�B^)"));

	//�E�B���h�E�\���E�X�V
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	hr = S_OK;

EXIT:
	m_spAdapter->ReleaseAdapter();

	return hr;
}

/**********************************************************************************************//**
 * @fn	void CDirectX11RenderDeviceManager::Clear(void)
 *
 * @brief	Clears this object to its blank/initial state.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 **************************************************************************************************/

void DirectX11RenderDeviceManager::ClearScreen(void)
{
	HRESULT hr = E_FAIL;
	HFMATRIX matWorld, matView, matProj, matWVP;

	FLOAT ClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// �o�b�N�o�b�t�@���N���A
	m_cpImmediateContext->ClearRenderTargetView(m_cpRenderTargetView.Get(), ClearColor);

	// �[�x�o�b�t�@���N���A
	if (m_cpDepthStencilView)
	{
		m_cpImmediateContext->ClearDepthStencilView(m_cpDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	if (m_spDeferredBuffer)
	{
	
		m_spDeferredBuffer->ClearRenderTargets(GetImmediateContext(), 0.0f, 0.0f, 0.0f, 0.0f);
	}
}

/**********************************************************************************************//**
 * @fn	void CDirectX11RenderDeviceManager::BeginRender(void)
 *
 * @brief	Begins a render.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 **************************************************************************************************/

void DirectX11RenderDeviceManager::BeginRender(void)
{

}

/**********************************************************************************************//**
 * @fn	void CDirectX11RenderDeviceManager::EndRender(void)
 *
 * @brief	Ends a render.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 **************************************************************************************************/

void DirectX11RenderDeviceManager::EndRender(void)
{
	HRESULT hr = E_FAIL;

	// �����_�����O���ꂽ�C���[�W�����[�U�[�ɕ\���B
	hr = m_spSwapChain->GetCpSwapChain()->Present(0, 0);
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::SetUpDeferredRenderer()
 *
 * @brief	Sets up the deferred renderer.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @return	A bool.
 **************************************************************************************************/
 /*
bool CDirectX11RenderDeviceManager::SetUpDeferredRenderer()
{
//	m_deferredRenderer = std::shared_ptr<DirectX11DeferredRenderer>(new DirectX11DeferredRenderer);
//	m_deferredRenderer->Setup();
	return S_OK;
}	  */

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::GetDisplayMode()
 *
 * @brief	�f�t�H���g�f�B�X�v���C�̃��[�h��񋓂���.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	The display mode.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::GetDisplayMode()
{
	HRESULT hr = E_FAIL;
	IDXGIOutput* pOutput = NULL;
	DXGI_MODE_DESC* desc = NULL;

	TCHAR s[256];

	OutputMsg(_T("�f�B�X�v���C���[�h�ꗗ�̗�"), _T(""), _T("�J�n"));

	m_DisplayModeDesc.clear();

	// �A�_�v�^�[���擾�B
	hr = m_spAdapter->CreateAdapter();
	if (FAILED(hr)) goto EXIT;

	// �A�_�v�^�[�ɐڑ�����Ă���v���C�}���f�B�X�v���C���擾�B
	// IDXGIAdapter::EnumOutputs
	hr = m_spAdapter->GetAdapter()->EnumOutputs(0, &pOutput);
	if (FAILED(hr)) goto EXIT;

	UINT num;

	// �f�B�X�v���C���[�h�ꗗ�̔z�񐔂��擾
	// IDXGIOutput::GetDisplayModeList
	hr = pOutput->GetDisplayModeList(D3D11USER_FORMAT, 0, &num, NULL);
	if (FAILED(hr)) goto EXIT;

	desc = new DXGI_MODE_DESC[num];

	// �f�B�X�v���C���[�h�̈ꗗ���擾
	hr = pOutput->GetDisplayModeList(D3D11USER_FORMAT, 0, &num, desc);
	if (FAILED(hr)) goto EXIT;

	for (UINT i = 0; i < num; i++)
	{
		m_DisplayModeDesc.push_back(desc[i]);
		_stprintf_s(s, _T("�𑜓x( %d : %d )�@���t���b�V�����[�g( %d / %d )"),
			m_DisplayModeDesc[i].Width, m_DisplayModeDesc[i].Height, m_DisplayModeDesc[i].RefreshRate.Denominator, m_DisplayModeDesc[i].RefreshRate.Numerator);
		OutputMsg(_T("�f�B�X�v���C���[�h"), s, _T("���X�g�ɒǉ�"));
	}

	OutputMsg(_T("�f�B�X�v���C���[�h�ꗗ�̗�"), _T(""), _T("����"));

	hr = S_OK;

EXIT:
	SAFE_DELETE_ARRAY(desc);
	SAFE_RELEASE(pOutput);

	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateDevice(bool DirectX11Only)
 *
 * @brief	�f�o�C�X�̍쐬.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param	DirectX11Only	true to direct x coordinate 11 only.
 *
 * @return	The new device.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateDevice(bool DirectX11Only)
{
	HRESULT hr = E_FAIL;


	// �f�o�C�X�쐬���Ɏg�p����r�f�I�J�[�h�̐��\�ꗗ
	// D3D_FEATURE_LEVEL
	D3D_FEATURE_LEVEL FeatureLevel[] = {
		D3D_FEATURE_LEVEL_11_0,  // Direct3D 11.0 SM 5
		D3D_FEATURE_LEVEL_10_1,  // Direct3D 10.1 SM 4
		D3D_FEATURE_LEVEL_10_0,  // Direct3D 10.0 SM 4
		D3D_FEATURE_LEVEL_9_3,   // Direct3D 9.3  SM 3
		D3D_FEATURE_LEVEL_9_2,   // Direct3D 9.2  SM 2
		D3D_FEATURE_LEVEL_9_1,   // Direct3D 9.1  SM 2
	};
	int featureCnt = 0;

	// �r�f�I�J�[�h��DirectX11����уV�F�[�_�[���f��5���T�|�[�g������ł̂ݎ��s�\
	if (DirectX11Only == TRUE)
		featureCnt = 1;

	// �r�f�I�J�[�h���T�|�[�g����Direct3D����уV�F�[�_�[���f���̃o�[�W��������ʂ��玩���I��
	else
		featureCnt = sizeof(FeatureLevel) / sizeof(D3D_FEATURE_LEVEL);

#if defined(DEBUG) || defined(_DEBUG)

	// �f�o�b�O�R���p�C���̏ꍇ�A�f�o�b�O���C���[��L���ɂ���B
	// �\�t�g�E�F�A ���C���[
	UINT createDeviceFlag = D3D11_CREATE_DEVICE_DEBUG;
#else
	UINT createDeviceFlag = 0;
#endif
	hr = D3D11CreateDevice(
		m_spAdapter->GetAdapter().Get(),
		D3D_DRIVER_TYPE_UNKNOWN,
		NULL,
		createDeviceFlag,
		FeatureLevel,
		featureCnt,
		D3D11_SDK_VERSION,
		m_cpD3DDevice.GetAddressOf(),
		&m_FeatureLevel,
		m_cpImmediateContext.GetAddressOf());

	if (FAILED(hr)) goto EXIT;

	// �A�_�v�^�[�̏����擾
	// DXGI_ADAPTER_DESC
	DXGI_ADAPTER_DESC desc;
	m_spAdapter->GetAdapter()->GetDesc(&desc);

	// DirectX�̃o�[�W�����A�V�F�[�_���f���̃o�[�W�����ƍ̗p�����A�_�v�^�[�̖��O���f�o�b�N�E�B���h�E�ɏo��
	TCHAR s[256];
	switch (m_FeatureLevel)
	{
	case D3D_FEATURE_LEVEL_11_0:
		_stprintf_s(s, _T("Direct3D(11.0) SM(5)�@%s"), desc.Description);
		break;
	case D3D_FEATURE_LEVEL_10_1:
		_stprintf_s(s, _T("Direct3D(10.1) SM(4)�@%s"), desc.Description);
		break;
	case D3D_FEATURE_LEVEL_10_0:
		_stprintf_s(s, _T("Direct3D(10.0) SM(4)�@%s"), desc.Description);
		break;
	case D3D_FEATURE_LEVEL_9_3:
		_stprintf_s(s, _T("Direct3D(9.3) SM(3)�@%s"), desc.Description);
		break;
	case D3D_FEATURE_LEVEL_9_2:
		_stprintf_s(s, _T("Direct3D(9.2) SM(2)�@%s"), desc.Description);
		break;
	case D3D_FEATURE_LEVEL_9_1:
		_stprintf_s(s, _T("Direct3D(9.1) SM(2)�@%s"), desc.Description);
		break;
	}


	// �f�o�C�X�쐬�͊���

	// �쐬
	hr = m_cpD3DDevice.Get()->QueryInterface(__uuidof(ID3D11Debug),(void**)(m_cpD3DDebug.GetAddressOf()));
	if (FAILED(hr))
	{
		return E_FAIL;
	}
	if (SUCCEEDED(hr))

		//	OutputMsg(_T("�r�f�I�J�[�h"), s, _T("�O�j"));
		//else
			//OutputMsg(_T("�r�f�I�J�[�h"), s, _T("�m�f"));

		//OutputMsg(_T("�f�o�C�X�쐬"), _T(""), _T("����"));

		hr = S_OK;
EXIT:

	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateRenderTargetView()
 *
 * @brief	�����_�����O�^�[�Q�b�g�r���[�̍쐬.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	The new render target view.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateRenderTargetView()
{
	HRESULT hr = E_FAIL;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer = NULL;

	OutputMsg(_T("�����_�����O�^�[�Q�b�g�r���[�쐬"), _T(""), _T("�J�n"));

	// �X���b�v�`�F�[������o�b�N�o�b�t�@���擾����
	hr = m_spSwapChain->GetCpSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	if (FAILED(hr)) goto EXIT;

	// �����_�����O�^�[�Q�b�g�r���[�̍쐬
	// CreateRenderTargetView
	hr = m_cpD3DDevice->CreateRenderTargetView(pBackBuffer.Get(), NULL, m_cpRenderTargetView.GetAddressOf());
	if (FAILED(hr)) goto EXIT;

	OutputMsg(_T("�����_�����O�^�[�Q�b�g�r���[�쐬"), _T(""), _T("����"));

	hr = S_OK;
EXIT:

	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateDepthStencilView()
 *
 * @brief	�[�x�X�e���V���r���[�̍쐬.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	The new depth stencil view.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateDepthStencilView()
{
	HRESULT hr = E_FAIL;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer = NULL;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthBuffer = NULL;

	// D3D11_TEXTURE2D_DESC
	D3D11_TEXTURE2D_DESC descDS;

	// D3D11_DEPTH_STENCIL_VIEW_DESC
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;

	if (m_UseDepthBuffer == FALSE)
	{
		hr = S_OK;
		goto EXIT;
	}

	//if (m_SwapChain == NULL) goto EXIT;

	OutputMsg(_T("�[�x�o�b�t�@�r���[�쐬"), _T(""), _T("�J�n"));

	DXGI_SWAP_CHAIN_DESC chainDesc;

	// �X���b�v�`�F�[���̐ݒ���擾����
	// GetDesc
	hr = m_spSwapChain->GetCpSwapChain()->GetDesc(&chainDesc);
	if (FAILED(hr)) goto EXIT;

	::ZeroMemory(&descDS, sizeof(D3D11_TEXTURE2D_DESC));
	descDS.Width = chainDesc.BufferDesc.Width;   // �o�b�N�o�b�t�@�Ɠ����ɂ���B
	descDS.Height = chainDesc.BufferDesc.Height;  // �o�b�N�o�b�t�@�Ɠ����ɂ���B
	descDS.MipLevels = 1;                            // �~�b�v�}�b�v���쐬���Ȃ�
	descDS.ArraySize = 1;                            // �e�N�X�`���[�̔z��
	descDS.Format = D3D11USER_DEPTH_FORMAT;       // �t�H�[�}�b�g
	descDS.SampleDesc.Count = chainDesc.SampleDesc.Count;   // �o�b�N�o�b�t�@�Ɠ����ɂ���B
	descDS.SampleDesc.Quality = chainDesc.SampleDesc.Quality; // �o�b�N�o�b�t�@�Ɠ����ɂ���B
	descDS.Usage = D3D11_USAGE_DEFAULT;          // GPU �ɂ��ǂݎ�肨��я������݃A�N�Z�X��K�v�Ƃ��郊�\�[�X�B

	//   descDS.BindFlags          = D3D11_BIND_DEPTH_STENCIL;     // �X�e���V���o�b�t�@
	descDS.BindFlags = D3D11_BIND_DEPTH_STENCIL |    // �[�x�X�e���V���o�b�t�@�Ƃ��č쐬����
		D3D11_BIND_SHADER_RESOURCE;   // �V�F�[�_�[���\�[�X�r���[�Ƃ��č쐬����
	descDS.CPUAccessFlags = 0;                            // CPU �A�N�Z�X���s�v�B
	descDS.MiscFlags = 0;                            // ���̑��̃t���O���ݒ肵�Ȃ��B

	// �[�x�o�b�t�@�p�̃e�N�X�`���[�쐬
	// CreateTexture2D
	hr = m_cpD3DDevice->CreateTexture2D(&descDS, NULL, pDepthBuffer.GetAddressOf());
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
	if (chainDesc.SampleDesc.Count > 1)
	{
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	}

	// �}���`�T���v�����g�p���Ă��Ȃ��ꍇ
	else                              descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	descDSV.Texture2D.MipSlice = 0;

	// �[�x�X�e���V���r���[���쐬
	// CreateDepthStencilView
	hr = m_cpD3DDevice->CreateDepthStencilView(pDepthBuffer.Get(), &descDSV, m_cpDepthStencilView.GetAddressOf());
	if (FAILED(hr)) goto EXIT;

	OutputMsg(_T("�[�x�o�b�t�@�r���[�쐬"), _T(""), _T("����"));

	hr = S_OK;

EXIT:

	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateViewport()
 *
 * @brief	�r���[�|�[�g�̍쐬.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	The new viewport.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateViewport()
{
	HRESULT hr = E_FAIL;

	//if (m_SwapChain == NULL) goto EXIT;

	OutputMsg(_T("�r���[�|�[�g�쐬"), _T(""), _T("�J�n"));

	DXGI_SWAP_CHAIN_DESC chainDesc;

	// �X���b�v�`�F�[���̐ݒ���擾����
	hr = m_spSwapChain->GetCpSwapChain()->GetDesc(&chainDesc);
	if (FAILED(hr)) goto EXIT;

	m_viewport[0].TopLeftX = 0;
	m_viewport[0].TopLeftY = 0;
	m_viewport[0].Width = (FLOAT)chainDesc.BufferDesc.Width;
	m_viewport[0].Height = (FLOAT)chainDesc.BufferDesc.Height;
	m_viewport[0].MinDepth = 0.0f;
	m_viewport[0].MaxDepth = 1.0f;

	// RSSetViewports
	m_cpImmediateContext->RSSetViewports(1, m_viewport);

	OutputMsg(_T("�r���[�|�[�g�쐬"), _T(""), _T("����"));

	hr = S_OK;
EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::SetWindowAssociation()
 *
 * @brief	�E�B���h�E�A�\�V�G�[�V����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	A hResult.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::SetWindowAssociation()
{
	HRESULT hr = E_FAIL;
	IDXGIFactory* pFactory = NULL;

	OutputMsg(_T("�E�B���h�E�A�\�V�G�[�V�����ݒ�"), _T(""), _T("�J�n"));

	// �t�@�N�g���[���쐬����
	// CreateDXGIFactory�ō쐬�����t�@�N�g���[���g�p����Ǝ��s�ł��邪���[�j���O�G���[�ɂȂ�̂� IDXGIAdapter ����쐬����B
	hr = m_spAdapter->GetAdapter()->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);
	if (FAILED(hr)) goto EXIT;

	// �\�����[�h�̎����؊����𖳌��ɂ���B
	// MakeWindowAssociation
	hr = pFactory->MakeWindowAssociation(m_hWnd, DXGI_MWA_NO_WINDOW_CHANGES);
	if (FAILED(hr)) goto EXIT;

	OutputMsg(_T("�E�B���h�E�A�\�V�G�[�V�����ݒ�"), _T(""), _T("����"));

	hr = S_OK;
EXIT:
	SAFE_RELEASE(pFactory);

	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::SetDefaultRasterize()
 *
 * @brief	�f�t�H���g�̃��X�^���C�U��ݒ�.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	A hResult.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::SetDefaultRasterize()
{
	HRESULT hr = E_FAIL;

	OutputMsg(_T("�f�t�H���g�̃��X�^���C�U��ݒ�"), _T(""), _T("�J�n"));

	// ID3D11RasterizerState
	// D3D11_RASTERIZER_DESC
	m_rasterStateDesc.FillMode = D3D11_FILL_SOLID;    // �|���S���ʕ`��
	m_rasterStateDesc.CullMode = D3D11_CULL_BACK;     // ���ʂ�`�悵�Ȃ�
	m_rasterStateDesc.FrontCounterClockwise = TRUE;  // ���v����\��
	m_rasterStateDesc.FrontCounterClockwise = FALSE;   // �����v����\��
	m_rasterStateDesc.DepthBias = 0;
	m_rasterStateDesc.DepthBiasClamp = 0;
	m_rasterStateDesc.SlopeScaledDepthBias = 0;
	m_rasterStateDesc.DepthClipEnable = TRUE;
	m_rasterStateDesc.ScissorEnable = FALSE;          // �V�U�[��`����

	// �X���b�v�`�F�[���̃}���`�T���v�����O�̐ݒ�ɂ��킹��
	DXGI_SWAP_CHAIN_DESC swapDesc;
	m_spSwapChain->GetCpSwapChain()->GetDesc(&swapDesc);
	if (swapDesc.SampleDesc.Count != 1)
		m_rasterStateDesc.MultisampleEnable = TRUE;
	else
		m_rasterStateDesc.MultisampleEnable = FALSE;

	m_rasterStateDesc.AntialiasedLineEnable = FALSE;

	// CreateRasterizerState
	hr = m_cpD3DDevice->CreateRasterizerState(&m_rasterStateDesc, m_rasterState.GetAddressOf());
	if (FAILED(hr)) goto EXIT;

	// RSSetState
	m_cpImmediateContext->RSSetState(m_rasterState.Get());

	hr = S_OK;

	OutputMsg(_T("�f�t�H���g�̃��X�^���C�U��ݒ�"), _T(""), _T("����"));

EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::SetDefaultDepthStencilState()
 *
 * @brief	�f�t�H���g�̐[�x�X�e���V���X�e�[�g��ݒ�.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	A hResult.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::SetDefaultDepthStencilState()
{
	HRESULT hr = E_FAIL;

	OutputMsg(_T("�f�t�H���g�̐[�x�X�e���V���X�e�[�g��ݒ�"), _T(""), _T("�J�n"));

	// D3D11_RASTERIZER_DESC
	D3D11_DEPTH_STENCIL_DESC dsState;
	::ZeroMemory(&dsState, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dsState.DepthEnable = TRUE;
	dsState.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsState.DepthFunc = D3D11_COMPARISON_LESS;
	dsState.StencilEnable = FALSE;

	hr = m_cpD3DDevice->CreateDepthStencilState(&dsState, m_depthStencilState.GetAddressOf());
	if (FAILED(hr)) goto EXIT;

	m_cpImmediateContext->OMSetDepthStencilState(m_depthStencilState.Get(), 0);

	::ZeroMemory(&dsState, sizeof(D3D11_DEPTH_STENCIL_DESC));

	// Now create a second depth stencil state which turns off the Z buffer for 2D rendering.  The only difference is
	// that DepthEnable is set to false, all other parameters are the same as the other depth stencil state.
	dsState.DepthEnable = false;	// �[�x��rofff
	dsState.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsState.DepthFunc = D3D11_COMPARISON_LESS;
	dsState.StencilEnable = true;
	dsState.StencilReadMask = 0xFF;
	dsState.StencilWriteMask = 0xFF;
	dsState.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsState.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsState.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsState.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsState.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsState.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsState.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsState.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the state using the device.

	hr = m_cpD3DDevice->CreateDepthStencilState(&dsState, m_depthDisabledStencilState.GetAddressOf());


	dsState.DepthEnable = false;
	dsState.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsState.DepthFunc = D3D11_COMPARISON_LESS;
	dsState.StencilEnable = true;
	dsState.StencilReadMask = 0xFF;
	dsState.StencilWriteMask = 0xFF;
	dsState.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsState.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsState.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsState.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsState.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsState.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsState.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsState.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;


	hr = m_cpD3DDevice->CreateDepthStencilState(&dsState, m_notWriteDepthStencilState.GetAddressOf());

	hr = S_OK;

	OutputMsg(_T("�f�t�H���g�̐[�x�X�e���V���X�e�[�g��ݒ�"), _T(""), _T("����"));

EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::ChangeWindowModeOptimization(UINT Width, UINT Height)
 *
 * @brief	�\�����[�h�̐؂�ւ����œK�� DXGI �̊T�v.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param	Width 	The width.
 * @param	Height	The height.
 *
 * @return	A hResult.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::ChangeWindowModeOptimization(UINT Width, UINT Height)
{
	HRESULT hr = E_FAIL;

	//	if (m_SwapChain == NULL) goto EXIT;

	OutputMsg(_T("�\�����[�h�ύX�̍œK������"), _T(""), _T("�J�n"));

	DXGI_SWAP_CHAIN_DESC desc;
	hr = m_spSwapChain->GetCpSwapChain()->GetDesc(&desc);
	if (FAILED(hr)) goto EXIT;

	// �^�[�Q�b�g�r���[������
	OutputMsg(_T("�^�[�Q�b�g�r���[������"), _T(""), _T("�J�n"));

	m_cpImmediateContext->OMSetRenderTargets(0, NULL, NULL);
	m_cpRenderTargetView.ReleaseAndGetAddressOf();

	OutputMsg(_T("�^�[�Q�b�g�r���[������"), _T(""), _T("����"));

	// �X���b�v �`�F�[���̃o�b�N �o�b�t�@�[ �T�C�Y�A�t�H�[�}�b�g�A����уo�b�t�@�[����ύX����B
	// �A�v���P�[�V���� �E�B���h�E�̃T�C�Y���ύX���ꂽ�Ƃ��ɌĂяo���K�v������B
	// ResizeBuffers
	hr = m_spSwapChain->GetCpSwapChain()->ResizeBuffers(desc.BufferCount, Width, Height, desc.BufferDesc.Format, desc.Flags);
	if (FAILED(hr)) goto EXIT;

	// �����_�����O�^�[�Q�b�g�r���[�̍쐬
	hr = CreateRenderTargetView();
	if (FAILED(hr)) goto EXIT;

	// �[�x�X�e���V���r���[�̍쐬
	hr = CreateDepthStencilView();
	if (FAILED(hr)) goto EXIT;

	// �^�[�Q�b�g�r���[�̐ݒ�
	m_cpImmediateContext->OMSetRenderTargets(1, m_cpRenderTargetView.GetAddressOf(), m_cpDepthStencilView.Get());

	OutputMsg(_T("�\�����[�h�ύX�̍œK������"), _T(""), _T("����"));

	hr = S_OK;
EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::ChangeWindowMode()
 *
 * @brief	�\�����[�h��؂�ւ���.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	A hResult.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::ChangeWindowMode()
{
	HRESULT hr = E_FAIL;

	//if (m_SwapChain == NULL) goto EXIT;

	OutputMsg(_T("�\�����[�h�ύX"), _T(""), _T("�J�n"));

	DXGI_SWAP_CHAIN_DESC desc;
	hr = m_spSwapChain->GetCpSwapChain()->GetDesc(&desc);
	if (FAILED(hr)) goto EXIT;

	BOOL FullScreen;

	// GetFullscreenState
	hr = m_spSwapChain->GetCpSwapChain()->GetFullscreenState(&FullScreen, NULL);
	if (FAILED(hr)) goto EXIT;

	// SetFullscreenState
	hr = m_spSwapChain->GetCpSwapChain()->SetFullscreenState(!FullScreen, NULL);
	if (FAILED(hr)) goto EXIT;

	switch (FullScreen)
	{
	case TRUE:
		OutputMsg(_T("�\�����[�h�ύX"), _T("�E�B���h�E���[�h�ɕύX"), _T("����"));
		break;
	case FALSE:
		OutputMsg(_T("�\�����[�h�ύX"), _T("�t���X�N���[���ɕύX"), _T("����"));
		break;
	}

	// �����N�����t���X�N���[�����[�h�ɂ����ꍇ�A�E�B���h�E���[�h�ɕύX�����
	// �E�B���h�E���A�N�e�B�u�ɂȂ�Ȃ��̂ŕ\��������B
	::ShowWindow(m_hWnd, SW_SHOW);

	// �t���X�N���[������E�B���h�E���[�h�ɐ؂�ւ���Ƃ� WM_SIZE �C�x���g�����������A���ʓI�� IDXGISwapChain::ResizeBuffers ���R�[������Ȃ��B
	// ���ɂ����悤�����A��ʏ�ɉ����\������Ȃ����ۂ���������\��������̂�
	// D3D11USER::ChangeWindowModeOptimization() �� D3D11USER::ChangeWindowMode() ���ŃR�[������悤�ɏC�����A�����ł̏����͖����ɂ���
	hr = ChangeWindowModeOptimization(0, 0);

	hr = S_OK;
EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateBuffer( Microsoft::WRL::ComPtr<ID3D11Buffer>& pBuffer, void* pData, size_t size, UINT CPUAccessFlag, D3D11_BIND_FLAG BindFlag )
 *
 * @brief	���_�A�C���f�b�N�X�A�萔�o�b�t�@���쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pBuffer	If non-null, the buffer.
 * @param [in,out]	pData  	If non-null, the data.
 * @param	size		   	The size.
 * @param	CPUAccessFlag  	The CPU access flag.
 * @param	BindFlag	   	The bind flag.
 *
 * @return	The new buffer.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateBuffer(
	Microsoft::WRL::ComPtr<ID3D11Buffer>& pBuffer,
	void* pData,
	size_t size,
	UINT CPUAccessFlag,
	D3D11_BIND_FLAG BindFlag
	)
{
	HRESULT hr = E_FAIL;

	// �o�b�t�@�[ ���\�[�X�B
	// D3D11_BUFFER_DESC
	D3D11_BUFFER_DESC BufferDesc;

	// �T�u���\�[�X
	// D3D11_SUBRESOURCE_DATA
	D3D11_SUBRESOURCE_DATA* resource = NULL;

	D3D11_USAGE Usage = D3D11_USAGE_DEFAULT;
	UINT CPUAccessFlags = 0;

	switch (CPUAccessFlag)
	{
		// CPU�A�N�Z�X�������Ȃ�
	case 0:
		Usage = D3D11_USAGE_DEFAULT;
		CPUAccessFlags = CPUAccessFlag;
		break;

		// CPU�A�N�Z�X��������
	default:
		Usage = D3D11_USAGE_DYNAMIC;
		CPUAccessFlags = CPUAccessFlag;
		break;
	}

	// �����l��ݒ肷��
	if (pData)
	{
		resource = new D3D11_SUBRESOURCE_DATA();
		resource->pSysMem = pData;
		resource->SysMemPitch = 0;
		resource->SysMemSlicePitch = 0;
	}

	// �o�b�t�@�̐ݒ�
	::ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.ByteWidth = size;                      // �o�b�t�@�T�C�Y
	BufferDesc.Usage = Usage;                     // ���\�[�X�g�p�@����肷��
	BufferDesc.BindFlags = BindFlag;                  // �o�b�t�@�̎��
	BufferDesc.CPUAccessFlags = CPUAccessFlags;            // CPU �A�N�Z�X
	BufferDesc.MiscFlags = 0;                         // ���̑��̃t���O���ݒ肵�Ȃ�

	// �o�b�t�@���쐬����
	// ID3D11Device::CreateBuffer
	hr = m_cpD3DDevice->CreateBuffer(&BufferDesc, resource, pBuffer.GetAddressOf());

	SAFE_DELETE(resource);
	if (SUCCEEDED(hr))
	{
		return true;
	} 
	else
	{
		return false;
	}
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateVertexBuffer( Microsoft::WRL::ComPtr< ID3D11Buffer>& pBuffer, void* pData, size_t size, UINT CPUAccessFlag )
 *
 * @brief	���_�o�b�t�@���쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pBuffer	If non-null, the buffer.
 * @param [in,out]	pData  	If non-null, the data.
 * @param	size		   	The size.
 * @param	CPUAccessFlag  	The CPU access flag.
 *
 * @return	The new vertex buffer.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateVertexBuffer(
	Microsoft::WRL::ComPtr< ID3D11Buffer>& pBuffer,
	void* pData,
	size_t size,
	UINT CPUAccessFlag
	)
{
	return CreateBuffer(pBuffer, pData, size, CPUAccessFlag, D3D11_BIND_VERTEX_BUFFER);
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateIndexBuffer( Microsoft::WRL::ComPtr<ID3D11Buffer>& pBuffer, void* pData, size_t size, UINT CPUAccessFlag )
 *
 * @brief	�C���f�b�N�X�o�b�t�@���쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pBuffer	If non-null, the buffer.
 * @param [in,out]	pData  	If non-null, the data.
 * @param	size		   	The size.
 * @param	CPUAccessFlag  	The CPU access flag.
 *
 * @return	The new index buffer.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateIndexBuffer(
	Microsoft::WRL::ComPtr<ID3D11Buffer>& pBuffer,
	void* pData,
	size_t size,
	UINT CPUAccessFlag
	)
{
	return CreateBuffer(pBuffer, pData, size, CPUAccessFlag, D3D11_BIND_INDEX_BUFFER);
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateConstantBuffer( Microsoft::WRL::ComPtr<ID3D11Buffer>& pBuffer, void* pData, size_t size, UINT CPUAccessFlag )
 *
 * @brief	�萔�o�b�t�@���쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pBuffer	If non-null, the buffer.
 * @param [in,out]	pData  	If non-null, the data.
 * @param	size		   	The size.
 * @param	CPUAccessFlag  	The CPU access flag.
 *
 * @return	The new constant buffer.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateConstantBuffer(
	std::shared_ptr<ConstantBuffer>& pBuffer,
	void* pData,
	size_t size,
	UINT CPUAccessFlag
	)
{
	return CreateBuffer(pBuffer->GetBuffer(), pData, size, CPUAccessFlag, D3D11_BIND_CONSTANT_BUFFER);
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateShaderResourceViewArray( TCHAR* pTextureFileNames[], UINT NumTextures, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& pSRVView)
 *
 * @brief	�e�N�X�`���[�t�@�C������V�F�[�_�[���\�[�X�r���[�z����쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pTextureFileNames	If non-null, std::list of names of the texture files.
 * @param	NumTextures				 	Number of textures.
 * @param [in,out]	pSRVView		 	If non-null, the server view.
 *
 * @return	The new shader resource view array.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateShaderResourceViewArray(
	const std::string pTextureFileNames[],
	UINT NumTextures,
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& pSRVView)
{
	HRESULT hr = E_FAIL;
#ifdef DIRECTXTEX
	ComPtr< ID3D11Texture2D> pTexture = NULL;

	
	D3D11_TEXTURE2D_DESC desc;
	::ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));

	for (UINT i = 0; i < NumTextures; i++)
	{
		Microsoft::WRL::ComPtr<ID3D11Resource> pLoadedRes = NULL;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> pLoadedTexture2D = NULL;

		DirectX::TexMetadata metadata;
		DirectX::ScratchImage image;
		LoadFromWICFile(UTILITY::Widen(pTextureFileNames[i]).c_str(), 0, &metadata, image);
		// �摜�t�@�C����ǂݍ���Ńe�N�X�`���[���쐬����
		DirectX::CreateTexture(sRENDER_DEVICE.Get(), image.GetImage(0, 0, 0), 1, metadata, pLoadedRes.GetAddressOf());
		if (FAILED(hr))
		{
			return hr;
		}

		hr = pLoadedRes.Get()->QueryInterface(
			__uuidof(ID3D11Texture2D),
			reinterpret_cast <void**>(pLoadedTexture2D.GetAddressOf())
			);

		if (FAILED(hr))
		{
			return hr;
		}

		// ��e�N�X�`���[�쐬
		if (i == 0)
		{
			// �摜�t�@�C����ǂݍ���ō쐬�����e�N�X�`���[�̏����擾����
			pLoadedTexture2D->GetDesc(&desc);

			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			desc.CPUAccessFlags = 0;
			desc.ArraySize = NumTextures;
			hr = m_cpD3DDevice->CreateTexture2D(&desc, NULL, pTexture.GetAddressOf());
			if (FAILED(hr))
			{
				return hr;
			}
		}

		D3D11_MAPPED_SUBRESOURCE mappedResource;

		// �t�@�C������摜�t�@�C����ǂݍ���ō쐬�����e�N�X�`���[���A�ǂݍ��݃��[�h�Ń}�b�v����
		hr = m_cpImmediateContext->Map(pLoadedTexture2D.Get(), NULL, D3D11_MAP_READ, 0, &mappedResource);
		if (FAILED(hr))
		{
			return hr;
		}

		// ��e�N�X�`���[�̃T�u���\�[�X���t�@�C������摜�t�@�C����ǂݍ���ō쐬�����e�N�X�`���[�̓��e�ōX�V����
		for (UINT iMip = 0; iMip < desc.MipLevels; iMip++)
		{
			m_cpImmediateContext->UpdateSubresource(pTexture.Get(),
				D3D11CalcSubresource(iMip, i, desc.MipLevels),
				NULL,
				mappedResource.pData,
				mappedResource.RowPitch,
				0
				);
		}
		m_cpImmediateContext->Unmap(pLoadedTexture2D.Get(), NULL);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	SRVDesc.Texture2DArray.MipLevels = desc.MipLevels;
	SRVDesc.Texture2DArray.ArraySize = NumTextures;

	// �V�F�[�_�[���\�[�X�r���[���쐬����
	hr = m_cpD3DDevice->CreateShaderResourceView(pTexture.Get(), &SRVDesc, pSRVView.GetAddressOf());
	if (FAILED(hr))
	{
		return hr;
	}	   
#endif // DIRECTXTEX

	hr = S_OK;

	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateVertexShaderFromFile(OUT ID3D11VertexShader** pVertexShader, IN TCHAR pSrcFile[], IN CHAR pFunctionName[], IN CHAR pProfile[], OUT ID3D11InputLayout** g_pLayout, IN D3D11_INPUT_ELEMENT_DESC pLayoutDesc[], UINT NumElements)
 *
 * @brief	���_�V�F�[�_�[���t�@�C������쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pVertexShader	If non-null, the vertex shader.
 * @param	pSrcFile			 	Source file.
 * @param	pFunctionName		 	Name of the function.
 * @param	pProfile			 	The profile.
 * @param [in,out]	g_pLayout	 	If non-null, the layout.
 * @param	pLayoutDesc			 	Information describing the layout.
 * @param	NumElements			 	Number of elements.
 *
 * @return	The new vertex shader from file.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateVertexShaderFromFile(OUT Microsoft::WRL::ComPtr< ID3D11VertexShader>& pVertexShader,
	IN HFString pSrcFile, IN HFString pFunctionName, IN HFString pProfile,
	OUT Microsoft::WRL::ComPtr< ID3D11InputLayout>& g_pLayout,
	IN D3D11_INPUT_ELEMENT_DESC pLayoutDesc[], UINT NumElements)
{
	HRESULT hr = E_FAIL;
	HFString Profile;

	Microsoft::WRL::ComPtr<ID3D10Blob> pBlob;
	Microsoft::WRL::ComPtr<ID3D10Blob> cpErrorMessage;

	// �s����D��Őݒ肵�A�Â��`���̋L�q�������Ȃ��悤�ɂ���
	UINT Flag1 = D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_ENABLE_STRICTNESS;

	// �œK�����x����ݒ肷��
#if defined(DEBUG) || defined(_DEBUG)
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL0;
#else
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif

	// Direct3D 9 ���[�h�Ŏ��s���̏ꍇ�́A�o�[�W������ύX����K�v������
	switch (m_FeatureLevel)
	{
	case D3D_FEATURE_LEVEL_9_1:
	case D3D_FEATURE_LEVEL_9_2:
		(Profile =  "vs_4_0_level_9_1");
		break;
	case D3D_FEATURE_LEVEL_9_3:
		(Profile = "vs_4_0_level_9_3");
		break;
	default:
		(Profile = pProfile);
		break;
	}

	// �t�@�C�������ɃG�t�F�N�g���R���p�C������
	//hr = D3DX11CompileFromFile((pSrcFile), NULL, NULL, pFunctionName, Profile, Flag1, 0, NULL, pBlob.GetAddressOf(), cpErrorMessage.GetAddressOf(), NULL);
	hr = D3DCompileFromFile(pSrcFile, NULL, NULL, pFunctionName, Profile, Flag1, 0, pBlob.GetAddressOf(), cpErrorMessage.GetAddressOf());

	if (FAILED(hr))
	{
		OutputShaderErrorMessage(cpErrorMessage, pSrcFile);
		return false;
	}

	// �R���p�C���ς݃V�F�[�_�[����A���_�V�F�[�_�[ �I�u�W�F�N�g���쐬����
	hr = m_cpD3DDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, pVertexShader.GetAddressOf());
	if (FAILED(hr))
	{
		return false;
	}

	BYTE* vsbuffer = (LPBYTE)pBlob->GetBufferPointer();
	size_t vsbuffersize = pBlob->GetBufferSize();

	// �V�F�[�_�[�Ŏg�p�������̓o�b�t�@�[���L�q���邽�߂̓��̓��C�A�E�g�I�u�W�F�N�g���쐬����B
	hr = m_cpD3DDevice->CreateInputLayout(pLayoutDesc, NumElements, vsbuffer, vsbuffersize, g_pLayout.GetAddressOf());
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateVertexShaderFromMemory(ID3D11VertexShader** pVertexShader, const BYTE* pShader, size_t size, OUT ID3D11InputLayout** g_pLayout, IN D3D11_INPUT_ELEMENT_DESC pLayoutDesc[], UINT NumElements)
 *
 * @brief	���_�V�F�[�_�[���w�b�_�t�@�C������쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pVertexShader	If non-null, the vertex shader.
 * @param	pShader				 	The shader.
 * @param	size				 	The size.
 * @param [in,out]	g_pLayout	 	If non-null, the layout.
 * @param	pLayoutDesc			 	Information describing the layout.
 * @param	NumElements			 	Number of elements.
 *
 * @return	The new vertex shader from memory.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateVertexShaderFromMemory(Microsoft::WRL::ComPtr< ID3D11VertexShader>& cpVertexShader,
	const BYTE* pShader, size_t size,
	OUT Microsoft::WRL::ComPtr< ID3D11InputLayout>& g_pLayout,
	IN D3D11_INPUT_ELEMENT_DESC pLayoutDesc[], UINT NumElements)
{
	HRESULT hr = E_FAIL;

	// �R���p�C���ς݃V�F�[�_�[����A���_�V�F�[�_�[ �I�u�W�F�N�g���쐬����
	hr = m_cpD3DDevice->CreateVertexShader(pShader, size, NULL, cpVertexShader.GetAddressOf());
	if (FAILED(hr)) goto EXIT;

	// �V�F�[�_�[�Ŏg�p�������̓o�b�t�@�[���L�q���邽�߂̓��̓��C�A�E�g�I�u�W�F�N�g���쐬����B
	hr = m_cpD3DDevice->CreateInputLayout(pLayoutDesc, NumElements, pShader, size, g_pLayout.GetAddressOf());
	if (FAILED(hr)) goto EXIT;

	hr = S_OK;
EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateHullShaderFromFile(ID3D11HullShader** pHullShader, TCHAR pSrcFile[], CHAR pFunctionName[], CHAR pProfile[])
 *
 * @brief	�n���V�F�[�_�[���t�@�C������쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pHullShader	If non-null, the hull shader.
 * @param	pSrcFile		   	Source file.
 * @param	pFunctionName	   	Name of the function.
 * @param	pProfile		   	The profile.
 *
 * @return	The new hull shader from file.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateHullShaderFromFile(ID3D11HullShader** pHullShader,
	HFString pSrcFile,
	HFString pFunctionName,
	HFString pProfile)
{
	HRESULT hr = E_FAIL;
	CHAR Profile[256];

	ID3D10Blob* pBlob = NULL;

	UINT Flag1 = D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL0;
#else
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif

	strcpy_s(Profile, pProfile);
	// �t�@�C�������ɃG�t�F�N�g���R���p�C������
	//D3DX11CompileFromFile(pSrcFile, NULL, NULL, pFunctionName, Profile, Flag1, 0, NULL, &pBlob, NULL, NULL);
	hr = D3DCompileFromFile((LPCWSTR)pSrcFile, NULL, NULL, pFunctionName, Profile, Flag1, 0, NULL, &pBlob);

	if (FAILED(hr)) goto EXIT;

	// �R���p�C���ς݃V�F�[�_�[����A�n���V�F�[�_�[ �I�u�W�F�N�g���쐬����
	hr = m_cpD3DDevice->CreateHullShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, pHullShader);
	if (FAILED(hr)) goto EXIT;

	hr = S_OK;
EXIT:
	SAFE_RELEASE(pBlob);
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateHullShaderFromMemory(ID3D11HullShader** pHullShader, const BYTE* pShader, size_t size)
 *
 * @brief	�n���V�F�[�_�[������������쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pHullShader	If non-null, the hull shader.
 * @param	pShader			   	The shader.
 * @param	size			   	The size.
 *
 * @return	The new hull shader from memory.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateHullShaderFromMemory(ID3D11HullShader** pHullShader, const BYTE* pShader, size_t size)
{
	HRESULT hr = E_FAIL;

	// �R���p�C���ς݃V�F�[�_�[����A�n���V�F�[�_�[ �I�u�W�F�N�g���쐬����
	hr = m_cpD3DDevice->CreateHullShader(pShader, size, NULL, pHullShader);
	if (FAILED(hr)) goto EXIT;

	hr = S_OK;
EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateDomainShaderFromFile(ID3D11DomainShader** pDomainShader, TCHAR pSrcFile[], CHAR pFunctionName[], CHAR pProfile[])
 *
 * @brief	�h���C���V�F�[�_�[���t�@�C������쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pDomainShader	If non-null, the domain shader.
 * @param	pSrcFile			 	Source file.
 * @param	pFunctionName		 	Name of the function.
 * @param	pProfile			 	The profile.
 *
 * @return	The new domain shader from file.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateDomainShaderFromFile(ID3D11DomainShader** pDomainShader,
	HFString pSrcFile,
	HFString pFunctionName,
	HFString pProfile)
{
	HRESULT hr = E_FAIL;
	CHAR Profile[256];

	ID3D10Blob* pBlob = NULL;

	UINT Flag1 = D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL0;
#else
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif

	strcpy_s(Profile, pProfile);

	// �t�@�C�������ɃG�t�F�N�g���R���p�C������
	//hr = D3DX11CompileFromFile(pSrcFile, NULL, NULL, pFunctionName, Profile, Flag1, 0, NULL, &pBlob, NULL, NULL);
	hr = D3DCompileFromFile((LPCWSTR)pSrcFile, NULL, NULL, pFunctionName, Profile, Flag1, 0, NULL, &pBlob);

	if (FAILED(hr)) goto EXIT;

	// �R���p�C���ς݃V�F�[�_�[����A�h���C���V�F�[�_�[ �I�u�W�F�N�g���쐬����
	hr = m_cpD3DDevice->CreateDomainShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, pDomainShader);
	if (FAILED(hr)) goto EXIT;

	hr = S_OK;
EXIT:
	SAFE_RELEASE(pBlob);
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateDomainShaderFromMemory(ID3D11DomainShader** pDomainShader, const BYTE* pShader, size_t size)
 *
 * @brief	�h���C���V�F�[�_�[������������쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pDomainShader	If non-null, the domain shader.
 * @param	pShader				 	The shader.
 * @param	size				 	The size.
 *
 * @return	The new domain shader from memory.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateDomainShaderFromMemory(ID3D11DomainShader** pDomainShader, const BYTE* pShader, size_t size)
{
	HRESULT hr = E_FAIL;

	// �R���p�C���ς݃V�F�[�_�[����A�h���C���V�F�[�_�[ �I�u�W�F�N�g���쐬����
	hr = m_cpD3DDevice->CreateDomainShader(pShader, size, NULL, pDomainShader);
	if (FAILED(hr)) goto EXIT;

	hr = S_OK;
EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateGeometryShaderFromFile(ID3D11GeometryShader** pGeometryShader, TCHAR pSrcFile[], CHAR pFunctionName[], CHAR pProfile[])
 *
 * @brief	�W�I���g���V�F�[�_�[���t�@�C������쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pGeometryShader	If non-null, the geometry shader.
 * @param	pSrcFile			   	Source file.
 * @param	pFunctionName		   	Name of the function.
 * @param	pProfile			   	The profile.
 *
 * @return	The new geometry shader from file.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateGeometryShaderFromFile(ID3D11GeometryShader** pGeometryShader,
	HFString pSrcFile,
	HFString pFunctionName,
	HFString pProfile)
{
	HRESULT hr = E_FAIL;
	CHAR Profile[256];

	ID3D10Blob* pBlob = NULL;

	UINT Flag1 = D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL0;
#else
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif

	//// Direct3D 9 ���[�h�Ŏ��s���̏ꍇ�̓G���[�Ƃ���
	//switch( m_FeatureLevel )
	//{
	//case D3D_FEATURE_LEVEL_9_1:
	//case D3D_FEATURE_LEVEL_9_2:
	//case D3D_FEATURE_LEVEL_9_3:
	//   goto EXIT;
	//default:
	strcpy_s(Profile, pProfile);

	//   break;
	//}

	// �t�@�C�������ɃG�t�F�N�g���R���p�C������
	hr = D3DCompileFromFile((LPCWSTR)pSrcFile, NULL, NULL, pFunctionName, Profile, Flag1, 0, NULL, &pBlob);
	//hr = D3DX11CompileFromFile(pSrcFile, NULL, NULL, pFunctionName, Profile, Flag1, 0, NULL, &pBlob, NULL, NULL);
	if (FAILED(hr)) goto EXIT;

	// �R���p�C���ς݃V�F�[�_�[����A�W�I���g���V�F�[�_�[ �I�u�W�F�N�g���쐬����
	// ID3D11Device::CreateGeometryShader
	hr = m_cpD3DDevice->CreateGeometryShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, pGeometryShader);
	if (FAILED(hr)) goto EXIT;

	hr = S_OK;
EXIT:
	SAFE_RELEASE(pBlob);
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateGeometryShaderFromMemory(ID3D11GeometryShader** pGeometryShader, const BYTE* pShader, size_t size)
 *
 * @brief	�W�I���g���V�F�[�_�[������������쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pGeometryShader	If non-null, the geometry shader.
 * @param	pShader				   	The shader.
 * @param	size				   	The size.
 *
 * @return	The new geometry shader from memory.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateGeometryShaderFromMemory(ID3D11GeometryShader** pGeometryShader, const BYTE* pShader, size_t size)
{
	HRESULT hr = E_FAIL;

	// �R���p�C���ς݃V�F�[�_�[����A�W�I���g���V�F�[�_�[ �I�u�W�F�N�g���쐬����
	hr = m_cpD3DDevice->CreateGeometryShader(pShader, size, NULL, pGeometryShader);
	if (FAILED(hr)) goto EXIT;

	hr = S_OK;
EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateGeometryShaderWithStreamOutputFromFile( ID3D11GeometryShader** pGeometryShader, TCHAR pSrcFile[], CHAR pFunctionName[], CHAR pProfile[], const D3D11_SO_DECLARATION_ENTRY *pSODeclaration, UINT NumEntries, const UINT *pBufferStrides, UINT NumStrides)
 *
 * @brief	�X�g���[�~���O�o�̓o�b�t�@�[�ւ̏������݂��\�ȃW�I���g�� �V�F�[�_�[���t�@�C������쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pGeometryShader	If non-null, the geometry shader.
 * @param	pSrcFile			   	Source file.
 * @param	pFunctionName		   	Name of the function.
 * @param	pProfile			   	The profile.
 * @param	pSODeclaration		   	The so declaration.
 * @param	NumEntries			   	Number of entries.
 * @param	pBufferStrides		   	The buffer strides.
 * @param	NumStrides			   	Number of strides.
 *
 * @return	The new geometry shader with stream output from file.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateGeometryShaderWithStreamOutputFromFile(
	ID3D11GeometryShader** pGeometryShader,
	HFString pSrcFile, HFString pFunctionName, HFString pProfile,
	const D3D11_SO_DECLARATION_ENTRY *pSODeclaration,
	UINT NumEntries,
	const UINT *pBufferStrides,
	UINT NumStrides)
{
	HRESULT hr = E_FAIL;
	CHAR Profile[256];

	ID3D10Blob* pBlob = NULL;

	UINT Flag1 = D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL0;
#else
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif
	strcpy_s(Profile, pProfile);

	// �t�@�C�������ɃG�t�F�N�g���R���p�C������
//	hr = D3DX11CompileFromFile(pSrcFile, NULL, NULL, pFunctionName, Profile, Flag1, 0, NULL, &pBlob, NULL, NULL);
	hr = D3DCompileFromFile((LPCWSTR)pSrcFile, NULL, NULL, pFunctionName, Profile, Flag1, 0, NULL, &pBlob);

	if (FAILED(hr)) goto EXIT;

	// �X�g���[���o�͂���W�I���g���V�F�[�_�[���쐬
	// ID3D11Device::CreateGeometryShaderWithStreamOutput
	hr = m_cpD3DDevice->CreateGeometryShaderWithStreamOutput(
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		pSODeclaration,
		NumEntries,
		pBufferStrides,
		NumStrides,
		D3D11_SO_NO_RASTERIZED_STREAM,
		NULL,
		pGeometryShader);
	if (FAILED(hr)) goto EXIT;

	hr = S_OK;
EXIT:
	SAFE_RELEASE(pBlob);
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateGeometryShaderWithStreamOutputFromMemory( ID3D11GeometryShader** pGeometryShader, const BYTE* pShader, size_t size, const D3D11_SO_DECLARATION_ENTRY *pSODeclaration, UINT NumEntries, const UINT *pBufferStrides, UINT NumStrides)
 *
 * @brief	�X�g���[�~���O�o�̓o�b�t�@�[�ւ̏������݂��\�ȃW�I���g�� �V�F�[�_�[������������쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pGeometryShader	If non-null, the geometry shader.
 * @param	pShader				   	The shader.
 * @param	size				   	The size.
 * @param	pSODeclaration		   	The so declaration.
 * @param	NumEntries			   	Number of entries.
 * @param	pBufferStrides		   	The buffer strides.
 * @param	NumStrides			   	Number of strides.
 *
 * @return	The new geometry shader with stream output from memory.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateGeometryShaderWithStreamOutputFromMemory(
	ID3D11GeometryShader** pGeometryShader,
	const BYTE* pShader, size_t size,
	const D3D11_SO_DECLARATION_ENTRY *pSODeclaration,
	UINT NumEntries,
	const UINT *pBufferStrides,
	UINT NumStrides)
{
	HRESULT hr = E_FAIL;

	// �X�g���[���o�͂���W�I���g���V�F�[�_�[���쐬
	// ID3D11Device::CreateGeometryShaderWithStreamOutput
	hr = m_cpD3DDevice->CreateGeometryShaderWithStreamOutput(
		pShader,
		size,
		pSODeclaration,
		NumEntries,
		pBufferStrides,
		NumStrides,
		D3D11_SO_NO_RASTERIZED_STREAM,
		NULL,
		pGeometryShader);
	if (FAILED(hr)) goto EXIT;

	hr = S_OK;
EXIT:
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreatePixelShaderFromFile(ID3D11PixelShader** pPixelShader, TCHAR pSrcFile[], CHAR pFunctionName[], CHAR pProfile[] )
 *
 * @brief	�s�N�Z���V�F�[�_�[���t�@�C������쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pPixelShader	If non-null, the pixel shader.
 * @param	pSrcFile				Source file.
 * @param	pFunctionName			Name of the function.
 * @param	pProfile				The profile.
 *
 * @return	The new pixel shader from file.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreatePixelShaderFromFile(Microsoft::WRL::ComPtr<ID3D11PixelShader>& pPixelShader,
	Microsoft::WRL::ComPtr< ID3D11ClassLinkage>& cpPSClassLinkage
	,
	HFString pSrcFile,
	HFString pFunctionName,
	HFString pProfile ,bool isLinkage
	)
{
	HRESULT hr = E_FAIL;
	CHAR Profile[256];

	Microsoft::WRL::ComPtr<ID3D10Blob> pBlob;
	Microsoft::WRL::ComPtr<ID3D10Blob> cpErrorMessage;

	UINT Flag1 = D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL0;
#else
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif

	// Direct3D 9 ���[�h�Ŏ��s���̏ꍇ�́A�o�[�W������ύX����K�v������
	switch (m_FeatureLevel)
	{
	case D3D_FEATURE_LEVEL_9_1:
	case D3D_FEATURE_LEVEL_9_2:
		strcpy_s(Profile, "ps_4_0_level_9_1");
		break;
	case D3D_FEATURE_LEVEL_9_3:
		strcpy_s(Profile, "ps_4_0_level_9_3");
		break;
	default:
		strcpy_s(Profile, pProfile);
		break;
	}
	

	// �t�@�C�������ɃR���p�C������
	hr = D3DCompileFromFile((LPCWSTR)pSrcFile, NULL, NULL, pFunctionName, Profile, Flag1, 0, pBlob.GetAddressOf(),cpErrorMessage.GetAddressOf() );

	if (FAILED(hr))
	{
		const TCHAR* text;// = (hr);
		OutputShaderErrorMessage(cpErrorMessage, pSrcFile);
		return hr;
	}

	// �R���p�C���ς݃V�F�[�_�[����A�s�N�Z���V�F�[�_�[ �I�u�W�F�N�g���쐬����
	if (isLinkage)
	{
		hr = m_cpD3DDevice->CreateClassLinkage(cpPSClassLinkage.GetAddressOf());

		hr = m_cpD3DDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), cpPSClassLinkage.Get(), pPixelShader.GetAddressOf());
	}
	else
	{
		hr = m_cpD3DDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, pPixelShader.GetAddressOf());

	}
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool DirectX11RenderDeviceManager::SetupGeometryBuffer()
{
	m_spDeferredBuffer = std::shared_ptr<GeometryBuffers>(new GeometryBuffers);
	return m_spDeferredBuffer->Setup(7, m_screenSize.x, m_screenSize.y, 10000, 1);
}

std::shared_ptr<GeometryBuffers> DirectX11RenderDeviceManager::GetGeometryBuffer()
{
	return m_spDeferredBuffer;
}

void DirectX11RenderDeviceManager::SetVertexBuffer(UINT startSlot, UINT bufferNum, std::vector<std::shared_ptr<VertexBuffer>>& vertexArray, const UINT* pStride, const UINT* pOffset)
{
	vector< ComPtr<ID3D11Buffer> >buffers;
	buffers.resize(bufferNum);
	for (int i = 0; i < bufferNum;i++)
	{
		buffers[i] = vertexArray[i]->GetBuffer();
	}
	m_cpImmediateContext->IASetVertexBuffers(startSlot, bufferNum, buffers[0].GetAddressOf(), pStride, pOffset);
}

void DirectX11RenderDeviceManager::SetIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer, const UINT offset)
{
	m_cpImmediateContext->IASetIndexBuffer(indexBuffer->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, offset);
}

void DirectX11RenderDeviceManager::SetConstantBuffers(DWORD shaderFlag,UINT startSlot, UINT bufferNum, std::vector<std::shared_ptr<ConstantBuffer>>& bufferArray)
{
	vector< ComPtr<ID3D11Buffer> >buffers;
	buffers.resize(bufferNum);
	for (int i = 0; i < bufferNum; i++)
	{
		buffers[i] = bufferArray[i]->GetBuffer();
	}

	switch(shaderFlag)
	{
	case HF_D3D11_VERTEX_SHADER: 
		m_cpImmediateContext->VSSetConstantBuffers(startSlot, bufferNum, buffers[0].GetAddressOf());
		break;
	case HF_D3D11_HULL_SHADER:	
		m_cpImmediateContext->HSSetConstantBuffers(startSlot, bufferNum, buffers[0].GetAddressOf());
		break;
	case HF_D3D11_DOMAIN_SHADER:
		m_cpImmediateContext->DSSetConstantBuffers(startSlot, bufferNum, buffers[0].GetAddressOf());
		break;
	case HF_D3D11_GEOMETRY_SHADER:	
		m_cpImmediateContext->GSSetConstantBuffers(startSlot, bufferNum, buffers[0].GetAddressOf());
		break;
	case HF_D3D11_PIXEL_SHADER:	  
		m_cpImmediateContext->PSSetConstantBuffers(startSlot, bufferNum, buffers[0].GetAddressOf());
		break;
	case HF_D3D11_COMPUTE_SHADER:				 
		m_cpImmediateContext->CSSetConstantBuffers(startSlot, bufferNum, buffers[0].GetAddressOf());
		break;
	default:
		break;
	}

}

void DirectX11RenderDeviceManager::
OutputShaderErrorMessage(
	Microsoft::WRL::ComPtr<ID3D10Blob> errorMessage,
	TCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	std::ofstream fout;
																						  
	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();


	return;
}
/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreatePixelShaderFromMemory(ID3D11PixelShader** pPixelShader, const BYTE* pShader, size_t size)
 *
 * @brief	�s�N�Z���V�F�[�_�[���w�b�_�t�@�C������쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pPixelShader	If non-null, the pixel shader.
 * @param	pShader					The shader.
 * @param	size					The size.
 *
 * @return	The new pixel shader from memory.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreatePixelShaderFromMemory(Microsoft::WRL::ComPtr<ID3D11PixelShader>& pPixelShader, const BYTE* pShader, size_t size)
{
	HRESULT hr = E_FAIL;

	// �R���p�C���ς݃V�F�[�_�[����A�s�N�Z���V�F�[�_�[ �I�u�W�F�N�g���쐬����
	hr = m_cpD3DDevice->CreatePixelShader(pShader, size, NULL, pPixelShader.GetAddressOf());
	if (FAILED(hr)) goto EXIT;

	hr = S_OK;
EXIT:
	return hr;
}



/**********************************************************************************************//**
 * @fn	D3D11_RENDER_TARGET_BLEND_DESC CDirectX11RenderDeviceManager::GetDefaultBlendDesc()
 *
 * @brief	�u�����h �X�e�[�g�𖳌��ɂ��邽�߂̐ݒ���擾����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	The default blend description.
 **************************************************************************************************/

D3D11_RENDER_TARGET_BLEND_DESC DirectX11RenderDeviceManager::GetDefaultBlendDesc()
{
	D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;

	RenderTarget.BlendEnable = FALSE;
	RenderTarget.SrcBlend = D3D11_BLEND_ONE;
	RenderTarget.DestBlend = D3D11_BLEND_ZERO;
	RenderTarget.BlendOp = D3D11_BLEND_OP_ADD;
	RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
	RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
	RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	return RenderTarget;
}

/**********************************************************************************************//**
 * @fn	D3D11_RENDER_TARGET_BLEND_DESC CDirectX11RenderDeviceManager::GetAlignmentBlendDesc()
 *
 * @brief	���`�����p�u�����h �X�e�[�g�̂��߂̂�ݒ���擾����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	The alignment blend description.
 **************************************************************************************************/

D3D11_RENDER_TARGET_BLEND_DESC DirectX11RenderDeviceManager::GetAlignmentBlendDesc()
{
	D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;

	RenderTarget.BlendEnable = TRUE;
	RenderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	RenderTarget.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	RenderTarget.BlendOp = D3D11_BLEND_OP_ADD;
	RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
	RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
	RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	return RenderTarget;
}

/**********************************************************************************************//**
 * @fn	D3D11_RENDER_TARGET_BLEND_DESC CDirectX11RenderDeviceManager::GetAddBlendDesc()
 *
 * @brief	���Z�����p�u�����h �X�e�[�g�̂��߂̂�ݒ���擾����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	The add blend description.
 **************************************************************************************************/

D3D11_RENDER_TARGET_BLEND_DESC DirectX11RenderDeviceManager::GetAddBlendDesc()
{
	D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;

	RenderTarget.BlendEnable = TRUE;
	RenderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	RenderTarget.DestBlend = D3D11_BLEND_ONE;
	RenderTarget.BlendOp = D3D11_BLEND_OP_ADD;
	RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
	RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
	RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	return RenderTarget;
}

/**********************************************************************************************//**
 * @fn	D3D11_RENDER_TARGET_BLEND_DESC CDirectX11RenderDeviceManager::GetSubtractBlendDesc()
 *
 * @brief	���Z�����p�u�����h �X�e�[�g�̂��߂̂�ݒ���擾����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	The subtract blend description.
 **************************************************************************************************/

D3D11_RENDER_TARGET_BLEND_DESC DirectX11RenderDeviceManager::GetSubtractBlendDesc()
{
	D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;

	RenderTarget.BlendEnable = TRUE;
	RenderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	RenderTarget.DestBlend = D3D11_BLEND_ONE;
	RenderTarget.BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
	RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
	RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	return RenderTarget;
}

/**********************************************************************************************//**
 * @fn	D3D11_RENDER_TARGET_BLEND_DESC CDirectX11RenderDeviceManager::GetMultipleBlendDesc()
 *
 * @brief	�ώZ�����p�u�����h �X�e�[�g�̂��߂̂�ݒ���擾����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	The multiple blend description.
 **************************************************************************************************/

D3D11_RENDER_TARGET_BLEND_DESC DirectX11RenderDeviceManager::GetMultipleBlendDesc()
{
	D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;

	RenderTarget.BlendEnable = TRUE;
	RenderTarget.SrcBlend = D3D11_BLEND_ZERO;
	RenderTarget.DestBlend = D3D11_BLEND_SRC_COLOR;
	RenderTarget.BlendOp = D3D11_BLEND_OP_ADD;
	RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
	RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
	RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	return RenderTarget;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::SetBlendState(D3D11_RENDER_TARGET_BLEND_DESC BlendStateArray[], UINT NumBlendState, bool AlphaToCoverageEnable)
 *
 * @brief	�u�����h�X�e�[�g��ݒ肷��.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param	BlendStateArray		 	Array of blend states.
 * @param	NumBlendState		 	Number of blend states.
 * @param	AlphaToCoverageEnable	true if alpha to coverage enable.
 *
 * @return	A hResult.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::SetBlendState(D3D11_RENDER_TARGET_BLEND_DESC BlendStateArray[], UINT NumBlendState, bool AlphaToCoverageEnable)
{
	HRESULT hr = E_FAIL;

	ComPtr< ID3D11BlendState> pBlendState = NULL;

	if (NumBlendState > 8)
	{
		return hr;
	}

	D3D11_BLEND_DESC BlendDesc;
	::ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = AlphaToCoverageEnable;

	// TRUE�̏ꍇ�A�}���`�����_�[�^�[�Q�b�g�Ŋe�����_�[�^�[�Q�b�g�̃u�����h�X�e�[�g�̐ݒ���ʂɐݒ�ł���
	// FALSE�̏ꍇ�A0�Ԗڂ݂̂��g�p�����
	BlendDesc.IndependentBlendEnable = TRUE;


	for (UINT i = 0; i < NumBlendState; i++)
	{
		::CopyMemory(&BlendDesc.RenderTarget[i], &BlendStateArray[i], sizeof(D3D11_RENDER_TARGET_BLEND_DESC));
	}

	for (UINT i = 0; i < 8; i++)
	{
		BlendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}

	hr = m_cpD3DDevice->CreateBlendState(&BlendDesc, pBlendState.GetAddressOf());
	m_cpImmediateContext->OMSetBlendState(pBlendState.Get(),0,0xffffffff);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = S_OK;
	return hr;
}

D3D11_RENDER_TARGET_BLEND_DESC DirectX11RenderDeviceManager::GetFontBlendState()
{
	HRESULT hr = E_FAIL;
	//�u�����h�`��̐ݒ�	  
	D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;

	RenderTarget.BlendEnable = TRUE;
	RenderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	RenderTarget.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	RenderTarget.BlendOp = D3D11_BLEND_OP_ADD;
	RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
	RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
	RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	return RenderTarget;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateSamplerState(ID3D11SamplerState** ppSamplerState, D3D11_FILTER Filter, UINT MaxAnisotropy)
 *
 * @brief	�W���T���v���[�X�e�[�g���쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	ppSamplerState	If non-null, state of the sampler.
 * @param	Filter				  	Specifies the filter.
 * @param	MaxAnisotropy		  	The maximum anisotropy.
 *
 * @return	The new sampler state.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateSamplerState(Microsoft::WRL::ComPtr< ID3D11SamplerState>& cpSamplerState, D3D11_FILTER Filter, UINT MaxAnisotropy)
{
	HRESULT hr = E_FAIL;

	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = Filter;                           // �T���v�����O���Ɏg�p����t�B���^
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;     // 0 �` 1 �͈̔͊O�ɂ��� u �e�N�X�`���[���W�̕`����@
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;     // 0 �` 1 �͈̔͊O�ɂ��� v �e�N�X�`���[���W
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;     // 0 �` 1 �͈̔͊O�ɂ��� w �e�N�X�`���[���W
	samplerDesc.MipLODBias = 0;                            // �v�Z���ꂽ�~�b�v�}�b�v ���x������̃o�C�A�X
	samplerDesc.MaxAnisotropy = MaxAnisotropy;             // �T���v�����O�Ɉٕ�����Ԃ��g�p���Ă���ꍇ�̌��E�l�B�L���Ȓl�� 1 �` 16 �B
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;  // ��r�I�v�V�����B
	::CopyMemory(samplerDesc.BorderColor, &HFVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), sizeof(HFVECTOR4)); // ���E�F
	samplerDesc.MinLOD = 0;                                // �A�N�Z�X�\�ȃ~�b�v�}�b�v�̉����l
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;                // �A�N�Z�X�\�ȃ~�b�v�}�b�v�̏���l
	hr = m_cpD3DDevice->CreateSamplerState(&samplerDesc, cpSamplerState.GetAddressOf());
	if (FAILED(hr)) 
	{
		return false;
	}
	return true;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::SetDepthStencilState(bool DepthEnable, D3D11_DEPTH_WRITE_MASK DepthWriteEnabled)
 *
 * @brief	�[�x�X�e���V���X�e�[�g�̒��Őݒ�ύX�p�x���������ȃp�����[�^��ݒ肷��.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param	DepthEnable		 	true if depth enable.
 * @param	DepthWriteEnabled	The depth write enabled.
 *
 * @return	A hResult.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::SetDepthStencilState(bool DepthEnable, D3D11_DEPTH_WRITE_MASK DepthWriteEnabled)
{
	HRESULT hr = E_FAIL;

	// �[�x�X�e���V���X�e�[�g
	ID3D11DepthStencilState*  pDepthStencilState = NULL;

	// �[�x�X�e���V���X�e�[�g���쐬����
	D3D11_DEPTH_STENCIL_DESC ddsDesc;
	::ZeroMemory(&ddsDesc, sizeof(ddsDesc));
	ddsDesc.DepthEnable = DepthEnable;           // �[�x�e�X�g���s����
	ddsDesc.DepthWriteMask = DepthWriteEnabled;  // �[�x�o�b�t�@�ւ̏������݂��s����
	ddsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	ddsDesc.StencilEnable = FALSE;
	hr = m_cpD3DDevice->CreateDepthStencilState(&ddsDesc, &pDepthStencilState);
	if (FAILED(hr))
		goto EXIT;

	m_cpImmediateContext->OMSetDepthStencilState(pDepthStencilState, 0);

	hr = S_OK;
EXIT:
	SAFE_RELEASE(pDepthStencilState);
	return hr;
}

/**********************************************************************************************//**
 * @fn	ID3D11ShaderResourceView* CDirectX11RenderDeviceManager::GetSRViewFromDepthStencil()
 *
 * @brief	�[�x�X�e���V���r���[�̃V�F�[�_�[���\�[�X�r���[���擾.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @return	null if it fails, else the sr view from depth stencil.
 **************************************************************************************************/

ComPtr< ID3D11ShaderResourceView> DirectX11RenderDeviceManager::GetSRViewFromDepthStencil()
{
	HRESULT hr = E_FAIL;
	ComPtr<ID3D11ShaderResourceView> pSRView ;
	ComPtr<ID3D11Resource> pResource;

	if (m_cpDepthStencilView == NULL)
	{
		return pSRView;
	}

	// �[�x�X�e���V���r���[�̐ݒ���擾����
	D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc;
	m_cpDepthStencilView->GetDesc(&DSVDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	::ZeroMemory(&SRVDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));


	// ���\�[�X�Ƀr���[��K�p����ꍇ�A���\�[�X �r���[�̋L�q�ŁA���\�[�X �t�H�[�}�b�g�ƌ݊����̂���^�̃t�H�[�}�b�g���w�肷��K�v������
	switch (DSVDesc.Format)
	{
		// 8�r�b�g�t�H�[�}�b�g�͎g�p�ł���̂��H
	case DXGI_FORMAT_R8_UNORM:
		SRVDesc.Format = DXGI_FORMAT_R8_UNORM;
		break;
	case DXGI_FORMAT_D16_UNORM:
		SRVDesc.Format = DXGI_FORMAT_R16_UNORM;
		break;
	case DXGI_FORMAT_D32_FLOAT:
		SRVDesc.Format = DXGI_FORMAT_R32_FLOAT;
		break;
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		SRVDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		break;
	}
	DXGI_SWAP_CHAIN_DESC SCDesc;

	// �X���b�v�`�F�[���̐ݒ���擾����
	m_spSwapChain->GetCpSwapChain()->GetDesc(&SCDesc);

	// �}���`�T���v�����O���g�p���Ȃ�
	if (SCDesc.SampleDesc.Count == 1)
		SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

	// �}���`�T���v�����O���g�p����
	else
		SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
	SRVDesc.Texture2D.MostDetailedMip = 0;
	SRVDesc.Texture2D.MipLevels = 1;

	// �[�x�X�e���V���r���[���烊�\�[�X���擾
	m_cpDepthStencilView->GetResource(pResource.GetAddressOf());

	// �V�F�[�_�[���\�[�X�r���[���쐬����
	hr = m_cpD3DDevice->CreateShaderResourceView(pResource.Get(), &SRVDesc, pSRView.GetAddressOf());
	if (FAILED(hr))
	{
		return pSRView;
	}

	hr = S_OK;

	return pSRView;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateRenderTargetView(ID3D11RenderTargetView** ppRTView, D3DXVECTOR2* pRTViewSize, DXGI_FORMAT Format)
 *
 * @brief	�V�F�[�_�[�Ƀo�C���h�\�ȃ����_�[�^�[�Q�b�g�r���[���쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	ppRTView   	If non-null, the right view.
 * @param [in,out]	pRTViewSize	If non-null, size of the right view.
 * @param	Format			   	Describes the format to use.
 *
 * @return	The new render target view.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateRenderTargetView(Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& ppRTView, HFVECTOR2* pRTViewSize, DXGI_FORMAT Format)
{
	HRESULT hr;
	hr = CreateRenderTargetView(ppRTView, pRTViewSize, Format, 1);
	return hr;
}

/**********************************************************************************************//**
 * @fn	bool CDirectX11RenderDeviceManager::CreateRenderTargetView(ID3D11RenderTargetView** ppRTView, D3DXVECTOR2* pRTViewSize, DXGI_FORMAT Format, UINT MipLevels)
 *
 * @brief	�V�F�[�_�[�Ƀo�C���h�\�ȃ����_�[�^�[�Q�b�g�r���[���쐬����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	ppRTView   	If non-null, the right view.
 * @param [in,out]	pRTViewSize	If non-null, size of the right view.
 * @param	Format			   	Describes the format to use.
 * @param	MipLevels		   	The mip levels.
 *
 * @return	The new render target view.
 **************************************************************************************************/

bool DirectX11RenderDeviceManager::CreateRenderTargetView(Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& ppRTView, HFVECTOR2* pRTViewSize, DXGI_FORMAT Format, UINT MipLevels)
{
	HRESULT hr = E_FAIL;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2D = NULL;

	// �X���b�v�`�F�[���̏����擾����
	DXGI_SWAP_CHAIN_DESC SCDesc;
	m_spSwapChain->GetCpSwapChain()->GetDesc(&SCDesc);

	UINT Width, Height;
	if (pRTViewSize == NULL)
	{
		Width = SCDesc.BufferDesc.Width;
		Height = SCDesc.BufferDesc.Height;
	}
	else
	{
		Width = (UINT)pRTViewSize->x;
		Height = (UINT)pRTViewSize->y;
	}

	D3D11_TEXTURE2D_DESC Tex2DDesc;
	D3D11_RENDER_TARGET_VIEW_DESC RTVDesc;

	::ZeroMemory(&Tex2DDesc, sizeof(D3D11_TEXTURE2D_DESC));
	Tex2DDesc.ArraySize = 1;
	Tex2DDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	Tex2DDesc.Usage = D3D11_USAGE_DEFAULT;
	Tex2DDesc.Format = Format;
	Tex2DDesc.Width = Width;
	Tex2DDesc.Height = Height;
	Tex2DDesc.MipLevels = MipLevels;
	Tex2DDesc.SampleDesc.Count = SCDesc.SampleDesc.Count;
	Tex2DDesc.SampleDesc.Quality = SCDesc.SampleDesc.Quality;

	::ZeroMemory(&RTVDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	RTVDesc.Format = Tex2DDesc.Format;
	if (Tex2DDesc.SampleDesc.Count == 1)
		RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	else
		RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
	RTVDesc.Texture2D.MipSlice = 0;

	// �~�b�v�}�b�v�`�F�[���̍쐬��������
	if (MipLevels != 1)
		Tex2DDesc.MiscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;

	hr = m_cpD3DDevice->CreateTexture2D(&Tex2DDesc, NULL, pTexture2D.GetAddressOf());
	if (FAILED(hr))
		goto EXIT;

	hr = m_cpD3DDevice->CreateRenderTargetView(pTexture2D.Get(), &RTVDesc, (ppRTView).GetAddressOf());
	if (FAILED(hr))
		goto EXIT;

	hr = S_OK;
EXIT:
	return hr;
}



/**********************************************************************************************//**
 * @fn	ID3D11ShaderResourceView* CDirectX11RenderDeviceManager::GetSRViewFromRTView(ID3D11RenderTargetView* pRTView)
 *
 * @brief	�����_�[�^�[�Q�b�g�r���[����V�F�[�_�[���\�[�X�r���[���擾����.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pRTView	If non-null, the right view.
 *
 * @return	null if it fails, else the sr view from right view.
 **************************************************************************************************/

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> DirectX11RenderDeviceManager::GetSRViewFromRTView(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRTView)
{
	Microsoft::WRL::ComPtr<ID3D11Resource> pResource = NULL;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pSRView = NULL;

	pRTView->GetResource(pResource.GetAddressOf());
	m_cpD3DDevice->CreateShaderResourceView(pResource.Get(), NULL, pSRView.GetAddressOf());
	(pResource);

	return pSRView;
}

void DirectX11RenderDeviceManager::SetBackBufferRenderTarget()
{
	// Bind the render target view and depth stencil buffer to the output render pipeline.
	m_cpImmediateContext->OMSetRenderTargets(1, m_cpRenderTargetView.GetAddressOf(), m_cpDepthStencilView.Get());
	return;
}

void DirectX11RenderDeviceManager::SetDefaultRasterizerState()
{
	// ID3D11RasterizerState
	// D3D11_RASTERIZER_DESC

	m_rasterStateDesc.FillMode = D3D11_FILL_SOLID;    // �|���S���ʕ`��
	m_rasterStateDesc.CullMode = D3D11_CULL_BACK;     // ���ʂ�`�悵�Ȃ�
	m_rasterStateDesc.FrontCounterClockwise = TRUE;  // ���v����\��
	m_rasterStateDesc.FrontCounterClockwise = FALSE;   // �����v����\��
	m_rasterStateDesc.DepthBias = 0;
	m_rasterStateDesc.DepthBiasClamp = 0;
	m_rasterStateDesc.SlopeScaledDepthBias = 0;
	m_rasterStateDesc.DepthClipEnable = TRUE;
	m_rasterStateDesc.ScissorEnable = FALSE;          // �V�U�[��`����

	m_cpD3DDevice->CreateRasterizerState(&m_rasterStateDesc, m_rasterState.GetAddressOf());

	// Assumes that "pDevice" is valid (ID3D11Device*)

	m_cpImmediateContext->RSSetState(m_rasterState.Get());
}

void DirectX11RenderDeviceManager::SetFrontCullingState()
{
	m_rasterStateDesc.FillMode = D3D11_FILL_SOLID;    // �|���S���ʕ`��
	m_rasterStateDesc.CullMode = D3D11_CULL_FRONT;     // ���ʂ�`�悵�Ȃ�
	m_rasterStateDesc.FrontCounterClockwise = TRUE;  // ���v����\��
	m_rasterStateDesc.FrontCounterClockwise = FALSE;   // �����v����\��
	m_rasterStateDesc.DepthBias = 0;
	m_rasterStateDesc.DepthBiasClamp = 0;
	m_rasterStateDesc.SlopeScaledDepthBias = 0;
	m_rasterStateDesc.DepthClipEnable = TRUE;
	m_rasterStateDesc.ScissorEnable = FALSE;          // �V�U�[��`����

	m_cpD3DDevice->CreateRasterizerState(&m_rasterStateDesc, m_rasterState.GetAddressOf());

	// Assumes that "pDevice" is valid (ID3D11Device*)

	m_cpImmediateContext->RSSetState(m_rasterState.Get());
}

void DirectX11RenderDeviceManager::SetBackCullingState()
{
	m_rasterStateDesc.FillMode = D3D11_FILL_SOLID;    // �|���S���ʕ`��
	m_rasterStateDesc.CullMode = D3D11_CULL_BACK;     // ���ʂ�`�悵�Ȃ�
	m_rasterStateDesc.FrontCounterClockwise = TRUE;  // ���v����\��
	m_rasterStateDesc.FrontCounterClockwise = FALSE;   // �����v����\��
	m_rasterStateDesc.DepthBias = 0;
	m_rasterStateDesc.DepthBiasClamp = 0;
	m_rasterStateDesc.SlopeScaledDepthBias = 0;
	m_rasterStateDesc.DepthClipEnable = TRUE;
	m_rasterStateDesc.ScissorEnable = FALSE;          // �V�U�[��`����

	m_cpD3DDevice->CreateRasterizerState(&m_rasterStateDesc, m_rasterState.GetAddressOf());

	// Assumes that "pDevice" is valid (ID3D11Device*)

	m_cpImmediateContext->RSSetState(m_rasterState.Get());
}

void DirectX11RenderDeviceManager::SetNoneCullingState()
{
	m_rasterStateDesc.FillMode = D3D11_FILL_SOLID;    // �|���S���ʕ`��
	m_rasterStateDesc.CullMode = D3D11_CULL_NONE;     // ���ʂ�`�悵�Ȃ�
	m_rasterStateDesc.FrontCounterClockwise = TRUE;  // ���v����\��
	m_rasterStateDesc.FrontCounterClockwise = FALSE;   // �����v����\��
	m_rasterStateDesc.DepthBias = 0;
	m_rasterStateDesc.DepthBiasClamp = 0;
	m_rasterStateDesc.SlopeScaledDepthBias = 0;
	m_rasterStateDesc.DepthClipEnable = TRUE;
	m_rasterStateDesc.ScissorEnable = FALSE;          // �V�U�[��`����

	m_cpD3DDevice->CreateRasterizerState(&m_rasterStateDesc, m_rasterState.GetAddressOf());

	// Assumes that "pDevice" is valid (ID3D11Device*)

	m_cpImmediateContext->RSSetState(m_rasterState.Get());
}

void DirectX11RenderDeviceManager::SetSolidRasterize()
{
	m_rasterStateDesc.FillMode = D3D11_FILL_SOLID;    // �|���S���ʕ`��

	m_cpD3DDevice->CreateRasterizerState(&m_rasterStateDesc, m_rasterState.GetAddressOf());

	m_cpImmediateContext->RSSetState(m_rasterState.Get());
}

void DirectX11RenderDeviceManager::SetWireframeRasterize()
{
	m_rasterStateDesc.FillMode = D3D11_FILL_WIREFRAME;    // �|���S���ʕ`��
	m_cpD3DDevice->CreateRasterizerState(&m_rasterStateDesc, m_rasterState.GetAddressOf());

	m_cpImmediateContext->RSSetState(m_rasterState.Get());
}

void DirectX11RenderDeviceManager::ResetViewport()
{
	// Set the viewport.
	m_cpImmediateContext->RSSetViewports(1, m_viewport);

	return;
}

void DirectX11RenderDeviceManager::TurnZBufferOn()
{
	m_cpImmediateContext->OMSetDepthStencilState(m_depthStencilState.Get(), 1);
	return;
}

void DirectX11RenderDeviceManager::TurnZBufferOff()
{
	m_cpImmediateContext->OMSetDepthStencilState(m_depthDisabledStencilState.Get(), 1);
	return;
}

void DirectX11RenderDeviceManager::ZBufferNotWriteNotEnable()
{
	m_cpImmediateContext->OMSetDepthStencilState(m_notWriteDepthStencilState.Get(), 1);
	return;
}