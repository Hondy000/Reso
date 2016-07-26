/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\Renderer\DirectX\ver.11\CDirectX11SwapChain.cpp
 *
 * @brief	Implements the direct x coordinate 11 swap chain class.
 **************************************************************************************************/

#include "../Public/DirectX11SwapChain.h"
#include "../../../../../Debug/Public/Debug.h"
#include "../../../../../Utility/Public/HFString.h"

/**********************************************************************************************//**
 * @fn	DirectX11SwapChain::DirectX11SwapChain()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 **************************************************************************************************/

DirectX11SwapChain::DirectX11SwapChain()
{
}

/**********************************************************************************************//**
 * @fn	DirectX11SwapChain::~DirectX11SwapChain()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 **************************************************************************************************/

DirectX11SwapChain::~DirectX11SwapChain()
{
}

/**********************************************************************************************//**
 * @fn	HRESULT DirectX11SwapChain::CreateSwapChain( DXGI_MODE_DESC* pDisplayMode, bool MultisampleEnabled, HWND hWnd )
 *
 * @brief	Creates swap chain.
 *
 * @author	Kazuyuki Honda
 * @date	2015/08/02
 *
 * @param [in,out]	pDisplayMode	If non-null, the display mode.
 * @param	MultisampleEnabled  	true to enable, false to disable the multisample.
 * @param	hWnd					Handle of the window.
 *
 * @return	The new swap chain.
 **************************************************************************************************/

HRESULT DirectX11SwapChain::CreateSwapChain(
	DXGI_MODE_DESC* pDisplayMode,
	bool MultisampleEnabled,
	HWND hWnd
	)
{
	HRESULT hr = E_FAIL;  HFString test;
	TCHAR s[256];
	IDXGIFactory* pFactory = NULL;

	//CONSOLE_LOG(_T("�X���b�v�`�F�[���쐬"), _T(""), _T("�J�n"));

	// DXGI_SWAP_CHAIN_DESC
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	// DXGI_MODE_DESC
	::CopyMemory(&(sd.BufferDesc), pDisplayMode, sizeof(DXGI_MODE_DESC));
	sd.BufferDesc.Format = D3D11USER_FORMAT;                         // �o�b�N�o�b�t�@�t�H�[�}�b�g
	// �o�b�N�o�b�t�@�̃T�[�t�F�X�g�p�@����� CPU �A�N�Z�X �I�v�V������\�� DXGI_USAGE �񋓌^�̃����o�[
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;                // �o�b�N�o�b�t�@�Ƀ����_�����O�\�ɂ���B
	//�X���b�v �`�F�[���̃o�b�t�@�[����\���l�B
	sd.BufferCount = 1;
	// �o�̓E�B���h�E�ւ� HWND �n���h���B���̃����o�[�� NULL �ɂ͂ł��Ȃ��B
	sd.OutputWindow = hWnd;
	// �o�͂��E�B���h�E ���[�h�̏ꍇ�� TRUE�B����ȊO�̏ꍇ�� FALSE�B
	// �����N�����̕\�����[�h�̓E�B���h�E���[�h�ɌŒ�Ƃ���B
	sd.Windowed = TRUE;
	// �T�[�t�F�X�̃X���b�v������Ƀo�b�N�o�b�t�@�̓��e��ێ����邩�B
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;                        // �o�b�N�o�b�t�@�̓��e��ێ����Ȃ��B
	// �X���b�v �`�F�[���̓���̃I�v�V�����B
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;               // �t���X�N���[�����[�h�ɐ؂�ւ���ƁA�A�v���P�[�V���� �E�B���h�E�̃T�C�Y�ɍ��킹�ĉ𑜓x���ύX�����B

	// �t�@�N�g���[���쐬����
	// CreateDXGIFactory�ō쐬�����t�@�N�g���[���g�p����Ǝ��s�ł��邪���[�j���O�G���[�ɂȂ�̂� IDXGIAdapter ����쐬����B
	hr = m_wpAdapter.lock()->GetAdapter()->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);
	if (FAILED(hr)) goto EXIT;

	// �}���`�T���v�����O�̐ݒ�
	// �}���`�T���v�����g�p���Ȃ��ꍇ�̐ݒ�
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	int startMultisample;

	// �T���v�����O�����ő�̂��̂��̗p����
	if (MultisampleEnabled == TRUE)
		startMultisample = D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT;
	// �}���`�T���v���𖳌��ɂ���B
	else
		startMultisample = 1;

	UINT Quality = 0;
	for (int i = startMultisample; i >= 0; i--)
	{
		// �T�|�[�g����N�H���e�B���x���̍ő�l���擾����
		// CheckMultisampleQualityLevels
		hr = m_cpDevice->CheckMultisampleQualityLevels(pDisplayMode->Format, (UINT)i, &Quality);
		if (FAILED(hr)) goto EXIT;

		// 0 �ȊO�̂Ƃ��t�H�[�}�b�g�ƃT���v�����O���̑g�ݍ��킹���T�|�[�g����
		// �I�����C���w���v�ł�CheckMultisampleQualityLevels�̖߂�l�� 0 �̂Ƃ��T�|�[�g����Ȃ��Ƃ�����Ă��邪
		// pNumQualityLevels �̖߂�l�� 0 ���Ŕ��f����B
		// Direct3D 10 �� �̃I�����C���w���v�ɂ͂���������Ă���̂ŁA�I�����C���w���v�̊ԈႢ�B
		if (Quality != 0)
		{
			sd.SampleDesc.Count = i;
			sd.SampleDesc.Quality = Quality-1;

			// �X���b�v�`�F�[�����쐬����B
			// CreateSwapChain
			hr = pFactory->CreateSwapChain(m_cpDevice.Get(), &sd, m_cpSwapChain.GetAddressOf());
			_stprintf_s(s, _T("Count(%d) Quality(%d)"), sd.SampleDesc.Count, sd.SampleDesc.Quality);
			if (SUCCEEDED(hr))
			{			
			//	HFDebug::Debug::GetInstance()->SetConsoleTextRed();
				CONSOLE_LOG(("�}���`�T���v��"), (s), ("OK\n"));
				break;
			}
			else
			{
				HFDebug::Debug::Log(HFString("�}���`�T���v��")+HFString(s)+ HFString("�m�f\n"));
			}
		}
	}
	if (m_cpSwapChain == NULL)
	{
		hr = E_FAIL;
		goto EXIT;
	}


	_stprintf_s(s, _T("�𑜓x( %d : %d )�@���t���b�V�����[�g( %d / %d )"),pDisplayMode->Width, pDisplayMode->Height, pDisplayMode->RefreshRate.Denominator, pDisplayMode->RefreshRate.Numerator);
	CONSOLE_LOG(_T("�f�B�X�v���C���[�h"), s, _T("�I��"));

	CONSOLE_LOG(_T("�X���b�v�`�F�[���쐬"),  _T("����"));

	//�g�p�\��MSAA���擾
	DXGI_SAMPLE_DESC MSAA;
	for (int i = 0; i <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; i++) {
		UINT Quality;
		if (SUCCEEDED(m_cpDevice->CheckMultisampleQualityLevels(D3D11USER_FORMAT, i, &Quality)))
		{
			if (0 < Quality)
			{
				MSAA.Count = i;
				MSAA.Quality = Quality - 1;
			}
		}
	}

	hr = S_OK;

EXIT:
	(pFactory)->Release();

	return hr;
}