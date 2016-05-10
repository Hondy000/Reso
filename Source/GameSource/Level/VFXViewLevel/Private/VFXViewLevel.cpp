#include "../Public/VFXViewLevel.h"
#include "../Public/VFXViewLevelStates.h"
using namespace std;

bool VFXViewLevel::Init()
{
	RegisterState(make_shared<VFXViewMainState>(), shared_from_this());
	return true;
}

/**=================================================================================================
 * @fn bool VFXViewLevel::Update()
 *
 * @brief Updates this object.
 *
 * @author Kazuyuki
 *
 * @return true if it succeeds, false if it fails.
 *===============================================================================================**/

bool VFXViewLevel::Update()
{
	UpdateState(shared_from_this());
	return false;
}
void VFXViewLevel::Reset()
{
	Init();
}
