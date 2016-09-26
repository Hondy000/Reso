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



	// �Ǘ��s����擾
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