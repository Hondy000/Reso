#include "..\Public\HFString.h"

HFString::HFString() {};

HFString::~HFString()
{

}
std::ostream &operator << (std::ostream &out, const HFString& hfstring)
{
	out << hfstring.GetString();
	return out;
}
