/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Graphics\Buffer\Private\VertexBuffer.cpp
 *
 * @brief	Implements the vertex buffer class.
 **************************************************************************************************/

#include "../Public/VertexBuffer.h"
#include "../../RenderDevice/Basic/Public/RendererManager.h"

/**********************************************************************************************//**
 * @fn	VertexBuffer::VertexBuffer()
 *
 * @brief	Default constructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

VertexBuffer::VertexBuffer()
{
}

/**********************************************************************************************//**
 * @fn	VertexBuffer::~VertexBuffer()
 *
 * @brief	Destructor.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

VertexBuffer::~VertexBuffer()
{
}

/**********************************************************************************************//**
 * @fn	bool VertexBuffer::SetData(void* pIn, size_t dataSize, int count, ACCESS_FLAG access_flag)
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

bool VertexBuffer::SetData(void* pIn, size_t dataSize, int count, ACCESS_FLAG access_flag)
{
	m_accessFlag = access_flag;
	return sRENDER_DEVICE_MANAGER->CreateBuffer
		(
			m_cpBuffer,
			pIn,
			dataSize * count,
			GetD311AccessFlag(access_flag),
			GetD311BindFlag(BaseBuffer::BIND_FLAG::VERTEX_BUFFER)
			);
}
