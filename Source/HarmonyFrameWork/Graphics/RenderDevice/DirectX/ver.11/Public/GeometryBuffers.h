#ifndef _DEFERREDBUFFERSCLASS_H_
#define _DEFERREDBUFFERSCLASS_H_

#define BUFFER_COUNT_MAX (7)	// BUFFERの最大数

#include "../../../../../Core/Public/Common.h"

class BaseTexture2D;
class GeometryBuffers
{
public:
	GeometryBuffers();
	GeometryBuffers(const GeometryBuffers&);
	~GeometryBuffers();

	// セットアップ
	BOOL Setup
		(
			int bufferCount,
			int textureWidth,
			int textureHeight,
			FLOAT screenDepth,
			FLOAT screenNear
			);

	// 描画するコンテキストを設定
	void SetRenderTargets(Microsoft::WRL::ComPtr<ID3D11DeviceContext>);

	void CleanUpRenderTargets();
	// コンテキストをクリア
	void ClearRenderTargets
		(
			Microsoft::WRL::ComPtr<ID3D11DeviceContext> cpContext,
			FLOAT red,
			FLOAT green,
			FLOAT blue,
			FLOAT alpha
			);

	std::shared_ptr<BaseTexture2D>& GetShaderResourceView(int);



	/*

	// Access the DepthStencilView
	const Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& GetDepthStencilView(void) const
	{
		return(m_depthStencilView);
	};*/

private:
	int m_textureWidth, m_textureHeight;   // テクスチャサイズ
	std::vector< Microsoft::WRL::ComPtr<ID3D11Texture2D>> m_renderTargetTextureArray; // レンダリングに使用するテクスチャ配列
	std::vector< Microsoft::WRL::ComPtr<ID3D11RenderTargetView> > m_renderTargetViewArray;  // 描画場所
	std::vector< std::shared_ptr<BaseTexture2D> > m_shaderResourceViewArray;
	//Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
	//Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	D3D11_VIEWPORT m_viewport;
	int m_bufferCount;	   // バッファ数
};

#endif