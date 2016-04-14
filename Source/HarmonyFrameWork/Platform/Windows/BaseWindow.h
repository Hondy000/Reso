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
#include <memory>

#define	_Include_CBaseWindow_h_	   
class BaseWindow;
class WindowManager
{
private:

	WindowManager() {};
public:
	static WindowManager* GetInstance()
	{
		static WindowManager instance;
		return &instance;
	}
	~WindowManager()
	{
	};

	bool Setup(HINSTANCE hInst)
	{
		m_hInstance = hInst;
		return true;
	}

	bool CreateMainWindow(bool isfullscreen)
	{
		m_mainWindow = std::make_shared<BaseWindow>(m_hInstance, nullptr, isfullscreen);
		if (m_mainWindow)
		{
			 return true;
		}
		else
		{
			 return false;
		}
	}

	std::shared_ptr<BaseWindow> GetMainWindow() const
	{
		return m_mainWindow;
	}

	void SetMainWindow(std::shared_ptr<BaseWindow> _val)
	{
		m_mainWindow = _val;
	}

private:
	std::shared_ptr<BaseWindow>m_mainWindow;
	HINSTANCE m_hInstance;
};

class BaseWindow
{
public:

	BaseWindow(const HINSTANCE hInst, const HWND hWndParent, const BOOL isFullWindow);
	virtual ~BaseWindow();
	virtual void Initialize(void);
	void Finalize(void);

	void SetWindowHandlePointer(HWND hWnd, LPVOID ptr)
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)ptr);
	}

	HWND GetHWND(void)
	{
		return m_hWnd;
	}
	static LRESULT	CALLBACK	BaseWindow::CommonWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual	LRESULT	CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	BOOL CreateMyWindow(const HWND, const BOOL);
	BOOL RegisterWindow(const HINSTANCE);
	void TransactMessage(void);

public:
	BOOL m_isMainWindow;
	BOOL m_isWindowDestory;

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
