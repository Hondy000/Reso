/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Graphics\Buffer\Private\IndexBuffer.cpp
 *
 * @brief	Implements the index buffer class.
 **************************************************************************************************/

#include "../Public/IndexBuffer.h"
#include "../../RenderDevice/Basic/Public/RendererManager.h"

/**********************************************************************************************//**
 * @fn	bool IndexBuffer::SetData(void* pIn, size_t dataSize, int count, ACCESS_FLAG access_flag)
 *
 * @brief	Sets a data.
 *
 * @author	Kazuyuki Honda
 *
 * @param [in,out]	pIn	If non-null, the in.
 * @param	dataSize   	Size of the data.
 * @param	count	   	Number of.
 * @param	access_flag	The access flag.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool IndexBuffer::SetData(void* pIn, size_t dataSize, int count, ACCESS_FLAG access_flag)
{
	m_accessFlag = access_flag;
	m_dataCount = count;
	return sRENDER_DEVICE_MANAGER->CreateBuffer
		(
			m_cpBuffer,
			pIn,
			dataSize * count,
			GetD311AccessFlag(access_flag),
			GetD311BindFlag(BaseBuffer::BIND_FLAG::INDEX_BUFFER)
			);
}
