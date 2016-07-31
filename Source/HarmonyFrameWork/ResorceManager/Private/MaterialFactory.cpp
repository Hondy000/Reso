#include "../Public/MaterialFactory.h"

using namespace std;

std::shared_ptr<Material> MaterialFactory::Create(const std::string& path)
{
	return make_shared<Material>();

}
