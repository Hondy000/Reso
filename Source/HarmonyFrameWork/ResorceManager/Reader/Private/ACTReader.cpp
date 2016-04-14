
#include "../Public/ACTReader.h"

BOOL ACTReader::Read(const std::string& path, const std::shared_ptr<IActor> object)
{
	ReadFileBuffer(path);
	return E_FAIL;
}
