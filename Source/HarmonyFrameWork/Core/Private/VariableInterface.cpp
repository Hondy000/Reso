/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Core\Private\VariableInterface.cpp
 *
 * @brief	Implements the variable interface class.
 **************************************************************************************************/

#include "../public/VariableInterface.h"
#include "..\..\Utility\Public\HFString.h"


void  S8_Assignment(std::shared_ptr<Variable<CHAR>> VariableA, std::shared_ptr<IVariable> iVariableB);
void  U8_Assignment(std::shared_ptr<Variable<UCHAR>> VariableA, std::shared_ptr<IVariable> iVariableB);
void  S16_Assignment(std::shared_ptr<Variable<SHORT>> VariableA, std::shared_ptr<IVariable> iVariableB);
void  U16_Assignment(std::shared_ptr<Variable<USHORT>> VariableA, std::shared_ptr<IVariable> iVariableB);
void  S32_Assignment(std::shared_ptr<Variable<INT>> VariableA, std::shared_ptr<IVariable> iVariableB);
void  U32_Assignment(std::shared_ptr<Variable<UINT>> VariableA, std::shared_ptr<IVariable> iVariableB);
void  F32_Assignment(std::shared_ptr<Variable<FLOAT>> VariableA, std::shared_ptr<IVariable> iVariableB);
void  F64_Assignment(std::shared_ptr<Variable<DOUBLE>> VariableA, std::shared_ptr<IVariable> iVariableB);
void  BOOL_Assignment(std::shared_ptr<Variable<bool>> VariableA, std::shared_ptr<IVariable> iVariableB);
void  VEC2_Assignment(std::shared_ptr<Variable<HFVECTOR2>> VariableA, std::shared_ptr<IVariable> iVariableB);
void  VEC3_Assignment(std::shared_ptr<Variable<HFVECTOR3>> VariableA, std::shared_ptr<IVariable> iVariableB);
void  VEC4_Assignment(std::shared_ptr<Variable<HFVECTOR4>> VariableA, std::shared_ptr<IVariable> iVariableB);
void  MAT44_Assignment(std::shared_ptr<Variable<HFMATRIX>> VariableA, std::shared_ptr<IVariable> iVariableB);
void  QUATERNION_Assignment(std::shared_ptr<Variable<HFQUATERNION>> VariableA, std::shared_ptr<IVariable> iVariableB);
void  STR_Assignment(std::shared_ptr<Variable<HFString>> VariableA, std::shared_ptr<IVariable> iVariableB);

void Assignment(std::shared_ptr<IVariable>iVariableA, std::shared_ptr<IVariable>iVariableB)
{

	switch (iVariableA->GetVariableType())
	{
	case VAR_TYPE_S8:
		S8_Assignment(std::dynamic_pointer_cast<Variable<CHAR>>(iVariableA), iVariableB);
		break;
	case VAR_TYPE_U8:
		U8_Assignment(std::dynamic_pointer_cast<Variable<UCHAR>>(iVariableA), iVariableB);
		break;
	case VAR_TYPE_S16:
		S16_Assignment(std::dynamic_pointer_cast<Variable<SHORT>>(iVariableA), iVariableB);
		break;
	case VAR_TYPE_U16:
		U16_Assignment(std::dynamic_pointer_cast<Variable<USHORT>>(iVariableA), iVariableB);
		break;
	case VAR_TYPE_S32:
		S32_Assignment(std::dynamic_pointer_cast<Variable<INT>>(iVariableA), iVariableB);
		break;
	case VAR_TYPE_U32:
		U32_Assignment(std::dynamic_pointer_cast<Variable<UINT>>(iVariableA), iVariableB);
		break;
	case VAR_TYPE_F32:
		F32_Assignment(std::dynamic_pointer_cast<Variable<FLOAT>>(iVariableA), iVariableB);
		break;
	case VAR_TYPE_F64:
		F64_Assignment(std::dynamic_pointer_cast<Variable<DOUBLE>>(iVariableA), iVariableB);
		break;
	case VAR_TYPE_BOOL:
		BOOL_Assignment(std::dynamic_pointer_cast<Variable<bool>>(iVariableA), iVariableB);
		break;
	case VAR_TYPE_VEC2:
		VEC2_Assignment(std::dynamic_pointer_cast<Variable<HFVECTOR2>>(iVariableA), iVariableB);
		break;
	case VAR_TYPE_VEC3:
		VEC3_Assignment(std::dynamic_pointer_cast<Variable<HFVECTOR3>>(iVariableA), iVariableB);
		break;
	case VAR_TYPE_VEC4:										
		VEC4_Assignment(std::dynamic_pointer_cast<Variable<HFVECTOR4>>(iVariableA), iVariableB);
		break;
	case VAR_TYPE_MAT44:
		MAT44_Assignment(std::dynamic_pointer_cast<Variable<HFMATRIX>>(iVariableA), iVariableB);
		break;
	case VAR_TYPE_QUATERNION:
		QUATERNION_Assignment(std::dynamic_pointer_cast<Variable<HFQUATERNION>>(iVariableA), iVariableB);
		break;
	case VAR_TYPE_STR:
		STR_Assignment(std::dynamic_pointer_cast<Variable<HFString>>(iVariableA), iVariableB);
		break;
	case VAR_TYPE_MAX:
		//errer
		break;
	case VAR_TYPE_HFBASE_CUSTOM:
		//errer	
		break;
	case VAR_TYPE_UNKNOWN:
		//errer
		break;
	default:
		break;
		
	}
}



void  S8_Assignment(std::shared_ptr<Variable<CHAR>> VariableA, std::shared_ptr<IVariable> iVariableB)
{
	VariableA->SetValue(std::dynamic_pointer_cast<Variable<CHAR>>(iVariableB)->GetValue());
};
void  U8_Assignment(std::shared_ptr<Variable<UCHAR>> VariableA, std::shared_ptr<IVariable> iVariableB)
{
	VariableA->SetValue(std::dynamic_pointer_cast<Variable<UCHAR>>(iVariableB)->GetValue());
};
void  S16_Assignment(std::shared_ptr<Variable<SHORT>> VariableA, std::shared_ptr<IVariable> iVariableB)
{
	VariableA->SetValue(std::dynamic_pointer_cast<Variable<SHORT>>(iVariableB)->GetValue());
};
void  U16_Assignment(std::shared_ptr<Variable<USHORT>> VariableA, std::shared_ptr<IVariable> iVariableB)
{
	VariableA->SetValue(std::dynamic_pointer_cast<Variable<USHORT>>(iVariableB)->GetValue());
};
void  S32_Assignment(std::shared_ptr<Variable<INT>> VariableA, std::shared_ptr<IVariable> iVariableB)
{
	VariableA->SetValue(std::dynamic_pointer_cast<Variable<INT>>(iVariableB)->GetValue());
};
void  U32_Assignment(std::shared_ptr<Variable<UINT>> VariableA, std::shared_ptr<IVariable> iVariableB)
{
	VariableA->SetValue(std::dynamic_pointer_cast<Variable<UINT>>(iVariableB)->GetValue());
};
void  F32_Assignment(std::shared_ptr<Variable<FLOAT>> VariableA, std::shared_ptr<IVariable> iVariableB)
{
	VariableA->SetValue(std::dynamic_pointer_cast<Variable<FLOAT>>(iVariableB)->GetValue());
};
void  F64_Assignment(std::shared_ptr<Variable<DOUBLE>> VariableA, std::shared_ptr<IVariable> iVariableB)
{
	VariableA->SetValue(std::dynamic_pointer_cast<Variable<DOUBLE>>(iVariableB)->GetValue());
};
void  BOOL_Assignment(std::shared_ptr<Variable<bool>> VariableA, std::shared_ptr<IVariable> iVariableB)
{
	VariableA->SetValue(std::dynamic_pointer_cast<Variable<bool>>(iVariableB)->GetValue());
};
void  VEC2_Assignment(std::shared_ptr<Variable<HFVECTOR2>> VariableA, std::shared_ptr<IVariable> iVariableB)
{
	VariableA->SetValue(std::dynamic_pointer_cast<Variable<HFVECTOR2>>(iVariableB)->GetValue());
};
void  VEC3_Assignment(std::shared_ptr<Variable<HFVECTOR3>> VariableA, std::shared_ptr<IVariable> iVariableB)
{
	VariableA->SetValue(std::dynamic_pointer_cast<Variable<HFVECTOR3>>(iVariableB)->GetValue());
};
void  VEC4_Assignment(std::shared_ptr<Variable<HFVECTOR4>> VariableA, std::shared_ptr<IVariable> iVariableB)
{
	VariableA->SetValue(std::dynamic_pointer_cast<Variable<HFVECTOR4>>(iVariableB)->GetValue());
};
void  MAT44_Assignment(std::shared_ptr<Variable<HFMATRIX>> VariableA, std::shared_ptr<IVariable> iVariableB)
{
	VariableA->SetValue(std::dynamic_pointer_cast<Variable<HFMATRIX>>(iVariableB)->GetValue());
};
void  QUATERNION_Assignment(std::shared_ptr<Variable<HFQUATERNION>> VariableA, std::shared_ptr<IVariable> iVariableB)
{
	VariableA->SetValue(std::dynamic_pointer_cast<Variable<HFQUATERNION>>(iVariableB)->GetValue());
};
void  STR_Assignment(std::shared_ptr<Variable<HFString>> VariableA, std::shared_ptr<IVariable> iVariableB)
{
	VariableA->SetValue(std::dynamic_pointer_cast<Variable<HFString>>(iVariableB)->GetValue());
};


void  S8_Assignment(std::shared_ptr<Variable<CHAR>> VariableA, CHAR iVariableB)
{
	VariableA->SetValue(&iVariableB);
};
void  U8_Assignment(std::shared_ptr<Variable<UCHAR>> VariableA, UCHAR iVariableB)
{
	VariableA->SetValue(&iVariableB);
};
void  S16_Assignment(std::shared_ptr<Variable<SHORT>> VariableA, SHORT iVariableB)
{
	VariableA->SetValue(&iVariableB);
};
void  U16_Assignment(std::shared_ptr<Variable<USHORT>> VariableA, USHORT  iVariableB)
{
	VariableA->SetValue(&iVariableB);
};
void  S32_Assignment(std::shared_ptr<Variable<INT>> VariableA, INT  iVariableB)
{
	VariableA->SetValue(&iVariableB);
};
void  U32_Assignment(std::shared_ptr<Variable<UINT>> VariableA, UINT iVariableB)
{
	VariableA->SetValue(&iVariableB);
};
void  F32_Assignment(std::shared_ptr<Variable<FLOAT>> VariableA, FLOAT  iVariableB)
{
	VariableA->SetValue(&iVariableB);
};
void  F64_Assignment(std::shared_ptr<Variable<DOUBLE>> VariableA, DOUBLE  iVariableB)
{
	VariableA->SetValue(&iVariableB);
};
void  BOOL_Assignment(std::shared_ptr<Variable<bool>> VariableA, bool  iVariableB)
{
	VariableA->SetValue(&iVariableB);
};
void  VEC2_Assignment(std::shared_ptr<Variable<HFVECTOR2>> VariableA, HFVECTOR2  iVariableB)
{
	VariableA->SetValue(&iVariableB);
};
void  VEC3_Assignment(std::shared_ptr<Variable<HFVECTOR3>> VariableA, HFVECTOR3 iVariableB)
{
	VariableA->SetValue(&iVariableB);
};
void  VEC4_Assignment(std::shared_ptr<Variable<HFVECTOR4>> VariableA, HFVECTOR4 iVariableB)
{
	VariableA->SetValue(&iVariableB);
};
void  MAT44_Assignment(std::shared_ptr<Variable<HFMATRIX>> VariableA, HFMATRIX  iVariableB)
{
	VariableA->SetValue(&iVariableB);
};
void  QUATERNION_Assignment(std::shared_ptr<Variable<HFQUATERNION>> VariableA, HFQUATERNION  iVariableB)
{
	VariableA->SetValue(&iVariableB);
};
void  STR_Assignment(std::shared_ptr<Variable<HFString>> VariableA, HFString  iVariableB)
{																						  
	VariableA->SetValue(&iVariableB);
};


/*
bool Equality(std::shared_ptr<IVariable>iVariableA, std::shared_ptr<IVariable>iVariableB)
{

} 

std::shared_ptr<IVariable>  S8_Add(std::shared_ptr<Variable<CHAR>> VariableA, std::shared_ptr<IVariable> iVariableB);
std::shared_ptr<IVariable>  U8_Add(std::shared_ptr<Variable<UCHAR>> VariableA, std::shared_ptr<IVariable> iVariableB);
std::shared_ptr<IVariable>  S16_Add(std::shared_ptr<Variable<SHORT>> VariableA, std::shared_ptr<IVariable> iVariableB);
std::shared_ptr<IVariable>  U16_Add(std::shared_ptr<Variable<USHORT>> VariableA, std::shared_ptr<IVariable> iVariableB);
std::shared_ptr<IVariable>  S32_Add(std::shared_ptr<Variable<INT>> VariableA, std::shared_ptr<IVariable> iVariableB);
std::shared_ptr<IVariable>  U32_Add(std::shared_ptr<Variable<UCHAR>> VariableA, std::shared_ptr<IVariable> iVariableB);
std::shared_ptr<IVariable>  F32_Add(std::shared_ptr<Variable<FLOAT>> VariableA, std::shared_ptr<IVariable> iVariableB);
std::shared_ptr<IVariable>  F64_Add(std::shared_ptr<Variable<DOUBLE>> VariableA, std::shared_ptr<IVariable> iVariableB);
std::shared_ptr<IVariable>  VEC2_Add(std::shared_ptr<Variable<HFVECTOR2>> VariableA, std::shared_ptr<IVariable> iVariableB);
std::shared_ptr<IVariable>  VEC3_Add(std::shared_ptr<Variable<HFVECTOR3>> VariableA, std::shared_ptr<IVariable> iVariableB);
std::shared_ptr<IVariable>  VEC4_Add(std::shared_ptr<Variable<HFVECTOR4>> VariableA, std::shared_ptr<IVariable> iVariableB);
std::shared_ptr<IVariable>  MAT44_Add(std::shared_ptr<Variable<HFMATRIX>> VariableA, std::shared_ptr<IVariable> iVariableB);
std::shared_ptr<IVariable>  QUATERNION_Add(std::shared_ptr<Variable<HFQUATERNION>> VariableA, std::shared_ptr<IVariable> iVariableB);
*/
/*

std::shared_ptr<IVariable>  Add(std::shared_ptr<IVariable> iVariableA, std::shared_ptr<IVariable> iVariableB)
{
}

std::shared_ptr<IVariable>  Subtruct(std::shared_ptr<IVariable> iVariableA, std::shared_ptr<IVariable> iVariableB)
{

}

std::shared_ptr<IVariable>  Multi(std::shared_ptr<IVariable> iVariableA, std::shared_ptr<IVariable> iVariableB)
{

}

std::shared_ptr<IVariable>  Division(std::shared_ptr<IVariable> iVariableA, std::shared_ptr<IVariable> iVariableB)
{

}


std::shared_ptr<IVariable> S8_Add(std::shared_ptr<Variable<CHAR>> VariableA, std::shared_ptr<IVariable> iVariableB)
{

}
}*/