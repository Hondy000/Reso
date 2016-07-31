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
	bool Read(const std::string& path, const std::shared_ptr<IActor> object);

	bool ReadState();
	bool ReadCompornent();
	bool ReadTask();
	bool ReadVar();

private:
	int m_offsetIndex;
};
