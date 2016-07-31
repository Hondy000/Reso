#pragma once
#include "Common.h"
#include "IBaseObject.h"
#include <unordered_map>


class IBaseTypeBuilder
{
public:
	IBaseTypeBuilder(){};
	virtual~IBaseTypeBuilder(){};

	virtual std::shared_ptr<IBaseObject> Create() = 0;
private:

};

// å^ê∂ê¨ÉNÉâÉX
template<class T> 
class TypeBuilder
	:
	public IBaseTypeBuilder
{
public:
	TypeBuilder() {};
	~TypeBuilder() {};
	std::shared_ptr<IBaseObject> Create()
	{
		return std::shared_ptr<T>(new T);
		
	};
};
#define REGISTER_TYPE(TYPE) typeid(TYPE).name(),std::shared_ptr<TypeBuilder<TYPE>>(new TypeBuilder<TYPE>)

class ReflectionSystem 
{
private:
	ReflectionSystem() {};
public:
	~ReflectionSystem()
	{

	}
	static ReflectionSystem* GetInstance()
	{
		static ReflectionSystem instance;
		return &instance;
	}
	void Register(const std::string& ty_name, std::shared_ptr<IBaseTypeBuilder> builder)
	{
		m_builderMap.insert(std::make_pair(ty_name, builder));
	}
	std::shared_ptr<IBaseObject> Create(const std::string& ty_name) 
	{
		std::unordered_map<std::string, std::shared_ptr<IBaseTypeBuilder>>::iterator itr = m_builderMap.find(ty_name);
		if (itr == m_builderMap.end())
		{
			return 0;
		}
		return (*itr).second->Create();
	}

	void Remove(const std::string& typeName);

private:
	std::unordered_map<std::string, std::shared_ptr<IBaseTypeBuilder >>	m_builderMap;
};
