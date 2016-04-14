
#include "../Public/CharactorActor.h"

using namespace std;
BOOL CharactorActor::Init()
{
	if(IActor::Init())
	{
		shared_ptr<StaticMeshCompornent> staticMesh = make_shared<StaticMeshCompornent>();
		RegisterCompornent(typeid(StaticMeshCompornent).name(), staticMesh);
	}
	return true;
}

