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
	HFString(const HFString& str);

							  
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

	HFString operator = (const HFString& str)
	{
		m_string = str.m_string;
		m_wString = str.m_wString;
		return *this;
	}
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
		result.SetString(this->m_string + str.m_string);
		return result;
	}
	HFString operator + (TCHAR* str)
	{
		HFString result;
		HFString add = str;
		result.SetString(this->m_string + add.m_string);
		return result;
	}

	std::wstring& CastWString()
	{
		return UTILITY::Widen(m_string);
	}

	operator LPCTSTR()
	{
		return m_string.c_str();
	}

	operator LPCWSTR()
	{
		return m_wString.c_str();
	}

	operator TCHAR*()
	{
		return const_cast<TCHAR*>(m_string.c_str());
	}
	bool operator == (HFString& str)
	{
		return this->m_string == str.GetString();
	}
	bool operator == (const HFString& str)
	{
		return this->m_string == str.GetString();
	}


	bool operator != (HFString& str)
	{
		return this->m_string != str.GetString();
	}
	bool operator != (const HFString& str)
	{
		return this->m_string != str.GetString();
	}

	// •¶Žš—ñ‚Ì˜AŒ‹
	template<typename... Args>
	static
		HFString Concat(const Args&... args)
	{
		std::stringstream sout;
		UTILITY::ConcatString(sout, args...);
		std::string out = sout.str();
		HFString output;
		output.SetString(sout.str());
		return output;
	};

};

std::ostream &operator << (std::ostream &out, const HFString& hfstring);