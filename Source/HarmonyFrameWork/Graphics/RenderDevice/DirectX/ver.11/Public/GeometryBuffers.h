#ifndef _DEFERREDBUFFERSCLASS_H_
#define _DEFERREDBUFFERSCLASS_H_

#define BUFFER_COUNT_MAX (7)	// BUFFER�̍ő吔

#include "../../../../../Core/Public/Common.h"

class BaseTexture2D;
class GeometryBuffers
{
public:
	GeometryBuffers();
	GeometryBuffers(const GeometryBuffers&);
	~GeometryBuffers();

	// �Z�b�g�A�b�v
	BOOL Setup
		(
			int bufferCount,
			int textureWidth,
			int textureHeight,
			FLOAT screenDepth,
			FLOAT screenNear
			);

	// �`�悷��R���e�L�X�g��ݒ�
	void SetRenderTargets(Microsoft::WRL::ComPtr<ID3D11DeviceContext>);

	void CleanUpRenderTargets();
	// �R���e�L�X�g���N���A
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
	int m_textureWidth, m_textureHeight;   // �e�N�X�`���T�C�Y
	std::vector< Microsoft::WRL::ComPtr<ID3D11Texture2D>> m_renderTargetTextureArray; // �����_�����O�Ɏg�p����e�N�X�`���z��
	std::vector< Microsoft::WRL::ComPtr<ID3D11RenderTargetView> > m_renderTargetViewArray;  // �`��ꏊ
	std::vector< std::shared_ptr<BaseTexture2D> > m_shaderResourceViewArray;
	//Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
	//Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	D3D11_VIEWPORT m_viewport;
	int m_bufferCount;	   // �o�b�t�@��
};

#endif