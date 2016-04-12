/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Public\Common.h
 *
 * @brief	Declares the common class.
 **************************************************************************************************/

#pragma once

//
// Common.h
// 共通で使用するマクロや定数の定義
//
#pragma once

#include <memory>
#include <list>
#include <vector>
#include <stack>
#include <unordered_map>
#include <stdlib.h>
#include <time.h>
#include <math.h>	
#include <tchar.h>

#ifdef DIRECTX11
#include "DirectX11Common.h"
#endif
//#include "HFTypes.h"	  
#include "../../Math/Public/HFMath.h"



/**********************************************************************************************//**
 * @class	MultipleInheritableEnableSharedFromThis Common.h
 * 			Source\HarmonyFrameWork\Core\Public\Common.h
 *
 * @brief	復数のenable_shared_from_thisを可能にするための基底クラス.
 *
 * @author	Kazuyuki Honda
 **************************************************************************************************/

class MultipleInheritableEnableSharedFromThis
	:
	public std::enable_shared_from_this<MultipleInheritableEnableSharedFromThis>
{
public:
	virtual ~MultipleInheritableEnableSharedFromThis()
	{}
};

/**********************************************************************************************//**
 * @class	inheritable_enable_shared_from_this Common.h
 * 			Source\HarmonyFrameWork\Core\Public\Common.h
 *
 * @brief	An inheritable enable shared from this.
 *
 * @author	Kazuyuki Honda
 *
 * @tparam	T	Generic type parameter.
 **************************************************************************************************/

template <class T>
class inheritable_enable_shared_from_this
	:
	virtual public MultipleInheritableEnableSharedFromThis
{
public:

	/**********************************************************************************************//**
	 * @fn	std::shared_ptr<T> shared_from_this()
	 *
	 * @brief	基底クラスをダウンキャストしてTクラスのスマートポインタを得る.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @return	std::shared_ptr&lt;T&gt;
	 **************************************************************************************************/

	std::shared_ptr<T> shared_from_this()
	{
		return std::dynamic_pointer_cast<T>(MultipleInheritableEnableSharedFromThis::shared_from_this());
	}

	/**********************************************************************************************//**
	 * @fn	template <class Down> std::shared_ptr<Down> downcasted_shared_from_this()
	 *
	 * @brief	ダウンキャストで自分のスマートポインタを得る.
	 *
	 * @author	Kazuyuki Honda
	 *
	 * @tparam	Down	Type of the down.
	 *
	 * @return	A std::shared_ptr&lt;Down&gt;
	 **************************************************************************************************/

	template <class Down>
	std::shared_ptr<Down> downcasted_shared_from_this()
	{
		return std::dynamic_pointer_cast<Down>(MultipleInheritableEnableSharedFromThis::shared_from_this());
	}
};
