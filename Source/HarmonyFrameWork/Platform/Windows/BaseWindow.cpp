/**********************************************************************************************//**
																								* @file	CBaseWindow.cpp
																								*
																								* @brief	Implements the base Windows Form.
																								**************************************************************************************************/

#include"BaseWindow.h"
#include <tchar.h>

																								//�ÓI�����o�̏�����
LONG	BaseWindow::stNowWindowCount = 0;

/**********************************************************************************************//**
																								* @fn	CBaseWindow::CBaseWindow(const HINSTANCE hInst, const HWND hWndParent, const BOOL isFullWindow)
																								*
																								* @brief	&lt; �t���E�B���h�E�Ő���.
																								*
																								* @author	Kazuyuki
																								* @date	2015/06/17
																								*
																								* @param	hInst			The instance.
																								* @param	hWndParent  	The window parent.
																								* @param	isFullWindow	The is full window.
																								**************************************************************************************************/

BaseWindow::BaseWindow(const HINSTANCE hInst, const HWND hWndParent, const BOOL isFullWindow)
{
	if (isFullWindow)
	{
		m_windowWidth = 300;
		m_windowHeight = 300;
	}
	else
	{
		m_windowWidth = 1280;
		m_windowHeight = 720;
	}

	//����������
	this->Initialize();

	//�E�B���h�E�N���X�o�^
	if (FAILED(this->RegisterWindow(hInst)))
	{
	}

	//�E�B���h�E�쐬
	if (FAILED(this->CreateMyWindow(hWndParent, isFullWindow)))
	{
	}

	//�E�B���h�E�n���h���Ƀ|�C���^���֘A�t����
	this->SetWindowHandlePointer(m_hWnd, this);
	SendMessage(m_hWnd, WM_CREATE, 0, 0);
}

/**********************************************************************************************//**
																								* @fn	CBaseWindow::~CBaseWindow()
																								*
																								* @brief	&lt; �f�X�g���N�^.
																								*
																								* @author	Kazuyuki
																								* @date	2015/06/17
																								**************************************************************************************************/

BaseWindow::~BaseWindow()
{
	ShowWindow(m_hWnd, SW_HIDE);
	UpdateWindow(m_hWnd);

	//�E�B���h�E�j������
	if (m_isWindowDestory == FALSE)
	{
		SendMessage(m_hWnd, WM_DESTROY, 0, 0);
		for (; m_isWindowDestory == FALSE;);
	}

	//�I������
	this->Finalize();
}

/**********************************************************************************************//**
																								* @fn	void CBaseWindow::Initialize()
																								*
																								* @brief	Initializes this object.
																								*
																								* @author	Kazuyuki
																								* @date	2015/06/17
																								**************************************************************************************************/

void BaseWindow::Initialize()
{
	ZeroMemory(&m_wcex, sizeof(WNDCLASSEX));

	//�E�B���h�E�n���h��������
	m_hWnd = nullptr;

	//�e�E�B���h�E�t���O������
	m_isMainWindow = FALSE;

	//�E�B���h�E�j���t���O������
	m_isWindowDestory = FALSE;

	//���݂̃E�B���h�E���J�E���g
	++stNowWindowCount;

	return;
}

/**********************************************************************************************//**
																								* @fn	void CBaseWindow::Finalize()
																								*
																								* @brief	Finalizes this object.
																								*
																								* @author	Kazuyuki
																								* @date	2015/06/17
																								**************************************************************************************************/

void	BaseWindow::Finalize()
{
	// �E�B���h�E�N���X�̉��
	if (m_hWnd != nullptr)
	{
		//�I������
		UnregisterClass(m_wcex.lpszClassName, m_wcex.hInstance);
		ZeroMemory(&m_wcex, sizeof(WNDCLASSEX));

		//�E�B���h�E�̊֘A�t�������
		this->SetWindowHandlePointer(m_hWnd, nullptr);
		m_hWnd = nullptr;
	}

	return;
}

/**********************************************************************************************//**
																								* @fn	LRESULT CALLBACK CBaseWindow::CommonWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
																								*
																								* @brief	Common window proc.
																								*
																								* @author	Kazuyuki
																								* @date	2015/06/17
																								*
																								* @param	hWnd  	Handle of the window.
																								* @param	msg   	The message.
																								* @param	wParam	The wParam field of the message.
																								* @param	lParam	The lParam field of the message.
																								*
																								* @return	A CALLBACK.
																								**************************************************************************************************/

LRESULT	CALLBACK	BaseWindow::CommonWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//�|�C���^�擾
	BaseWindow* pMenuWindow = (BaseWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	//�|�C���^�擾
	if (pMenuWindow)
	{
		//�I�[�o�[���C�h�����E�B���h�E�v���V�[�W���̏���
		return pMenuWindow->WndProc(hWnd, msg, wParam, lParam);
	}

	//�|�C���^�擾�Ɏ��s������ʏ폈��
	return	DefWindowProc(hWnd, msg, wParam, lParam);
}

/**********************************************************************************************//**
																								* @fn	LRESULT CALLBACK CBaseWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
																								*
																								* @brief	Window proc.
																								*
																								* @author	Kazuyuki
																								* @date	2015/06/17
																								*
																								* @param	hWnd  	Handle of the window.
																								* @param	msg   	The message.
																								* @param	wParam	The wParam field of the message.
																								* @param	lParam	The lParam field of the message.
																								*
																								* @return	A CALLBACK.
																								**************************************************************************************************/

LRESULT	CALLBACK	BaseWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		srand((UINT)time(0));
	}
	break;
	case WM_TIMER:
	{
	}
	break;
	case WM_LBUTTONDOWN:
	{
	}
	break;
	case WM_LBUTTONUP:
	{
	}
	break;
	case WM_PAINT:

		break;
	case WM_MOUSEWHEEL:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		m_isWindowDestory = TRUE;
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

inline	BOOL	BaseWindow::RegisterWindow(const HINSTANCE hInst)
{
	//Windows�o�^���
	m_wcex.cbSize = sizeof(WNDCLASSEX);
	m_wcex.style = CS_HREDRAW | CS_VREDRAW;
	m_wcex.hInstance = hInst;
	m_wcex.lpszClassName = (_T("dev"));
	m_wcex.lpfnWndProc = BaseWindow::CommonWndProc;
	m_wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	m_wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	m_wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	m_wcex.lpszMenuName = nullptr;
	m_wcex.cbClsExtra = 0;
	m_wcex.cbWndExtra = 0;

	//�݌v�`�F�b�N
	if (!RegisterClassEx(&m_wcex)) {
		MessageBox(nullptr, _T("�݌v�G���["), _T("�G���["), MB_OK);
		return	E_FAIL;
	}

	return	S_OK;
}

BOOL	BaseWindow::CreateMyWindow(const HWND hWndParent, const BOOL isFullWindow)
{
	DWORD dwStyle = 0;
	SHORT nWidth, nHeight;

	if (isFullWindow)
	{
		dwStyle = WS_VISIBLE | WS_POPUP;
		nWidth = m_windowWidth;
		nHeight = m_windowHeight;
	}
	else
	{
		dwStyle = WS_OVERLAPPEDWINDOW;
		nWidth = m_windowWidth;
		nHeight = m_windowHeight;
	}

	RECT rc = { 0, 0, nWidth, nHeight };
	::SetRect(&rc, 0, 0, nWidth, nHeight);

	//AdjustWindowRectEx(&rc, dwStyle, FALSE, WS_EX_OVERLAPPEDWINDOW);
	::AdjustWindowRect(&rc, dwStyle, FALSE);

	//�E�B���h�E�쐬
	m_hWnd = CreateWindow(
		m_wcex.lpszClassName,
		m_wcex.lpszClassName,
		dwStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		hWndParent,
		nullptr,
		m_wcex.hInstance,
		nullptr
		);

	//�G���[�`�F�b�N
	if (m_hWnd == nullptr)
	{
		MessageBox(nullptr, _T("�E�B���h�E�쐬���s"), _T("�݌v�i�K1"), MB_ABORTRETRYIGNORE);
		return	E_FAIL;
	}

	//�E�B���h�E���e���ǂ���
	m_isMainWindow = (hWndParent == nullptr) ? TRUE : FALSE;

	//�E�B���h�E�\���E�X�V
	//ShowWindow(m_hWnd, SW_SHOWNORMAL);
	//UpdateWindow(m_hWnd);

	return	S_OK;
}

void BaseWindow::TransactMessage(void)
{
	MSG msg;
	//���b�Z�[�W��o��
	if (PeekMessage(&msg, this->m_hWnd, 0, 0, PM_REMOVE))
	{
		//���b�Z�[�W����
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void BaseWindow::ChangeWindowSize(LONG x, LONG y)
{
	// �N���C�A���g�̈�̃T�C�Y����E�B���h�E�T�C�Y��ݒ�
	RECT    rect = { 0, 0, x, y };
	::AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, 0);
	::SetWindowPos(m_hWnd, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
}
