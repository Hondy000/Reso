
#include "../Public/ComTexture2DFactory.h"
#include "../../Graphics/RenderDevice/Basic/Public/RendererManager.h"

#include "../Public/DDSTextureLoader.h"
#if DIRECTXTEX	   
#include <WICTextureLoader.h>
#include <DirectXTex.h>
#endif
#include "../../Utility/Public/StringUtility.h"

Microsoft::WRL::ComPtr<ID3D11Texture2D> ComTexture2DFactory::Create(const std::string& path)
{					
	Microsoft::WRL::ComPtr<ID3D11Texture2D> cpTexture;

	D3D11_TEXTURE2D_DESC desc;
	::ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));

	Microsoft::WRL::ComPtr<ID3D11Resource> pLoadedRes = NULL;
#ifdef DIRECTXTEX
	DirectX::TexMetadata metadata;
	DirectX::ScratchImage image;
	LoadFromWICFile(UTILITY::Widen(path).c_str(), 0, &metadata, image);
	// 画像ファイルを読み込んでテクスチャーを作成する
	DirectX::CreateTexture(sRENDER_DEVICE.Get(), image.GetImage(0,0,0), 1, metadata, pLoadedRes.GetAddressOf());


	pLoadedRes.Get()->QueryInterface(
		__uuidof(ID3D11Texture2D),
		reinterpret_cast <void**>(cpTexture.GetAddressOf())
		);
					
#endif // DIRECTXTEX
	return cpTexture;
}
