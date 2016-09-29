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

// �ˑ��N���X
class BaseRenderTarget;
class BaseDepthStencilBuffer;

class BaseRenderDeviceManager
{
public:
	BaseRenderDeviceManager();
	virtual ~BaseRenderDeviceManager() {};

	virtual bool Setup(void) = 0;

	virtual void ClearScreen(void) = 0;	// ��ʂ�Clear

	virtual void BeginRender(void) = 0;	   // �`��J�n
	virtual void EndRender(void) = 0;	   // �`��I��

	// �s��̐ݒ�
	virtual void SetTransform(
		const HFMATRIX* transform,
		HF_TRANSFORM_STATE_TYPE hftsType)
	{
		m_transformArray[hftsType] = *transform;
	};

	// �Ǘ��s����擾
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
	 * @brief �f�t�H���g�Ŏg�p����郌���_�[�^�[�Q�b�g���擾.
	 *
	 * @author Kazuyuki
	 *
	 * @return �f�t�H���g�̃����_�[�^�[�Q�b�g.
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
	 * @brief	�Ǘ��s����擾.
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