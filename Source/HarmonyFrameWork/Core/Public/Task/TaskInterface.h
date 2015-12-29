#pragma once

#include "../Common.h"
#include "../BaseObject.h"

/**********************************************************************************************//**
 * @interface	IBaseTask TaskInterface.h Source\HarmonyFrame\Core\TaskInterface.h
 *
 * @brief	タスクインターフェース(ジョブだかアクターだかゲームオブジェクトに当たる奴)
 * @brief	細かい仕事を行う
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

class IBaseTask
	:
	virtual public BaseObject
{
public:
	typedef DWORD PRIORITY;

protected:
	IBaseTask();
	bool m_isUsage;	// タスク有効フラグ（trueでないとタスクが働かないとします）

	PRIORITY m_priority;
public:
	friend class TaskFactory;
	friend class ActorFactory;
	virtual ~IBaseTask() {};
	virtual bool Init() = 0;
	// 更新する
	virtual bool Update() = 0;

	// タスクの状態をリセットする
	virtual void Reset() = 0;

	// 現在の状態を取得する
	bool CheckUsageFlag() { return m_isUsage; }

	// 更新条件が揃っているかチェックする
	virtual bool AllowUpdate() { return true; }


	// Access the Priority
	const PRIORITY& GetPriority(void) const
	{
		return(m_priority);
	};

	void SetPriority(const PRIORITY& priority)
	{
		m_priority = priority;
	};
};



// 描画関係タスク
class IDrawTask
	:
	virtual public IBaseTask
{
protected:
	IDrawTask() {};
public:
	virtual bool Draw() = 0;
	virtual ~IDrawTask() {};
};