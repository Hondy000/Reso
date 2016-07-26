#include "..\Public\HFString.h"

HFString::HFString() {};

HFString::~HFString()
{

}
HFString::HFString(const HFString & str)
{
	m_string = str.GetString();
	m_wString = str.GetWString();
}
std::ostream &operator << (std::ostream &out, const HFString& hfstring)
{
	out << hfstring.GetString();
	return out;
}
