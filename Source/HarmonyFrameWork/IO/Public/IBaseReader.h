#pragma once
#include "../../Core/Public/Common.h"
#include "../../Core/Public/IBaseObject.h"


class IBaseReader
{
public:
	IBaseReader();
	virtual~IBaseReader();
	virtual bool ReadFileBuffer(const std::string& path);

protected:
	std::string m_buffer;
	int m_readOffsetIndex;

};

template <class T>
class BaseReader
	:
	public IBaseReader
{
public:
	BaseReader(){};
	virtual ~BaseReader(){};

	virtual bool Read(const std::string& path,const std::shared_ptr<T>& object) = 0;
protected:
#ifdef DEBUG
	std::string m_fileName;
#endif
};



