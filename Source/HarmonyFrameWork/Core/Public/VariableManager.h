#pragma once
#include "Common.h"
#include "IBaseObject.h"
#include "ManagerInterface.h"

class IVariableManager
	:
	public ObjectManager
{
public:
	IVariableManager(){};
	virtual~IVariableManager(){};

	virtual
	BOOL Create(GLOBAL_ID id, const std::string& name) = 0;

private:

};



template<class T> class VariableManager
	:
	public IVariableManager
{
public:

	typedef std::unordered_map<std::string, std::shared_ptr<Variable<T>> > VARIABLE_MAP;
	typedef std::unordered_map<GLOBAL_ID, VARIABLE_MAP> ID_MAP;
private:
	ID_MAP	  m_idMap;


public:
	VariableManager()
	{

	};
	~VariableManager()
	{

	};

	BOOL Create(GLOBAL_ID id, const std::string& name)
	{

		std::shared_ptr<Variable<T>> variablePtr = std::make_shared<Variable<T>>();
		ID_MAP::iterator idIt = m_idMap.find(id);
		if (idIt != m_idMap.end())
		{
			std::pair<std::string, std::shared_ptr<Variable<T>>> key;
			key.first = name;
			key.second = variablePtr;
			std::pair<VARIABLE_MAP::iterator, BOOL> resVarIt = idIt->second.insert(key);
			if (resVarIt.second != false)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		std::pair<GLOBAL_ID, VARIABLE_MAP> idKey;
		VARIABLE_MAP varMap;
		idKey.first = id;
		idKey.second = varMap;
		std::pair<ID_MAP::iterator, BOOL>  resIdIt = m_idMap.insert(idKey);
		if (resIdIt.second != false)
		{
			std::pair<std::string, std::shared_ptr<Variable<T>>> key;
			key.first = name;
			key.second = variablePtr;
			auto varIt = m_idMap.find(id);
			std::pair<VARIABLE_MAP::iterator, BOOL> resVarIt = varIt->second.insert(key);
			if (resVarIt.second != false)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		return false;
	};



	BOOL RegisterVariable(GLOBAL_ID id, const std::string& name ,std::shared_ptr<Variable<T>> variablePtr)
	{
		ID_MAP::iterator idIt = m_idMap.find(id);
		if (idIt != m_idMap.end())
		{
			std::pair<std::string, std::shared_ptr<Variable<T>>> key;
			key.first = name;
			key.second = variablePtr;
			std::pair<VARIABLE_MAP::iterator,BOOL> resVarIt = idIt->second.insert(key);
			if (resVarIt.second != false)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		std::pair<GLOBAL_ID, VARIABLE_MAP> idKey;
		VARIABLE_MAP varMap;
		idKey.first = id;
		idKey.second = varMap;
		std::pair<ID_MAP::iterator, BOOL>  resIdIt = m_idMap.insert(idKey);
		if(resIdIt.second != false)
		{
			std::pair<std::string, std::shared_ptr<Variable<T>>> key;
			key.first = name;
			key.second = variablePtr;
			auto varIt = m_idMap.find(id);
			std::pair<VARIABLE_MAP::iterator, BOOL> resVarIt = varIt->second.insert(key);
			if(resVarIt.second != false)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		return false;
	}


	std::shared_ptr<Variable<T>> GetVariable(GLOBAL_ID id, const std::string& name)
	{
		auto idIt = m_idMap.find(id);
		if(idIt != m_idMap.end())
		{

			VARIABLE_MAP::iterator variableIt = idIt->second.find(name);
			if (variableIt != idIt->second.end())
			{
				return variableIt->second;
			}
		}
		return nullptr;
	}
	
};


class VariableManagersManager
	:
	public ObjectManager

{
public:
	VariableManagersManager() {};
	~VariableManagersManager() {};


	static VariableManagersManager* GetInstance()
	{
		static VariableManagersManager instance;
		return &instance;
	};

	template<class T> BOOL CreateManager()
	{
		std::shared_ptr<VariableManager<T>> manager = std::make_shared<VariableManager<T>>();

		auto res = m_variableManagersMap.insert(std::make_pair<std::string, std::shared_ptr<IVariableManager>>(typeid(T).name(), manager));
		return res->second;

	};


	BOOL CreateVariable(GLOBAL_ID id,const std::string& name,const std::string& typeName)
	{

		auto findRes = m_variableManagersMap.find(typeName);
		if (findRes != m_variableManagersMap.end())
		{
			findRes->second->Create(id, name);
		}
		return true;

	};

	template<class T> BOOL RegsigterVariable(GLOBAL_ID id, std::string variableName, std::shared_ptr<Variable<T>> var)
	{


			return GetVariableManager<T>()->RegisterVariable(id, variableName, var);
		;

	};

	template<class T> BOOL RegsigterVariable(GLOBAL_ID id, std::string variableName, std::shared_ptr<T> constant)
	{

		std::shared_ptr<Variable<T>> wrapVar = std::make_shared<Variable<T>>();

		wrapVar->SetValue(constant);


		return GetVariableManager<T>()->RegisterVariable(id, variableName, wrapVar);
		;

	};

	template<class T> BOOL RegsigterVariable(GLOBAL_ID id, std::string variableName, const T& var)
	{

		std::shared_ptr<Variable<T>> wrapVar = std::make_shared<Variable<T>>();
		
		std::shared_ptr<T> constant = make_shared<T>();
		*constant = var;
		wrapVar->SetValue(constant);
		return GetVariableManager<T>()->RegisterVariable(id, variableName, wrapVar);

		;

	};

	BOOL RegsigterFloatVariable(GLOBAL_ID id, std::string variableName)
	{

		std::shared_ptr<Variable< FLOAT>> wrapVar = std::make_shared<Variable<FLOAT>>();

		std::shared_ptr<FLOAT> constant = std::make_shared<FLOAT>();
		*constant = 0.0f;
		wrapVar->SetValue(constant);
		return GetVariableManager<FLOAT>()->RegisterVariable(id, variableName, wrapVar);
		;
	};

	BOOL RegsigterDoubleFloatVariable(GLOBAL_ID id, std::string variableName)
	{

		std::shared_ptr<Variable< DOUBLE>> wrapVar = std::make_shared<Variable<DOUBLE>>();

		std::shared_ptr<DOUBLE> constant = std::make_shared<DOUBLE>();
		*constant = 0.0;
		wrapVar->SetValue(constant);
		return  GetVariableManager<DOUBLE>()->RegisterVariable(id, variableName, wrapVar);
		;
	};


	template<typename T>
	std::shared_ptr<VariableManager<T>> GetVariableManager()
	{
		auto res = m_variableManagersMap.find(typeid(T).name());
		if(res != m_variableManagersMap.end())
		{
			return std::dynamic_pointer_cast<VariableManager<T>>(res->second);
		}
		else
		{
			std::shared_ptr<VariableManager<T>> manager = std::make_shared<VariableManager<T>>();

			std::pair<std::string, std::shared_ptr<IVariableManager>> key;
			key.first = std::string(typeid(T).name());
			key.second = manager;
			
			auto res = m_variableManagersMap.insert(key);


			return manager;
		}
	}

	template<class T>
	std::shared_ptr<Variable<T>> GetVariable(GLOBAL_ID id, std::string variableName)
	{

		auto it = m_variableManagersMap.find(typeid(T).name());
		if (it != m_variableManagersMap.end())
		{
			if (std::dynamic_pointer_cast<VariableManager<T>>(it->second))
			{
				return std::dynamic_pointer_cast<VariableManager<T>>(it->second)->GetVariable(id, variableName);
			}
			
		}

		return nullptr;

	};

	template<class T>
	BOOL EraseVariable(GLOBAL_ID id, std::string variableName, Variable<T>)
	{
		HRESULT hr = E_FAIL;

		return hr;

	};



private:
	std::unordered_map<std::string, std::shared_ptr<IVariableManager>> m_variableManagersMap;
};
