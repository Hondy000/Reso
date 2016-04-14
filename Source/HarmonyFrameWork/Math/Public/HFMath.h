#pragma once
#include <math.h>
#ifdef DIRECTX

#include "DirectXMath.h"   	   

#endif
#ifdef DIRECTXTK   
#include <SimpleMath.h>	  

#endif // WINDOWS10


// 他に数学ライブラリが存在しない,対応させていない場合

//===========================================================================
//
// General purpose utilities
//
//===========================================================================
#define HF_PI    ((FLOAT)  3.141592654f)
#define HF_1BYPI ((FLOAT)  0.318309886f)

#define HFToRadian( degree ) ((degree) * (HF_PI / 180.0f))
#define HFToDegree( radian ) ((radian) * (180.0f / HF_PI))

//===========================================================================
//
// 16 bit floating point numbers
//
//===========================================================================

#define HF_16F_DIG          3                // # of decimal digits of precision
#define HF_16F_EPSILON      4.8875809e-4f    // smallest such that 1.0 + epsilon != 1.0
#define HF_16F_MANT_DIG     11               // # of bits in mantissa
#define HF_16F_MAX          6.550400e+004    // max value
#define HF_16F_MAX_10_EXP   4                // max decimal exponent
#define HF_16F_MAX_EXP      15               // max binary exponent
#define HF_16F_MIN          6.1035156e-5f    // min positive value
#define HF_16F_MIN_10_EXP   (-4)             // min decimal exponent
#define HF_16F_MIN_EXP      (-14)            // min binary exponent
#define HF_16F_RADIX        2                // exponent radix
#define HF_16F_ROUNDS       1                // addition rounding: near



//===========================================================================
//
// Vectors
//
//===========================================================================

//--------------------------
// 2D Vector
//--------------------------
typedef struct HFVECTOR2
{
#ifdef __cplusplus
public:
	HFVECTOR2() {};
	HFVECTOR2(FLOAT x, FLOAT y);


	// assignment operators
	HFVECTOR2& operator += (const HFVECTOR2&);
	HFVECTOR2& operator -= (const HFVECTOR2&);
	HFVECTOR2& operator *= (FLOAT);
	HFVECTOR2& operator /= (FLOAT);

	// unary operators
	HFVECTOR2 operator + () const;
	HFVECTOR2 operator - () const;

	// binary operators
	HFVECTOR2 operator + (const HFVECTOR2&) const;
	HFVECTOR2 operator - (const HFVECTOR2&) const;
	HFVECTOR2 operator * (FLOAT) const;
	HFVECTOR2 operator / (FLOAT) const;

	friend HFVECTOR2 operator * (FLOAT, const HFVECTOR2&);

	BOOL operator == (const HFVECTOR2&) const;
	BOOL operator != (const HFVECTOR2&) const;

public:
#endif //__cplusplus
	FLOAT x, y;
} HFVECTOR2, *LPHFVECTOR2;



//--------------------------
// 3D Vector
//--------------------------

typedef struct HFVECTOR3
{
public:
	HFVECTOR3() {};
	HFVECTOR3(const HFVECTOR3&);
#if DIRECTXTK
	HFVECTOR3(const DirectX::SimpleMath::Vector3&);
#endif
	HFVECTOR3(FLOAT x, FLOAT y, FLOAT z);

	// assignment operators
	HFVECTOR3& operator += (const HFVECTOR3&);
	HFVECTOR3& operator -= (const HFVECTOR3&);
	HFVECTOR3& operator *= (FLOAT);
	HFVECTOR3& operator /= (FLOAT);

	// unary operators
	HFVECTOR3 operator + () const;
	HFVECTOR3 operator - () const;

	// binary operators
	HFVECTOR3 operator + (const HFVECTOR3&) const;
	HFVECTOR3 operator - (const HFVECTOR3&) const;
	HFVECTOR3 operator * (FLOAT) const;
	HFVECTOR3 operator / (FLOAT) const;

	friend HFVECTOR3 operator * (FLOAT, const struct HFVECTOR3&);

	BOOL operator == (const HFVECTOR3&) const;
	BOOL operator != (const HFVECTOR3&) const;

	// cast
#if DIRECTXTK
	operator DirectX::SimpleMath::Vector3 ();
#endif
	

public:

	FLOAT x;
	FLOAT y;
	FLOAT z;
} HFVECTOR3, *LPHFVECTOR3;



  //--------------------------
  // 4D Vector
  //--------------------------
typedef struct HFVECTOR4
{
#ifdef __cplusplus
public:
	HFVECTOR4() {};
	HFVECTOR4(const HFVECTOR3& xyz, FLOAT w);
	HFVECTOR4(FLOAT x, FLOAT y, FLOAT z, FLOAT w);

	// assignment operators
	HFVECTOR4& operator += (const HFVECTOR4&);
	HFVECTOR4& operator -= (const HFVECTOR4&);
	HFVECTOR4& operator *= (FLOAT);
	HFVECTOR4& operator /= (FLOAT);

	// unary operators
	HFVECTOR4 operator + () const;
	HFVECTOR4 operator - () const;

	// binary operators
	HFVECTOR4 operator + (const HFVECTOR4&) const;
	HFVECTOR4 operator - (const HFVECTOR4&) const;
	HFVECTOR4 operator * (FLOAT) const;
	HFVECTOR4 operator / (FLOAT) const;

	friend HFVECTOR4 operator * (FLOAT, const HFVECTOR4&);

	BOOL operator == (const HFVECTOR4&) const;
	BOOL operator != (const HFVECTOR4&) const;

public:
#endif //__cplusplus
	FLOAT x, y, z, w;
} HFVECTOR4, *LPHFVECTOR4;


   //===========================================================================
   //
   // Matrices
   //
   //===========================================================================
#ifdef __cplusplus
typedef struct HFMATRIX
{
public:
	HFMATRIX() {};
	HFMATRIX(FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
		FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
		FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
		FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44);
#ifdef DIRECTXTK
	HFMATRIX(DirectX::SimpleMath::Matrix mat)
	{
		this->_11 = mat._11;
		this->_12 = mat._12;
		this->_13 = mat._13;
		this->_14 = mat._14;

		this->_21 = mat._21;
		this->_22 = mat._22;
		this->_23 = mat._23;
		this->_24 = mat._24;

		this->_31 = mat._31;
		this->_32 = mat._32;
		this->_33 = mat._33;
		this->_34 = mat._34;

		this->_41 = mat._41;
		this->_42 = mat._42;
		this->_43 = mat._43;
		this->_44 = mat._44;
	};
#endif
	// access grants
	FLOAT& operator () (UINT Row, UINT Col);
	FLOAT  operator () (UINT Row, UINT Col) const;

	// assignment operators
	HFMATRIX& operator *= (const HFMATRIX&);
	HFMATRIX& operator += (const HFMATRIX&);
	HFMATRIX& operator -= (const HFMATRIX&);
	HFMATRIX& operator *= (FLOAT);
	HFMATRIX& operator /= (FLOAT);

	// unary operators
	HFMATRIX operator + () const;
	HFMATRIX operator - () const;

	// binary operators
	HFMATRIX operator * (const HFMATRIX&) const;
	HFMATRIX operator + (const HFMATRIX&) const;
	HFMATRIX operator - (const HFMATRIX&) const;
	HFMATRIX operator * (FLOAT) const;
	HFMATRIX operator / (FLOAT) const;

	friend HFMATRIX operator * (FLOAT, const HFMATRIX&);

	BOOL operator == (const HFMATRIX&) const;
	BOOL operator != (const HFMATRIX&) const;

	// cast 
#ifdef DIRECTXSDK		
	operator D3DXMATRIX();
#endif
public:

	// 列優先
	union {
		struct {
			FLOAT        _11, _12, _13, _14;
			FLOAT        _21, _22, _23, _24;
			FLOAT        _31, _32, _33, _34;
			FLOAT        _41, _42, _43, _44;
		};
		FLOAT m[4][4];
	};
} HFMATRIX, *LPHFMATRIX;




#else //!__cplusplus
typedef struct _HFMATRIX HFMATRIX, *LPHFMATRIX;
#endif //!__cplusplus


//===========================================================================
//
//    Quaternions
//
//===========================================================================
typedef struct HFQUATERNION
{
#ifdef __cplusplus
public:
	HFQUATERNION() {}
	HFQUATERNION(FLOAT x, FLOAT y, FLOAT z, FLOAT w);

	// assignment operators
	HFQUATERNION& operator += (const HFQUATERNION&);
	HFQUATERNION& operator -= (const HFQUATERNION&);
	HFQUATERNION& operator *= (const HFQUATERNION&);
	HFQUATERNION& operator *= (FLOAT);
	HFQUATERNION& operator /= (FLOAT);

	// unary operators
	HFQUATERNION  operator + () const;
	HFQUATERNION  operator - () const;

	// binary operators
	HFQUATERNION operator + (const HFQUATERNION&) const;
	HFQUATERNION operator - (const HFQUATERNION&) const;
	HFQUATERNION operator * (const HFQUATERNION&) const;
	HFQUATERNION operator * (FLOAT) const;
	HFQUATERNION operator / (FLOAT) const;

	friend HFQUATERNION operator * (FLOAT, const HFQUATERNION&);

	BOOL operator == (const HFQUATERNION&) const;
	BOOL operator != (const HFQUATERNION&) const;

#endif //__cplusplus
	FLOAT x, y, z, w;
} HFQUATERNION, *LPHFQUATERNION;




//===========================================================================
//
// D3DX math functions:
//
// NOTE:
//  * All these functions can take the same object as in and out parameters.
//
//  * Out parameters are typically also returned as return values, so that
//    the output of one function may be used as a parameter to another.
//
//===========================================================================



// function
//--------------------------
// 2D Vector
//--------------------------

// inline

inline FLOAT HFVec2Length
(const HFVECTOR2 *pV);

inline FLOAT HFVec2LengthSq
(const HFVECTOR2 *pV);

inline FLOAT HFVec2Dot
(const HFVECTOR2 *pV1, const HFVECTOR2 *pV2);
// Z component of ((x1,y1,0) cross (x2,y2,0))
inline FLOAT HFVec2CCW
(const HFVECTOR2 *pV1, const HFVECTOR2 *pV2);
inline HFVECTOR2* HFVec2Add
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2);

inline HFVECTOR2* HFVec2Subtract
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2);

// Minimize each component.  x = min(x1, x2), y = min(y1, y2)
inline HFVECTOR2* HFVec2Minimize
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2);

// Maximize each component.  x = max(x1, x2), y = max(y1, y2)
inline HFVECTOR2* HFVec2Maximize
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2);

inline HFVECTOR2* HFVec2Scale
(HFVECTOR2 *pOut, const HFVECTOR2 *pV, FLOAT s);

// Linear interpolation. V1 + s(V2-V1)
inline HFVECTOR2* HFVec2Lerp
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2,
	FLOAT s);

inline HFVECTOR2*  HFVec2Normalize
(HFVECTOR2 *pOut, const HFVECTOR2 *pV);

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
inline HFVECTOR2*  HFVec2Hermite
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pT1,
	const HFVECTOR2 *pV2, const HFVECTOR2 *pT2, FLOAT s); 

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
inline HFVECTOR2*  HFVec2CatmullRom
(HFVECTOR2 *pOut, const HFVECTOR2 *pV0, const HFVECTOR2 *pV1,
	const HFVECTOR2 *pV2, const HFVECTOR2 *pV3, FLOAT s);

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
inline HFVECTOR2*  HFVec2BaryCentric
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2,
	const HFVECTOR2 *pV3, FLOAT f, FLOAT g);
// Transform (x, y, 0, 1) by matrix.
inline HFVECTOR4*  HFVec2Transform
(HFVECTOR4 *pOut, const HFVECTOR2 *pV, const HFMATRIX *pM);

// Transform (x, y, 0, 1) by matrix, project result back into w=1.
inline HFVECTOR2*  HFVec2TransformCoord
(HFVECTOR2 *pOut, const HFVECTOR2 *pV, const HFMATRIX *pM);





//--------------------------
// 3D Vector
//--------------------------

// inline

FLOAT HFVec3Length
(const HFVECTOR3 *pV);

FLOAT HFVec3LengthSq
(const HFVECTOR3 *pV);

FLOAT HFVec3Dot
(const HFVECTOR3 *pV1, const HFVECTOR3 *pV2);

HFVECTOR3* HFVec3Cross
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2);

HFVECTOR3* HFVec3Add
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2);

HFVECTOR3* HFVec3Subtract
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2);

// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
HFVECTOR3* HFVec3Minimize
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2);

// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
HFVECTOR3* HFVec3Maximize
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2);

HFVECTOR3* HFVec3Scale
(HFVECTOR3 *pOut, const HFVECTOR3 *pV, FLOAT s);

// Linear interpolation. V1 + s(V2-V1)
HFVECTOR3* HFVec3Lerp
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2,
	FLOAT s);

HFVECTOR3*  HFVec3Normalize
(HFVECTOR3 *pOut, const HFVECTOR3 *pV);

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
HFVECTOR3*  HFVec3Hermite
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pT1,
	const HFVECTOR3 *pV2, const HFVECTOR3 *pT2, FLOAT s);

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
HFVECTOR3*  HFVec3CatmullRom
(HFVECTOR3 *pOut, const HFVECTOR3 *pV0, const HFVECTOR3 *pV1,
	const HFVECTOR3 *pV2, const HFVECTOR3 *pV3, FLOAT s);

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
HFVECTOR3*  HFVec3BaryCentric
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2,
	const HFVECTOR3 *pV3, FLOAT f, FLOAT g);

// Transform (x, y, z, 1) by matrix.
HFVECTOR4*  HFVec3Transform
(HFVECTOR4 *pOut, const HFVECTOR3 *pV, const HFMATRIX *pM);

// Transform (x, y, z, 1) by matrix, project result back into w=1.
HFVECTOR3*  HFVec3TransformCoord
(HFVECTOR3 *pOut, const HFVECTOR3 *pV, const HFMATRIX *pM);


//--------------------------
// 4D Vector
//--------------------------

// inline

FLOAT HFVec4Length
(const HFVECTOR4 *pV);


FLOAT HFVec4LengthSq
(const HFVECTOR4 *pV);

FLOAT HFVec4Dot
(const HFVECTOR4 *pV1, const HFVECTOR4 *pV2);

HFVECTOR4* HFVec4Add
(HFVECTOR4 *pOut, const HFVECTOR4 *pV1, const HFVECTOR4 *pV2);

HFVECTOR4* HFVec4Subtract
(HFVECTOR4 *pOut, const HFVECTOR4 *pV1, const HFVECTOR4 *pV2);

// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
HFVECTOR4* HFVec4Minimize
(HFVECTOR4 *pOut, const HFVECTOR4 *pV1, const HFVECTOR4 *pV2);

// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
HFVECTOR4* HFVec4Maximize
(HFVECTOR4 *pOut, const HFVECTOR4 *pV1, const HFVECTOR4 *pV2);

HFVECTOR4* HFVec4Scale
(HFVECTOR4 *pOut, const HFVECTOR4 *pV, FLOAT s);

// Linear interpolation. V1 + s(V2-V1)
HFVECTOR4* HFVec4Lerp
(HFVECTOR4 *pOut, const HFVECTOR4 *pV1, const HFVECTOR4 *pV2,
	FLOAT s);

// Cross-product in 4 dimensions.
HFVECTOR4*  HFVec4Cross
(HFVECTOR4 *pOut, const HFVECTOR4 *pV1, const HFVECTOR4 *pV2,
	const HFVECTOR4 *pV3);

HFVECTOR4*  HFVec4Normalize
(HFVECTOR4 *pOut, const HFVECTOR4 *pV);

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
HFVECTOR4*  HFVec4Hermite
(HFVECTOR4 *pOut, const HFVECTOR4 *pV1, const HFVECTOR4 *pT1,
	const HFVECTOR4 *pV2, const HFVECTOR4 *pT2, FLOAT s);

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
HFVECTOR4*  HFVec4CatmullRom
(HFVECTOR4 *pOut, const HFVECTOR4 *pV0, const HFVECTOR4 *pV1,
	const HFVECTOR4 *pV2, const HFVECTOR4 *pV3, FLOAT s);

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
HFVECTOR4*  HFVec4BaryCentric
(HFVECTOR4 *pOut, const HFVECTOR4 *pV1, const HFVECTOR4 *pV2,
	const HFVECTOR4 *pV3, FLOAT f, FLOAT g);

// Transform std::vector by matrix.
HFVECTOR4*  HFVec4Transform
(HFVECTOR4 *pOut, const HFVECTOR4 *pV, const HFMATRIX *pM);

// Transform std::vector array by matrix.
HFVECTOR4*  HFVec4TransformArray
(HFVECTOR4 *pOut, UINT OutStride, const HFVECTOR4 *pV, UINT VStride, const HFMATRIX *pM, UINT n);

//--------------------------
// 4D Matrix
//--------------------------

// inline

HFMATRIX* HFMatrixIdentity
(HFMATRIX *pOut);

BOOL HFMatrixIsIdentity
(const HFMATRIX *pM);


HFMATRIX  HFMatrixTranspose
(const HFMATRIX M);


HFMATRIX HFMatrixAdd(const HFMATRIX M1, const HFMATRIX M2);

HFMATRIX HFMatrixSubtruct(const HFMATRIX M1, const HFMATRIX M2);


// Matrix multiplication.  The result represents the transformation M2
// followed by the transformation M1.  (Out = M1 * M2)
HFMATRIX  HFMatrixMultiply
(const HFMATRIX M1, const HFMATRIX M2);

// Matrix multiplication, followed by a transpose. (Out = T(M1 * M2))
HFMATRIX  HFMatrixMultiplyTranspose
(const HFMATRIX M1, const HFMATRIX M2);

// Calculate inverse of matrix.  Inversion my fail, in which case NULL will
// be returned.  The determinant of pM is also returned it pfDeterminant
// is non-NULL.
HFMATRIX*  HFMatrixInverse
(HFMATRIX *pOut, FLOAT *pDeterminant, const HFMATRIX *pM);

// Build a matrix which scales by (sx, sy, sz)
HFMATRIX*  HFMatrixScaling
(HFMATRIX *pOut, FLOAT sx, FLOAT sy, FLOAT sz);

// Build a matrix which translates by (x, y, z)
HFMATRIX*  HFMatrixTranslation
(HFMATRIX *pOut, FLOAT x, FLOAT y, FLOAT z);
// Build a matrix which rotates around the X axis
HFMATRIX*  HFMatrixRotationX
(HFMATRIX *pOut, FLOAT Angle);

// Build a matrix which rotates around the Y axis
HFMATRIX*  HFMatrixRotationY
(HFMATRIX *pOut, FLOAT Angle);

// Build a matrix which rotates around the Z axis
HFMATRIX*  HFMatrixRotationZ
(HFMATRIX *pOut, FLOAT Angle);

// Build a matrix which rotates around an arbitrary axis
HFMATRIX*  HFMatrixRotationAxis
(HFMATRIX *pOut, const HFVECTOR3 *pV, FLOAT Angle);

// Build a matrix from a quaternion
HFMATRIX*  HFMatrixRotationQuaternion
(HFMATRIX *pOut, const HFQUATERNION *pQ);

HFMATRIX *HFMatrixRotationYawPitchRoll(HFMATRIX *pOut,
	FLOAT Yaw,
	FLOAT Pitch,
	FLOAT Roll
	);

// Build a lookat matrix. (right-handed)
HFMATRIX*  HFMatrixLookAtRH
(HFMATRIX *pOut, const HFVECTOR3 *pEye, const HFVECTOR3 *pAt,
	const HFVECTOR3 *pUp);

// Build a lookat matrix. (left-handed)
HFMATRIX*  HFMatrixLookAtLH
(HFMATRIX *pOut, const HFVECTOR3 *pEye, const HFVECTOR3 *pAt,
	const HFVECTOR3 *pUp);

// Build a perspective projection matrix. (right-handed)
HFMATRIX*  HFMatrixPerspectiveRH
(HFMATRIX *pOut, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf);

// Build a perspective projection matrix. (left-handed)
HFMATRIX*  HFMatrixPerspectiveLH
(HFMATRIX *pOut, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf);

// Build a perspective projection matrix. (right-handed)
HFMATRIX*  HFMatrixPerspectiveFovRH
(HFMATRIX *pOut, FLOAT fovy, FLOAT Aspect, FLOAT zn, FLOAT zf);

// Build a perspective projection matrix. (left-handed)
HFMATRIX*  HFMatrixPerspectiveFovLH
(HFMATRIX *pOut, FLOAT fovy, FLOAT Aspect, FLOAT zn, FLOAT zf);


// Build an ortho projection matrix. (right-handed)
HFMATRIX*  HFMatrixOrthoRH
(HFMATRIX *pOut, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf);

// Build an ortho projection matrix. (left-handed)
HFMATRIX*  HFMatrixOrthoLH
(HFMATRIX *pOut, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf);

// Build an ortho projection matrix. (right-handed)
HFMATRIX*  HFMatrixOrthoOffCenterRH
(HFMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn,
	FLOAT zf);

// Build an ortho projection matrix. (left-handed)
HFMATRIX*  HFMatrixOrthoOffCenterLH
(HFMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn,
	FLOAT zf);



//--------------------------
// Quaternion
//--------------------------

// inline

FLOAT HFQuaternionLength
(const HFQUATERNION *pQ);

// Length squared, or "norm"
FLOAT HFQuaternionLengthSq
(const HFQUATERNION *pQ);

FLOAT HFQuaternionDot
(const HFQUATERNION *pQ1, const HFQUATERNION *pQ2);

// (0, 0, 0, 1)
HFQUATERNION* HFQuaternionIdentity
(HFQUATERNION *pOut);

BOOL HFQuaternionIsIdentity
(const HFQUATERNION *pQ);

// (-x, -y, -z, w)
HFQUATERNION* HFQuaternionConjugate
(HFQUATERNION *pOut, const HFQUATERNION *pQ);

// non-inline

// Compute a quaternin's axis and angle of rotation. Expects unit quaternions.
void  HFQuaternionToAxisAngle
(const HFQUATERNION *pQ, HFVECTOR3 *pAxis, FLOAT *pAngle);

// Build a quaternion from a rotation matrix.
HFQUATERNION*  HFQuaternionRotationMatrix
(HFQUATERNION *pOut, const HFMATRIX *pM);

// Rotation about arbitrary axis.
HFQUATERNION*  HFQuaternionRotationAxis
(HFQUATERNION *pOut, const HFVECTOR3 *pV, FLOAT Angle);

// Yaw around the Y axis, a pitch around the X axis,
// and a roll around the Z axis.
HFQUATERNION*  HFQuaternionRotationYawPitchRoll
(HFQUATERNION *pOut, FLOAT Yaw, FLOAT Pitch, FLOAT Roll);

// Quaternion multiplication.  The result represents the rotation Q2
// followed by the rotation Q1.  (Out = Q2 * Q1)
HFQUATERNION*  HFQuaternionMultiply
(HFQUATERNION *pOut, const HFQUATERNION *pQ1,
	const HFQUATERNION *pQ2);

HFQUATERNION*  HFQuaternionNormalize
(HFQUATERNION *pOut, const HFQUATERNION *pQ);

// Conjugate and re-norm
HFQUATERNION*  HFQuaternionInverse
(HFQUATERNION *pOut, const HFQUATERNION *pQ);

// Expects unit quaternions.
// if q = (cos(theta), sin(theta) * v); ln(q) = (0, theta * v)
HFQUATERNION*  HFQuaternionLn
(HFQUATERNION *pOut, const HFQUATERNION *pQ);

// Expects pure quaternions. (w == 0)  w is ignored in calculation.
// if q = (0, theta * v); exp(q) = (cos(theta), sin(theta) * v)
HFQUATERNION*  HFQuaternionExp
(HFQUATERNION *pOut, const HFQUATERNION *pQ);

// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1).
// Expects unit quaternions.
HFQUATERNION*  HFQuaternionSlerp
(HFQUATERNION *pOut, const HFQUATERNION *pQ1,
	const HFQUATERNION *pQ2, FLOAT t);

// Spherical quadrangle interpolation.
// Slerp(Slerp(Q1, C, t), Slerp(A, B, t), 2t(1-t))
HFQUATERNION*  HFQuaternionSquad
(HFQUATERNION *pOut, const HFQUATERNION *pQ1,
	const HFQUATERNION *pA, const HFQUATERNION *pB,
	const HFQUATERNION *pC, FLOAT t);

// Setup control points for spherical quadrangle interpolation
// from Q1 to Q2.  The control points are chosen in such a way
// to ensure the continuity of tangents with adjacent segments.
void  HFQuaternionSquadSetup
(HFQUATERNION *pAOut, HFQUATERNION *pBOut, HFQUATERNION *pCOut,
	const HFQUATERNION *pQ0, const HFQUATERNION *pQ1,
	const HFQUATERNION *pQ2, const HFQUATERNION *pQ3);

// Barycentric interpolation.
// Slerp(Slerp(Q1, Q2, f+g), Slerp(Q1, Q3, f+g), g/(f+g))
HFQUATERNION*  HFQuaternionBaryCentric
(HFQUATERNION *pOut, const HFQUATERNION *pQ1,
	const HFQUATERNION *pQ2, const HFQUATERNION *pQ3,
	FLOAT f, FLOAT g);


// Y角度から3次元ベクトルベクトル
inline FLOAT* AngleYToVec3(HFVECTOR3 *pOut, FLOAT*pIn)
{
	DOUBLE radian = *pIn * (HF_PI / 180);
	FLOAT momentX = (FLOAT)(sin(radian) * 0.1);
	FLOAT momentZ = (FLOAT)(cos(radian) * 0.1);
	*pOut = HFVECTOR3(momentX, 0, momentZ);
}

// X角度から3次元ベクトルベクトル
inline FLOAT* AngleXToVec3(HFVECTOR3 *pOut, FLOAT*pIn)
{
	DOUBLE radian = *pIn * (HF_PI / 180);
	FLOAT momentY = (FLOAT)(sin(radian) * 0.1);
	FLOAT momentZ = (FLOAT)(cos(radian) * 0.1);
	*pOut = HFVECTOR3(0, momentY, momentZ);
}

// Z角度から3次元ベクトルベクトル
inline FLOAT* AngleZToVec3(HFVECTOR3 *pOut, FLOAT*pIn)
{
	DOUBLE radian = *pIn * (HF_PI / 180);
	FLOAT momentY = (FLOAT)(sin(radian) * 0.1);
	FLOAT momentX = (FLOAT)(cos(radian) * 0.1);
	*pOut = HFVECTOR3(momentX, momentY, 0);
}

inline FLOAT GetLengthOfArc(FLOAT radius, FLOAT radianAngle)
{
	//π × 半径 × 2 × 中心角 ÷ 360
	FLOAT ans = HF_PI * radius * 2 * radianAngle / (HF_PI * 2);
	return ans;
}
