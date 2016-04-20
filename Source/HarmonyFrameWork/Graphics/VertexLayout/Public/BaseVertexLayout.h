/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\GraphicsObject\Basic\BaseVertexLayout.h
 *
 * @brief	頂点情報格納クラス.
 **************************************************************************************************/

#pragma once
#include "../../../Core/Public/Common.h"
#include <wrl\client.h>


/**********************************************************************************************//**
  * @class	BaseVertexLayout BaseVertexLayout.h
  * 			Source\HarmonyFrame\Graphics\GraphicsObject\Basic\BaseVertexLayout.h
  *
  * @brief	DirectXの入力レイアウトとかを格納するクラス.
  *
  * @author	Kazuyuki Honda
  * @date	2015/11/04
  **************************************************************************************************/

class BaseVertexLayout
{
public:
	BaseVertexLayout() {}
	virtual ~BaseVertexLayout() {}

#ifdef DIRECTX11
	Microsoft::WRL::ComPtr<ID3D11InputLayout>& GetMain()
	{
		return m_cpInputLayout;
	}
	bool BaseVertexLayout::Setup(D3D11_INPUT_ELEMENT_DESC* polygonLayout, UINT numElements, const void * vertexBuffer, SIZE_T BytecodeLength);
#endif

protected:
	//ひとまず継承などせずここに書いとく
#ifdef DIRECTX11
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_cpInputLayout;
#endif
};
