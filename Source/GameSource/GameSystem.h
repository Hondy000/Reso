#pragma once
#include <mutex>
#include "../HarmonyFrameWork/Core/Public/Common.h"
#include "../HarmonyFrameWork/Core/Public/Level/LevelInterface.h"


class GameSystem
{
public:
	virtual ~GameSystem();
	static bool isEnd;
	static std::mutex s_mutex;
	bool Init();

	static GameSystem* GetInstance(void)
	{
		static GameSystem singleton;
		return &singleton;
	}

	void GameMain(void);
	void TransitionState();
	bool Update();
	bool Draw();
	void Reset();

private:
	GameSystem();
	//std::shared_ptr< SceneManager> m_spSceneManager;
	DWORD execLastTime;
	DWORD currentTime;
	std::shared_ptr<ILevel> m_spScene;
	
#ifdef DEBUG
	FILE *fp;
#endif
};
