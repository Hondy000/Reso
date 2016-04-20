#pragma once
#include <mutex>
#include "../HarmonyFrameWork/Core/Public/Common.h"
#include "../HarmonyFrameWork/Core/Level/Public/LevelInterface.h"
#include "../HarmonyFrameWork/Core/Level/Public/LevelManager.h"


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
	void Reset();

private:
	GameSystem();
	unsigned long execLastTime;
	unsigned long currentTime;
	std::shared_ptr<LevelManager> m_levelManager;
	
#ifdef DEBUG
	FILE *fp;
#endif
};
