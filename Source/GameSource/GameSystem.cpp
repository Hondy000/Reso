/**********************************************************************************************//**
 * @file	CGameMain.cpp
 *
 * @brief	Implements the game main class.
 **************************************************************************************************/

#include "GameSystem.h"
#include "..\HarmonyFrameWork\Input\Public\InputManager.h"
#include "..\HarmonyFrameWork\Graphics\RenderDevice\Basic\Public\RendererManager.h"
#include "..\HarmonyFrameWork\Core\Task\Public\TaskSystem.h"
#include "..\HarmonyFrameWork\Graphics\Rendering\DeferredRendering\Public\DeferredRenderingManager.h"
BOOL GameSystem::isEnd = 0;

/**********************************************************************************************//**
 * @fn	CGameMain::CGameMain()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki
 * @date	2015/06/17
 **************************************************************************************************/

BOOL GameSystem::Update()
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
 * @fn	void CGameMain::Init(BOOL isFull,int width,int height)
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

BOOL GameSystem::Init()
{
	m_levelManager = std::make_shared<LevelManager>();
	RendererManager::GetInstance()->Setup();
	sRENDER_DEVICE_MANAGER->Setup();
	
	InputManager::GetInstance()->Setup();
	sINPUT->Setup();
	std::shared_ptr<DeferredRenderingManager> deferredRender = std::make_shared<DeferredRenderingManager>();
	sTASK_SYSTEM->RegisterTask("deferredRender",deferredRender);
	m_levelManager->Init();
#ifdef WINDOWS
	
#endif // WINDOWS

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
	while(isEnd == false)
	{
		currentTime = timeGetTime();
		long frameTime = currentTime - execLastTime;
		if (frameTime >= 1000 / 60)
		{

			sINPUT->Update();
			sTASK_SYSTEM->Update();
			sTASK_SYSTEM->Render();
			execLastTime = timeGetTime();
		}


	}
	sRENDER_DEVICE_MANAGER->GetCpD3DDebug()->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
}
