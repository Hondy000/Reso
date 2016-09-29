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

	std::shared_ptr<BaseDepthStencilBuffer> GetDefaultDepthStencil(void);
	
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
	virtual void SetMainRenderTarget(std::shared_ptr<BaseRenderTarget> _renderTarget);

	/***************************************************************************************************//*
	 * @fn	std::shared_ptr<BaseDepthStencilBuffer> BaseRenderDeviceManager::GetMainDepthStencil(void);
	 *
	 * @brief	Gets main depth stencil.
	 *
	 * @author	Hondy
	 * @date	2016/09/27
	 *
	 * @return	The main depth stencil.
	 *****************************************************************************************************/
	std::shared_ptr<BaseDepthStencilBuffer> GetMainUseDepthStencil(void);

	/***************************************************************************************************//*
	 * @fn	void BaseRenderDeviceManager::SetMainDepthStencil(std::shared_ptr<BaseDepthStencilBuffer> _depthStencil);
	 *
	 * @brief	Sets main depth stencil.
	 *
	 * @author	Hondy
	 * @date	2016/09/27
	 *
	 * @param	_depthStencil	The depth stencil.
	 *****************************************************************************************************/
	virtual void SetMainUseDepthStencil(std::shared_ptr<BaseDepthStencilBuffer> _depthStencil);

	/***************************************************************************************************//*
	 * @fn	virtual HFVECTOR3 BaseRenderDeviceManager::GetViewPosition()
	 *
	 * @brief	管理行列を取得.
	 *
	 * @author	Hondy
	 * @date	2016/09/27
	 *
	 * @return	The view position.
	 *****************************************************************************************************/
	virtual HFVECTOR3 GetViewPosition()
	{
		return m_viewPosition;
	};

	/***************************************************************************************************//*
	 * @fn	virtual HFVECTOR2 BaseRenderDeviceManager::GetScreenSize()
	 *
	 * @brief	Gets screen size.
	 *
	 * @author	Hondy
	 * @date	2016/09/27
	 *
	 * @return	The screen size.
	 *****************************************************************************************************/
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
	/** @brief	Buffer for depth data. */
	std::shared_ptr<BaseDepthStencilBuffer> m_defaultDepthStencilBuffer;
	/** @brief	Buffer for depth data. */
	std::shared_ptr<BaseDepthStencilBuffer> m_usingDepthStencilBuffer;
	/** @brief	The render target. */
	std::shared_ptr<BaseRenderTarget> m_defaultRenderTarget;
	/** @brief	The render target. */
	std::shared_ptr<BaseRenderTarget> m_usingRenderTarget;
};

#endif