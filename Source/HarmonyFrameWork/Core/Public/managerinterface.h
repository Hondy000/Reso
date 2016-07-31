#pragma once
#include "Common.h"
#include <unordered_map>


class IObjectManager
	:
	public inheritable_enable_shared_from_this<IObjectManager>
{
public:
	IObjectManager() {};
	virtual~IObjectManager() {};

};


class ObjectManagersManager
{
protected:
	ObjectManagersManager() {};

protected:
	static std::list<IObjectManager*> m_pManagerList;


public:
	~ObjectManagersManager() {};

	static ObjectManagersManager& GetInstance()
	{
		static ObjectManagersManager inst;
		return inst;
	}

	bool Register(IObjectManager* pObjectFactory)
	{
		m_pManagerList.push_back(pObjectFactory);
		return true;
	}
};


class ObjectManager
	:
	public IObjectManager
{
public:
	ObjectManager()
	{
		ObjectManagersManager::GetInstance().Register(this);
	}
protected:
private:
};


template<class T> class GeneralResourceManager
	:
	public ObjectManager
{
protected:
	typedef std::pair<size_t, std::shared_ptr<T>> ResourcePair;
	typedef std::unordered_map<size_t, std::shared_ptr<T>> ResourceMap;
	std::unordered_map<size_t, std::shared_ptr<T>> m_resourceMap;
	GeneralResourceManager() {};
public:
	virtual~GeneralResourceManager()
	{

	}

	virtual bool Register(const std::string& path, std::shared_ptr<T> object)
	{

		ResourcePair resorcePair;
		std::hash<std::string> hash;
		resorcePair.first = hash(path);
		resorcePair.second = object;

		auto it = m_resourceMap.insert(resorcePair);

		return true;
	};

	virtual std::shared_ptr<T> Get(const std::string& path)
	{

		std::hash<std::string> hash;
		auto it = m_resourceMap.find(hash(path));
		if (it != m_resourceMap.end())
		{
			// 内部情報の複製
			return (it->second);
		}
		else 
		{
			std::shared_ptr<T> object;
			object = RequestCreate(path);
			ResourcePair resoursePair;
			resoursePair.first = hash(path);
			resoursePair.second = object;
			m_resourceMap.insert(resoursePair);
			return object;
		}
	};
private:
	virtual std::shared_ptr<T> RequestCreate(const std::string& path) = 0;

};

