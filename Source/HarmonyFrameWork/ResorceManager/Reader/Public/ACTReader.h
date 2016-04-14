#pragma once
#include "../../../Core/Actor/Public/ActorInterface.h"
#include "../../../IO/Public/IBaseReader.h"

class ACTReader :
	public BaseReader<IActor>
{
public:
	ACTReader()
	{
	};

	~ACTReader()
	{
	};
	BOOL Read(const std::string& path, const std::shared_ptr<IActor> object);

	BOOL ReadState();
	BOOL ReadCompornent();
	BOOL ReadTask();
	BOOL ReadVar();

private:
	int m_offsetIndex;
};
