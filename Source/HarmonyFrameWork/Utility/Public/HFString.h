#pragma once
#include <string>	
#include <sstream>    
#include <tchar.h>		
#include <iostream>
#include "StringUtility.h"
#include <wtypes.h>		

class HFString
{
private:
	std::string m_string;  std::wstring m_wString;
public:
	HFString();
	~HFString();

							  
	std::wstring GetWString() const
	{ 
		return m_wString; 
	}
	void SetWString(std::wstring val)
	{
		m_wString = val;
		m_string = (UTILITY::Narrow(val));
	}
	std::string GetString() const 
	{ 
		return m_string;
	}
	void SetString(std::string val) 
	{ 
		m_string = val;
		m_wString = (UTILITY::Widen(val));
	}

	HFString(TCHAR* str)
	{
		m_string = (str);
		m_wString = (UTILITY::Widen(str));
	};

	HFString operator = (TCHAR *str)
	{
		m_string = (str);
		m_wString = (UTILITY::Widen(str));
		return *this;
	}
	HFString operator = (std::string str)
	{
		m_string = (str);
		m_wString = (UTILITY::Widen(str));
		return *this;
	}

	HFString operator = (std::wstring& str)
	{
		m_string = (UTILITY::Narrow(str));
		m_wString = ((str));
		return *this;
	}

	HFString operator +(HFString& str)
	{
		HFString result;
		result.SetString(this->GetString() + str.GetString());
		return result;
	}
	HFString operator + (TCHAR* str)
	{
		HFString result;
		HFString add = str;
		result.SetString(this->GetString() + add.GetString());
		return result;
	}

	std::wstring& CastWString()
	{
		return UTILITY::Widen(GetString());
	}

	operator LPCTSTR()
	{
		return GetString().c_str();
	}

	operator LPCWSTR()
	{
		SetWString(UTILITY::Widen(GetString()).c_str());
		return GetWString().c_str();
	}

	operator TCHAR*()
	{
		return const_cast<TCHAR*>(GetString().c_str());
	}


	// •¶Žš—ñ‚Ì˜AŒ‹
	template<typename... Args>
	static
		HFString& Concat(const Args&... args)
	{
		std::stringstream sout;
		UTILITY::ConcatString(sout, args...);
		std::string out = sout.str();
		HFString output ;
		return output;
	};

};

std::ostream &operator << (std::ostream &out, const HFString& hfstring);