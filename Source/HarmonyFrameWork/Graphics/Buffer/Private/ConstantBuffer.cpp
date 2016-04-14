
#include "../Public/ConstantBuffer.h"
#include "../../RenderDevice/Basic/Public/RendererManager.h"

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
}


BOOL ConstantBuffer::SetData(void* pIn, size_t dataSize, int count, ACCESS_FLAG access_flag)
{
	m_accessFlag = access_flag;
	return sRENDER_DEVICE_MANAGER->CreateBuffer
		(
			m_cpBuffer,
			pIn,
			dataSize * count,
			GetD311AccessFlag(access_flag),
			GetD311BindFlag(BaseBuffer::BIND_FLAG::CONSTANT_BUFFER)
			);
}
