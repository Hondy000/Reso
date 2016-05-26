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

class BaseRenderDeviceManager
{
public:
	BaseRenderDeviceManager();
	virtual ~BaseRenderDeviceManager() {};

	virtual bool Setup(void) = 0;

	virtual void ClearScreen(void) = 0;	// ζΚΜClear

	virtual void BeginRender(void) = 0;	   // `ζJn
	virtual void EndRender(void) = 0;	   // `ζIΉ

	// sρΜέθ
	virtual void SetTransform(
		const HFMATRIX* transform,
		HF_TRANSFORM_STATE_TYPE hftsType)
	{
		m_transformArray[hftsType] = *transform;
	};

	// ΗsρπζΎ
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

	// ΗsρπζΎ
	virtual HFVECTOR3 GetViewPosition()
	{
		return m_viewPosition;
	};
	virtual HFVECTOR2 GetScreenSize()
	{
		return m_screenSize;
	}

protected:
	std::vector<HFMATRIX> m_transformArray;
	HFVECTOR2 m_screenSize;
	HFVECTOR3 m_viewPosition;
};

#endif