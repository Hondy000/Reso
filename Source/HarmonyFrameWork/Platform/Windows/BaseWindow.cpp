/**********************************************************************************************//**
																								* @file	CBaseWindow.cpp
																								*
																								* @brief	Implements the base Windows Form.
																								**************************************************************************************************/

#include"BaseWindow.h"
#include <tchar.h>

																								//静的メンバの初期化
LONG	BaseWindow::stNowWindowCount = 0;

/**********************************************************************************************//**
																								* @fn	CBaseWindow::CBaseWindow(const HINSTANCE hInst, const HWND hWndParent, const BOOL isFullWindow)
																								*
																								* @brief	&lt; フルウィンドウで生成.
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

	//初期化処理
	this->Initialize();

	//ウィンドウクラス登録
	if (FAILED(this->RegisterWindow(hInst)))
	{
	}

	//ウィンドウ作成
	if (FAILED(this->CreateMyWindow(hWndParent, isFullWindow)))
	{
	}

	//ウィンドウハンドルにポインタを関連付ける
	this->SetWindowHandlePointer(m_hWnd, this);
	SendMessage(m_hWnd, WM_CREATE, 0, 0);
}

/**********************************************************************************************//**
																								* @fn	CBaseWindow::~CBaseWindow()
																								*
																								* @brief	&lt; デストラクタ.
																								*
																								* @author	Kazuyuki
																								* @date	2015/06/17
																								**************************************************************************************************/

BaseWindow::~BaseWindow()
{
	ShowWindow(m_hWnd, SW_HIDE);
	UpdateWindow(m_hWnd);

	//ウィンドウ破棄処理
	if (m_isWindowDestory == FALSE)
	{
		SendMessage(m_hWnd, WM_DESTROY, 0, 0);
		for (; m_isWindowDestory == FALSE;);
	}

	//終了処理
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

	//ウィンドウハンドル初期化
	m_hWnd = nullptr;

	//親ウィンドウフラグ初期化
	m_isMainWindow = FALSE;

	//ウィンドウ破棄フラグ初期化
	m_isWindowDestory = FALSE;

	//現在のウィンドウ数カウント
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
	// ウィンドウクラスの解放
	if (m_hWnd != nullptr)
	{
		//終了処理
		UnregisterClass(m_wcex.lpszClassName, m_wcex.hInstance);
		ZeroMemory(&m_wcex, sizeof(WNDCLASSEX));

		//ウィンドウの関連付けを解放
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
	//ポインタ取得
	BaseWindow* pMenuWindow = (BaseWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	//ポインタ取得
	if (pMenuWindow)
	{
		//オーバーライドしたウィンドウプロシージャの処理
		return pMenuWindow->WndProc(hWnd, msg, wParam, lParam);
	}

	//ポインタ取得に失敗したら通常処理
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
	//Windows登録情報
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

	//設計チェック
	if (!RegisterClassEx(&m_wcex)) {
		MessageBox(nullptr, _T("設計エラー"), _T("エラー"), MB_OK);
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

	//ウィンドウ作成
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

	//エラーチェック
	if (m_hWnd == nullptr)
	{
		MessageBox(nullptr, _T("ウィンドウ作成失敗"), _T("設計段階1"), MB_ABORTRETRYIGNORE);
		return	E_FAIL;
	}

	//ウィンドウが親かどうか
	m_isMainWindow = (hWndParent == nullptr) ? TRUE : FALSE;

	//ウィンドウ表示・更新
	//ShowWindow(m_hWnd, SW_SHOWNORMAL);
	//UpdateWindow(m_hWnd);

	return	S_OK;
}

void BaseWindow::TransactMessage(void)
{
	MSG msg;
	//メッセージ取出し
	if (PeekMessage(&msg, this->m_hWnd, 0, 0, PM_REMOVE))
	{
		//メッセージ処理
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void BaseWindow::ChangeWindowSize(LONG x, LONG y)
{
	// クライアント領域のサイズからウィンドウサイズを設定
	RECT    rect = { 0, 0, x, y };
	::AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, 0);
	::SetWindowPos(m_hWnd, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
}
