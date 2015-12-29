#pragma once
#include <math.h>
#ifdef DIRECTX

#include "DirectXMath.h"

#endif

// 他に数学ライブラリが存在しない,対応させていない場合

//===========================================================================
//
// General purpose utilities
//
//===========================================================================
#define HF_PI    ((FLOAT)  3.141592654f)
#define HF_1BYPI ((FLOAT)  0.318309886f)

#define HFToRadian( degree ) ((degree) * (D3DX_PI / 180.0f))
#define HFToDegree( radian ) ((radian) * (180.0f / D3DX_PI))

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

// Y角度から3次元ベクトルベクトル
inline float* AngleYToVec3(HFVECTOR3 *pOut, float*pIn)
{
	double radian = *pIn * (HF_PI / 180);
	float momentX = (float)(sin(radian) * 0.1);
	float momentZ = (float)(cos(radian) * 0.1);
	*pOut = HFVECTOR3(momentX, 0, momentZ);
}

// X角度から3次元ベクトルベクトル
inline float* AngleXToVec3(HFVECTOR3 *pOut, float*pIn)
{
	double radian = *pIn * (HF_PI / 180);
	float momentY = (float)(sin(radian) * 0.1);
	float momentZ = (float)(cos(radian) * 0.1);
	*pOut = HFVECTOR3(0, momentY, momentZ);
}

// Z角度から3次元ベクトルベクトル
inline float* AngleZToVec3(HFVECTOR3 *pOut, float*pIn)
{
	double radian = *pIn * (HF_PI / 180);
	float momentY = (float)(sin(radian) * 0.1);
	float momentX = (float)(cos(radian) * 0.1);
	*pOut = HFVECTOR3(momentX, momentY, 0);
}

inline float GetLengthOfArc(float radius, float radianAngle)
{
	//π × 半径 × 2 × 中心角 ÷ 360
	float ans = HF_PI * radius * 2 * radianAngle / (HF_PI * 2);
	return ans;
}

#ifdef UNDEVELOPED
typedef struct HFFLOAT16
{
#ifdef __cplusplus
public:
	HFFLOAT16() {};
	HFFLOAT16(FLOAT);
	HFFLOAT16(const HFFLOAT16&);

	// casting
	operator FLOAT ();

	// binary operators
	BOOL operator == (const HFFLOAT16&) const;
	BOOL operator != (const HFFLOAT16&) const;

protected:
#endif //__cplusplus
	WORD value;
} HFFLOAT16, *LPHFFLOAT16;

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
	HFVECTOR2(const FLOAT *);
	HFVECTOR2(const HFFLOAT16 *);
	HFVECTOR2(FLOAT x, FLOAT y);

	// casting
	operator FLOAT* ();
	operator const FLOAT* () const;

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
// 2D Vector (16 bit)
//--------------------------

typedef struct HFVECTOR2_16F
{
#ifdef __cplusplus
public:
	HFVECTOR2_16F() {};
	HFVECTOR2_16F(const FLOAT *);
	HFVECTOR2_16F(const HFFLOAT16 *);
	HFVECTOR2_16F(const HFFLOAT16 &x, const HFFLOAT16 &y);

	// casting
	operator HFFLOAT16* ();
	operator const HFFLOAT16* () const;

	// binary operators
	BOOL operator == (const HFVECTOR2_16F&) const;
	BOOL operator != (const HFVECTOR2_16F&) const;

public:
#endif //__cplusplus
	HFFLOAT16 x, y;
} HFVECTOR2_16F, *LPHFVECTOR2_16F;

//--------------------------
// 3D Vector
//--------------------------

typedef struct HFVECTOR3
{
public:
	HFVECTOR3() {};
	HFVECTOR3(const FLOAT *);
	HFVECTOR3(const D3DVECTOR&);
	HFVECTOR3(const HFFLOAT16 *);
	HFVECTOR3(FLOAT x, FLOAT y, FLOAT z);

	// casting
	operator FLOAT* ();
	operator const FLOAT* () const;

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

public:

	float x;
	float y;
	float z;
} HFVECTOR3, *LPHFVECTOR3;

/*

//--------------------------
// 3D Vector (16 bit)
//--------------------------
typedef struct D3DXVECTOR3_16F
{
#ifdef __cplusplus
public:
	D3DXVECTOR3_16F() {};
	D3DXVECTOR3_16F(const FLOAT *);
	D3DXVECTOR3_16F(const D3DVECTOR&);
	D3DXVECTOR3_16F(const D3DXFLOAT16 *);
	D3DXVECTOR3_16F(const D3DXFLOAT16 &x, const D3DXFLOAT16 &y, const D3DXFLOAT16 &z);

	// casting
	operator D3DXFLOAT16* ();
	operator const D3DXFLOAT16* () const;

	// binary operators
	BOOL operator == (const D3DXVECTOR3_16F&) const;
	BOOL operator != (const D3DXVECTOR3_16F&) const;

public:
#endif //__cplusplus
	D3DXFLOAT16 x, y, z;
} D3DXVECTOR3_16F, *LPD3DXVECTOR3_16F;

  */

  //--------------------------
  // 4D Vector
  //--------------------------
typedef struct HFVECTOR4
{
#ifdef __cplusplus
public:
	HFVECTOR4() {};
	HFVECTOR4(const FLOAT*);
	HFVECTOR4(const HFFLOAT16*);
	HFVECTOR4(const D3DVECTOR& xyz, FLOAT w);
	HFVECTOR4(FLOAT x, FLOAT y, FLOAT z, FLOAT w);

	// casting
	operator FLOAT* ();
	operator const FLOAT* () const;

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

/*

//--------------------------
// 4D Vector (16 bit)
//--------------------------
typedef struct D3DXVECTOR4_16F
{
#ifdef __cplusplus
public:
	D3DXVECTOR4_16F() {};
	D3DXVECTOR4_16F(const FLOAT *);
	D3DXVECTOR4_16F(const D3DXFLOAT16*);
	D3DXVECTOR4_16F(const D3DXVECTOR3_16F& xyz, const D3DXFLOAT16& w);
	D3DXVECTOR4_16F(const D3DXFLOAT16& x, const D3DXFLOAT16& y, const D3DXFLOAT16& z, const D3DXFLOAT16& w);

	// casting
	operator D3DXFLOAT16* ();
	operator const D3DXFLOAT16* () const;

	// binary operators
	BOOL operator == (const D3DXVECTOR4_16F&) const;
	BOOL operator != (const D3DXVECTOR4_16F&) const;

public:
#endif //__cplusplus
	D3DXFLOAT16 x, y, z, w;
} D3DXVECTOR4_16F, *LPD3DXVECTOR4_16F;

   */

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
	HFMATRIX(const FLOAT *);
	HFMATRIX(const HFFLOAT16 *);
	HFMATRIX(FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
		FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
		FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
		FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44);

	// access grants
	FLOAT& operator () (UINT Row, UINT Col);
	FLOAT  operator () (UINT Row, UINT Col) const;

	// casting operators
	operator FLOAT* ();
	operator const FLOAT* () const;

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
public:

	// 列優先
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;
		};
		float m[4][4];
	};
} HFMATRIX, *LPHFMATRIX;

#else //!__cplusplus
typedef struct _HFMATRIX HFMATRIX, *LPHFMATRIX;
#endif //!__cplusplus

/*

//---------------------------------------------------------------------------
// Aligned Matrices
//
// This class helps keep matrices 16-byte aligned as preferred by P4 cpus.
// It aligns matrices on the stack and on the heap or in global scope.
// It does this using __declspec(align(16)) which works on VC7 and on VC 6
// with the processor pack. Unfortunately there is no way to detect the
// latter so this is turned on only on VC7. On other compilers this is the
// the same as D3DXMATRIX.
//
// Using this class on a compiler that does not actually do the alignment
// can be dangerous since it will not expose bugs that ignore alignment.
// E.g if an object of this class in inside a struct or class, and some code
// memcopys data in it assuming tight packing. This could break on a compiler
// that eventually start aligning the matrix.
//---------------------------------------------------------------------------
#ifdef __cplusplus
typedef struct _D3DXMATRIXA16 : public D3DXMATRIX
{
	_D3DXMATRIXA16() {}
	_D3DXMATRIXA16(const FLOAT *);
	_D3DXMATRIXA16(const D3DMATRIX&);
	_D3DXMATRIXA16(const D3DXFLOAT16 *);
	_D3DXMATRIXA16(FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
		FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
		FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
		FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44);

	// new operators
	void* operator new   (size_t);
	void* operator new[](size_t);

	// delete operators
	void operator delete   (void*);   // These are NOT virtual; Do not
	void operator delete[](void*);   // cast to D3DXMATRIX and delete.

	// assignment operators
	_D3DXMATRIXA16& operator = (const D3DXMATRIX&);
} _D3DXMATRIXA16;

#else //!__cplusplus
typedef D3DXMATRIX  _D3DXMATRIXA16;
#endif //!__cplusplus

#if _MSC_VER >= 1300  // VC7
#define D3DX_ALIGN16 __declspec(align(16))
#else
#define D3DX_ALIGN16  // Earlier compiler may not understand this, do nothing.
#endif

typedef D3DX_ALIGN16 _D3DXMATRIXA16 D3DXMATRIXA16, *LPD3DXMATRIXA16;

*/

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
	HFQUATERNION(const FLOAT *);
	HFQUATERNION(const HFFLOAT16 *);
	HFQUATERNION(FLOAT x, FLOAT y, FLOAT z, FLOAT w);

	// casting
	operator FLOAT* ();
	operator const FLOAT* () const;

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
// Planes
//
//===========================================================================
typedef struct HFPLANE
{
#ifdef __cplusplus
public:
	HFPLANE() {}
	HFPLANE(const FLOAT*);
	HFPLANE(const HFFLOAT16*);
	HFPLANE(FLOAT a, FLOAT b, FLOAT c, FLOAT d);

	// casting
	operator FLOAT* ();
	operator const FLOAT* () const;

	// assignment operators
	HFPLANE& operator *= (FLOAT);
	HFPLANE& operator /= (FLOAT);

	// unary operators
	HFPLANE operator + () const;
	HFPLANE operator - () const;

	// binary operators
	HFPLANE operator * (FLOAT) const;
	HFPLANE operator / (FLOAT) const;

	friend HFPLANE operator * (FLOAT, const HFPLANE&);

	BOOL operator == (const HFPLANE&) const;
	BOOL operator != (const HFPLANE&) const;

#endif //__cplusplus
	FLOAT a, b, c, d;
} HFPLANE, *LPHFPLANE;

//===========================================================================
//
// Colors
//
//===========================================================================

typedef struct HFCOLOR
{
#ifdef __cplusplus
public:
	HFCOLOR() {}
	HFCOLOR(DWORD argb);
	HFCOLOR(const FLOAT *);
	HFCOLOR(const HFFLOAT16 *);
	HFCOLOR(const D3DCOLORVALUE&);
	HFCOLOR(FLOAT r, FLOAT g, FLOAT b, FLOAT a);

	// casting
	operator DWORD () const;

	operator FLOAT* ();
	operator const FLOAT* () const;

	operator D3DCOLORVALUE* ();
	operator const D3DCOLORVALUE* () const;

	operator D3DCOLORVALUE& ();
	operator const D3DCOLORVALUE& () const;

	// assignment operators
	HFCOLOR& operator += (const HFCOLOR&);
	HFCOLOR& operator -= (const HFCOLOR&);
	HFCOLOR& operator *= (FLOAT);
	HFCOLOR& operator /= (FLOAT);

	// unary operators
	HFCOLOR operator + () const;
	HFCOLOR operator - () const;

	// binary operators
	HFCOLOR operator + (const HFCOLOR&) const;
	HFCOLOR operator - (const HFCOLOR&) const;
	HFCOLOR operator * (FLOAT) const;
	HFCOLOR operator / (FLOAT) const;

	friend HFCOLOR operator * (FLOAT, const HFCOLOR&);

	BOOL operator == (const HFCOLOR&) const;
	BOOL operator != (const HFCOLOR&) const;

#endif //__cplusplus
	FLOAT r, g, b, a;
} HFCOLOR, *LPHFCOLOR;

/*

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

//--------------------------
// Float16
//--------------------------

// non-inline
#ifdef __cplusplus
extern "C" {
#endif

	// Converts an array 32-bit floats to 16-bit floats
	D3DXFLOAT16*  D3DXFloat32To16Array
		(D3DXFLOAT16 *pOut, const FLOAT *pIn, UINT n);

	// Converts an array 16-bit floats to 32-bit floats
	FLOAT*  D3DXFloat16To32Array
		(FLOAT *pOut, const D3DXFLOAT16 *pIn, UINT n);

#ifdef __cplusplus
}
#endif
*/

/*

//===========================================================================
//
//    Matrix Stack
//
//===========================================================================

typedef interface ID3DXMatrixStack ID3DXMatrixStack;
typedef interface ID3DXMatrixStack *LPD3DXMATRIXSTACK;

// {C7885BA7-F990-4fe7-922D-8515E477DD85}
DEFINE_GUID(IID_ID3DXMatrixStack,
	0xc7885ba7, 0xf990, 0x4fe7, 0x92, 0x2d, 0x85, 0x15, 0xe4, 0x77, 0xdd, 0x85);

#undef INTERFACE
#define INTERFACE ID3DXMatrixStack

DECLARE_INTERFACE_(ID3DXMatrixStack, IUnknown)
{
	//
	// IUnknown methods
	//
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS)PURE;
	STDMETHOD_(ULONG, Release)(THIS)PURE;

	//
	// ID3DXMatrixStack methods
	//

	// Pops the top of the stack, returns the current top
	// *after* popping the top.
	STDMETHOD(Pop)(THIS)PURE;

	// Pushes the stack by one, duplicating the current matrix.
	STDMETHOD(Push)(THIS)PURE;

	// Loads identity in the current matrix.
	STDMETHOD(LoadIdentity)(THIS)PURE;

	// Loads the given matrix into the current matrix
	STDMETHOD(LoadMatrix)(THIS_ const D3DXMATRIX* pM) PURE;

	// Right-Multiplies the given matrix to the current matrix.
	// (transformation is about the current world origin)
	STDMETHOD(MultMatrix)(THIS_ const D3DXMATRIX* pM) PURE;

	// Left-Multiplies the given matrix to the current matrix
	// (transformation is about the local origin of the object)
	STDMETHOD(MultMatrixLocal)(THIS_ const D3DXMATRIX* pM) PURE;

	// Right multiply the current matrix with the computed rotation
	// matrix, counterclockwise about the given axis with the given angle.
	// (rotation is about the current world origin)
	STDMETHOD(RotateAxis)
		(THIS_ const D3DXVECTOR3* pV, FLOAT Angle) PURE;

	// Left multiply the current matrix with the computed rotation
	// matrix, counterclockwise about the given axis with the given angle.
	// (rotation is about the local origin of the object)
	STDMETHOD(RotateAxisLocal)
		(THIS_ const D3DXVECTOR3* pV, FLOAT Angle) PURE;

	// Right multiply the current matrix with the computed rotation
	// matrix. All angles are counterclockwise. (rotation is about the
	// current world origin)

	// The rotation is composed of a yaw around the Y axis, a pitch around
	// the X axis, and a roll around the Z axis.
	STDMETHOD(RotateYawPitchRoll)
		(THIS_ FLOAT Yaw, FLOAT Pitch, FLOAT Roll) PURE;

	// Left multiply the current matrix with the computed rotation
	// matrix. All angles are counterclockwise. (rotation is about the
	// local origin of the object)

	// The rotation is composed of a yaw around the Y axis, a pitch around
	// the X axis, and a roll around the Z axis.
	STDMETHOD(RotateYawPitchRollLocal)
		(THIS_ FLOAT Yaw, FLOAT Pitch, FLOAT Roll) PURE;

	// Right multiply the current matrix with the computed scale
	// matrix. (transformation is about the current world origin)
	STDMETHOD(Scale)(THIS_ FLOAT x, FLOAT y, FLOAT z) PURE;

	// Left multiply the current matrix with the computed scale
	// matrix. (transformation is about the local origin of the object)
	STDMETHOD(ScaleLocal)(THIS_ FLOAT x, FLOAT y, FLOAT z) PURE;

	// Right multiply the current matrix with the computed translation
	// matrix. (transformation is about the current world origin)
	STDMETHOD(Translate)(THIS_ FLOAT x, FLOAT y, FLOAT z) PURE;

	// Left multiply the current matrix with the computed translation
	// matrix. (transformation is about the local origin of the object)
	STDMETHOD(TranslateLocal)(THIS_ FLOAT x, FLOAT y, FLOAT z) PURE;

	// Obtain the current matrix at the top of the stack
	STDMETHOD_(D3DXMATRIX*, GetTop)(THIS)PURE;
};

#ifdef __cplusplus
extern "C" {
#endif

	HRESULT
		D3DXCreateMatrixStack(
		DWORD               Flags,
		LPD3DXMATRIXSTACK*  ppStack);

#ifdef __cplusplus
}
#endif

//===========================================================================
//
//  Spherical Harmonic Runtime Routines
//
// NOTE:
//  * Most of these functions can take the same object as in and out parameters.
//    The exceptions are the rotation functions.
//
//  * Out parameters are typically also returned as return values, so that
//    the output of one function may be used as a parameter to another.
//
//============================================================================

// non-inline
#ifdef __cplusplus
extern "C" {
#endif

	//============================================================================
	//
	//  Basic Spherical Harmonic math routines
	//
	//============================================================================

#define D3DXSH_MINORDER 2
#define D3DXSH_MAXORDER 6

	//============================================================================
	//
	//  D3DXSHEvalDirection:
	//  --------------------
	//  Evaluates the Spherical Harmonic basis functions
	//
	//  Parameters:
	//   pOut
	//      Output SH coefficients - basis function Ylm is stored at l*l + m+l
	//      This is the pointer that is returned.
	//   Order
	//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
	//   pDir
	//      Direction to evaluate in - assumed to be normalized
	//
	//============================================================================

	FLOAT*  D3DXSHEvalDirection
		(FLOAT *pOut, UINT Order, const D3DXVECTOR3 *pDir);

	//============================================================================
	//
	//  D3DXSHRotate:
	//  --------------------
	//  Rotates SH std::vector by a rotation matrix
	//
	//  Parameters:
	//   pOut
	//      Output SH coefficients - basis function Ylm is stored at l*l + m+l
	//      This is the pointer that is returned (should not alias with pIn.)
	//   Order
	//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
	//   pMatrix
	//      Matrix used for rotation - rotation sub matrix should be orthogonal
	//      and have a unit determinant.
	//   pIn
	//      Input SH coeffs (rotated), incorect results if this is also output.
	//
	//============================================================================

	FLOAT*  D3DXSHRotate
		(FLOAT *pOut, UINT Order, const D3DXMATRIX *pMatrix, const FLOAT *pIn);

	//============================================================================
	//
	//  D3DXSHRotateZ:
	//  --------------------
	//  Rotates the SH std::vector in the Z axis by an angle
	//
	//  Parameters:
	//   pOut
	//      Output SH coefficients - basis function Ylm is stored at l*l + m+l
	//      This is the pointer that is returned (should not alias with pIn.)
	//   Order
	//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
	//   Angle
	//      Angle in radians to rotate around the Z axis.
	//   pIn
	//      Input SH coeffs (rotated), incorect results if this is also output.
	//
	//============================================================================

	FLOAT*  D3DXSHRotateZ
		(FLOAT *pOut, UINT Order, FLOAT Angle, const FLOAT *pIn);

	//============================================================================
	//
	//  D3DXSHAdd:
	//  --------------------
	//  Adds two SH vectors, pOut[i] = pA[i] + pB[i];
	//
	//  Parameters:
	//   pOut
	//      Output SH coefficients - basis function Ylm is stored at l*l + m+l
	//      This is the pointer that is returned.
	//   Order
	//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
	//   pA
	//      Input SH coeffs.
	//   pB
	//      Input SH coeffs (second std::vector.)
	//
	//============================================================================

	FLOAT*  D3DXSHAdd
		(FLOAT *pOut, UINT Order, const FLOAT *pA, const FLOAT *pB);

	//============================================================================
	//
	//  D3DXSHScale:
	//  --------------------
	//  Adds two SH vectors, pOut[i] = pA[i]*Scale;
	//
	//  Parameters:
	//   pOut
	//      Output SH coefficients - basis function Ylm is stored at l*l + m+l
	//      This is the pointer that is returned.
	//   Order
	//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
	//   pIn
	//      Input SH coeffs.
	//   Scale
	//      Scale factor.
	//
	//============================================================================

	FLOAT*  D3DXSHScale
		(FLOAT *pOut, UINT Order, const FLOAT *pIn, const FLOAT Scale);

	//============================================================================
	//
	//  D3DXSHDot:
	//  --------------------
	//  Computes the dot product of two SH vectors
	//
	//  Parameters:
	//   Order
	//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
	//   pA
	//      Input SH coeffs.
	//   pB
	//      Second set of input SH coeffs.
	//
	//============================================================================

	FLOAT  D3DXSHDot
		(UINT Order, const FLOAT *pA, const FLOAT *pB);

	//============================================================================
	//
	//  D3DXSHMultiply[O]:
	//  --------------------
	//  Computes the product of two functions represented using SH (f and g), where:
	//  pOut[i] = int(y_i(s) * f(s) * g(s)), where y_i(s) is the ith SH basis
	//  function, f(s) and g(s) are SH functions (sum_i(y_i(s)*c_i)).  The order O
	//  determines the lengths of the arrays, where there should always be O^2
	//  coefficients.  In general the product of two SH functions of order O generates
	//  and SH function of order 2*O - 1, but we truncate the result.  This means
	//  that the product commutes (f*g == g*f) but doesn't associate
	//  (f*(g*h) != (f*g)*h.
	//
	//  Parameters:
	//   pOut
	//      Output SH coefficients - basis function Ylm is stored at l*l + m+l
	//      This is the pointer that is returned.
	//   pF
	//      Input SH coeffs for first function.
	//   pG
	//      Second set of input SH coeffs.
	//
	//============================================================================

	FLOAT*  D3DXSHMultiply2(FLOAT *pOut, const FLOAT *pF, const FLOAT *pG);
	FLOAT*  D3DXSHMultiply3(FLOAT *pOut, const FLOAT *pF, const FLOAT *pG);
	FLOAT*  D3DXSHMultiply4(FLOAT *pOut, const FLOAT *pF, const FLOAT *pG);
	FLOAT*  D3DXSHMultiply5(FLOAT *pOut, const FLOAT *pF, const FLOAT *pG);
	FLOAT*  D3DXSHMultiply6(FLOAT *pOut, const FLOAT *pF, const FLOAT *pG);

	//============================================================================
	//
	//  Basic Spherical Harmonic lighting routines
	//
	//============================================================================

	//============================================================================
	//
	//  D3DXSHEvalDirectionalLight:
	//  --------------------
	//  Evaluates a directional light and returns spectral SH data.  The output
	//  std::vector is computed so that if the intensity of R/G/B is unit the resulting
	//  exit radiance of a point directly under the light on a diffuse object with
	//  an albedo of 1 would be 1.0.  This will compute 3 spectral samples, pROut
	//  has to be specified, while pGout and pBout are optional.
	//
	//  Parameters:
	//   Order
	//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
	//   pDir
	//      Direction light is coming from (assumed to be normalized.)
	//   RIntensity
	//      Red intensity of light.
	//   GIntensity
	//      Green intensity of light.
	//   BIntensity
	//      Blue intensity of light.
	//   pROut
	//      Output SH std::vector for Red.
	//   pGOut
	//      Output SH std::vector for Green (optional.)
	//   pBOut
	//      Output SH std::vector for Blue (optional.)
	//
	//============================================================================

	HRESULT  D3DXSHEvalDirectionalLight
		(UINT Order, const D3DXVECTOR3 *pDir,
		FLOAT RIntensity, FLOAT GIntensity, FLOAT BIntensity,
		FLOAT *pROut, FLOAT *pGOut, FLOAT *pBOut);

	//============================================================================
	//
	//  D3DXSHEvalSphericalLight:
	//  --------------------
	//  Evaluates a spherical light and returns spectral SH data.  There is no
	//  normalization of the intensity of the light like there is for directional
	//  lights, care has to be taken when specifiying the intensities.  This will
	//  compute 3 spectral samples, pROut has to be specified, while pGout and
	//  pBout are optional.
	//
	//  Parameters:
	//   Order
	//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
	//   pPos
	//      Position of light - reciever is assumed to be at the origin.
	//   Radius
	//      Radius of the spherical light source.
	//   RIntensity
	//      Red intensity of light.
	//   GIntensity
	//      Green intensity of light.
	//   BIntensity
	//      Blue intensity of light.
	//   pROut
	//      Output SH std::vector for Red.
	//   pGOut
	//      Output SH std::vector for Green (optional.)
	//   pBOut
	//      Output SH std::vector for Blue (optional.)
	//
	//============================================================================

	HRESULT  D3DXSHEvalSphericalLight
		(UINT Order, const D3DXVECTOR3 *pPos, FLOAT Radius,
		FLOAT RIntensity, FLOAT GIntensity, FLOAT BIntensity,
		FLOAT *pROut, FLOAT *pGOut, FLOAT *pBOut);

	//============================================================================
	//
	//  D3DXSHEvalConeLight:
	//  --------------------
	//  Evaluates a light that is a cone of constant intensity and returns spectral
	//  SH data.  The output std::vector is computed so that if the intensity of R/G/B is
	//  unit the resulting exit radiance of a point directly under the light oriented
	//  in the cone direction on a diffuse object with an albedo of 1 would be 1.0.
	//  This will compute 3 spectral samples, pROut has to be specified, while pGout
	//  and pBout are optional.
	//
	//  Parameters:
	//   Order
	//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
	//   pDir
	//      Direction light is coming from (assumed to be normalized.)
	//   Radius
	//      Radius of cone in radians.
	//   RIntensity
	//      Red intensity of light.
	//   GIntensity
	//      Green intensity of light.
	//   BIntensity
	//      Blue intensity of light.
	//   pROut
	//      Output SH std::vector for Red.
	//   pGOut
	//      Output SH std::vector for Green (optional.)
	//   pBOut
	//      Output SH std::vector for Blue (optional.)
	//
	//============================================================================

	HRESULT  D3DXSHEvalConeLight
		(UINT Order, const D3DXVECTOR3 *pDir, FLOAT Radius,
		FLOAT RIntensity, FLOAT GIntensity, FLOAT BIntensity,
		FLOAT *pROut, FLOAT *pGOut, FLOAT *pBOut);

	//============================================================================
	//
	//  D3DXSHEvalHemisphereLight:
	//  --------------------
	//  Evaluates a light that is a linear interpolant between two colors over the
	//  sphere.  The interpolant is linear along the axis of the two points, not
	//  over the surface of the sphere (ie: if the axis was (0,0,1) it is linear in
	//  Z, not in the azimuthal angle.)  The resulting spherical lighting function
	//  is normalized so that a point on a perfectly diffuse surface with no
	//  shadowing and a normal pointed in the direction pDir would result in exit
	//  radiance with a value of 1 if the top color was white and the bottom color
	//  was black.  This is a very simple model where Top represents the intensity
	//  of the "sky" and Bottom represents the intensity of the "ground".
	//
	//  Parameters:
	//   Order
	//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
	//   pDir
	//      Axis of the hemisphere.
	//   Top
	//      Color of the upper hemisphere.
	//   Bottom
	//      Color of the lower hemisphere.
	//   pROut
	//      Output SH std::vector for Red.
	//   pGOut
	//      Output SH std::vector for Green
	//   pBOut
	//      Output SH std::vector for Blue
	//
	//============================================================================

	HRESULT  D3DXSHEvalHemisphereLight
		(UINT Order, const D3DXVECTOR3 *pDir, D3DXCOLOR Top, D3DXCOLOR Bottom,
		FLOAT *pROut, FLOAT *pGOut, FLOAT *pBOut);

	//============================================================================
	//
	//  Basic Spherical Harmonic projection routines
	//
	//============================================================================

	//============================================================================
	//
	//  D3DXSHProjectCubeMap:
	//  --------------------
	//  Projects a function represented on a cube std::map into spherical harmonics.
	//
	//  Parameters:
	//   Order
	//      Order of the SH evaluation, generates Order^2 coefs, degree is Order-1
	//   pCubeMap
	//      CubeMap that is going to be projected into spherical harmonics
	//   pROut
	//      Output SH std::vector for Red.
	//   pGOut
	//      Output SH std::vector for Green
	//   pBOut
	//      Output SH std::vector for Blue
	//
	//============================================================================

	HRESULT  D3DXSHProjectCubeMap
		(UINT uOrder, LPDIRECT3DCUBETEXTURE9 pCubeMap,
		FLOAT *pROut, FLOAT *pGOut, FLOAT *pBOut);

#ifdef __cplusplus
}
#endif

*/
#endif

// function
//--------------------------
// 2D Vector
//--------------------------

// inline

inline FLOAT HFVec2Length
(const HFVECTOR2 *pV)
{
	return D3DXVec2Length(pV);
};

inline FLOAT HFVec2LengthSq
(const HFVECTOR2 *pV)
{
	return D3DXVec2LengthSq(pV);
};

inline FLOAT HFVec2Dot
(const HFVECTOR2 *pV1, const HFVECTOR2 *pV2)
{
	return D3DXVec2Dot(pV1, pV2);
};

// Z component of ((x1,y1,0) cross (x2,y2,0))
inline FLOAT HFVec2CCW
(const HFVECTOR2 *pV1, const HFVECTOR2 *pV2)
{
	return D3DXVec2CCW(pV1, pV2);
};

inline HFVECTOR2* HFVec2Add
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2)
{
	return D3DXVec2Add(pOut, pV1, pV2);
};

inline HFVECTOR2* HFVec2Subtract
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2)
{
	return D3DXVec2Subtract(pOut, pV1, pV2);
};

// Minimize each component.  x = min(x1, x2), y = min(y1, y2)
inline HFVECTOR2* HFVec2Minimize
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2)
{
	return D3DXVec2Minimize(pOut, pV1, pV2);
};

// Maximize each component.  x = max(x1, x2), y = max(y1, y2)
inline HFVECTOR2* HFVec2Maximize
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2)
{
	return D3DXVec2Maximize(pOut, pV1, pV2);
};

inline HFVECTOR2* HFVec2Scale
(HFVECTOR2 *pOut, const HFVECTOR2 *pV, FLOAT s)
{
	return D3DXVec2Scale(pOut, pV, s);
};

// Linear interpolation. V1 + s(V2-V1)
inline HFVECTOR2* HFVec2Lerp
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2,
	FLOAT s)
{
	return D3DXVec2Lerp(pOut, pV1, pV2, s);
};

inline HFVECTOR2*  HFVec2Normalize
(HFVECTOR2 *pOut, const HFVECTOR2 *pV)
{
	return D3DXVec2Normalize(pOut, pV);
};

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
inline HFVECTOR2*  HFVec2Hermite
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pT1,
	const HFVECTOR2 *pV2, const HFVECTOR2 *pT2, FLOAT s)
{
	return D3DXVec2Hermite(pOut, pV1, pT1, pV2, pT2, s);
};

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
inline HFVECTOR2*  HFVec2CatmullRom
(HFVECTOR2 *pOut, const HFVECTOR2 *pV0, const HFVECTOR2 *pV1,
	const HFVECTOR2 *pV2, const HFVECTOR2 *pV3, FLOAT s)
{
	return D3DXVec2CatmullRom(pOut, pV0, pV1, pV2, pV3, s);
};

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
inline HFVECTOR2*  HFVec2BaryCentric
(HFVECTOR2 *pOut, const HFVECTOR2 *pV1, const HFVECTOR2 *pV2,
	const HFVECTOR2 *pV3, FLOAT f, FLOAT g)
{
	return D3DXVec2BaryCentric(pOut, pV1, pV2, pV3, f, g);
};

// Transform (x, y, 0, 1) by matrix.
inline HFVECTOR4*  HFVec2Transform
(HFVECTOR4 *pOut, const HFVECTOR2 *pV, const HFMATRIX *pM)
{
	D3DXVec2Transform(pOut, pV, pM);
};

// Transform (x, y, 0, 1) by matrix, project result back into w=1.
inline HFVECTOR2*  HFVec2TransformCoord
(HFVECTOR2 *pOut, const HFVECTOR2 *pV, const HFMATRIX *pM)
{
	D3DXVec2TransformCoord(pOut, pV, pM);
};

// Transform (x, y, 0, 0) by matrix.
inline HFVECTOR2* HFVec2TransformNormal
(HFVECTOR2 *pOut, const HFVECTOR2 *pV, const HFMATRIX *pM)
{
	D3DXVec2TransformNormal(pOut, pV, pM);
};

// Transform Array (x, y, 0, 1) by matrix.
inline HFVECTOR4*  HFVec2TransformArray
(HFVECTOR4 *pOut, UINT OutStride, const HFVECTOR2 *pV, UINT VStride, const HFMATRIX *pM, UINT n)
{
	return D3DXVec2TransformArray(pOut, OutStride, pV, VStride, pM, n);
};

// Transform Array (x, y, 0, 1) by matrix, project result back into w=1.
inline HFVECTOR2*  HFVec2TransformCoordArray
(HFVECTOR2 *pOut, UINT OutStride, const HFVECTOR2 *pV, UINT VStride, const HFMATRIX *pM, UINT n)
{
	return D3DXVec2TransformCoordArray(pOut, OutStride, pV, VStride, pM, n);
};

// Transform Array (x, y, 0, 0) by matrix.
inline HFVECTOR2*  HFVec2TransformNormalArray
(HFVECTOR2 *pOut, UINT OutStride, const HFVECTOR2 *pV, UINT VStride, const HFMATRIX *pM, UINT n)
{
	return D3DXVec2TransformNormalArray(pOut, OutStride, pV, VStride, pM, n);
};

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

// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a
// non-affine matrix, the matrix you pass to this function should be the
// transpose of the inverse of the matrix you would use to transform a coord.
HFVECTOR3*  HFVec3TransformNormal
(HFVECTOR3 *pOut, const HFVECTOR3 *pV, const HFMATRIX *pM);

// Transform Array (x, y, z, 1) by matrix.
HFVECTOR4*  HFVec3TransformArray
(HFVECTOR4 *pOut, UINT OutStride, const HFVECTOR3 *pV, UINT VStride, const HFMATRIX *pM, UINT n);

// Transform Array (x, y, z, 1) by matrix, project result back into w=1.
HFVECTOR3*  HFVec3TransformCoordArray
(HFVECTOR3 *pOut, UINT OutStride, const HFVECTOR3 *pV, UINT VStride, const HFMATRIX *pM, UINT n);

// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a
// non-affine matrix, the matrix you pass to this function should be the
// transpose of the inverse of the matrix you would use to transform a coord.
HFVECTOR3*  HFVec3TransformNormalArray
(HFVECTOR3 *pOut, UINT OutStride, const HFVECTOR3 *pV, UINT VStride, const HFMATRIX *pM, UINT n);

// Project std::vector from object space into screen space
HFVECTOR3*  HFVec3Project
(HFVECTOR3 *pOut, const HFVECTOR3 *pV, const D3DVIEWPORT9 *pViewport,
	const HFMATRIX *pProjection, const HFMATRIX *pView, const HFMATRIX *pWorld);

// Project std::vector from screen space into object space
HFVECTOR3*  HFVec3Unproject
(HFVECTOR3 *pOut, const HFVECTOR3 *pV, const D3DVIEWPORT9 *pViewport,
	const HFMATRIX *pProjection, const HFMATRIX *pView, const HFMATRIX *pWorld);

// Project std::vector Array from object space into screen space
HFVECTOR3*  HFVec3ProjectArray
(HFVECTOR3 *pOut, UINT OutStride, const HFVECTOR3 *pV, UINT VStride, const D3DVIEWPORT9 *pViewport,
	const HFMATRIX *pProjection, const HFMATRIX *pView, const HFMATRIX *pWorld, UINT n);

// Project std::vector Array from screen space into object space
HFVECTOR3*  HFVec3UnprojectArray
(HFVECTOR3 *pOut, UINT OutStride, const HFVECTOR3 *pV, UINT VStride, const D3DVIEWPORT9 *pViewport,
	const HFMATRIX *pProjection, const HFMATRIX *pView, const HFMATRIX *pWorld, UINT n);

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

// non-inline

FLOAT HFMatrixDeterminant
(const HFMATRIX *pM);

HRESULT  HFMatrixDecompose
(HFVECTOR3 *pOutScale, HFQUATERNION *pOutRotation,
	HFVECTOR3 *pOutTranslation, const HFMATRIX *pM);

HFMATRIX*  HFMatrixTranspose
(HFMATRIX *pOut, const HFMATRIX *pM);

// Matrix multiplication.  The result represents the transformation M2
// followed by the transformation M1.  (Out = M1 * M2)
HFMATRIX*  HFMatrixMultiply
(HFMATRIX *pOut, const HFMATRIX *pM1, const HFMATRIX *pM2);

// Matrix multiplication, followed by a transpose. (Out = T(M1 * M2))
HFMATRIX*  HFMatrixMultiplyTranspose
(HFMATRIX *pOut, const HFMATRIX *pM1, const HFMATRIX *pM2);

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

// Yaw around the Y axis, a pitch around the X axis,
// and a roll around the Z axis.
HFMATRIX*  HFMatrixRotationYawPitchRoll
(HFMATRIX *pOut, FLOAT Yaw, FLOAT Pitch, FLOAT Roll);

// Build transformation matrix.  NULL arguments are treated as identity.
// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
HFMATRIX*  HFMatrixTransformation
(HFMATRIX *pOut, const HFVECTOR3 *pScalingCenter,
	const HFQUATERNION *pScalingRotation, const HFVECTOR3 *pScaling,
	const HFVECTOR3 *pRotationCenter, const HFQUATERNION *pRotation,
	const HFVECTOR3 *pTranslation);

// Build 2D transformation matrix in XY plane.  NULL arguments are treated as identity.
// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
HFMATRIX*  HFMatrixTransformation2D
(HFMATRIX *pOut, const HFVECTOR2* pScalingCenter,
	FLOAT ScalingRotation, const HFVECTOR2* pScaling,
	const HFVECTOR2* pRotationCenter, FLOAT Rotation,
	const HFVECTOR2* pTranslation);

// Build affine transformation matrix.  NULL arguments are treated as identity.
// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
HFMATRIX*  HFMatrixAffineTransformation
(HFMATRIX *pOut, FLOAT Scaling, const HFVECTOR3 *pRotationCenter,
	const HFQUATERNION *pRotation, const HFVECTOR3 *pTranslation);

// Build 2D affine transformation matrix in XY plane.  NULL arguments are treated as identity.
// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
HFMATRIX*  HFMatrixAffineTransformation2D
(HFMATRIX *pOut, FLOAT Scaling, const HFVECTOR2* pRotationCenter,
	FLOAT Rotation, const HFVECTOR2* pTranslation);

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

// Build a perspective projection matrix. (right-handed)
HFMATRIX*  HFMatrixPerspectiveOffCenterRH
(HFMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn,
	FLOAT zf);

// Build a perspective projection matrix. (left-handed)
HFMATRIX*  HFMatrixPerspectiveOffCenterLH
(HFMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn,
	FLOAT zf);

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

// Build a matrix which flattens geometry into a plane, as if casting
// a shadow from a light.
HFMATRIX*  HFMatrixShadow
(HFMATRIX *pOut, const HFVECTOR4 *pLight,
	const HFPLANE *pPlane);

// Build a matrix which reflects the coordinate system about a plane
HFMATRIX*  HFMatrixReflect
(HFMATRIX *pOut, const HFPLANE *pPlane);

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

//--------------------------
// Plane
//--------------------------

// inline

// ax + by + cz + dw
FLOAT HFPlaneDot
(const HFPLANE *pP, const HFVECTOR4 *pV);

// ax + by + cz + d
FLOAT HFPlaneDotCoord
(const HFPLANE *pP, const HFVECTOR3 *pV);

// ax + by + cz
FLOAT HFPlaneDotNormal
(const HFPLANE *pP, const HFVECTOR3 *pV);

HFPLANE* HFPlaneScale
(HFPLANE *pOut, const HFPLANE *pP, FLOAT s);

// non-inline

// Normalize plane (so that |a,b,c| == 1)
HFPLANE*  HFPlaneNormalize
(HFPLANE *pOut, const HFPLANE *pP);

// Find the intersection between a plane and a line.  If the line is
// parallel to the plane, NULL is returned.
HFVECTOR3*  HFPlaneIntersectLine
(HFVECTOR3 *pOut, const HFPLANE *pP, const HFVECTOR3 *pV1,
	const HFVECTOR3 *pV2);

// construct a plane from a point and a normal
HFPLANE*  HFPlaneFromPointNormal
(HFPLANE *pOut, const HFVECTOR3 *pPoint, const HFVECTOR3 *pNormal);

// construct a plane from 3 points
HFPLANE*  HFPlaneFromPoints
(HFPLANE *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2,
	const HFVECTOR3 *pV3);

// Transform a plane by a matrix.  The std::vector (a,b,c) must be normal.
// M should be the inverse transpose of the transformation desired.
HFPLANE*  HFPlaneTransform
(HFPLANE *pOut, const HFPLANE *pP, const HFMATRIX *pM);

// Transform an array of planes by a matrix.  The vectors (a,b,c) must be normal.
// M should be the inverse transpose of the transformation desired.
HFPLANE*  HFPlaneTransformArray
(HFPLANE *pOut, UINT OutStride, const HFPLANE *pP, UINT PStride, const HFMATRIX *pM, UINT n);

//--------------------------
// Color
//--------------------------

// inline

// (1-r, 1-g, 1-b, a)
HFCOLOR* HFColorNegative
(HFCOLOR *pOut, const HFCOLOR *pC);

HFCOLOR* HFColorAdd
(HFCOLOR *pOut, const HFCOLOR *pC1, const HFCOLOR *pC2);

HFCOLOR* HFColorSubtract
(HFCOLOR *pOut, const HFCOLOR *pC1, const HFCOLOR *pC2);

HFCOLOR* HFColorScale
(HFCOLOR *pOut, const HFCOLOR *pC, FLOAT s);

// (r1*r2, g1*g2, b1*b2, a1*a2)
HFCOLOR* HFColorModulate
(HFCOLOR *pOut, const HFCOLOR *pC1, const HFCOLOR *pC2);

// Linear interpolation of r,g,b, and a. C1 + s(C2-C1)
HFCOLOR* HFColorLerp
(HFCOLOR *pOut, const HFCOLOR *pC1, const HFCOLOR *pC2, FLOAT s);

// non-inline

// Interpolate r,g,b between desaturated color and color.
// DesaturatedColor + s(Color - DesaturatedColor)
HFCOLOR*  HFColorAdjustSaturation
(HFCOLOR *pOut, const HFCOLOR *pC, FLOAT s);

// Interpolate r,g,b between 50% grey and color.  Grey + s(Color - Grey)
HFCOLOR*  HFColorAdjustContrast
(HFCOLOR *pOut, const HFCOLOR *pC, FLOAT c);

//--------------------------
// Misc
//--------------------------

// Calculate Fresnel term given the cosine of theta (likely obtained by
// taking the dot of two normals), and the refraction index of the material.
FLOAT  HFFresnelTerm(FLOAT CosTheta, FLOAT RefractionIndex);
