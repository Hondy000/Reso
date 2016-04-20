////////////////////////////////////////////////////////////////////////////////
// Filename: LightShaderOfDeferredRender.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _LightShader_H_
#define _LightShader_H_

#include "../../../Basic/Public/BaseShader.h"
#include "../../../../Lighting/Public/LightTypes.h"
#include "../../../../RenderDevice/DirectX/ver.11/Public/GeometryBuffers.h"

class BaseTexture2D;
struct MeshData;

////////////////////////////////////////////////////////////////////////////////
// Class name: LightShaderOfDeferredRender
////////////////////////////////////////////////////////////////////////////////
class LightShaderOfDeferredRender
	:
	public BaseShader
{
public:

private:
	struct MatrixBufferType
	{
		HFMATRIX WVP;
	};

	struct LightBufferType
	{
		HFVECTOR3 lightDirection;
		FLOAT padding;
	};

	// 動的シェーダーリンケージ( サンプルではピクセルシェーダーのみ )用の定数バッファ定義
	// この並び順はシェーダーソース内で宣言している定数バッファの並び順と同じくなるようにすること
	typedef struct CBUFFER0
	{
		// シンプル用
		HFVECTOR3 lightDirection0;
		FLOAT padding0;	  // 16バイト アライメント用

		 // アルベド
		HFVECTOR4 lightDirection1;
		// position
		HFVECTOR4 lightDirection2;

		// Normal用
		HFVECTOR4 lightDirection3;

		// ポイントライティングテスト用
		HFVECTOR4 lightDirection4;
		HFGraphics::POINT_LIGHT_PRAM pointLight0;

		// スポットライティングテスト用
		HFVECTOR4 lightDirection5;
		HFGraphics::SPOT_LIGHT_PRAM spotLight0;

		//
		HFVECTOR4 lightDirection;
		HFGraphics::POINT_LIGHT_PRAM pointLightArray[64];
		HFGraphics::SPOT_LIGHT_PRAM spotLightArray[64];
	}CBUFFER0;

public:
	LightShaderOfDeferredRender();
	LightShaderOfDeferredRender(const LightShaderOfDeferredRender&);
	~LightShaderOfDeferredRender();

	bool Setup();
	void Destroy();

	bool PreProcessOfRender(std::shared_ptr<SubMesh> shape, std::shared_ptr<Material>materials);

	bool Render();

	bool PostProcessOfRender();

	void SetGeometryBuffers(const std::shared_ptr<GeometryBuffers>& buffers)
	{
		m_spDefferBuffers = buffers;
	}
	const std::shared_ptr<GeometryBuffers>& GetGeometryBuffers(void) const
	{
		return m_spDefferBuffers;
	}

private:
	bool InitializeShader(TCHAR*, TCHAR*);

	bool SetShaderParameters(
		HFMATRIX,
		HFMATRIX,
		HFMATRIX,
		HFVECTOR3);

private:

	std::shared_ptr<GeometryBuffers> m_spDefferBuffers;
	int indexCount;
};

#endif