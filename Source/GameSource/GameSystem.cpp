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
bool GameSystem::isEnd = 0;

/**********************************************************************************************//**
 * @fn	bool GameSystem::Update()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki
 * @date	2015/06/17
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool GameSystem::Update()
{
	return true;
}

/**********************************************************************************************//**
 * @fn	void GameSystem::Reset()
 *
 * @brief	Resets this object.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

void GameSystem::Reset()
{
}

/**********************************************************************************************//**
 * @fn	GameSystem::GameSystem()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

GameSystem::GameSystem()
{
}

/**********************************************************************************************//**
 * @fn	GameSystem::~GameSystem()
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
 * @fn	bool GameSystem::Init()
 *
 * @brief	Initialises this object.
 *
 * @author	Kazuyuki Honda
 * @date	2015/06/30
 *
 * @return	true if it succeeds, false if it fails.
 *
 * ### param	isFull	true if this object is full.
 * ### param	width 	The width.
 * ### param	height	The height.
 **************************************************************************************************/

bool GameSystem::Init()
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
 * @fn	void GameSystem::TransitionState()
 *
 * @brief	Game main.
 *
 * @author	Kazuyuki
 * @date	2015/06/17
 **************************************************************************************************/

void GameSystem::TransitionState()
{
	
}

/**********************************************************************************************//**
 * @fn	void GameSystem::GameMain(void)
 *
 * @brief	Game main.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

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
