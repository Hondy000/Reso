/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Task\Public\TaskInterface.h
 *
 * @brief	Declares the task interface class.
 **************************************************************************************************/

#pragma once
#include "../../Public/IBaseObject.h"
#include "../../Public/VariableManager.h"	
#include "..\..\..\Math\Public\Transform.h"

/**=================================================================================================
 * @def GET_TASK_VAR_PTR(spTask,typeName,varName) (spTask->GetVariable<typeName>(varName)-
 * >GetValue())
 *
 * @brief A macro that defines get task variable pointer.
 *
 * @author Kazuyuki
 *
 * @param spTask   The sp task.
 * @param typeName Name of the type.
 * @param varName  Name of the variable.
 *===============================================================================================**/

#define GET_TASK_VAR_PTR(spTask,typeName,varName)  (spTask->GetVariable<typeName>(varName)->GetValue())

/**=================================================================================================
 * @def GET_TASK_VAR(spTask,typeName,varName) (*(spTask->GetVariable<typeName>(varName)-
 * >GetValue()))
 *
 * @brief A macro that defines get task variable.
 *
 * @author Kazuyuki
 *
 * @param spTask   The sp task.
 * @param typeName Name of the type.
 * @param varName  Name of the variable.
 *===============================================================================================**/

#define GET_TASK_VAR(spTask,typeName,varName)  (*(spTask->GetVariable<typeName>(varName)->GetValue()))

/**=================================================================================================
 * @class IBaseTask TaskInterface.h Source\HarmonyFrameWork\Core\Task\Public\TaskInterface.h
 *
 * @brief A base task.
 *
 * @author Kazuyuki
 *
 * @sa IBaseObject
 *===============================================================================================**/

class IBaseTask
	:
	virtual public IBaseObject
{
public:

	/**=================================================================================================
	 * @typedef size_t PRIORITY
	 *
	 * @brief Defines an alias representing the priority.
	 *===============================================================================================**/

	typedef size_t PRIORITY;



protected:


	IBaseTask()
		:

		/**=================================================================================================
		 * @fn m_isUsage(true),m_isDestroy(false)
		 *
		 * @brief Initializes a new instance of the TaskInterface class.
		 *
		 * @author Kazuyuki
		 *
		 * @param parameter1 The first parameter.
		 *===============================================================================================**/

		m_isUsage(true),m_isDestroy(false)
	{
		Init();
	};

	/** @brief true if this object is usage. */

	bool m_isUsage; 

	/** @brief true if this object is destroy. */

	bool m_isDestroy; 

	/** @brief The update priority. */

	PRIORITY m_updatePriority;  

	/** @brief Identifier for the task. */

	unsigned long m_taskId;

	/** @brief The name. */

	std::string m_name; 

	/** @brief The variable map. */

	std::unordered_map<std::string, std::shared_ptr<IVariable>> m_varMap;  

	/** @brief The child task list. */
	
	std::list<std::shared_ptr<IBaseTask>>m_childTaskList;

public:

	/**=================================================================================================
	 * @fn virtual ~IBaseTask();
	 *
	 * @brief Finalizes an instance of the TaskInterface class.
	 *
	 * @author Kazuyuki
	 *===============================================================================================**/

	virtual ~IBaseTask();

	/**=================================================================================================
	 * @fn bool Init();
	 *
	 * @brief Initialises this object.
	 *
	 * @author Kazuyuki
	 *
	 * @return true if it succeeds, false if it fails.
	 *===============================================================================================**/

	bool Init();

	/**=================================================================================================
	 * @fn virtual bool Update() = 0;
	 *
	 * @brief Updates this object.
	 *
	 * @author Kazuyuki
	 *
	 * @return true if it succeeds, false if it fails.
	 *===============================================================================================**/

	virtual bool Update() = 0;

	/**=================================================================================================
	 * @fn void UpdateChildTask();
	 *
	 * @brief Updates the child task.
	 *
	 * @author Kazuyuki
	 *===============================================================================================**/

	void UpdateChildTask();

	/**=================================================================================================
	 * @fn virtual void Reset() = 0;
	 *
	 * @brief Resets this object.
	 *
	 * @author Kazuyuki
	 *===============================================================================================**/

	virtual void Reset() = 0;

	/**=================================================================================================
	 * @fn virtual bool LoadTaskData(const std::string& path);
	 *
	 * @brief Loads task data.
	 *
	 * @author Kazuyuki
	 *
	 * @param path Full pathname of the file.
	 *
	 * @return true if it succeeds, false if it fails.
	 *===============================================================================================**/

	virtual bool LoadTaskData(const std::string& path);

	/**=================================================================================================
	 * @fn bool CheckUsageFlag();
	 *
	 * @brief Determines if we can check usage flag.
	 *
	 * @author Kazuyuki
	 *
	 * @return true if it succeeds, false if it fails.
	 *===============================================================================================**/

	bool CheckUsageFlag();

	/**=================================================================================================
	 * @fn bool CheckDestroy();
	 *
	 * @brief Determines if we can check destroy.
	 *
	 * @author Kazuyuki
	 *
	 * @return true if it succeeds, false if it fails.
	 *===============================================================================================**/

	bool CheckDestroy();

	/**=================================================================================================
	 * @fn virtual bool AllowUpdate();
	 *
	 * @brief Determine if we allow update.
	 *
	 * @author Kazuyuki
	 *
	 * @return true if we allow update, false if not.
	 *===============================================================================================**/

	virtual bool AllowUpdate();

	/**=================================================================================================
	 * @fn const PRIORITY& GetUpdatePriority(void) const;
	 *
	 * @brief Gets update priority.
	 *
	 * @author Kazuyuki
	 *
	 * @return The update priority.
	 *===============================================================================================**/

	const PRIORITY& GetUpdatePriority(void) const;

	/**=================================================================================================
	 * @fn void SetUpdatePriority(const PRIORITY& priority);
	 *
	 * @brief Sets update priority.
	 *
	 * @author Kazuyuki
	 *
	 * @param priority The priority.
	 *===============================================================================================**/

	void SetUpdatePriority(const PRIORITY& priority);

	/**=================================================================================================
	 * @fn const unsigned long& GetTaskId(void) const;
	 *
	 * @brief Gets task identifier.
	 *
	 * @author Kazuyuki
	 *
	 * @return The task identifier.
	 *===============================================================================================**/

	const unsigned long& GetTaskId(void) const;

	/**=================================================================================================
	 * @fn void SetTaskId(const unsigned long& taskId);
	 *
	 * @brief Sets task identifier.
	 *
	 * @author Kazuyuki
	 *
	 * @param taskId Identifier for the task.
	 *===============================================================================================**/

	void SetTaskId(const unsigned long& taskId);


	bool GetIsDestroy() const;

	void SetIsDestroy(bool _val);


	/**********************************************************************************************//**
	 * @fn	const std::string& GetTaskName(void)const
	 *
	 * @brief	Gets task name.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	The task name.
	 **************************************************************************************************/

	const std::string& GetTaskName(void)const;

	/**********************************************************************************************//**
	 * @fn	void SetTaskName(const std::string& name)
	 *
	 * @brief	Sets task name.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @param	name	The name.
	 **************************************************************************************************/

	void SetTaskName(const std::string& name);

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
	 * @brief	shared_ptr&lt;T&gt;ÇTå^VariableÇ∆ÇµÇƒÉ^ÉXÉNì‡Ç…ìoò^.
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
	 * @brief	Tå^Ç©ÇÁîhê∂ÇµÇΩVå^É|ÉCÉìÉ^ÇÉ^ÉXÉNÇ…ìoò^.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @tparam	T	Generic type parameter.
	 * @tparam	V	Generic type parameter.
	 * @param	variableName			Name of the variable.
	 * @param	spDerivationVariable	îhê∂É|ÉCÉìÉ^.
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
	 * @brief	Tå^ÉXÉ}Å[ÉgÉ|ÉCÉìÉ^ÇÉ^ÉXÉNÇ…ìoò^.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @tparam	T	Generic type parameter.
	 * @param	variableName	Name of the variable.
	 * @param	spVariable  	Tå^ÉXÉ}Å[ÉgÉ|ÉCÉìÉ^.
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
	 * @brief	Tå^ÇÃïœêîÇÉ^ÉXÉNÇ…ìoò^.
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

