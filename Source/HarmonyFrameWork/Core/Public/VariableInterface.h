#pragma once
#include "Common.h"

enum VariableType
{
	VAR_TYPE_S8,	/*!< An enum constant representing the variable type signed 8 bit option */
	VAR_TYPE_U8,	/*!< An enum constant representing the variable type unsigned 8 bit option */
	VAR_TYPE_S16,   /*!< An enum constant representing the variable type signed 16 bit option */
	VAR_TYPE_U16,   /*!< An enum constant representing the variable type unsigned 16 bit option */
	VAR_TYPE_S32,   /*!< An enum constant representing the variable type sigend 32 bit option */
	VAR_TYPE_U32,   /*!< An enum constant representing the variable type unsigned 32 bit option */
	VAR_TYPE_F32,   /*!< An enum constant representing the variable type FLOAT 32 bit option */
	VAR_TYPE_F64,   /*!< An enum constant representing the variable type flaot 64 bit option */
	VAR_TYPE_BOOL,  /*!< An enum constant representing the variable type bool option */
	VAR_TYPE_VEC2,  /*!< An enum constant representing the variable type vector 2 dimensional option */
	VAR_TYPE_VEC3,  /*!< An enum constant representing the variable type vector 3 dimensional option */
	VAR_TYPE_VEC4,		// An enum constant representing the variable type vector 4 dimensional option */
	VAR_TYPE_MAT44, /*!< An enum constant representing the variable type matrix FLOAT 4x4 option */
	VAR_TYPE_QUATERNION,	/*!< An enum constant representing the variable type quaternion option */
	VAR_TYPE_STR,   /*!< An enum constant representing the variable type string option */
	VAR_TYPE_HFBASE_CUSTOM,	/*!< An enum constant representing the variable type custom option */
	VAR_TYPE_UNKNOWN,   /*!< An enum constant representing the variable type unknown option */
	VAR_TYPE_MAX	/*!< An enum constant representing the variable type maximum option */
};


// 先行宣言
class IVariable;
class HFString;
template <class T>class Variable;

// VariableInterfase演算用関数

void Assignment(std::shared_ptr<IVariable>iVariableA, std::shared_ptr<IVariable>iVariableB);



void  S8_Assignment(std::shared_ptr<Variable<CHAR>> VariableA, CHAR iVariableB);
void  U8_Assignment(std::shared_ptr<Variable<UCHAR>> VariableA, UCHAR iVariableB);
void  S16_Assignment(std::shared_ptr<Variable<SHORT>> VariableA, SHORT iVariableB);
void  U16_Assignment(std::shared_ptr<Variable<USHORT>> VariableA, USHORT  iVariableB);
void  S32_Assignment(std::shared_ptr<Variable<INT>> VariableA, INT iVariableB);
void  U32_Assignment(std::shared_ptr<Variable<UINT>> VariableA, UINT  iVariableB);
void  F32_Assignment(std::shared_ptr<Variable<FLOAT>> VariableA, FLOAT ariableB);
void  F64_Assignment(std::shared_ptr<Variable<DOUBLE>> VariableA, DOUBLE  VariableB);
void  BOOL_Assignment(std::shared_ptr<Variable<bool>> VariableA, bool VariableB);
void  VEC2_Assignment(std::shared_ptr<Variable<HFVECTOR2>> VariableA, HFVECTOR2  iVariableB);
void  VEC3_Assignment(std::shared_ptr<Variable<HFVECTOR3>> VariableA, HFVECTOR3 iVariableB);
void  VEC4_Assignment(std::shared_ptr<Variable<HFVECTOR4>> VariableA, HFVECTOR4 iVariableB);
void  MAT44_Assignment(std::shared_ptr<Variable<HFMATRIX>> VariableA, HFMATRIX  iVariableB);
void  QUATERNION_Assignment(std::shared_ptr<Variable<HFQUATERNION>> VariableA, HFQUATERNION iVariableB);
void  STR_Assignment(std::shared_ptr<Variable<HFString>> VariableA, HFString  iVariableB);


bool Equality(std::shared_ptr<IVariable>iVariableA, std::shared_ptr<IVariable>iVariableB);

std::shared_ptr<IVariable>  Add(std::shared_ptr<IVariable> iVariableA, std::shared_ptr<IVariable> iVariableB);

std::shared_ptr<IVariable>  Subtruct(std::shared_ptr<IVariable> iVariableA, std::shared_ptr<IVariable> iVariableB);

std::shared_ptr<IVariable>  Multi(std::shared_ptr<IVariable> iVariableA, std::shared_ptr<IVariable> iVariableB);


std::shared_ptr<IVariable>  Division(std::shared_ptr<IVariable> iVariableA, std::shared_ptr<IVariable> iVariableB);

template<typename T>
bool Equality(std::shared_ptr<IVariable>iVariable, T var);

template<typename T>
std::shared_ptr<IVariable>  Add(std::shared_ptr<IVariable> iVariable, T var);

template<typename T>
std::shared_ptr<IVariable>  Subtruct(std::shared_ptr<IVariable> iVariable, T var);


/*
template<class T>
void Assignment(std::shared_ptr<IVariable>iVariableA, T iVariableB)
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
		std::dynamic_pointer_cast<Variable<T>>(iVariableA)->SetValue(iVariableB);
		break;
	case VAR_TYPE_VEC3:
		std::dynamic_pointer_cast<Variable<T>>(iVariableA)->SetValue(iVariableB);
		break;
	case VAR_TYPE_VEC4:
		std::dynamic_pointer_cast<Variable<T>>(iVariableA)->SetValue(iVariableB);
		break;
	case VAR_TYPE_MAT44:
		std::dynamic_pointer_cast<Variable<T>>(iVariableA)->SetValue(iVariableB);
		break;
	case VAR_TYPE_QUATERNION:
		std::dynamic_pointer_cast<Variable<T>>(iVariableA)->SetValue(iVariableB);
		break;
	case VAR_TYPE_STR:
		std::dynamic_pointer_cast<Variable<T>>(iVariableA)->SetValue(iVariableB);
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
	   */
class IVariable
	:
	public inheritable_enable_shared_from_this<IVariable>
{
public:
	IVariable() {};
	IVariable(IVariable& var)
	{
	
	};
	virtual~IVariable() {};

			 /*
	virtual bool operator== (IVariable& var)
	{

		return Equality(this->shared_from_this(), var.shared_from_this());
	}


	template<typename T>
	bool operator == (T var)
	{
		return Equality(this->shared_from_this(), var);
	}

				   
	virtual IVariable operator + (IVariable& var)
	{
		return *Add(this->shared_from_this(), var.shared_from_this());
	}
	template<typename T>
	IVariable operator + (T var)
	{
		return *Add(this->shared_from_this(), var);
	}

	template<typename T>
	void operator = (T var)
	{
		Assignment(this->shared_from_this(), var);
	}

	void operator = (IVariable var)
	{
		Assignment(this->shared_from_this(), var.shared_from_this());
	}

	// Access the VariableType
	VariableType GetVariableType(void) const
	{
		return(m_variableType);
	};
	void SetVariableType(const VariableType& variableType)
	{
		m_variableType = variableType;
	};

					 */
	

protected:


	VariableType m_variableType;
}; 



template <class T>
class Variable
	:
	public IVariable
{
public:
	// Access the Name
	const std::string& GetName(void) const	{ return(m_name);	};
	void SetName(const std::string& name)	{ m_name = name;	};


	// Access the Value
	std::shared_ptr<T> GetValue(void)
	{
		return(m_value);
	};
	void SetValue(std::shared_ptr<T>& value)
	{
		m_value = value;
	};

	void SetValue(T* value)
	{
		if (m_value)
		{
			*m_value = *value;
		}
		else if (value)
		{
		}
		else
		{
			m_value = std::make_shared<T>();
			*m_value = *value;
		}
	};

private:

	std::string m_name;
	std::shared_ptr<T> m_value;
};


template <class T>
class VariableArray
	:
	public IVariable
{
public:



	// Access the Name
	const std::string& GetName(void) const { return(m_name); };
	void SetName(const std::string& name) { m_name = name; };

	// Access the Array
	const std::vector<std::shared_ptr<T>>& GetArray(void) const	{ return(m_array);	};
	void SetArray(const std::vector<std::shared_ptr<T>>& array)	{ m_array = array;	};

private:

	std::string m_name;
	std::vector<std::shared_ptr<T>> m_array;
};

