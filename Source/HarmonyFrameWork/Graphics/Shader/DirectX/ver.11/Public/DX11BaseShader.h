#pragma once
#include "../../../Basic/Public/BaseGraphicsShader.h"
struct MeshData;

class DX11BaseShader
	:
	public BaseGraphicsShader
{
public:

	DX11BaseShader()
	{
	};

	virtual ~DX11BaseShader()
	{
	};

	// 初期化
	virtual bool Init(const BYTE* pVS,
		size_t VSSize
		, const BYTE* pPS, size_t PSSize
		);
	virtual bool Init(TCHAR pSrcFile[], TCHAR pVSMain[], TCHAR pPSMain[]);
	virtual bool Init() = 0;

	virtual bool SetupBuffer(std::shared_ptr<BaseBuffer> spOutVertexBuffer, std::shared_ptr<BaseBuffer> spOutIndexBuffer, std::shared_ptr<MeshData> spInMeshData);

	// 頂点シェーダー用の定数バッファを設定する
	virtual bool SetCBVertexShader(Microsoft::WRL::ComPtr< ID3D11DeviceContext>  pD3DDeviceContext
		, HFMATRIX* p_matWVP
		);
	// ハーフランバート用の定数バッファを設定
	bool SetCBHalfLambert(Microsoft::WRL::ComPtr< ID3D11DeviceContext>  pD3DDeviceContext
		, HFVECTOR4* p_vecLight
		, Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> pDecalMap
		);
	// フォンシェーディング用の定数バッファを設定
	bool SetCBPhongShading(Microsoft::WRL::ComPtr< ID3D11DeviceContext>  pD3DDeviceContext
		, HFVECTOR4* p_vecLight
		, HFVECTOR4* p_EyePos
		, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pDecalMap
		);
	// セルシェーディング用の定数バッファを設定
	bool SetCBCelShading(Microsoft::WRL::ComPtr< ID3D11DeviceContext> cpD3DDeviceContext
		, HFVECTOR4* p_vecLight
		, Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> cpDecalMap
		, Microsoft::WRL::ComPtr< ID3D11ShaderResourceView> cpCelMap
		);
	// 描画開始処理
	virtual bool Render();
	// 描画終了処理
	virtual bool End();

	void CreateAndRegisterGraphicsCommand(std::shared_ptr<BaseRenderMeshObject> renderObject, UINT element);
protected:
	// 動的シェーダーリンケージ( サンプルではピクセルシェーダーのみ )用の定数バッファ定義
	// この並び順はシェーダーソース内で宣言している定数バッファの並び順と同じくなるようにすること
	typedef struct _CBUFFER0
	{
		// ハーフランバート用
		HFVECTOR4 vecLight0;

		// フォンシェーディング用
		HFVECTOR4 vecLight1;
		HFVECTOR4 EyePos;

		// セルシェーディング用
		HFVECTOR4 vecLight2;
	}CBUFFER0;

	// 頂点シェーダー用の定数バッファ定義
	typedef struct _CBUFFER1
	{
		// ワールド × ビュー × 射影 行列
		HFMATRIX  matWVP;
	}CBUFFER1;

	// 入力レイアウト
	Microsoft::WRL::ComPtr< ID3D11InputLayout> m_cpLayout;

	// 定数バッファ
	Microsoft::WRL::ComPtr< ID3D11Buffer> m_cpConstantBuffers[2];

	// 頂点シェーダー
	Microsoft::WRL::ComPtr< ID3D11VertexShader> m_cpVertexShader;

	// ピクセルシェーダー
	Microsoft::WRL::ComPtr< ID3D11PixelShader> m_cpPixelShader;

	// 動的シェーダーリンク
	// ID3D11ClassLinkage
	Microsoft::WRL::ComPtr< ID3D11ClassLinkage> m_cpPSClassLinkage;

	// ピクセルシェーダーに設定時に使用するクラスインスタンス
	// ID3D11ClassInstance
	Microsoft::WRL::ComPtr< ID3D11ClassInstance> m_cpClassInstance;
	LPCSTR m_pClassInstanceName;
};
