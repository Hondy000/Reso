/**********************************************************************************************//**
 * @file	CGameMain.cpp
 *
 * @brief	Implements the game main class.
 **************************************************************************************************/

#include "GameSystem.h"
#include "../../../GameDev2015Winter/Source/HarmonyFrame/Windows/CBaseWindow.h"
#include "../HarmonyFrameWork/Graphics/Public/Renderer/Basic/RendererManager.h"
#include "../HarmonyFrameWork/Input/Public/InputManager.h"
#include "../HarmonyFrameWork/Core/Public/Task/TaskSystem.h"

bool GameSystem::isEnd = 0;

/**********************************************************************************************//**
 * @fn	CGameMain::CGameMain()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki
 * @date	2015/06/17
 **************************************************************************************************/

bool GameSystem::Update()
{
	return true;
}
void GameSystem::Reset()
{
}

GameSystem::GameSystem()
{
}

/**********************************************************************************************//**
 * @fn	CGameMain::~CGameMain()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki
 * @date	2015/06/17
 **************************************************************************************************/

GameSystem::~GameSystem()
{
}

/**********************************************************************************************//**
 * @fn	void CGameMain::Init(bool isFull,int width,int height)
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/06/30
 *
 * @param	isFull	true if this object is full.
 * @param	width 	The width.
 * @param	height	The height.
 **************************************************************************************************/

bool GameSystem::Init()
{
	HWND hWnd = GetActiveWindow();
	RendererManager::GetInstance()->Setup();
	sRENDER_DEVICE_MANAGER->Setup();

	//CAudioManager::GetInstance()->Init();
	InputManager::GetInstance()->Setup();
	//m_spSceneManager = std::shared_ptr<SceneManager>(new SceneManager);
	timeBeginPeriod(1);				//タイマーの精度を1msに設定
	execLastTime = timeGetTime();
	//ActorFactory::GetInstance()->Create<TestScene>(scene);
	
	return true;
}

/**********************************************************************************************//**
 * @fn	void CGameMain::GameMain(void)
 *
 * @brief	Game main.
 *
 * @author	Kazuyuki
 * @date	2015/06/17
 **************************************************************************************************/

void GameSystem::TransitionState()
{
	
}

void GameSystem::GameMain(void)
{
	timeBeginPeriod(1);				//タイマーの精度を1msに設定

	while (true)
	{
		currentTime = timeGetTime();
		if (currentTime - execLastTime > 1000 / 60)
		{
#ifdef DEBUG

			//printf("%d fps\n",1000/( currentTime - execLastTime));

#endif
			sRENDER_DEVICE_MANAGER->Clear();
			execLastTime = currentTime;
			TaskSystem::GetInstance()->Update();
			TaskSystem::GetInstance()->Draw();
		//	Draw();
		}

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 || isEnd == true)
		{
			break;
		}
		}
	timeEndPeriod(1);							// タイマの分解能力もとに戻す
	}
