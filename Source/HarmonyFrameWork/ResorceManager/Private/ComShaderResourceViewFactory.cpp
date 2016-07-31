
#include "../Public/ComShaderResourceViewFacotry.h"
#include "../../Graphics/RenderDevice/Basic/Public/RendererManager.h"

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ComShaderResourceViewFactory::Create(Microsoft::WRL::ComPtr<ID3D11Texture2D> resource)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;

	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	resource->GetDesc(&texDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

	// V‹Kì¬
	bool res = sRENDER_DEVICE->CreateShaderResourceView(resource.Get(), &srvDesc, srv.GetAddressOf());
	return srv;
}
