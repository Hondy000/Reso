#include "../Public/BaseVertexLayout.h"
#include "../../RenderDevice/Basic/Public/RendererManager.h"

bool BaseVertexLayout::Setup(D3D11_INPUT_ELEMENT_DESC* polygonLayout,UINT numElements, const void * shaderPtr, SIZE_T BytecodeLength)
{

	bool result = sRENDER_DEVICE->CreateInputLayout(polygonLayout, numElements, shaderPtr, BytecodeLength,
		GetMain().GetAddressOf());
	return result;
}
