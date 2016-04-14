
#include "../Public/IndexBuffer.h"
#include "../../RenderDevice/Basic/Public/RendererManager.h"

BOOL IndexBuffer::SetData(void* pIn, size_t dataSize, int count, ACCESS_FLAG access_flag)
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
