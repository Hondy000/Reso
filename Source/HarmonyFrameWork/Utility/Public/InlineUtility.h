/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Utility\InlineUtility.h
 *
 * @brief	Declares the inline utility class.
 **************************************************************************************************/

#pragma once
#include <string>
#include <random>
#include "../../Math/Public/HFMath.h"

namespace UTILITY
{
	inline FLOAT Rand(FLOAT min, FLOAT max)
	{
		std::random_device rd;

		std::mt19937 mt(rd());
		std::uniform_real_distribution<FLOAT> score(min, max);
		
		return score(mt);
	}

	inline void sincos(FLOAT x, FLOAT* outs, FLOAT* outc)
	{
		*outs = sin(x);
		*outc = cos(x);
	}

	inline HFVECTOR3 RandUnitVec3(void)
	{
		std::random_device rd;

		std::mt19937 mt(rd());
		std::uniform_real_distribution<FLOAT> score();
		UINT value = mt();
		UINT theta;
		FLOAT sin, cos;
		// pitch
		theta = (value & 0xFFFF0000);
		theta = (theta >> 9) | (theta >> 25) | 0x40000000;
		sincos((*(FLOAT*)&theta - 3.0f) * HF_PI, &sin, &cos);
		HFVECTOR3 out;
		out.x = cos;
		out.y = cos;
		out.z = -sin;
		// yaw
		theta = (value & 0x0000FFFF);
		theta = (theta << 7) | (theta >> 9) | 0x40000000;
		sincos((*(FLOAT*)&theta - 3.0f) *HF_PI, &sin, &cos);
		out.x *= cos;
		out.y *= sin;
		return out;
	}

	

}
