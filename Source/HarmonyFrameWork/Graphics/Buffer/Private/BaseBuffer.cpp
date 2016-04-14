
#include "../Public/BaseBuffer.h"
#include "../../RenderDevice/Basic/Public/RendererManager.h"

#ifdef DIRECTX11
D3D11_BIND_FLAG BaseBuffer::GetD311BindFlag(BaseBuffer::BIND_FLAG flag)
{
	switch (flag)
	{
	case BIND_FLAG::VERTEX_BUFFER:
		return D3D11_BIND_VERTEX_BUFFER;
		break;
	case BIND_FLAG::INDEX_BUFFER:
		return D3D11_BIND_INDEX_BUFFER;
		break;
	case BIND_FLAG::CONSTANT_BUFFER:
		return D3D11_BIND_CONSTANT_BUFFER;
		break;
	case BIND_FLAG::OTHER:
		return D3D11_BIND_CONSTANT_BUFFER;
		break;
	default:
		return D3D11_BIND_CONSTANT_BUFFER;
		break;
	}
}

DWORD BaseBuffer::GetD311AccessFlag(BaseBuffer::ACCESS_FLAG flag)
{
	switch (flag)
	{
	case ACCESS_FLAG::WRITEONLY:
		return D3D11_CPU_ACCESS_WRITE;
		break;
	case ACCESS_FLAG::READONLY:
		return D3D11_CPU_ACCESS_READ;
		break;
	case ACCESS_FLAG::WRITEANDREAD:
		return D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		break;
	default:
		return 0;
		break;
	}
}



BOOL BaseBuffer::GetData(void* pOut, size_t)
{
	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE resource;
	hr = sRENDER_DEVICE_MANAGER->GetImmediateContext()->Map(m_cpBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	pOut = (resource.pData);

	sRENDER_DEVICE_MANAGER->GetImmediateContext()->Unmap(m_cpBuffer.Get(), 0);
	return hr;
}
#endif