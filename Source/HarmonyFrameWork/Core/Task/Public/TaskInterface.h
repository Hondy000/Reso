/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Task\Public\TaskInterface.h
 *
 * @brief	Declares the task interface class.
 **************************************************************************************************/

#pragma once
#include "../../Public/IBaseObject.h"
#include "../../Public/VariableManager.h"

/**********************************************************************************************//**
 * @class	IBaseTask TaskInterface.h Source\HarmonyFrameWork\Core\Task\Public\TaskInterface.h
 *
 * @brief	タスクインターフェース(ジョブだかアクターだかゲームオブジェクトに当たる奴)
 * @brief	細かい仕事を行う.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

class IBaseTask
	:
	virtual public IBaseObject
{
public:

	/**********************************************************************************************//**
	 * @typedef	size_t PRIORITY
	 *
	 * @brief	Defines an alias representing the priority.
	 **************************************************************************************************/

	typedef size_t PRIORITY;


protected:
	IBaseTask()
		:
		m_isUsage(true),m_isDestroy(false)
	{
		Init();
	};
	bool m_isUsage; /*!< タスク有効フラグ（trueでないとタスクが働かないとします） */
	bool m_isDestroy;   /*!< 消去フラグ */
	PRIORITY m_updatePriority;  /*!< The update priority */
	unsigned long m_taskId; /*!< Identifier for the task */
	std::string m_name; /*!< The name */
	std::unordered_map<std::string, std::shared_ptr<IVariable>> m_varMap;   /*!< The variable map */
public:

	/**********************************************************************************************//**
	 * @class	TaskFactory TaskInterface.h Source\HarmonyFrameWork\Core\Task\Public\TaskInterface.h
	 *
	 * @brief	A task factory.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	friend class TaskFactory;
	friend class ActorFactory;
	virtual ~IBaseTask() {}

	bool Init();

	/**********************************************************************************************//**
	 * @fn	virtual bool Update() = 0;
	 *
	 * @brief	更新する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	virtual bool Update() = 0;

	/**********************************************************************************************//**
	 * @fn	virtual void Reset() = 0;
	 *
	 * @brief	タスクの状態をリセットする.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	virtual void Reset() = 0;

	/**********************************************************************************************//**
	 * @fn	virtual bool LoadTaskData(const std::string& path);
	 *
	 * @brief	Loads task data.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param	path	Full pathname of the file.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	virtual bool LoadTaskData(const std::string& path);

	/**********************************************************************************************//**
	 * @fn	bool CheckUsageFlag()
	 *
	 * @brief	現在の状態を取得する.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool CheckUsageFlag()
	{
		return m_isUsage;
	}

	/**********************************************************************************************//**
	 * @fn	bool CheckDestroy()
	 *
	 * @brief	Determines if we can check destroy.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool CheckDestroy()
	{
		return m_isDestroy;
	}

	/**********************************************************************************************//**
	 * @fn	virtual bool AllowUpdate()
	 *
	 * @brief	更新条件が揃っているかチェックする.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	true if we allow update, false if not.
	 **************************************************************************************************/

	virtual bool AllowUpdate()
	{
		return true;
	} 

	/**********************************************************************************************//**
	 * @fn	const PRIORITY& GetUpdatePriority(void) const
	 *
	 * @brief	Access the Priority.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The update priority.
	 **************************************************************************************************/

	const PRIORITY& GetUpdatePriority(void) const
	{
		return(m_updatePriority);
	};

	/**********************************************************************************************//**
	 * @fn	void SetUpdatePriority(const PRIORITY& priority)
	 *
	 * @brief	Sets update priority.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param	priority	The priority.
	 **************************************************************************************************/

	void SetUpdatePriority(const PRIORITY& priority)
	{
		m_updatePriority = priority;
	};

	/**********************************************************************************************//**
	 * @fn	const unsigned long& GetTaskId(void) const
	 *
	 * @brief	Access the TaskId.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The task identifier.
	 **************************************************************************************************/

	const unsigned long& GetTaskId(void) const
	{
		return(m_taskId);
	};

	/**********************************************************************************************//**
	 * @fn	void SetTaskId(const unsigned long& taskId)
	 *
	 * @brief	Sets task identifier.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param	taskId	Identifier for the task.
	 **************************************************************************************************/

	void SetTaskId(const unsigned long& taskId)
	{
		m_taskId = taskId;
	};

	/**********************************************************************************************//**
	 * @fn	const std::string& GetTaskName(void)const
	 *
	 * @brief	Gets task name.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The task name.
	 **************************************************************************************************/

	const std::string& GetTaskName(void)const
	{
		return m_name;
	};

	/**********************************************************************************************//**
	 * @fn	void SetTaskName(const std::string& name)
	 *
	 * @brief	Sets task name.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param	name	The name.
	 **************************************************************************************************/

	void SetTaskName(const std::string& name)
	{
		m_name = name;
	};

	/**********************************************************************************************//**
	 * @fn	template<typename T> std::shared_ptr<Variable<T>> GetVariable(const std::string& variableName)
	 *
	 * @brief	Gets a variable.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @tparam	T	Generic type parameter.
	 * @param	variableName	Name of the variable.
	 *
	 * @return	The variable.
	 **************************************************************************************************/

	template<typename T>
	std::shared_ptr<Variable<T>> GetVariable(const std::string& variableName)
	{				  
		return VariableManagersManager::GetInstance()->GetVariable<T>(m_globalID, variableName);
	};

	/**********************************************************************************************//**
	 * @fn	std::shared_ptr<IVariable> GetVariable(const std::string& variableName)
	 *
	 * @brief	Gets a variable.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param	variableName	Name of the variable.
	 *
	 * @return	The variable.
	 **************************************************************************************************/

	std::shared_ptr<IVariable> GetVariable(const std::string& variableName)
	{
		auto res = m_varMap.find(variableName);
		if (res != m_varMap.end())
		{
			return res->second;
		}
		return nullptr;
	};
	public:

	/**********************************************************************************************//**
	 * @fn	template <typename T> bool RegisterVariable ( const std::string& variableName, std::shared_ptr<Variable<T>> spVariable )
	 *
	 * @brief	shared_ptr&lt;T&gt;をT型Variableとしてタスク内に登録.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @tparam	T	Generic type parameter.
	 * @param	variableName	Name of the variable.
	 * @param	spVariable  	The shared_ptr of variable.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	template <typename T>
	bool RegisterVariable
	(
		const std::string& variableName,
		std::shared_ptr<Variable<T>> spVariable
	)
	{

		std::pair<std::string, std::shared_ptr<IVariable>> key;
		key.first = variableName;
		key.second = spVariable;
		auto res = m_varMap.insert(key);
		if(res.second)
		{
			if (VariableManagersManager::GetInstance()->RegsigterVariable<T>(this->m_globalID, variableName, spVariable))
			{
				return true;
			}
		}
		return false;
	};

	/**********************************************************************************************//**
	 * @fn	template <typename T, typename V> bool RegisterVariable ( const std::string& variableName, std::shared_ptr<V> spDerivationVariable )
	 *
	 * @brief	T型から派生したV型ポインタをタスクに登録.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @tparam	T	Generic type parameter.
	 * @tparam	V	Generic type parameter.
	 * @param	variableName			Name of the variable.
	 * @param	spDerivationVariable	派生ポインタ.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	template <typename T, typename V>
	bool RegisterVariable
	(
		const std::string& variableName,
		std::shared_ptr<V> spDerivationVariable
	)
	{
		std::shared_ptr<Variable<T>> wrapVar = std::make_shared<Variable<T>>();

		wrapVar->SetValue(std::dynamic_pointer_cast<T>(spDerivationVariable));
		std::pair<std::string, std::shared_ptr<IVariable>> key;
		key.first = variableName;
		key.second = wrapVar;
		auto res = m_varMap.insert(key);
		if (res.second)
		{
			if (VariableManagersManager::GetInstance()->RegsigterVariable<T>(this->m_globalID, variableName, wrapVar))
			{
				return true;
			}
		}
	};

	/**********************************************************************************************//**
	 * @fn	template <typename T> bool RegisterVariable ( const std::string& variableName, std::shared_ptr<T> spVariable )
	 *
	 * @brief	T型スマートポインタをタスクに登録.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @tparam	T	Generic type parameter.
	 * @param	variableName	Name of the variable.
	 * @param	spVariable  	T型スマートポインタ.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	template <typename T>
	bool RegisterVariable
	(
		const std::string& variableName,
		std::shared_ptr<T> spVariable
	)
	{
		std::shared_ptr<Variable<T>> wrapVar = std::make_shared<Variable<T>>();

		wrapVar->SetValue(spVariable);
		std::pair<std::string, std::shared_ptr<IVariable>> key;
		key.first = variableName;
		key.second = wrapVar;
		auto res = m_varMap.insert(key);
		if (res.second)
		{
			if (VariableManagersManager::GetInstance()->RegsigterVariable<T>(this->m_globalID, variableName, wrapVar))
			{
				return true;
			}
		}
	};

	/**********************************************************************************************//**
	 * @fn	template <typename T> bool RegisterVariable(const std::string& variableName, T variable)
	 *
	 * @brief	T型の変数をタスクに登録.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @tparam	T	Generic type parameter.
	 * @param	variableName	Name of the variable.
	 * @param	variable		The variable.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	template <typename T>
	bool RegisterVariable
	(
		const std::string& variableName, 
		T variable
	)
	{
		std::shared_ptr<Variable<T>> wrapVar = std::make_shared<Variable<T>>();

		std::shared_ptr<T> constant = std::make_shared<T>();
		*constant = variable;
		wrapVar->SetValue(constant);
		std::pair<std::string, std::shared_ptr<IVariable>> key;
		key.first = variableName;
		key.second = wrapVar;
		auto res = m_varMap.insert(key);
		if (res.second)
		{
			if (VariableManagersManager::GetInstance()->RegsigterVariable<T>(this->m_globalID, variableName, wrapVar))
			{
				return true;
			}
		}
	};
	bool CreateVariable(const std::string& variableName,std::string typeName)
	{
		return VariableManagersManager::GetInstance()->CreateVariable(this->m_globalID, variableName, typeName);
	}

};

/**********************************************************************************************//**
 * @class	IDrawTask TaskInterface.h Source\HarmonyFrameWork\Core\Task\Public\TaskInterface.h
 *
 * @brief	描画関係タスク.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

class IDrawTask
	:
	virtual public IBaseTask
{

protected:

	/**********************************************************************************************//**
	 * @fn	IDrawTask()
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	IDrawTask() {};
	PRIORITY m_drawPriority;	/*!< The draw priority */
public:

	/**********************************************************************************************//**
	 * @fn	virtual bool Draw() = 0;
	 *
	 * @brief	Draws this object.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	virtual bool Draw() = 0;

	/**********************************************************************************************//**
	 * @fn	virtual ~IDrawTask()
	 *
	 * @brief	Destructor.
	 *
	 * @author	Kazuyuki Honda
	 **************************************************************************************************/

	virtual ~IDrawTask() {};

	/**********************************************************************************************//**
	 * @fn	const PRIORITY& GetDrawPriority(void) const
	 *
	 * @brief	Access the DrawPriority.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The draw priority.
	 **************************************************************************************************/

	const PRIORITY& GetDrawPriority(void) const
	{
		return(m_drawPriority);
	};

	/**********************************************************************************************//**
	 * @fn	void SetDrawPriority(const PRIORITY& drawPriority)
	 *
	 * @brief	Sets draw priority.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param	drawPriority	The draw priority.
	 **************************************************************************************************/

	void SetDrawPriority(const PRIORITY& drawPriority)
	{
		m_drawPriority = drawPriority;
	};
};