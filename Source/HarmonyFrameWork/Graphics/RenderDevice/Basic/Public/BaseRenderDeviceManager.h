#pragma once
#define _INCLUDE_BASE_RENDER_DEVICE_HEADER

#ifdef _INCLUDE_BASE_RENDER_DEVICE_HEADER
#include "../../../../Core/Public/Common.h"

enum HF_TRANSFORM_STATE_TYPE
{
	HFTS_VIEW,
	HFTS_PERSPECTIVE,
	HFTS_ORTHOGONAL,
	HFTS_WORLD,
	HFTS_MAX
};

typedef struct BASE_DEVICE_INITIALIZE_OPERATION
{
}BaseDevInitOP;

// 依存クラス
class BaseRenderTarget;
class BaseDepthStencilBuffer;

class BaseRenderDeviceManager
{
public:
	BaseRenderDeviceManager();
	virtual ~BaseRenderDeviceManager() {};

	virtual bool Setup(void) = 0;

	virtual void ClearScreen(void) = 0;	// 画面のClear

	virtual void BeginRender(void) = 0;	   // 描画開始
	virtual void EndRender(void) = 0;	   // 描画終了

	// 行列の設定
	virtual void SetTransform(
		const HFMATRIX* transform,
		HF_TRANSFORM_STATE_TYPE hftsType)
	{
		m_transformArray[hftsType] = *transform;
	};

	// 管理行列を取得
	virtual HFMATRIX* GetTransform(
		HFMATRIX* transform,
		HF_TRANSFORM_STATE_TYPE hftsType)
	{
		*transform = m_transformArray[hftsType];
		return transform;
	};


	virtual void SetViewPosition(
		const HFVECTOR3	 val
		)
	{
		m_viewPosition = val;
	};
	/**********************************************************************************************//**
	 * @fn std::shared_ptr<BaseRenderTarget> BaseRenderDeviceManager::GetDefaultRenderTarget(void);
	 *
	 * @brief デフォルトで使用されるレンダーターゲットを取得.
	 *
	 * @author Kazuyuki
	 *
	 * @return デフォルトのレンダーターゲット.
	 **************************************************************************************************/
	std::shared_ptr<BaseRenderTarget> GetDefaultRenderTarget(void);	   
	
	/**********************************************************************************************//**
	 * @fn std::shared_ptr<BaseRenderTarget> BaseRenderDeviceManager::GetMainRenderTarget(void);
	 *
	 * @brief Gets main render target.
	 *
	 * @author Kazuyuki
	 *
	 * @return The main render target.
	 **************************************************************************************************/
	std::shared_ptr<BaseRenderTarget> GetMainRenderTarget(void);

	/***********************************************************************************************
	 * Sets main render target.
	 *
	 * @author Kazuyuki
	 *
	 * @param _renderTarget The render target.
	 *************************************************************************************************/
	void SetMainRenderTarget(std::shared_ptr<BaseRenderTarget> _renderTarget);

	std::shared_ptr<BaseDepthStencilBuffer> GetMainDepthStencil(void);
	void SetMainDepthStencil(std::shared_ptr<BaseDepthStencilBuffer> _depthStencil);



	// 管理行列を取得
	virtual HFVECTOR3 GetViewPosition()
	{
		return m_viewPosition;
	};
	virtual HFVECTOR2 GetScreenSize()
	{
		return m_screenSize;
	}

protected:
	/** Array of transforms. */
	std::vector<HFMATRIX> m_transformArray;
	/** Size of the screen. */
	HFVECTOR2 m_screenSize;
	/** The view position. */
	HFVECTOR3 m_viewPosition;
	std::shared_ptr<BaseDepthStencilBuffer> m_depthBuffer;
	std::shared_ptr<BaseRenderTarget> m_renderTarget;
};

#endif