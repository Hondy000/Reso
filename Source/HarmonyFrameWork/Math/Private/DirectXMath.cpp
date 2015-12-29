#include "../Public/DirectXMath.h"
#include "../Public/HFMath.h"
#ifdef DIRECTX

//--------------------------
// 3D Vector
//--------------------------

// inline

FLOAT HFVec3Length
(const HFVECTOR3 *pV)
{
	return D3DXVec3Length(pV);
};

FLOAT HFVec3LengthSq
(const HFVECTOR3 *pV)
{
	return 	HFVec3LengthSq(pV);
};

FLOAT HFVec3Dot
(const HFVECTOR3 *pV1, const HFVECTOR3 *pV2)
{
	return D3DXVec3Dot(pV1, pV2);
};

HFVECTOR3* HFVec3Cross
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2)
{
	return D3DXVec3Cross(pOut, pV1, pV2);
};

HFVECTOR3* HFVec3Add
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2)
{
	return D3DXVec3Add(pOut, pV1, pV2);
};

HFVECTOR3* HFVec3Subtract
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2)
{
	return D3DXVec3Subtract(pOut, pV1, pV2);
};

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
(HFVECTOR3 *pOut, const HFVECTOR3 *pV)
{
	return D3DXVec3Normalize(pOut, pV);
};

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
HFVECTOR3*  HFVec3Hermite
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pT1,
	const HFVECTOR3 *pV2, const HFVECTOR3 *pT2, FLOAT s)
{
	return D3DXVec3Hermite(pOut, pV1, pT1, pV2, pT2, s);
};

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
HFVECTOR3*  HFVec3CatmullRom
(HFVECTOR3 *pOut, const HFVECTOR3 *pV0, const HFVECTOR3 *pV1,
	const HFVECTOR3 *pV2, const HFVECTOR3 *pV3, FLOAT s);

// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
HFVECTOR3*  HFVec3BaryCentric
(HFVECTOR3 *pOut, const HFVECTOR3 *pV1, const HFVECTOR3 *pV2,
	const HFVECTOR3 *pV3, FLOAT f, FLOAT g)
{
	return D3DXVec3BaryCentric(pOut, pV1, pV2, pV3, f, g);
};

// Transform (x, y, z, 1) by matrix.
HFVECTOR4*  HFVec3Transform
(HFVECTOR4 *pOut, const HFVECTOR3 *pV, const HFMATRIX *pM)
{
	return D3DXVec3Transform(pOut, pV, pM);
};

// Transform (x, y, z, 1) by matrix, project result back into w=1.
HFVECTOR3*  HFVec3TransformCoord
(HFVECTOR3 *pOut, const HFVECTOR3 *pV, const HFMATRIX *pM)
{
	return D3DXVec3TransformCoord(pOut, pV, pM);
};

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
// 4D Matrix
//--------------------------

// inline

HFMATRIX* HFMatrixIdentity(HFMATRIX *pOut)
{
	return D3DXMatrixIdentity(pOut);
};

BOOL HFMatrixIsIdentity(CONST HFMATRIX *pM)
{
	return D3DXMatrixIsIdentity(pM);
};

FLOAT  HFMatrixDeterminant(CONST HFMATRIX *pM)
{
	return D3DXMatrixDeterminant(pM);
};

HRESULT  HFMatrixDecompose
(HFVECTOR3 *pOutScale, HFQUATERNION *pOutRotation,
	HFVECTOR3 *pOutTranslation, CONST HFMATRIX *pM)
{
	return D3DXMatrixDecompose(pOutScale, pOutRotation, pOutTranslation, pM);
};

HFMATRIX*  HFMatrixTranspose
(HFMATRIX *pOut, CONST HFMATRIX *pM)
{
	return D3DXMatrixTranspose(pOut, pM);
};

// Matrix multiplication.  The result represents the transformation M2
// followed by the transformation M1.  (Out = M1 * M2)
HFMATRIX*  HFMatrixMultiply
(HFMATRIX *pOut, CONST HFMATRIX *pM1, CONST HFMATRIX *pM2)
{
	return D3DXMatrixMultiply(pOut, pM1, pM2);
};

// Matrix multiplication, followed by a transpose. (Out = T(M1 * M2))
HFMATRIX*  HFMatrixMultiplyTranspose
(HFMATRIX *pOut, CONST HFMATRIX *pM1, CONST HFMATRIX *pM2)
{
	return D3DXMatrixMultiplyTranspose(pOut, pM1, pM2);
};

// Calculate inverse of matrix.  Inversion my fail, in which case NULL will
// be returned.  The determinant of pM is also returned it pfDeterminant
// is non-NULL.
HFMATRIX*  HFMatrixInverse
(HFMATRIX *pOut, FLOAT *pDeterminant, CONST HFMATRIX *pM)
{
	return D3DXMatrixInverse(pOut, pDeterminant, pM);
};

// Build a matrix which scales by (sx, sy, sz)
HFMATRIX*  HFMatrixScaling
(HFMATRIX *pOut, FLOAT sx, FLOAT sy, FLOAT sz)
{
	return D3DXMatrixScaling(pOut, sx, sy, sz);
};

// Build a matrix which translates by (x, y, z)
HFMATRIX*  HFMatrixTranslation
(HFMATRIX *pOut, FLOAT x, FLOAT y, FLOAT z)
{
	return D3DXMatrixTranslation(pOut, x, y, z);
};

// Build a matrix which rotates around the X axis
HFMATRIX*  HFMatrixRotationX
(HFMATRIX *pOut, FLOAT Angle)
{
	return D3DXMatrixRotationX(pOut, Angle);
};

// Build a matrix which rotates around the Y axis
HFMATRIX*  HFMatrixRotationY
(HFMATRIX *pOut, FLOAT Angle)
{
	return D3DXMatrixRotationY(pOut, Angle);
};

// Build a matrix which rotates around the Z axis
HFMATRIX*  HFMatrixRotationZ
(HFMATRIX *pOut, FLOAT Angle)
{
	return D3DXMatrixRotationX(pOut, Angle);
};

// Build a matrix which rotates around an arbitrary axis
HFMATRIX*  HFMatrixRotationAxis
(HFMATRIX *pOut, CONST HFVECTOR3 *pV, FLOAT Angle)
{
	return D3DXMatrixRotationAxis(pOut, pV, Angle);
};

// Build a matrix from a quaternion
HFMATRIX*  HFMatrixRotationQuaternion
(HFMATRIX *pOut, CONST HFQUATERNION *pQ)
{
	return D3DXMatrixRotationQuaternion(pOut, pQ);
};

// Yaw around the Y axis, a pitch around the X axis,
// and a roll around the Z axis.
HFMATRIX*  HFMatrixRotationYawPitchRoll
(HFMATRIX *pOut, FLOAT Yaw, FLOAT Pitch, FLOAT Roll)
{
	return D3DXMatrixRotationYawPitchRoll(pOut, Yaw, Pitch, Roll);
};

// Build transformation matrix.  NULL arguments are treated as identity.
// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
HFMATRIX*  HFMatrixTransformation
(HFMATRIX *pOut, CONST HFVECTOR3 *pScalingCenter,
	CONST HFQUATERNION *pScalingRotation, CONST HFVECTOR3 *pScaling,
	CONST HFVECTOR3 *pRotationCenter, CONST HFQUATERNION *pRotation,
	CONST HFVECTOR3 *pTranslation)
{
	return D3DXMatrixTransformation(
		pOut,
		pScalingCenter,
		pScalingRotation,
		pScaling,
		pRotationCenter,
		pRotation,
		pTranslation);
};

// Build 2D transformation matrix in XY plane.  NULL arguments are treated as identity.
// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
HFMATRIX*  HFMatrixTransformation2D
(HFMATRIX *pOut, CONST HFVECTOR2* pScalingCenter,
	FLOAT ScalingRotation, CONST HFVECTOR2* pScaling,
	CONST HFVECTOR2* pRotationCenter, FLOAT Rotation,
	CONST HFVECTOR2* pTranslation)
{
	return D3DXMatrixTransformation2D(
		pOut,
		pScalingCenter,
		ScalingRotation,
		pScaling,
		pRotationCenter,
		Rotation,
		pTranslation);
};

// Build affine transformation matrix.  NULL arguments are treated as identity.
// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
HFMATRIX*  HFMatrixAffineTransformation
(HFMATRIX *pOut, FLOAT Scaling, CONST HFVECTOR3 *pRotationCenter,
	CONST HFQUATERNION *pRotation, CONST HFVECTOR3 *pTranslation)
{
	return D3DXMatrixAffineTransformation(
		pOut,
		Scaling,
		pRotationCenter,
		pRotation,
		pTranslation);
};

// Build 2D affine transformation matrix in XY plane.  NULL arguments are treated as identity.
// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
HFMATRIX*  HFMatrixAffineTransformation2D
(HFMATRIX *pOut, FLOAT Scaling, CONST HFVECTOR2* pRotationCenter,
	FLOAT Rotation, CONST HFVECTOR2* pTranslation)
{
	return D3DXMatrixAffineTransformation2D(
		pOut,
		Scaling,
		pRotationCenter,
		Rotation,
		pTranslation);
};

// Build a lookat matrix. (right-handed)
HFMATRIX*  HFMatrixLookAtRH
(HFMATRIX *pOut, CONST HFVECTOR3 *pEye, CONST HFVECTOR3 *pAt,
	CONST HFVECTOR3 *pUp)
{
	return D3DXMatrixLookAtRH(pOut, pEye, pAt, pUp);
};

// Build a lookat matrix. (left-handed)
HFMATRIX*  HFMatrixLookAtLH
(HFMATRIX *pOut, CONST HFVECTOR3 *pEye, CONST HFVECTOR3 *pAt,
	CONST HFVECTOR3 *pUp)
{
	return D3DXMatrixLookAtLH(pOut, pEye, pAt, pUp);
};

// Build a perspective projection matrix. (right-handed)
HFMATRIX*  HFMatrixPerspectiveRH
(HFMATRIX *pOut, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf)
{
	return D3DXMatrixPerspectiveRH(pOut, w, h, zn, zf);
};

// Build a perspective projection matrix. (left-handed)
HFMATRIX*  HFMatrixPerspectiveLH
(HFMATRIX *pOut, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf)
{
	return D3DXMatrixPerspectiveLH(pOut, w, h, zn, zf);
};

// Build a perspective projection matrix. (right-handed)
HFMATRIX*  HFMatrixPerspectiveFovRH
(HFMATRIX *pOut, FLOAT fovy, FLOAT Aspect, FLOAT zn, FLOAT zf)
{
	return D3DXMatrixPerspectiveRH(pOut, fovy, Aspect, zn, zf);
};

// Build a perspective projection matrix. (left-handed)
HFMATRIX*  HFMatrixPerspectiveFovLH
(HFMATRIX *pOut, FLOAT fovy, FLOAT Aspect, FLOAT zn, FLOAT zf)
{
	return D3DXMatrixPerspectiveFovLH(pOut, fovy, Aspect, zn, zf);
};

// Build a perspective projection matrix. (right-handed)
HFMATRIX*  HFMatrixPerspectiveOffCenterRH
(HFMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn,
	FLOAT zf)
{
	return D3DXMatrixPerspectiveOffCenterRH(pOut, l, r, b, t, zn, zf);
};

// Build a perspective projection matrix. (left-handed)
HFMATRIX*  HFMatrixPerspectiveOffCenterLH
(HFMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn,
	FLOAT zf)
{
	return D3DXMatrixPerspectiveOffCenterLH(pOut, l, r, b, t, zn, zf);
};

// Build an ortho projection matrix. (right-handed)
HFMATRIX*  HFMatrixOrthoRH
(HFMATRIX *pOut, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf)
{
	return D3DXMatrixOrthoRH(pOut, w, h, zn, zf);
};

// Build an ortho projection matrix. (left-handed)
HFMATRIX*  HFMatrixOrthoLH
(HFMATRIX *pOut, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf)
{
	return D3DXMatrixOrthoLH(pOut, w, h, zn, zf);
};

// Build an ortho projection matrix. (right-handed)
HFMATRIX*  HFMatrixOrthoOffCenterRH
(HFMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn,
	FLOAT zf)
{
	return D3DXMatrixOrthoOffCenterRH(pOut, l, r, b, t, zn, zf);
};

// Build an ortho projection matrix. (left-handed)
HFMATRIX*  HFMatrixOrthoOffCenterLH
(HFMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn,
	FLOAT zf)
{
	return D3DXMatrixOrthoOffCenterLH(pOut, l, r, b, t, zn, zf);
};

// Build a matrix which flattens geometry into a plane, as if casting
// a shadow from a light.
HFMATRIX*  HFMatrixShadow
(HFMATRIX *pOut, CONST HFVECTOR4 *pLight,
	CONST HFPLANE *pPlane);

// Build a matrix which reflects the coordinate system about a plane
HFMATRIX*  HFMatrixReflect
(HFMATRIX *pOut, CONST HFPLANE *pPlane);

//--------------------------
// Quaternion
//--------------------------

// inline

FLOAT HFQuaternionLength
(CONST HFQUATERNION *pQ)
{
	return D3DXQuaternionLength(pQ);
};

// Length squared, or "norm"
FLOAT HFQuaternionLengthSq
(CONST HFQUATERNION *pQ)
{
	return D3DXQuaternionLengthSq(pQ);
};

FLOAT HFQuaternionDot
(CONST HFQUATERNION *pQ1, CONST HFQUATERNION *pQ2)
{
	return D3DXQuaternionDot(pQ1, pQ2);
};

// (0, 0, 0, 1)
HFQUATERNION* HFQuaternionIdentity
(HFQUATERNION *pOut)
{
	return D3DXQuaternionIdentity(pOut);
};

BOOL HFQuaternionIsIdentity
(CONST HFQUATERNION *pQ)
{
	return D3DXQuaternionIsIdentity(pQ);
};

// (-x, -y, -z, w)
HFQUATERNION* HFQuaternionConjugate
(HFQUATERNION *pOut, CONST HFQUATERNION *pQ)
{
	return D3DXQuaternionConjugate(pOut, pQ);
};

// Compute a quaternin's axis and angle of rotation. Expects unit quaternions.
void  HFQuaternionToAxisAngle
(CONST HFQUATERNION *pQ, HFVECTOR3 *pAxis, FLOAT *pAngle)
{
	D3DXQuaternionToAxisAngle(pQ, pAxis, pAngle);
};

// Build a quaternion from a rotation matrix.
HFQUATERNION*  HFQuaternionRotationMatrix
(HFQUATERNION *pOut, CONST HFMATRIX *pM)
{
	return D3DXQuaternionRotationMatrix(pOut, pM);
};

// Rotation about arbitrary axis.
HFQUATERNION*  HFQuaternionRotationAxis
(HFQUATERNION *pOut, CONST HFVECTOR3 *pV, FLOAT Angle)
{
	return D3DXQuaternionRotationAxis(pOut, pV, Angle);
};

// Yaw around the Y axis, a pitch around the X axis,
// and a roll around the Z axis.
HFQUATERNION*  HFQuaternionRotationYawPitchRoll
(HFQUATERNION *pOut, FLOAT Yaw, FLOAT Pitch, FLOAT Roll)
{
	return D3DXQuaternionRotationYawPitchRoll(pOut, Yaw, Pitch, Roll);
};

// Quaternion multiplication.  The result represents the rotation Q2
// followed by the rotation Q1.  (Out = Q2 * Q1)
HFQUATERNION*  HFQuaternionMultiply
(HFQUATERNION *pOut, CONST HFQUATERNION *pQ1,
	CONST HFQUATERNION *pQ2)
{
	return D3DXQuaternionMultiply(pOut, pQ1, pQ2);
};

HFQUATERNION*  HFQuaternionNormalize
(HFQUATERNION *pOut, CONST HFQUATERNION *pQ)
{
	return D3DXQuaternionNormalize(pOut, pQ);
};

// Conjugate and re-norm
HFQUATERNION*  HFQuaternionInverse
(HFQUATERNION *pOut, CONST HFQUATERNION *pQ)
{
	return D3DXQuaternionInverse(pOut, pQ);
};

// Expects unit quaternions.
// if q = (cos(theta), sin(theta) * v); ln(q) = (0, theta * v)
HFQUATERNION*  HFQuaternionLn
(HFQUATERNION *pOut, CONST HFQUATERNION *pQ)
{
	return D3DXQuaternionLn(pOut, pQ);
};

// Expects pure quaternions. (w == 0)  w is ignored in calculation.
// if q = (0, theta * v); exp(q) = (cos(theta), sin(theta) * v)
HFQUATERNION*  HFQuaternionExp
(HFQUATERNION *pOut, CONST HFQUATERNION *pQ)
{
	return D3DXQuaternionExp(pOut, pQ);
};

// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1).
// Expects unit quaternions.
HFQUATERNION*  HFQuaternionSlerp
(HFQUATERNION *pOut, CONST HFQUATERNION *pQ1,
	CONST HFQUATERNION *pQ2, FLOAT t)
{
	return D3DXQuaternionSlerp(pOut, pQ1, pQ2, t);
};

// Spherical quadrangle interpolation.
// Slerp(Slerp(Q1, C, t), Slerp(A, B, t), 2t(1-t))
HFQUATERNION*  HFQuaternionSquad
(HFQUATERNION *pOut, CONST HFQUATERNION *pQ1,
	CONST HFQUATERNION *pA, CONST HFQUATERNION *pB,
	CONST HFQUATERNION *pC, FLOAT t)
{
	return D3DXQuaternionSquad(pOut, pQ1, pA, pB, pC, t);
};

// Setup control points for spherical quadrangle interpolation
// from Q1 to Q2.  The control points are chosen in such a way
// to ensure the continuity of tangents with adjacent segments.
void  HFQuaternionSquadSetup
(HFQUATERNION *pAOut, HFQUATERNION *pBOut, HFQUATERNION *pCOut,
	CONST HFQUATERNION *pQ0, CONST HFQUATERNION *pQ1,
	CONST HFQUATERNION *pQ2, CONST HFQUATERNION *pQ3)
{
	return D3DXQuaternionSquadSetup(pAOut, pBOut, pCOut, pQ0, pQ1, pQ2, pQ3);
};

// Barycentric interpolation.
// Slerp(Slerp(Q1, Q2, f+g), Slerp(Q1, Q3, f+g), g/(f+g))
HFQUATERNION*  HFQuaternionBaryCentric
(HFQUATERNION *pOut, CONST HFQUATERNION *pQ1,
	CONST HFQUATERNION *pQ2, CONST HFQUATERNION *pQ3,
	FLOAT f, FLOAT g)
{
	return D3DXQuaternionBaryCentric(pOut, pQ1, pQ2, pQ3, f, g);
};

//--------------------------
// Plane
//--------------------------

// inline

// ax + by + cz + dw
FLOAT HFPlaneDot
(CONST HFPLANE *pP, CONST HFVECTOR4 *pV);

// ax + by + cz + d
FLOAT HFPlaneDotCoord
(CONST HFPLANE *pP, CONST HFVECTOR3 *pV);

// ax + by + cz
FLOAT HFPlaneDotNormal
(CONST HFPLANE *pP, CONST HFVECTOR3 *pV);

HFPLANE* HFPlaneScale
(HFPLANE *pOut, CONST HFPLANE *pP, FLOAT s);

// Normalize plane (so that |a,b,c| == 1)
HFPLANE*  HFPlaneNormalize
(HFPLANE *pOut, CONST HFPLANE *pP);

// Find the intersection between a plane and a line.  If the line is
// parallel to the plane, NULL is returned.
HFVECTOR3*  HFPlaneIntersectLine
(HFVECTOR3 *pOut, CONST HFPLANE *pP, CONST HFVECTOR3 *pV1,
	CONST HFVECTOR3 *pV2);

// Construct a plane from a point and a normal
HFPLANE*  HFPlaneFromPointNormal
(HFPLANE *pOut, CONST HFVECTOR3 *pPoint, CONST HFVECTOR3 *pNormal);

// Construct a plane from 3 points
HFPLANE*  HFPlaneFromPoints
(HFPLANE *pOut, CONST HFVECTOR3 *pV1, CONST HFVECTOR3 *pV2,
	CONST HFVECTOR3 *pV3);

// Transform a plane by a matrix.  The std::vector (a,b,c) must be normal.
// M should be the inverse transpose of the transformation desired.
HFPLANE*  HFPlaneTransform
(HFPLANE *pOut, CONST HFPLANE *pP, CONST HFMATRIX *pM);

// Transform an array of planes by a matrix.  The vectors (a,b,c) must be normal.
// M should be the inverse transpose of the transformation desired.
HFPLANE*  HFPlaneTransformArray
(HFPLANE *pOut, UINT OutStride, CONST HFPLANE *pP, UINT PStride, CONST HFMATRIX *pM, UINT n);

//--------------------------
// Color
//--------------------------

// inline

// (1-r, 1-g, 1-b, a)
HFCOLOR* HFColorNegative
(HFCOLOR *pOut, CONST HFCOLOR *pC);

HFCOLOR* HFColorAdd
(HFCOLOR *pOut, CONST HFCOLOR *pC1, CONST HFCOLOR *pC2);

HFCOLOR* HFColorSubtract
(HFCOLOR *pOut, CONST HFCOLOR *pC1, CONST HFCOLOR *pC2);

HFCOLOR* HFColorScale
(HFCOLOR *pOut, CONST HFCOLOR *pC, FLOAT s);

// (r1*r2, g1*g2, b1*b2, a1*a2)
HFCOLOR* HFColorModulate
(HFCOLOR *pOut, CONST HFCOLOR *pC1, CONST HFCOLOR *pC2);

// Linear interpolation of r,g,b, and a. C1 + s(C2-C1)
HFCOLOR* HFColorLerp
(HFCOLOR *pOut, CONST HFCOLOR *pC1, CONST HFCOLOR *pC2, FLOAT s);

// Interpolate r,g,b between desaturated color and color.
// DesaturatedColor + s(Color - DesaturatedColor)
HFCOLOR*  HFColorAdjustSaturation
(HFCOLOR *pOut, CONST HFCOLOR *pC, FLOAT s);

// Interpolate r,g,b between 50% grey and color.  Grey + s(Color - Grey)
HFCOLOR*  HFColorAdjustContrast
(HFCOLOR *pOut, CONST HFCOLOR *pC, FLOAT c);

//--------------------------
// Misc
//--------------------------

// Calculate Fresnel term given the cosine of theta (likely obtained by
// taking the dot of two normals), and the refraction index of the material.
FLOAT  HFFresnelTerm
(FLOAT CosTheta, FLOAT RefractionIndex);

#endif