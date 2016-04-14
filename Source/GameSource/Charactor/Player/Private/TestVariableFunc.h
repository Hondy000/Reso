/**********************************************************************************************//**
 * @file	Source\GameSource\Charactor\Player\Private\TestVariableFunc.h
 *
 * @brief	Variable同士のの演算 他のすまーとな方法もあるかもしれないが取り敢えず物量で行う.
 **************************************************************************************************/

#pragma once
#include "../../../../HarmonyFrameWork/Core/Public/VariableInterface.h"

using namespace std;

/**********************************************************************************************//**
 * @enum	VariableType
 *
 * @brief	基本のデータ型の分類(他のクラスとかはとりあえず除外).
 **************************************************************************************************/

enum VariableType
{
	VAR_TYPE_S8,
	VAR_TYPE_U8,
	VAR_TYPE_S16,
	VAR_TYPE_U16,
	VAR_TYPE_S32,
	VAR_TYPE_U32,
	VAR_TYPE_F32,
	VAR_TYPE_F64,
	VAR_TYPE_VEC2,
	VAR_TYPE_VEC3,
	VAR_TYPE_VEC4,
	VAR_TYPE_MAT44,
	VAR_TYPE_BOOL,
	VAR_TYPE_STR,
	VAR_TYPE_MAX
};




shared_ptr<IVariable> S8_Add(shared_ptr<Variable<char>> varA, VariableType typeNameB, shared_ptr<IVariable> varB)
{
	shared_ptr<Variable<char>> reternVar = make_shared<Variable<char>>();
	switch(typeNameB)
	{
	case VAR_TYPE_S8:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<char>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U8:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UCHAR>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<short>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<USHORT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<int>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UINT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<FLOAT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F64:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<DOUBLE>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_VEC2:
		return nullptr;

		break;
	case VAR_TYPE_VEC3:
		return nullptr;
		break;
	case VAR_TYPE_VEC4:
		return nullptr;
		break;
	case VAR_TYPE_MAT44:
		return nullptr;
		break;
	case VAR_TYPE_BOOL:
		return nullptr;
		break;
	case VAR_TYPE_STR:
		return nullptr;
		break;
	default:
		return nullptr;
		break;
		
	}
}


shared_ptr<IVariable> U8_Add(shared_ptr<Variable<UCHAR>> varA, VariableType typeNameB, shared_ptr<IVariable> varB)
{
	shared_ptr<Variable<UCHAR>> reternVar = make_shared<Variable<UCHAR>>();
	switch (typeNameB)
	{
	case VAR_TYPE_S8:
		reternVar->SetValue(*varA->GetValue() + *std::static_pointer_cast<Variable<char>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U8:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UCHAR>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<short>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<USHORT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<int>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UINT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<FLOAT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F64:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<DOUBLE>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_VEC2:
		return nullptr;

		break;
	case VAR_TYPE_VEC3:
		return nullptr;
		break;
	case VAR_TYPE_VEC4:
		return nullptr;
		break;
	case VAR_TYPE_MAT44:
		return nullptr;
		break;
	case VAR_TYPE_BOOL:
		return nullptr;
		break;
	case VAR_TYPE_STR:
		return nullptr;
		break;
	default:
		return nullptr;
		break;

	}
}


shared_ptr<IVariable> S16_Add(shared_ptr<Variable<short>> varA, VariableType typeNameB, shared_ptr<IVariable> varB)
{
	shared_ptr<Variable<short>> reternVar = make_shared<Variable<short>>();
	switch (typeNameB)
	{
	case VAR_TYPE_S8:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<char>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U8:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UCHAR>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<short>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<USHORT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<int>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UINT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<FLOAT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F64:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<DOUBLE>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_VEC2:
		return nullptr;

		break;
	case VAR_TYPE_VEC3:
		return nullptr;
		break;
	case VAR_TYPE_VEC4:
		return nullptr;
		break;
	case VAR_TYPE_MAT44:
		return nullptr;
		break;
	case VAR_TYPE_BOOL:
		return nullptr;
		break;
	case VAR_TYPE_STR:
		return nullptr;
		break;
	default:
		return nullptr;
		break;

	}
}


shared_ptr<IVariable> U16_Add(shared_ptr<Variable<USHORT>> varA, VariableType typeNameB, shared_ptr<IVariable> varB)
{
	shared_ptr<Variable<USHORT>> reternVar = make_shared<Variable<USHORT>>();
	switch (typeNameB)
	{
	case VAR_TYPE_S8:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<char>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U8:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UCHAR>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<short>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<USHORT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<int>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UINT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<FLOAT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F64:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<DOUBLE>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_VEC2:
		return nullptr;

		break;
	case VAR_TYPE_VEC3:
		return nullptr;
		break;
	case VAR_TYPE_VEC4:
		return nullptr;
		break;
	case VAR_TYPE_MAT44:
		return nullptr;
		break;
	case VAR_TYPE_BOOL:
		return nullptr;
		break;
	case VAR_TYPE_STR:
		return nullptr;
		break;
	default:
		return nullptr;
		break;

	}
}
shared_ptr<IVariable> S32_Add(shared_ptr<Variable<int>> varA, VariableType typeNameB, shared_ptr<IVariable> varB)
{
	shared_ptr<Variable<int>> reternVar = make_shared<Variable<int>>();
	switch (typeNameB)
	{
	case VAR_TYPE_S8:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<char>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U8:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UCHAR>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<short>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<USHORT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<int>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UINT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<FLOAT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F64:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<DOUBLE>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_VEC2:
		return nullptr;

		break;
	case VAR_TYPE_VEC3:
		return nullptr;
		break;
	case VAR_TYPE_VEC4:
		return nullptr;
		break;
	case VAR_TYPE_MAT44:
		return nullptr;
		break;
	case VAR_TYPE_BOOL:
		return nullptr;
		break;
	case VAR_TYPE_STR:
		return nullptr;
		break;
	default:
		return nullptr;
		break;

	}
}


shared_ptr<IVariable> U32_Add(shared_ptr<Variable<UINT>> varA, VariableType typeNameB, shared_ptr<IVariable> varB)
{
	shared_ptr<Variable<UINT>> reternVar = make_shared<Variable<UINT>>();
	switch (typeNameB)
	{
	case VAR_TYPE_S8:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<char>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U8:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UCHAR>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<short>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<USHORT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<int>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UINT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<FLOAT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F64:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<DOUBLE>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_VEC2:
		return nullptr;

		break;
	case VAR_TYPE_VEC3:
		return nullptr;
		break;
	case VAR_TYPE_VEC4:
		return nullptr;
		break;
	case VAR_TYPE_MAT44:
		return nullptr;
		break;
	case VAR_TYPE_BOOL:
		return nullptr;
		break;
	case VAR_TYPE_STR:
		return nullptr;
		break;
	default:
		return nullptr;
		break;

	}
}


shared_ptr<IVariable> F32_Add(shared_ptr<Variable<FLOAT>> varA, VariableType typeNameB, shared_ptr<IVariable> varB)
{
	shared_ptr<Variable<FLOAT>> reternVar = make_shared<Variable<FLOAT>>();
	switch (typeNameB)
	{
	case VAR_TYPE_S8:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<char>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U8:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UCHAR>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<short>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<USHORT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<int>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UINT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<FLOAT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F64:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<DOUBLE>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_VEC2:
		return nullptr;

		break;
	case VAR_TYPE_VEC3:
		return nullptr;
		break;
	case VAR_TYPE_VEC4:
		return nullptr;
		break;
	case VAR_TYPE_MAT44:
		return nullptr;
		break;
	case VAR_TYPE_BOOL:
		return nullptr;
		break;
	case VAR_TYPE_STR:
		return nullptr;
		break;
	default:
		return nullptr;
		break;

	}
}


shared_ptr<IVariable> F64_Add(shared_ptr<Variable<DOUBLE>> varA, VariableType typeNameB, shared_ptr<IVariable> varB)
{
	shared_ptr<Variable<DOUBLE>> reternVar = make_shared<Variable<DOUBLE>>();
	switch (typeNameB)
	{
	case VAR_TYPE_S8:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<char>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U8:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UCHAR>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<short>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U16:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<USHORT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_S32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<int>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_U32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<UINT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F32:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<FLOAT>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_F64:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<DOUBLE>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_VEC2:
		return nullptr;

		break;
	case VAR_TYPE_VEC3:
		return nullptr;
		break;
	case VAR_TYPE_VEC4:
		return nullptr;
		break;
	case VAR_TYPE_MAT44:
		return nullptr;
		break;
	case VAR_TYPE_BOOL:
		return nullptr;
		break;
	case VAR_TYPE_STR:
		return nullptr;
		break;
	default:
		return nullptr;
		break;

	}
}

shared_ptr<IVariable> VEC2_Add(shared_ptr<Variable<HFVECTOR2>> varA, VariableType typeNameB, shared_ptr<IVariable> varB)
{
	shared_ptr<Variable<HFVECTOR2>> reternVar = make_shared<Variable<HFVECTOR2>>();
	switch (typeNameB)
	{
	case VAR_TYPE_S8:
		return nullptr;
		break;
	case VAR_TYPE_U8:
		return nullptr;
		break;
	case VAR_TYPE_S16:
		return nullptr;
		break;
	case VAR_TYPE_U16:
		return nullptr;
		break;
	case VAR_TYPE_S32:
		return nullptr;
		break;
	case VAR_TYPE_U32:
		return nullptr;
		break;
	case VAR_TYPE_F32:
		return nullptr;
		break;
	case VAR_TYPE_F64:
		return nullptr;
		break;
	case VAR_TYPE_VEC2:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<HFVECTOR2>>(varB)->GetValue());
		return reternVar;
		return nullptr;

		break;
	case VAR_TYPE_VEC3:
		return nullptr;
		break;
	case VAR_TYPE_VEC4:
		return nullptr;
		break;
	case VAR_TYPE_MAT44:
		return nullptr;
		break;
	case VAR_TYPE_BOOL:
		return nullptr;
		break;
	case VAR_TYPE_STR:
		return nullptr;
		break;
	default:
		return nullptr;
		break;

	}
}


shared_ptr<IVariable> VEC3_Add(shared_ptr<Variable<HFVECTOR3>> varA, VariableType typeNameB, shared_ptr<IVariable> varB)
{
	shared_ptr<Variable<HFVECTOR3>> reternVar = make_shared<Variable<HFVECTOR3>>();
	switch (typeNameB)
	{
	case VAR_TYPE_S8:
		return nullptr;
		break;
	case VAR_TYPE_U8:
		return nullptr;
		break;
	case VAR_TYPE_S16:
		return nullptr;
		break;
	case VAR_TYPE_U16:
		return nullptr;
		break;
	case VAR_TYPE_S32:
		return nullptr;
		break;
	case VAR_TYPE_U32:
		return nullptr;
		break;
	case VAR_TYPE_F32:
		return nullptr;
		break;
	case VAR_TYPE_F64:
		return nullptr;
		break;
	case VAR_TYPE_VEC2:
		return nullptr;
		break;
	case VAR_TYPE_VEC3:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<HFVECTOR3>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_VEC4:
		return nullptr;
		break;
	case VAR_TYPE_MAT44:
		return nullptr;
		break;
	case VAR_TYPE_BOOL:
		return nullptr;
		break;
	case VAR_TYPE_STR:
		return nullptr;
		break;
	default:
		return nullptr;
		break;

	}
}


shared_ptr<IVariable> VEC4_Add(shared_ptr<Variable<HFVECTOR4>> varA, VariableType typeNameB, shared_ptr<IVariable> varB)
{
	shared_ptr<Variable<HFVECTOR4>> reternVar = make_shared<Variable<HFVECTOR4>>();
	switch (typeNameB)
	{
	case VAR_TYPE_S8:
		return nullptr;
		break;
	case VAR_TYPE_U8:
		return nullptr;
		break;
	case VAR_TYPE_S16:
		return nullptr;
		break;
	case VAR_TYPE_U16:
		return nullptr;
		break;
	case VAR_TYPE_S32:
		return nullptr;
		break;
	case VAR_TYPE_U32:
		return nullptr;
		break;
	case VAR_TYPE_F32:
		return nullptr;
		break;
	case VAR_TYPE_F64:
		return nullptr;
		break;
	case VAR_TYPE_VEC2:
		return nullptr;
		break;
	case VAR_TYPE_VEC3:
		return nullptr;
		break;
	case VAR_TYPE_VEC4:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<HFVECTOR4>>(varB)->GetValue());
		return reternVar;
		return nullptr;
		break;
	case VAR_TYPE_MAT44:
		return nullptr;
		break;
	case VAR_TYPE_BOOL:
		return nullptr;
		break;
	case VAR_TYPE_STR:
		return nullptr;
		break;
	default:
		return nullptr;
		break;

	}
}


shared_ptr<IVariable> VEC4_Add(shared_ptr<Variable<HFMATRIX>> varA, VariableType typeNameB, shared_ptr<IVariable> varB)
{
	shared_ptr<Variable<HFMATRIX>> reternVar = make_shared<Variable<HFMATRIX>>();
	switch (typeNameB)
	{
	case VAR_TYPE_S8:
		return nullptr;
		break;
	case VAR_TYPE_U8:
		return nullptr;
		break;
	case VAR_TYPE_S16:
		return nullptr;
		break;
	case VAR_TYPE_U16:
		return nullptr;
		break;
	case VAR_TYPE_S32:
		return nullptr;
		break;
	case VAR_TYPE_U32:
		return nullptr;
		break;
	case VAR_TYPE_F32:
		return nullptr;
		break;
	case VAR_TYPE_F64:
		return nullptr;
		break;
	case VAR_TYPE_VEC2:
		return nullptr;
		break;
	case VAR_TYPE_VEC3:
		return nullptr;
		break;
	case VAR_TYPE_VEC4:
		return nullptr;
		break;
	case VAR_TYPE_MAT44:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<HFMATRIX>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_BOOL:
		return nullptr;
		break;
	case VAR_TYPE_STR:
		return nullptr;
		break;
	default:
		return nullptr;
		break;

	}
}


shared_ptr<IVariable> VEC4_Add(shared_ptr<Variable<BOOL>> varA, VariableType typeNameB, shared_ptr<IVariable> varB)
{
	shared_ptr<Variable<BOOL>> reternVar = make_shared<Variable<BOOL>>();
	switch (typeNameB)
	{
	case VAR_TYPE_S8:
		return nullptr;
		break;
	case VAR_TYPE_U8:
		return nullptr;
		break;
	case VAR_TYPE_S16:
		return nullptr;
		break;
	case VAR_TYPE_U16:
		return nullptr;
		break;
	case VAR_TYPE_S32:
		return nullptr;
		break;
	case VAR_TYPE_U32:
		return nullptr;
		break;
	case VAR_TYPE_F32:
		return nullptr;
		break;
	case VAR_TYPE_F64:
		return nullptr;
		break;
	case VAR_TYPE_VEC2:
		return nullptr;
		break;
	case VAR_TYPE_VEC3:
		return nullptr;
		break;
	case VAR_TYPE_VEC4:
		return nullptr;
		break;
	case VAR_TYPE_MAT44:
		return nullptr;
		break;
	case VAR_TYPE_BOOL:
		reternVar->SetValue(*varA->GetValue() + *std::dynamic_pointer_cast<Variable<BOOL>>(varB)->GetValue());
		return reternVar;
		break;
	case VAR_TYPE_STR:
		return nullptr;
		break;
	default:
		return nullptr;
		break;

	}
}

shared_ptr<IVariable> Add(VariableType typeNameA, shared_ptr<IVariable> varA, VariableType typeNameB, shared_ptr<IVariable> varB)
{

	switch (typeNameA)
	{
	case VAR_TYPE_S8:
		return S8_Add(dynamic_pointer_cast<Variable<char>>(varA), typeNameB, varB);
		break;
	case VAR_TYPE_U8:
		return U8_Add(dynamic_pointer_cast<Variable<UCHAR>>(varA), typeNameB, varB);
		break;
	case VAR_TYPE_S16:
		return S16_Add(dynamic_pointer_cast<Variable<short>>(varA), typeNameB, varB);
		break;
	case VAR_TYPE_U16:
		return U16_Add(dynamic_pointer_cast<Variable<USHORT>>(varA), typeNameB, varB);
		break;
	case VAR_TYPE_S32:
		return S32_Add(dynamic_pointer_cast<Variable<int>>(varA), typeNameB, varB);
		break;
	case VAR_TYPE_U32:
		return U32_Add(dynamic_pointer_cast<Variable<UINT>>(varA), typeNameB, varB);
		break;
	case VAR_TYPE_F32:
		return F32_Add(dynamic_pointer_cast<Variable<FLOAT>>(varA), typeNameB, varB);
		break;
	case VAR_TYPE_F64:
		return F64_Add(dynamic_pointer_cast<Variable<DOUBLE>>(varA), typeNameB, varB);
		break;
	case VAR_TYPE_VEC2:
		return VEC2_Add(dynamic_pointer_cast<Variable<HFVECTOR2>>(varA), typeNameB, varB);
		break;
	case VAR_TYPE_VEC3:
		return VEC3_Add(dynamic_pointer_cast<Variable<HFVECTOR3>>(varA), typeNameB, varB);
		break;
	case VAR_TYPE_VEC4:
		return VEC4_Add(dynamic_pointer_cast<Variable<HFVECTOR4>>(varA), typeNameB, varB);
		break;
	case VAR_TYPE_MAT44:
		break;
	case VAR_TYPE_BOOL:
		break;
	case VAR_TYPE_STR:
		break;
	default:
		break;

	}
}