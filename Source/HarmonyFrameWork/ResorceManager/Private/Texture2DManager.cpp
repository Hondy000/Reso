#include "../Public/Texture2DManager.h"

std::shared_ptr<BaseTexture2D> Texture2DManager::RequestCreate(const std::string& path)
{
	std::shared_ptr<BaseTexture2D> texture = Texture2DFactory::GetInstance()->Create(path);
	if (texture)
	{
		return texture;
	}
	return Texture2DFactory::GetInstance()->Create("Resource/Texture/DefaultWhite.png");
}
