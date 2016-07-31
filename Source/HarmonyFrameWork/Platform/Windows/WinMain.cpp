/**********************************************************************************************//**
 * @file	WinMain.cpp
 *
 * @brief	Implements the window main class.
 **************************************************************************************************/

#include<crtdbg.h>
#include <thread>
#include "BaseWindow.h"
//#include "..\..\Graphics\RenderDevice\Basic\Public\RendererManager.h"
#include "..\..\..\GameSource\GameSystem.h"
#include "..\..\Graphics\RenderDevice\Basic\Public\RendererManager.h"

/**********************************************************************************************//**
  * @fn	int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
  *
  * @brief	エントリーポイント.
  *
  * @author	Kazuyuki Honda
  * @date	2015/06/30
  *
  * @param	hInst	 	The instance.
  * @param	hPrev	 	The previous.
  * @param	lpCmdLine	The command line.
  * @param	nCmdShow 	The command show.
  *
  * @return	A WINAPI.
  **************************************************************************************************/

int	WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(480);
#endif // _DEBUG

	WindowManager::GetInstance()->Setup(hInst);

	HWND hWnd;
	//メッセージループ
	MSG msg;


	GameSystem::GetInstance()->Init();
	std::thread gameMainThread([&] {GameSystem::GetInstance()->GameMain(); });
	while (1)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			//終了メッセージがきたら終了
			if (msg.message == WM_QUIT)
			{
				if (msg.message == WM_QUIT)
				{
					GameSystem::GetInstance()->isEnd = true;
					gameMainThread.join();
					break;
				}
				break;
			}

			/**********************************************************************************************//**
			 * @brief	Message describing the dispatch.
			 *
			 * ### summary	@brief	Message describing the dispatch.
			 **************************************************************************************************/

			DispatchMessage(&msg);
		}
		else
		{
			if (!WindowManager::GetInstance()->GetMainWindow()->m_isWindowDestory)
			{
			}
			else
			{
				WaitMessage();
			}
		}
	}
	return 0;
}