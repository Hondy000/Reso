#pragma once
#include "Common.h"
#include "IBaseObject.h"
#include <unordered_map>
namespace Factorys
{

	typedef size_t 	 ManufacturerID;


	interface IObjectFactory
		:
		public inheritable_enable_shared_from_this<IObjectFactory>
	{
	protected:
		IObjectFactory() {};
	public:
		virtual~IObjectFactory() {};

	};

	class FactorysManager
	{
	protected:
		FactorysManager() {};

	protected:
		static std::list<IObjectFactory*> m_pFactoryList;


	public:
		~FactorysManager() {};

		static FactorysManager* GetInstance()
		{
			static FactorysManager inst;
			return &inst;
		}

		bool Register(IObjectFactory* pObjectFactory)
		{
			m_pFactoryList.push_back(pObjectFactory);
			return true;
		}
	};


	class ObjectFactory
		:
		public IObjectFactory
	{
	protected:

		ObjectFactory()
		{

		}
	public:

		virtual ~ObjectFactory()
		{

		}
	protected:
	private:
	};

	// 外部リソースから作成するFactory
	template<class T> 
	class ExternalResourceFactory
		:
		public ObjectFactory
	{
	protected:
		ExternalResourceFactory() {};
	public:
		virtual ~ExternalResourceFactory()
		{

		}

		virtual std::shared_ptr<T> Create(const std::string& path) = 0;


	};


	// ComオブジェクトのFactory
	template<class T> 
	class IComResourceFactory
		:
		public ObjectFactory
	{
	protected:
		IComResourceFactory() {};
	public:
		virtual ~IComResourceFactory()
		{

		}


	};

};