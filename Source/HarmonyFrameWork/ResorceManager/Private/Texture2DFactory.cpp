#include "../Public/Texture2DFactory.h"
#include "../../Graphics/Texture/Public/BaseTexture2D.h"
#include "../../Graphics/RenderDevice/Basic/Public/RendererManager.h"
#include "../../Graphics/Texture/Public/DX11ShaderResourceView.h"
#include "../Public/ComTexture2DFactory.h"
#include "../Public/ComShaderResourceViewFacotry.h"

using namespace std;
using namespace Microsoft::WRL;

Texture2DFactory::~Texture2DFactory()
{

}

Texture2DFactory::Texture2DFactory()
{

}

std::shared_ptr<BaseTexture2D> Texture2DFactory::Create(const std::string& path)
{
	std::shared_ptr<BaseTexture2D> texture = std::make_shared<BaseTexture2D>();


#ifdef DIRECTX11

	if (texture)
	{
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> cpSRV = texture->GetSharderResorceView();

		texture->SetCpTexture(ComTexture2DFactory::GetInstance()->Create(path));
		cpSRV = ComShaderResourceViewFactory::GetInstance()->Create(texture->GetCpTexture());
		texture->SetSharderResorceView(cpSRV);

		texture->SetName(path);
	}
#endif

	return texture;
}
