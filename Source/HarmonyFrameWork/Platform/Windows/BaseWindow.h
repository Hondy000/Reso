/*************************************************************
*	@file   	CBaseWindows.h
*	@brief  	Window基底クラス
*	@note		特になし
*	@author		Honda Kazuyuki
*	@date		2014/03/06
*************************************************************/

#pragma once
#include <time.h>

#include <Windows.h>

#define	_Include_CBaseWindow_h_

class BaseWindow
{
public:

	BaseWindow(CONST HINSTANCE hInst, CONST HWND hWndParent, CONST BOOL isFullWindow);
	virtual ~BaseWindow();
	virtual void Initialize(void);
	void Finalize(void);

	void SetWindowHandlePointer(HWND hWnd, LPVOID ptr)
	{
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)ptr);
	}

	HWND GetHWND(void)
	{
		return m_hWnd;
	}
	static LRESULT	CALLBACK	BaseWindow::CommonWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual	LRESULT	CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HRESULT CreateMyWindow(CONST HWND, CONST BOOL);
	HRESULT RegisterWindow(CONST HINSTANCE);
	void TransactMessage(void);

public:
	bool m_isMainWindow;
	bool m_isWindowDestory;

	// Access the WindowWidth
	LONG GetWindowWidth(void) const { return(m_windowWidth); };
	void SetWindowWidth(LONG windowWidth) { m_windowWidth = windowWidth; };

	// Access the WindowHeight
	LONG GetWindowHeight(void) const { return(m_windowHeight); };
	void SetWindowHeight(LONG windowHeight) { m_windowHeight = windowHeight; };

	void ChangeWindowSize(LONG x,LONG y);
protected:
	WNDCLASSEX m_wcex;

	HWND m_hWnd;

	MSG	m_msg;				///< メッセージ

	LONG m_windowWidth;
	LONG m_windowHeight;

	static LONG stNowWindowCount;
};
