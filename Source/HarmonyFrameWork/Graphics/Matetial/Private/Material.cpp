

#include "..\Public\Material.h"
#include "..\..\..\ResorceManager\Public\Texture2DManager.h"
#include "..\..\..\Utility\Public\HFString.h"

bool Material::LoadDiffuseTexture2D(HFString texturePath)
{
	std::string path = texturePath;
	m_diffuseTexture = sTEXTURE2D_MANAGER->Get(path);
	if (m_diffuseTexture)
	{
		return true;
	}
	return false;
}
