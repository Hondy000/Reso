#pragma once
#include <string>
#include "StringUtility.h"

class HFString
{
public:
	HFString(){};
	~HFString(){};



	HFString(TCHAR* str)
	{
		main = str;
	};

	HFString operator = (TCHAR *str)
	{
		main = str;
		return *this;
	}
	HFString operator = (std::string str)
	{
		main = str;
		return *this;
	}

	HFString operator = (std::wstring& str)
	{
		main = UTILITY::Narrow(str);
		return *this;
	}

	std::wstring& CastWString()
	{
		return UTILITY::Widen(main);
	}

	operator LPCTSTR()
	{
		return main.c_str();
	}

	operator LPCWSTR()
	{
		test =  UTILITY::Widen(main).c_str();
		return test.c_str();
	}

	operator TCHAR*()
	{
		return const_cast<TCHAR*>(main.c_str());
	}
private:
	std::string main;  std::wstring test;
};
