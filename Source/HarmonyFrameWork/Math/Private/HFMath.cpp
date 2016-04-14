#include "../Public/DirectXMath.h"
#include "../Public/HFMath.h"
#ifdef DIRECTX

HFVECTOR2::HFVECTOR2(FLOAT x, FLOAT y)
{
	this->x = x;
	this->y = y;
}

BOOL HFVECTOR2::operator!=(const HFVECTOR2& V) const
{
	if(this->x != V.x && this->y != V.y)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL HFVECTOR2::operator==(const HFVECTOR2& V) const
{

	if (this->x == V.x && this->y == V.y)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

HFVECTOR2 HFVECTOR2::operator/(FLOAT S) const
{
	return HFVECTOR2(x / S, y / S);
}

HFVECTOR2 HFVECTOR2::operator*(FLOAT S) const
{
	return HFVECTOR2(x * S, y * S);
}

HFVECTOR2 HFVECTOR2::operator-(const HFVECTOR2& V) const
{
	return HFVECTOR2(x - V.x, y - V.y);
}

HFVECTOR2 HFVECTOR2::operator+(const HFVECTOR2& V) const
{

	return HFVECTOR2(x + V.x, y + V.y);
}

HFVECTOR2 HFVECTOR2::operator-() const
{
	return HFVECTOR2(-x, -y);
}

HFVECTOR2 HFVECTOR2::operator+() const
{
	return HFVECTOR2(+x,+y);
}

HFVECTOR2& HFVECTOR2::operator+=(const HFVECTOR2& V)
{
	this->x += V.x;
	this->y += V.y;
	return *this;
}

HFVECTOR2& HFVECTOR2::operator-=(const HFVECTOR2& V)
{
	this->x -= V.x;
	this->y -= V.y;
	return *this;

}

HFVECTOR2& HFVECTOR2::operator*=(FLOAT S)
{

	this->x *= S;
	this->y *= S;
	return *this;
}

HFVECTOR2& HFVECTOR2::operator/=(FLOAT S)
{
	this->x /= S;
	this->y /= S;
	return *this;

}
HFVECTOR2 operator* (FLOAT S, const HFVECTOR2& V)
{
	HFVECTOR2 r = V *  S;
	return r;
}

HFVECTOR3 operator*(FLOAT S, const HFVECTOR3 &V)
{
	return V * S;
}

HFVECTOR3::HFVECTOR3(const HFVECTOR3&V)
{
	this->x = V.x;
	this->y = V.y;
	this->z = V.z;
}

HFVECTOR3::HFVECTOR3(FLOAT x, FLOAT y, FLOAT z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
#ifdef DIRECTXTK	 
HFVECTOR3::HFVECTOR3(const DirectX::SimpleMath::Vector3&V)
{
	this->x = V.x;
	this->y = V.y;
	this->z = V.z;
}
#endif // DIRECTXTK

BOOL HFVECTOR3::operator!=(const HFVECTOR3&V) const
{
	if (this->x != V.x && this->y != V.y && this->z != V.z)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

#ifdef DIRECTXTK	   
HFVECTOR3::operator DirectX::SimpleMath::Vector3()
{
	return DirectX::SimpleMath::Vector3(x, y, z);
}
#endif

BOOL HFVECTOR3::operator==(const HFVECTOR3&V) const
{
	if (this->x == V.x && this->y == V.y && this->z == V.z)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

HFVECTOR3 HFVECTOR3::operator/(FLOAT S) const
{
	return HFVECTOR3(x / S, y / S, z / S);
}

HFVECTOR3 HFVECTOR3::operator*(FLOAT S) const
{
	return HFVECTOR3(x * S, y * S, z * S);
}

HFVECTOR3 HFVECTOR3::operator-(const HFVECTOR3&V) const
{
	return HFVECTOR3(this->x - V.x, this->y - V.y, this->z - V.z);
}

HFVECTOR3 HFVECTOR3::operator+(const HFVECTOR3&V) const
{
	return HFVECTOR3(this->x + V.x, this->y + V.y, this->z + V.z);
}

HFVECTOR3 & HFVECTOR3::operator+=(const HFVECTOR3 &V)
{
	this->x += V.x;
	this->y += V.y;
	this->z += V.z;
	return *this;
}

HFVECTOR3 & HFVECTOR3::operator-=(const HFVECTOR3 &V)
{
	this->x -= V.x;
	this->y -= V.y;
	this->z -= V.z;
	return *this;
}

HFVECTOR3 & HFVECTOR3::operator*=(FLOAT S)
{
	this->x *= S;
	this->y *= S;
	this->z *= S;
	return *this;
}


HFVECTOR3& HFVECTOR3::operator/=(FLOAT S)
{
	this->x /= S;
	this->y /= S;
	this->z /= S;
	return *this;
}

HFVECTOR3 HFVECTOR3::operator+() const
{
	return HFVECTOR3(+x,+y,+z);
}

HFVECTOR3 HFVECTOR3::operator-() const
{
	return HFVECTOR3(-x, -y, -z);
}
HFVECTOR4::HFVECTOR4(const HFVECTOR3 & xyz, FLOAT w)
{
	this->x = xyz.x;
	this->y = xyz.y;
	this->z = xyz.z;
	this->w = w;
}

HFVECTOR4::HFVECTOR4(FLOAT x, FLOAT y, FLOAT z, FLOAT w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

BOOL HFVECTOR4::operator==(const HFVECTOR4& v) const
{				  
	if (this->x == v.x && this->y == v.y &&this->z == v.z &&this->w == v.w)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL HFVECTOR4::operator!=(const HFVECTOR4 &v) const
{
	if (this->x != v.x && this->y != v.y &&this->z != v.z &&this->w != v.w)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

HFVECTOR4& HFVECTOR4::operator+=(const HFVECTOR4&V)
{
	this->x += V.x;
	this->y += V.y;
	this->z += V.z;
	this->w += V.w;
	return *this;
}

HFVECTOR4& HFVECTOR4::operator-=(const HFVECTOR4&V)
{
	this->x -= V.x;
	this->y -= V.y;
	this->z -= V.z;
	this->w -= V.w;
	return *this;
}

HFVECTOR4 & HFVECTOR4::operator*=(FLOAT s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	this->w *= s;
	return *this;
}

HFVECTOR4 & HFVECTOR4::operator/=(FLOAT s)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
	this->w /= s;
	return *this;
}

HFVECTOR4 HFVECTOR4::operator+() const
{
	return HFVECTOR4(+x,+y,+z,+w);
}

HFVECTOR4 HFVECTOR4::operator-() const
{
	return HFVECTOR4(-x, -y, -z, -w);
}

HFVECTOR4 HFVECTOR4::operator+(const HFVECTOR4 &V) const
{
	return HFVECTOR4(this->x+  V.x, this->y + V.y, this->z + V.z, this->w + V.w);
}

HFVECTOR4 HFVECTOR4::operator-(const HFVECTOR4 &V) const
{
	return HFVECTOR4(this->x - V.x, this->y - V.y, this->z - V.z, this->w - V.w);
}

HFVECTOR4 HFVECTOR4::operator*(FLOAT s) const
{
	return HFVECTOR4(this->x * s, this->y * s, this->z * s, this->w * s);
}

HFVECTOR4 HFVECTOR4::operator/(FLOAT s) const
{
	return HFVECTOR4(this->x / s, this->y / s, this->z / s, this->w / s);
}


HFVECTOR4 operator*(FLOAT s, const HFVECTOR4 & v)
{
	return HFVECTOR4(v.x * s, v.y * s, v.z * s, v.w * s);
}

HFMATRIX operator*(FLOAT, const HFMATRIX &)
{
	return HFMATRIX();
}

HFMATRIX::HFMATRIX(FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14, FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24, FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34, FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44)
{
	this->_11 = _11;
	this->_12 = _12;
	this->_13 = _13;
	this->_14 = _14;

	this->_21 = _21;
	this->_22 = _22;
	this->_23 = _23;
	this->_24 = _24;

	this->_31 = _31;
	this->_32 = _32;
	this->_33 = _33;
	this->_34 = _34;

	this->_41 = _41;
	this->_42 = _42;
	this->_43 = _43;
	this->_44 = _44;
}
FLOAT & HFMATRIX::operator()(UINT Row, UINT Col)
{
	return m[Row][Col];
}


FLOAT HFMATRIX::operator()(UINT Row, UINT Col) const
{
	return m[Row][Col];
}

HFMATRIX HFMATRIX::operator/(FLOAT s) const
{
	return HFMATRIX(
		_11 / s, _12 / s, _13 / s, _14 / s,
		_21 / s, _22 / s, _23 / s, _24 / s,
		_31 / s, _32 / s, _33 / s, _34 / s,
		_41 / s, _42 / s, _43 / s, _44 / s
		);
}

#ifdef DIRECTXSDK
HFMATRIX::operator D3DXMATRIX()
{
	D3DXMATRIX mat =  D3DXMATRIX(
		_11, _12, _13, _14,
		_21, _22, _23, _24,
		_31, _32, _33, _34,
		_41, _42, _43, _44
		);
	return mat;
}
#endif // DIRECTXSDK

HFMATRIX HFMATRIX::operator*(FLOAT s) const
{

	return HFMATRIX(
		_11*s, _12*s, _13*s, _14*s,
		_21*s, _22*s, _23*s, _24*s,
		_31*s, _32*s, _33*s, _34*s,
		_41*s, _42*s, _43*s, _44*s
		);
}

HFMATRIX& HFMATRIX::operator*=(const HFMATRIX&M2)
{
	HFMATRIX M1 = *this;

	FLOAT x = M1.m[0][0];
	FLOAT y = M1.m[0][1];
	FLOAT z = M1.m[0][2];
	FLOAT w = M1.m[0][3];

	this->m[0][0] = (M2.m[0][0] * x) + (M2.m[1][0] * y) + (M2.m[2][0] * z) + (M2.m[3][0] * w);
	this->m[0][1] = (M2.m[0][1] * x) + (M2.m[1][1] * y) + (M2.m[2][1] * z) + (M2.m[3][1] * w);
	this->m[0][2] = (M2.m[0][2] * x) + (M2.m[1][2] * y) + (M2.m[2][2] * z) + (M2.m[3][2] * w);
	this->m[0][3] = (M2.m[0][3] * x) + (M2.m[1][3] * y) + (M2.m[2][3] * z) + (M2.m[3][3] * w);

	x = M1.m[1][0];
	y = M1.m[1][1];
	z = M1.m[1][2];
	w = M1.m[1][3];
	this->m[1][0] = (M2.m[0][0] * x) + (M2.m[1][0] * y) + (M2.m[2][0] * z) + (M2.m[3][0] * w);
	this->m[1][1] = (M2.m[0][1] * x) + (M2.m[1][1] * y) + (M2.m[2][1] * z) + (M2.m[3][1] * w);
	this->m[1][2] = (M2.m[0][2] * x) + (M2.m[1][2] * y) + (M2.m[2][2] * z) + (M2.m[3][2] * w);
	this->m[1][3] = (M2.m[0][3] * x) + (M2.m[1][3] * y) + (M2.m[2][3] * z) + (M2.m[3][3] * w);
	x = M1.m[2][0];
	y = M1.m[2][1];
	z = M1.m[2][2];
	w = M1.m[2][3];
	this->m[2][0] = (M2.m[0][0] * x) + (M2.m[1][0] * y) + (M2.m[2][0] * z) + (M2.m[3][0] * w);
	this->m[2][1] = (M2.m[0][1] * x) + (M2.m[1][1] * y) + (M2.m[2][1] * z) + (M2.m[3][1] * w);
	this->m[2][2] = (M2.m[0][2] * x) + (M2.m[1][2] * y) + (M2.m[2][2] * z) + (M2.m[3][2] * w);
	this->m[2][3] = (M2.m[0][3] * x) + (M2.m[1][3] * y) + (M2.m[2][3] * z) + (M2.m[3][3] * w);
	x = M1.m[3][0];
	y = M1.m[3][1];
	z = M1.m[3][2];
	w = M1.m[3][3];
	this->m[3][0] = (M2.m[0][0] * x) + (M2.m[1][0] * y) + (M2.m[2][0] * z) + (M2.m[3][0] * w);
	this->m[3][1] = (M2.m[0][1] * x) + (M2.m[1][1] * y) + (M2.m[2][1] * z) + (M2.m[3][1] * w);
	this->m[3][2] = (M2.m[0][2] * x) + (M2.m[1][2] * y) + (M2.m[2][2] * z) + (M2.m[3][2] * w);
	this->m[3][3] = (M2.m[0][3] * x) + (M2.m[1][3] * y) + (M2.m[2][3] * z) + (M2.m[3][3] * w);
	return *this;
}

HFMATRIX & HFMATRIX::operator+=(const HFMATRIX &m)
{
	this->_11 += m._11;
	this->_12 += m._12;
	this->_13 += m._13;
	this->_14 += m._14;

	this->_21 += m._21;
	this->_22 += m._22;
	this->_23 += m._23;
	this->_24 += m._24;

	this->_31 += m._31;
	this->_32 += m._32;
	this->_33 += m._33;
	this->_34 += m._34;

	this->_41 += m._41;
	this->_42 += m._42;
	this->_43 += m._43;
	this->_44 += m._44;
	return *this;
}

HFMATRIX & HFMATRIX::operator-=(const HFMATRIX &m)
{
	this->_11 -= m._11;
	this->_12 -= m._12;
	this->_13 -= m._13;
	this->_14 -= m._14;

	this->_21 -= m._21;
	this->_22 -= m._22;
	this->_23 -= m._23;
	this->_24 -= m._24;

	this->_31 -= m._31;
	this->_32 -= m._32;
	this->_33 -= m._33;
	this->_34 -= m._34;

	this->_41 -= m._41;
	this->_42 -= m._42;
	this->_43 -= m._43;
	this->_44 -= m._44;
	return *this;
}

HFMATRIX & HFMATRIX::operator*=(FLOAT s)
{
	this->_11 *= s;
	this->_12 *= s;
	this->_13 *= s;
	this->_14 *= s;

	this->_21 *= s;
	this->_22 *= s;
	this->_23 *= s;
	this->_24 *= s;

	this->_31 *= s;
	this->_32 *= s;
	this->_33 *= s;
	this->_34 *= s;

	this->_41 *= s;
	this->_42 *= s;
	this->_43 *= s;
	this->_44 *= s;
	return *this;
}

HFMATRIX & HFMATRIX::operator/=(FLOAT s)
{
	this->_11 /= s;
	this->_12 /= s;
	this->_13 /= s;
	this->_14 /= s;

	this->_21 /= s;
	this->_22 /= s;
	this->_23 /= s;
	this->_24 /= s;

	this->_31 /= s;
	this->_32 /= s;
	this->_33 /= s;
	this->_34 /= s;

	this->_41 /= s;
	this->_42 /= s;
	this->_43 /= s;
	this->_44 /= s;
	return *this;
}

HFMATRIX HFMATRIX::operator+() const
{
	return HFMATRIX(
		+_11, +_12, +_13, +_14,
		+_21, +_22, +_23, +_24,
		+_31, +_32, +_33, +_34,
		+_41, +_42, +_43, +_44
		);
}

HFMATRIX HFMATRIX::operator-() const
{
	return HFMATRIX(
		-_11, -_12, -_13, -_14,
		-_21, -_22, -_23, -_24,
		-_31, -_32, -_33, -_34,
		-_41, -_42, -_43, -_44
		);
}

HFMATRIX HFMATRIX::operator*(const HFMATRIX &m) const
{
	return HFMatrixMultiply(*this, m);
}

HFMATRIX HFMATRIX::operator+(const HFMATRIX & m) const
{
	return HFMatrixAdd(*this, m);
}

HFMATRIX HFMATRIX::operator-(const HFMATRIX &m) const
{
	return HFMatrixSubtruct(*this, m);
}




FLOAT HFVec2Length
(const HFVECTOR2 *pV)
{
	return sqrt(pV->x*pV->x + pV->y*pV->y);
};

FLOAT HFVec2LengthSq
(const HFVECTOR2 *pV)
{
	return (pV->x*pV->x + pV->y*pV->y);
};

FLOAT HFVec2Dot
(const HFVECTOR2 *pV1, const HFVECTOR2 *pV2)
{
	return pV1->x *pV2->x + pV1->y *pV2->y;
};

// Z component of ((x1,y1,0) cross (x2,y2,0))
FLOAT HFVec2CCW
(const HFVECTOR2 *pV1, const HFVECTOR2 *pV2)
{
	return pV1->x * pV2->y - pV1->y * pV2->x;
};

HFVECTOR2* HFVec2Add
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2)
{
	*pOut = *pV1 + *pV2;
	return pOut;
};

HFVECTOR2* HFVec2Subtract
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2)
{
	*pOut = *pV1 - *pV2;
	return pOut;
};

// Minimize each component.  x = min(x1, x2), y = min(y1, y2)
HFVECTOR2* HFVec2Minimize
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2)
{
	if (pOut&&pV1&&pV2)
	{

		if (pV1->x < pV2->x)
		{
			pOut->x = pV1->x;
		}
		else
		{
			pOut->x = pV2->x;
		}

		if (pV1->y < pV2->y)
		{
			pOut->y = pV1->y;
		}
		else
		{
			pOut->y = pV2->y;
		}
	}
	return pOut;
};

// Maximize each component.  x = max(x1, x2), y = max(y1, y2)
HFVECTOR2* HFVec2Maximize
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2)
{
	if (pOut&&pV1&&pV2)
	{

		if (pV1->x > pV2->x)
		{
			pOut->x = pV1->x;
		}
		else
		{
			pOut->x = pV2->x;
		}

		if (pV1->y > pV2->y)
		{
			pOut->y = pV1->y;
		}
		else
		{
			pOut->y = pV2->y;
		}
	}
};

HFVECTOR2* HFVec2Scale
(HFVECTOR2 *pOut, const HFVECTOR2 *pV, FLOAT s)
{
	if (pOut&& pV)
	{
		*pOut = *pV * s;
	}
	return pOut;
};

// Linear interpolation. V1 + s(V2-V1)
HFVECTOR2* HFVec2Lerp
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2,
	FLOAT s)
{
	if (pOut&&pV1&&pV2)
	{
		*pOut = *pV1 + (*pV2 - *pV1)*s;
	}
	return pOut;
};

HFVECTOR2*  HFVec2Normalize
(HFVECTOR2 *pOut, const HFVECTOR2 *pV)
{
	if (pOut&& pV)
	{
		FLOAT sum = pV->x + pV->y;
		*pOut = *pV / sum;
	}
	return pOut;
};

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
HFVECTOR2*  HFVec2Hermite
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pT1,
	const HFVECTOR2 *pV2, const HFVECTOR2 *pT2, FLOAT s)
{
	*pOut = (2 * s * 3 - 3 * s * 2 + 1) * *pV1
		+ (-2 * s * 3 + 3 * s * 2) * *pV2 +
		(s * 3 - 2 * s * 2 + s)* *pT1 +
		(s * 3 - s * 2) * *pT2;
	return pOut;
};

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
HFVECTOR2*  HFVec2CatmullRom
(HFVECTOR2 *pOut, const HFVECTOR2 *pV0, const HFVECTOR2 *pV1,
	const HFVECTOR2 *pV2, const HFVECTOR2 *pV3, FLOAT s)
{
	*pOut = (
		(-s * 3 + 2 * s * 2 - s) * *pV0
		+ (3 * s * 3 - 5 * s * 2 + 2)* *pV1
		+ (-3 * s * 3 + 4 * s * 2 + s) * *pV2
		+ (s * 3 - s * 2)* *pV3
		) / 2;
	return pOut;
};

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
HFVECTOR2*  HFVec2BaryCentric
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2,
	const HFVECTOR2 *pV3, FLOAT f, FLOAT g)
{
	*pOut = *pV1 + f * (*pV2 - *pV1) + g * (*pV3 - *pV1);
	return pOut;
};

// Transform (x, y, 0, 1) by matrix.
HFVECTOR4*  HFVec2Transform
(HFVECTOR4 *pOut, const HFVECTOR2 *pV, const HFMATRIX *pM)
{
	HFMATRIX temp;
	HFMatrixTranslation(&temp, pV->x, pV->x, 0);
	temp *= *pM;
	pOut->x = temp._41;
	pOut->y = temp._42;
	pOut->z = temp._43;
	pOut->w = temp._44;

	return pOut;
};

HFVECTOR2* HFVec2TransformCoord(HFVECTOR2 *pOut, const HFVECTOR2 *pV, const HFMATRIX *pM)
{
	HFMATRIX temp;
	HFMatrixTranslation(&temp, pV->x, pV->x, 0);
	temp *= *pM;
	pOut->x = 1 / temp._41;
	pOut->y = 1 / temp._42;
	return pOut;
};
//--------------------------
// 3D Vector
//--------------------------

// inline

FLOAT HFVec3Length
(const HFVECTOR3 *pV)
{
	return sqrt(pV->x*pV->x + pV->y*pV->y + pV->z * pV->z);
};

FLOAT HFVec3LengthSq
(const HFVECTOR3 *pV)
{
	return (pV->x*pV->x + pV->y*pV->y + pV->z * pV->z);
};

FLOAT HFVec3Dot
(const HFVECTOR3 *pV1, const HFVECTOR3 *pV2)
{
	return pV1->x * pV2->x + pV1->y * pV2->y + pV1->z * pV2->z;
};

HFVECTOR3* HFVec3Cross
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2)
{
	pOut->x = pV1->y *pV2->z - pV1->z *pV2->y;
	pOut->y = pV1->z *pV2->x - pV1->x *pV2->z;
	pOut->z = pV1->x *pV2->y - pV1->y *pV2->x;
	return pOut;
};

HFVECTOR3* HFVec3Add
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2)
{
	*pOut = *pV1 + *pV2;
	return pOut;
};

HFVECTOR3* HFVec3Subtract
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2)
{
	*pOut = *pV1 - *pV2;
	return pOut;
};

// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
HFVECTOR3* HFVec3Minimize
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2)
{
	pOut->x = min(pV1->x, pV2->x);
	pOut->y = min(pV1->y, pV2->y);
	pOut->z = min(pV1->z, pV2->z);
	return pOut;
};

// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
HFVECTOR3* HFVec3Maximize
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2)
{
	pOut->x = max(pV1->x, pV2->x);
	pOut->y = max(pV1->y, pV2->y);
	pOut->z = max(pV1->z, pV2->z);
	return pOut;
};

HFVECTOR3* HFVec3Scale
(HFVECTOR3 *pOut, const HFVECTOR3 *pV, FLOAT s)
{
	if (pOut&& pV)
	{
		*pOut = *pV * s;
	}
	return pOut;
};

// Linear interpolation. V1 + s(V2-V1)
HFVECTOR3* HFVec3Lerp
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2,
	FLOAT s)
{
	if (pOut&&pV1&&pV2)
	{
		*pOut = *pV1 + (*pV2 - *pV1)*s;
	}
	return pOut;
};

HFVECTOR3*  HFVec3Normalize
(HFVECTOR3 *pOut, const HFVECTOR3 *pV)
{
	if (pOut&& pV)
	{
		FLOAT sum = HFVec3Length(pV);
		*pOut = *pV / sum;
	}
	return pOut;
};

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
HFVECTOR3*  HFVec3Hermite
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pT1,
	const HFVECTOR3 *pV2, const HFVECTOR3 *pT2, FLOAT s)
{
	*pOut = (2 * s * 3 - 3 * s * 2 + 1) * *pV1
		+ (-2 * s * 3 + 3 * s * 2) * *pV2 +
		(s * 3 - 2 * s * 2 + s)* *pT1 +
		(s * 3 - s * 2) * *pT2;
	return pOut;
};

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
HFVECTOR3*  HFVec3CatmullRom
(HFVECTOR3 *pOut, const HFVECTOR3 *pV0, const HFVECTOR3 *pV1,
	const HFVECTOR3 *pV2, const HFVECTOR3 *pV3, FLOAT s)
{
	*pOut = (
		(-s * 3 + 2 * s * 2 - s) * *pV0
		+ (3 * s * 3 - 5 * s * 2 + 2)* *pV1
		+ (-3 * s * 3 + 4 * s * 2 + s) * *pV2
		+ (s * 3 - s * 2)* *pV3
		) / 2;
	return pOut;
}
// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
HFVECTOR3*  HFVec3BaryCentric
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2,
	const HFVECTOR3 *pV3, FLOAT f, FLOAT g)
{
	*pOut = *pV1 + f * (*pV2 - *pV1) + g * (*pV3 - *pV1);
	return pOut;
};

// Transform (x, y, z, 1) by matrix.
HFVECTOR4*  HFVec3Transform
(HFVECTOR4 *pOut, const HFVECTOR3 *pV, const HFMATRIX *pM)	  
{
	HFMATRIX temp;
	HFMatrixTranslation(&temp, pV->x, pV->x, 0);
	temp *= *pM;
	pOut->x = temp._41;
	pOut->y = temp._42;
	pOut->z = temp._43;
	pOut->w = temp._44;

	return pOut;
};

// Transform (x, y, z, 1) by matrix, project result back into w=1.
HFVECTOR3*  HFVec3TransformCoord
(HFVECTOR3 *pOut, const HFVECTOR3 *pV, const HFMATRIX *pM)
{
	HFMATRIX temp;
	HFMatrixTranslation(&temp, pV->x, pV->y, pV->z);
	temp *= *pM;
	pOut->x = 1 / temp._41;
	if (isinf( pOut->x))
	{
		pOut->x = 0;
	}
	pOut->y = 1 / temp._42;
	if (isinf(pOut->y))
	{
		pOut->y = 0;
	}
	pOut->z = 1 / temp._43;
	if (isinf(pOut->z))
	{
		pOut->z = 0;
	}
	return pOut;
};

FLOAT HFVec4Length(const HFVECTOR4 *pV)
{
	return sqrt(pV->x*pV->x + pV->y*pV->y + pV->z * pV->z + pV->w * pV->w);
}

FLOAT HFVec4LengthSq(const HFVECTOR4 *pV)
{
	return (pV->x*pV->x + pV->y*pV->y + pV->z * pV->z + pV->w * pV->w);
}

FLOAT HFVec4Dot(const HFVECTOR4 *pV1, const HFVECTOR4 *pV2)
{
	return pV1->x *pV2->x + pV1->y *pV2->y + pV1->z *pV2->z + pV1->w *pV2->w;
}

HFVECTOR4* HFVec4Add(HFVECTOR4 *pOut, const HFVECTOR4 *pV1, const HFVECTOR4 *pV2)
{
	pOut->x = pV1->x + pV2->x;
	pOut->y = pV1->y + pV2->y;
	pOut->z = pV1->z + pV2->z;
	pOut->w = pV1->w + pV2->w;
	return pOut;
}

HFVECTOR4* HFVec4Subtract(HFVECTOR4 *pOut, const HFVECTOR4 *pV1, const HFVECTOR4 *pV2)
{
	pOut->x = pV1->x - pV2->x;
	pOut->y = pV1->y - pV2->y;
	pOut->z = pV1->z - pV2->z;
	pOut->w = pV1->w - pV2->w;
	return pOut;
}

HFVECTOR4* HFVec4Minimize(HFVECTOR4 *pOut, const HFVECTOR4 *pV1, const HFVECTOR4 *pV2)
{
	pOut->x = min(pV1->x, pV2->x);
	pOut->y = min(pV1->y, pV2->y);
	pOut->z = min(pV1->z, pV2->z);
	pOut->w = min(pV1->w, pV2->w);
	return pOut;
}

HFVECTOR4* HFVec4Maximize(HFVECTOR4 *pOut, const HFVECTOR4 *pV1, const HFVECTOR4 *pV2)
{
	pOut->x = max(pV1->x, pV2->x);
	pOut->y = max(pV1->y, pV2->y);
	pOut->z = max(pV1->z, pV2->z);
	pOut->w = max(pV1->w, pV2->w);
	return pOut;
}

HFVECTOR4* HFVec4Scale(HFVECTOR4 *pOut, const HFVECTOR4 *pV, FLOAT s)
{
	if (pOut&& pV)
	{
		*pOut = *pV * s;
	}
	return pOut;
}





//--------------------------
// 4D Matrix
//--------------------------

// inline

HFMATRIX* HFMatrixIdentity(HFMATRIX *pOut)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			pOut->m[i][j] = (i == j) ? 1.0 : 0.0;
		}
	}
	return pOut;
};

BOOL HFMatrixIsIdentity(const HFMATRIX *pM)
{
	if (
		pM->_11 == 1 &&
		pM->_12 == 0 &&
		pM->_13 == 0 &&
		pM->_14 == 0 &&
		pM->_21 == 0 &&
		pM->_22 == 1 &&
		pM->_23 == 0 &&
		pM->_24 == 0 &&
		pM->_31 == 0 &&
		pM->_32 == 0 &&
		pM->_33 == 1 &&
		pM->_34 == 0 &&
		pM->_41 == 0 &&
		pM->_42 == 0 &&
		pM->_43 == 0 &&
		pM->_44 == 1
		)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
};

FLOAT  HFMatrixDeterminant(const HFMATRIX *pM)
{	DOUBLE det = 1.0, buf;
	int n = 4;  //配列の次数
	int i, j, k;
	HFMATRIX temp = *pM;

	//三角行列を作成
	for (i = 0; i < 4; i++) 
	{
		for (j = 0; j < 4; j++) 
		{
			if (i < j) 
			{
				buf = temp.m[j][i] / temp.m[i][i];
				for (k = 0; k < n; k++)
				{
					temp.m[j][k] -= temp.m[i][k] * buf;
				}
			}
		}
	}

	//対角部分の積
	for (i = 0; i < n; i++)
	{
		det *= temp.m[i][i];
	}

	return det;
};

HRESULT  HFMatrixDecompose
(HFVECTOR3 *pOutScale, HFQUATERNION *pOutRotation,
	HFVECTOR3 *pOutTranslation, const HFMATRIX *pM)
{
	pOutScale->x = pM->_11;
	pOutScale->y = pM->_22;
	pOutScale->z = pM->_33;
	
	HFQuaternionRotationMatrix(pOutRotation, pM);
	pOutTranslation->x = pM->_41;
	pOutTranslation->y = pM->_42;
	pOutTranslation->z = pM->_43;
	return S_OK;
};

HFMATRIX*  HFMatrixTranspose
(HFMATRIX *pOut, const HFMATRIX *pM)
{
	pOut->_11 = pM->_11;
	pOut->_12 = pM->_21;
	pOut->_13 = pM->_31;
	pOut->_14 = pM->_41;

	pOut->_21 = pM->_12;
	pOut->_22 = pM->_22;
	pOut->_23 = pM->_32;
	pOut->_24 = pM->_42;

	pOut->_31 = pM->_13;
	pOut->_32 = pM->_23;
	pOut->_33 = pM->_33;
	pOut->_34 = pM->_43;

	pOut->_41 = pM->_14;
	pOut->_42 = pM->_24;
	pOut->_43 = pM->_34;
	pOut->_44 = pM->_44;
	
	return pOut;
};

HFMATRIX HFMatrixTranspose(const HFMATRIX M)
{

	HFMATRIX r;
	r._11 = M._11;
	r._12 = M._21;
	r._13 = M._31;
	r._14 = M._41;

	r._21 = M._12;
	r._22 = M._22;
	r._23 = M._32;
	r._24 = M._42;

	r._31 = M._13;
	r._32 = M._23;
	r._33 = M._33;
	r._34 = M._43;

	r._41 = M._14;
	r._42 = M._24;
	r._43 = M._34;
	r._44 = M._44;
	return r;
}

HFMATRIX HFMatrixAdd(const HFMATRIX M1, const HFMATRIX M2)
{
	HFMATRIX mResult;
	mResult._11 = M1._11 + M2._11;
	mResult._12 = M1._12 + M2._12;
	mResult._13 = M1._13 + M2._13;
	mResult._14 = M1._14 + M2._14;

	mResult._21 = M1._21 + M2._21;
	mResult._22 = M1._22 + M2._22;
	mResult._23 = M1._23 + M2._23;
	mResult._24 = M1._24 + M2._24;

	mResult._31 = M1._31 + M2._31;
	mResult._32 = M1._32 + M2._32;
	mResult._33 = M1._33 + M2._33;
	mResult._34 = M1._34 + M2._34;

	mResult._41 = M1._41 + M2._41;
	mResult._42 = M1._42 + M2._42;
	mResult._43 = M1._43 + M2._43;
	mResult._44 = M1._44 + M2._44;
	return mResult;
}

HFMATRIX HFMatrixSubtruct(const HFMATRIX M1, const HFMATRIX M2)
{

	HFMATRIX mResult;
	mResult._11 = M1._11 - M2._11;
	mResult._12 = M1._12 - M2._12;
	mResult._13 = M1._13 - M2._13;
	mResult._14 = M1._14 - M2._14;

	mResult._21 = M1._21 - M2._21;
	mResult._22 = M1._22 - M2._22;
	mResult._23 = M1._23 - M2._23;
	mResult._24 = M1._24 - M2._24;

	mResult._31 = M1._31 - M2._31;
	mResult._32 = M1._32 - M2._32;
	mResult._33 = M1._33 - M2._33;
	mResult._34 = M1._34 - M2._34;

	mResult._41 = M1._41 - M2._41;
	mResult._42 = M1._42 - M2._42;
	mResult._43 = M1._43 - M2._43;
	mResult._44 = M1._44 - M2._44;
	return mResult;
}

// Matrix multiplication.  The result represents the transformation M2
// followed by the transformation M1.  (Out = M1 * M2)
HFMATRIX  HFMatrixMultiply
( const HFMATRIX M1, const HFMATRIX M2)
{

	HFMATRIX mResult;
	// Cache the invariants in registers
	FLOAT x = M1.m[0][0];
	FLOAT y = M1.m[0][1];
	FLOAT z = M1.m[0][2];
	FLOAT w = M1.m[0][3];
	// Perform the operation on the first row
	mResult.m[0][0] = (M2.m[0][0] * x) + (M2.m[1][0] * y) + (M2.m[2][0] * z) + (M2.m[3][0] * w);
	mResult.m[0][1] = (M2.m[0][1] * x) + (M2.m[1][1] * y) + (M2.m[2][1] * z) + (M2.m[3][1] * w);
	mResult.m[0][2] = (M2.m[0][2] * x) + (M2.m[1][2] * y) + (M2.m[2][2] * z) + (M2.m[3][2] * w);
	mResult.m[0][3] = (M2.m[0][3] * x) + (M2.m[1][3] * y) + (M2.m[2][3] * z) + (M2.m[3][3] * w);
	// Repeat for all the other rows
	x = M1.m[1][0];
	y = M1.m[1][1];
	z = M1.m[1][2];
	w = M1.m[1][3];
	mResult.m[1][0] = (M2.m[0][0] * x) + (M2.m[1][0] * y) + (M2.m[2][0] * z) + (M2.m[3][0] * w);
	mResult.m[1][1] = (M2.m[0][1] * x) + (M2.m[1][1] * y) + (M2.m[2][1] * z) + (M2.m[3][1] * w);
	mResult.m[1][2] = (M2.m[0][2] * x) + (M2.m[1][2] * y) + (M2.m[2][2] * z) + (M2.m[3][2] * w);
	mResult.m[1][3] = (M2.m[0][3] * x) + (M2.m[1][3] * y) + (M2.m[2][3] * z) + (M2.m[3][3] * w);
	x = M1.m[2][0];
	y = M1.m[2][1];
	z = M1.m[2][2];
	w = M1.m[2][3];
	mResult.m[2][0] = (M2.m[0][0] * x) + (M2.m[1][0] * y) + (M2.m[2][0] * z) + (M2.m[3][0] * w);
	mResult.m[2][1] = (M2.m[0][1] * x) + (M2.m[1][1] * y) + (M2.m[2][1] * z) + (M2.m[3][1] * w);
	mResult.m[2][2] = (M2.m[0][2] * x) + (M2.m[1][2] * y) + (M2.m[2][2] * z) + (M2.m[3][2] * w);
	mResult.m[2][3] = (M2.m[0][3] * x) + (M2.m[1][3] * y) + (M2.m[2][3] * z) + (M2.m[3][3] * w);
	x = M1.m[3][0];
	y = M1.m[3][1];
	z = M1.m[3][2];
	w = M1.m[3][3];
	mResult.m[3][0] = (M2.m[0][0] * x) + (M2.m[1][0] * y) + (M2.m[2][0] * z) + (M2.m[3][0] * w);
	mResult.m[3][1] = (M2.m[0][1] * x) + (M2.m[1][1] * y) + (M2.m[2][1] * z) + (M2.m[3][1] * w);
	mResult.m[3][2] = (M2.m[0][2] * x) + (M2.m[1][2] * y) + (M2.m[2][2] * z) + (M2.m[3][2] * w);
	mResult.m[3][3] = (M2.m[0][3] * x) + (M2.m[1][3] * y) + (M2.m[2][3] * z) + (M2.m[3][3] * w);
	return mResult;

	/*
	HFMATRIX mResult;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			// Multiply the row of A by the column of B to get the row, column of product.
			for (int inner = 0; inner < 2; inner++) {
				mResult.m[row][col] += M1.m[row][inner] * M2.m[inner][col];
			}
		}
	}
	return mResult;
	*/
};

// Matrix multiplication, followed by a transpose. (Out = T(M1 * M2))
HFMATRIX  HFMatrixMultiplyTranspose
(const HFMATRIX M1, const HFMATRIX M2)
{
	return HFMatrixTranspose(HFMatrixMultiply(M1,M2));
};

// Calculate inverse of matrix.  Inversion my fail, in which case NULL will
// be returned.  The determinant of pM is also returned it pfDeterminant
// is non-NULL.
HFMATRIX*  HFMatrixInverse
(HFMATRIX *pOut, FLOAT *pDeterminant, const HFMATRIX *pM)
{
	HFMATRIX temp = *pM;
	DOUBLE buf; //一時的なデータを蓄える
	int i, j, k; //カウンタ
	int n = 4;  //配列の次数

				//単位行列を作る
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			pOut->m[i][j] = (i == j) ? 1.0 : 0.0;
		}
	}
	//掃き出し法
	for (i = 0; i < n; i++) {
		buf = 1 / temp.m[i][i];
		for (j = 0; j < n; j++) {
			temp.m[i][j] *= buf;
			pOut->m[i][j] *= buf;
		}
		for (j = 0; j < n; j++) {
			if (i != j) {
				buf = temp.m[j][i];
				for (k = 0; k < n; k++) {
					temp.m[j][k] -= temp.m[i][k] * buf;
					pOut->m[j][k] -= pOut->m[i][k] * buf;
				}
			}
		}
	}
	return pOut;
};


// Build a matrix which scales by (sx, sy, sz)
HFMATRIX*  HFMatrixScaling
(HFMATRIX *pOut, FLOAT sx, FLOAT sy, FLOAT sz)
{
	HFMatrixIdentity(pOut);
	pOut->_11 = sx;
	pOut->_22 = sy;
	pOut->_33 = sz;
	return pOut;
};

// Build a matrix which translates by (x, y, z)
HFMATRIX*  HFMatrixTranslation
(HFMATRIX *pOut, FLOAT x, FLOAT y, FLOAT z)
{
	HFMatrixIdentity(pOut);
	pOut->_41 = x;
	pOut->_42 = y;
	pOut->_43 = z;
	return pOut;
};


// Build a matrix which rotates around the X axis
HFMATRIX*  HFMatrixRotationX
(HFMATRIX *pOut, FLOAT Angle)
{

	*pOut = HFMATRIX
		(
			1, 0, 0, 0,
			0, cos((Angle)), -sin((Angle)), 0,
			0, sin((Angle)), cos((Angle)), 0,
			0, 0, 0, 1
			);
	return pOut;
};

// Build a matrix which rotates around the Y axis
HFMATRIX*  HFMatrixRotationY
(HFMATRIX *pOut, FLOAT Angle)
{
	*pOut = HFMATRIX
		(
			cos((Angle)), 0, sin((Angle)), 0,
			0, 1, 0, 0,
			-sin((Angle)), 0, cos((Angle)), 0,
			0, 0, 0, 1
			);
	return pOut;
};

// Build a matrix which rotates around the Z axis
HFMATRIX*  HFMatrixRotationZ
(HFMATRIX *pOut, FLOAT Angle)
{
	*pOut = HFMATRIX
		(
			cos((Angle)), -sin((Angle)), 0, 0,
			sin((Angle)), cos((Angle)), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
			);
	return pOut;
};


HFMATRIX * HFMatrixRotationYawPitchRoll(HFMATRIX *pOut, FLOAT Yaw, FLOAT Pitch, FLOAT Roll)
{
	return HFMatrixRotationX(HFMatrixRotationX(HFMatrixRotationX(pOut, Yaw), Yaw), Yaw);

}

// Build a lookat matrix. (right-handed)
HFMATRIX*  HFMatrixLookAtRH
(HFMATRIX *pOut, const HFVECTOR3 *pEye, const HFVECTOR3 *pAt,
	const HFVECTOR3 *pUp)
{
	HFVECTOR3 temp;
	HFVECTOR3 zaxis = *HFVec3Normalize(&temp, &HFVECTOR3(*pEye - *pAt));
	HFVECTOR3 xaxis = *HFVec3Normalize(&temp, HFVec3Cross(&temp, (pUp), &zaxis));
	HFVECTOR3 yaxis = *HFVec3Cross(&temp, &zaxis, &xaxis);
	*pOut = HFMATRIX
		(
			xaxis.x, yaxis.x, zaxis.x, 0,
			xaxis.y, yaxis.y, zaxis.y, 0,
			xaxis.z, yaxis.z, zaxis.z, 0,
			-HFVec3Dot(&xaxis, pEye), -HFVec3Dot(&yaxis, pEye), -HFVec3Dot(&zaxis, pEye), 1
			);
	return pOut;
};

// Build a lookat matrix. (left-handed)
HFMATRIX*  HFMatrixLookAtLH
(HFMATRIX *pOut, const HFVECTOR3 *pEye, const HFVECTOR3 *pAt,
	const HFVECTOR3 *pUp)
{
	HFVECTOR3 temp;
	HFVECTOR3 zaxis = *HFVec3Normalize(&temp, &HFVECTOR3(*pAt - *pEye));
	HFVECTOR3 xaxis = *HFVec3Normalize(&temp,HFVec3Cross(&temp,(pUp), &zaxis));
	HFVECTOR3 yaxis = *HFVec3Cross(&temp, &zaxis, &xaxis);
	*pOut = HFMATRIX
		(
			xaxis.x, yaxis.x, zaxis.x, 0,
			xaxis.y, yaxis.y, zaxis.y, 0,
			xaxis.z, yaxis.z, zaxis.z, 0,
			-HFVec3Dot(&xaxis, pEye), -HFVec3Dot(&yaxis, pEye), -HFVec3Dot(&zaxis, pEye), 1
			);
	return pOut;
};

// Build a perspective projection matrix. (right-handed)
HFMATRIX*  HFMatrixPerspectiveRH
(HFMATRIX *pOut, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf)
{
	*pOut = HFMATRIX
		(
			2 * zn / w, 0, 0, 0,
			0, 2 * zn / h, 0, 0,
			0, 0, zf / (zn - zf), 1,
			0, 0, zn*zf / (zn - zf), 0
			);
	return pOut;
};

// Build a perspective projection matrix. (left-handed)
HFMATRIX*  HFMatrixPerspectiveLH
(HFMATRIX *pOut, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf)
{
	*pOut = 
	HFMATRIX(
		2 * zn / w, 0, 0, 0,
		0, 2 * zn / h, 0, 0,
		0, 0, zf / (zf - zn), 1,
		0, 0, zn*zf / (zn - zf), 0
		);
	return pOut;
};

// Build a perspective projection matrix. (right-handed)
HFMATRIX*  HFMatrixPerspectiveFovRH
(HFMATRIX *pOut, FLOAT fovy, FLOAT Aspect, FLOAT zn, FLOAT zf)
{
	FLOAT h = 1 / tan(fovy / 2);
	FLOAT w = h / Aspect;
	*pOut =
		HFMATRIX(
			w, 0, 0, 0,
			0, h, 0, 0,
			0, 0, zf / (zn - zf), -1,
			0, 0, zn*zf / (zn - zf), 0);
	return pOut;
};

// Build a perspective projection matrix. (left-handed)
HFMATRIX*  HFMatrixPerspectiveFovLH
(HFMATRIX *pOut, FLOAT fovy, FLOAT Aspect, FLOAT zn, FLOAT zf)
{
	FLOAT    h, w, Q;

	h = (FLOAT)1 / tan(fovy*0.5);   // 1/tan(x) == cot(x)
	w = (FLOAT)h / Aspect;  // 1/tan(x) == cot(x)
	Q = zf / (zf - zn);

	HFMATRIX ret;
	ZeroMemory(&ret, sizeof(ret));

	ret(0, 0) = w;
	ret(1, 1) = h;
	ret(2, 2) = Q;
	ret(3, 2) = -Q*zn;
	ret(2, 3) = 1;
	*pOut = ret;
	return pOut;
};
/*


void cot(
FLOAT* pSin,
FLOAT* pCos,
FLOAT  Value)
{

assert(pSin);

// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
FLOAT quotient = HF_PI /2 *Value;
if (Value >= 0.0f)
{
quotient = (FLOAT)((int)(quotient + 0.5f));
}
else
{
quotient = (FLOAT)((int)(quotient - 0.5f));
}
FLOAT y = Value - HF_PI*quotient;

// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
FLOAT sign;
if (y > HF_PI / 2)
{
y = HF_PI - y;
sign = -1.0f;
}
else if (y < -HF_PI / 2)
{
y = -HF_PI - y;
sign = -1.0f;
}
else
{
sign = +1.0f;
}

FLOAT y2 = y * y;

// 11-degree minimax approximation
*pSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

// 10-degree minimax approximation
FLOAT p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
*pCos = sign*p;
}
// Build a perspective projection matrix. (left-handed)
HFMATRIX*  HFMatrixPerspectiveFovLH
(HFMATRIX *pOut, FLOAT fovy, FLOAT Aspect, FLOAT zn, FLOAT zf)
{
FLOAT    SinFov;
FLOAT    CosFov;
cot(&SinFov,&CosFov, 0.5f * fovy);

FLOAT Height = CosFov / SinFov;
FLOAT Width = Height / Aspect;
FLOAT fRange = zf / (zf - zn);

HFMATRIX M;
pOut->m[0][0] = Width;
pOut->m[0][1] = 0.0f;
pOut->m[0][2] = 0.0f;
pOut->m[0][3] = 0.0f;

pOut->m[1][0] = 0.0f;
pOut->m[1][1] = Height;
pOut->m[1][2] = 0.0f;
pOut->m[1][3] = 0.0f;

pOut->m[2][0] = 0.0f;
pOut->m[2][1] = 0.0f;
pOut->m[2][2] = fRange;
pOut->m[2][3] = 1.0f;

pOut->m[3][0] = 0.0f;
pOut->m[3][1] = 0.0f;
pOut->m[3][2] = -fRange * zn;
pOut->m[3][3] = 0.0f;
return pOut;
};
*/
// Build an ortho projection matrix. (right-handed)
HFMATRIX*  HFMatrixOrthoRH
(HFMATRIX *pOut, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf)
{
	*pOut = 
	HFMATRIX(
		2 / w, 0, 0, 0,
		0, 2 / h, 0, 0,
		0, 0, 1 / (zn - zf), 0,
		0, 0, zn / (zn - zf), 1
		);
	return pOut;
};

// Build an ortho projection matrix. (left-handed)
HFMATRIX*  HFMatrixOrthoLH
(HFMATRIX *pOut, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf)
{
	*pOut =
		HFMATRIX(
			2 / w, 0, 0, 0,
			0, 2 / h, 0, 0,
			0, 0, 1 / (zf - zn), 0,
			0, 0, zn / (zn - zf), 1
			);
	return pOut;
};

// Build an ortho projection matrix. (right-handed)
HFMATRIX*  HFMatrixOrthoOffCenterRH
(HFMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn,
	FLOAT zf)
{

	*pOut =
		HFMATRIX(
			2 / (r - l), 0, 0, 0,
			0, 2 / (t - b), 0, 0,
			0, 0, 1 / (zn - zf), 0,
			(l + r) / (l - r), (t + b) / (b - t), zn / (zn - zf), 1
			);
	return pOut;
};

// Build an ortho projection matrix. (left-handed)
HFMATRIX*  HFMatrixOrthoOffCenterLH
(HFMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn,
	FLOAT zf)
{
	*pOut =
		HFMATRIX(
			2 / (r - l), 0, 0, 0,
			0, 2 / (t - b), 0, 0,
			0, 0, 1 / (zf - zn), 0,
			(l + r) / (l - r), (t + b) / (b - t), zn / (zn - zf), 1
			);
	return pOut;
};


//--------------------------
// Quaternion
//--------------------------

// inline					 

HFQUATERNION::HFQUATERNION(FLOAT x, FLOAT y, FLOAT z, FLOAT w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

FLOAT HFQuaternionLength
(const HFQUATERNION *pQ)
{
	return sqrt(pQ->x * pQ->x + pQ->y * pQ->y);
};

// Length squared, or "norm"
FLOAT HFQuaternionLengthSq
(const HFQUATERNION *pQ)
{
	return pQ->x * pQ->x + pQ->y * pQ->y;
};

FLOAT HFQuaternionDot
(const HFQUATERNION *pQ1, const HFQUATERNION *pQ2)
{
	return pQ1->x *pQ2->x + pQ1->y *pQ2->y + pQ1->z *pQ2->z + pQ1->w *pQ2->w;
};

// (0, 0, 0, 1)
HFQUATERNION* HFQuaternionIdentity
(HFQUATERNION *pOut)
{							  
	*pOut = HFQUATERNION(0, 0, 0, 1);
	return pOut;
};

BOOL HFQuaternionIsIdentity
(const HFQUATERNION *pQ)
{
	if (pQ->x == 0 && pQ->y == 0 && pQ->z == 0 && pQ->w == 1)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
};

// (-x, -y, -z, w)
HFQUATERNION* HFQuaternionConjugate
(HFQUATERNION *pOut, const HFQUATERNION *pQ)
{
	*pOut = HFQUATERNION(-pQ->x, -pQ->y ,- pQ->z, - pQ->w);
	return pOut;
};



void HFQuaternionToAxisAngle(const HFQUATERNION *pQ, HFVECTOR3 *pAxis, FLOAT *pAngle)
{

}

// Build a quaternion from a rotation matrix.
HFQUATERNION*  HFQuaternionRotationMatrix
(HFQUATERNION *pOut, const HFMATRIX *pM)
{
	// 最大成分を検索
	FLOAT elem[4]; // 0:x, 1:y, 2:z, 3:w
	elem[0] = pM->_11 - pM->_22 - pM->_33 + 1.0f;
	elem[1] = -pM->_11 + pM->_22 - pM->_33 + 1.0f;
	elem[2] = -pM->_11 - pM->_22 + pM->_33 + 1.0f;
	elem[3] = pM->_11 + pM->_22 + pM->_33 + 1.0f;

	unsigned biggestIndex = 0;
	for (int i = 1; i < 4; i++) {
		if (elem[i] > elem[biggestIndex])
			biggestIndex = i;
	}

	if (elem[biggestIndex] < 0.0f)
		return false; // 引数の行列に間違いあり！

					  // 最大要素の値を算出
	FLOAT *q[4] = { &pOut->x, &pOut->y, &pOut->z, &pOut->w };
	FLOAT v = sqrtf(elem[biggestIndex]) * 0.5f;
	*q[biggestIndex] = v;
	FLOAT mult = 0.25f / v;

	switch (biggestIndex) {
	case 0: // x
		*q[1] = (pM->_12 + pM->_21) * mult;
		*q[2] = (pM->_31 + pM->_13) * mult;
		*q[3] = (pM->_23 - pM->_32) * mult;
		break;
	case 1: // y
		*q[0] = (pM->_12 + pM->_21) * mult;
		*q[2] = (pM->_23 + pM->_32) * mult;
		*q[3] = (pM->_31 - pM->_13) * mult;
		break;
	case 2: // z
		*q[0] = (pM->_31 + pM->_13) * mult;
		*q[1] = (pM->_23 + pM->_32) * mult;
		*q[3] = (pM->_12 - pM->_21) * mult;
		break;
	case 3: // w
		*q[0] = (pM->_23 - pM->_32) * mult;
		*q[1] = (pM->_31 - pM->_13) * mult;
		*q[2] = (pM->_12 - pM->_21) * mult;
		break;
	}

	return pOut;
};




#endif
