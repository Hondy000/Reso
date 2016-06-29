/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Collision\CollisionAPI.cpp
 *
 * @brief	Implements the collision a pi class.
 **************************************************************************************************/

#include "../Public/CollisionAPI.h"
#include "..\CollisionObject\Public\OBBCollisionObject.h"

/**********************************************************************************************//**
 * @fn	bool isCollisionOfPlanesAndOBB( CCollisionPlanesObject* planes, CollisionOBBObject* obb)
 *
 * @brief	Query if 'planes' is collision of planes and obb.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param [in,out]	planes	If non-null, the planes.
 * @param [in,out]	obb   	If non-null, the obb.
 *
 * @return	true if collision of planes and obb, false if not.
 **************************************************************************************************/

bool isCollisionOfPlanesAndOBB(CollisionPlanesObject* planes, CollisionOBBObject* obb)
{
	const HFVECTOR3* pvec = obb->GetDirection();
	int collisionCount = 0;
	for (int i = 0; i < planes->GetPlaneCount(); i++)
	{
		HFVECTOR3 pos;
		HFVECTOR3 distance;
		if (isCollisionOfPlaneAndOBB(planes->GetPlaneInfoArray()[i].get(), obb, &pos, &distance))
		{
			collisionCount++;
		}
	}
	if (collisionCount > 0)
	{
		return true;
	}
	return false;
}

/**********************************************************************************************//**
 * @fn	bool isCollisionOfPlaneAndOBB(CCollisionPlanesObject::PLANE_INFO *plane, CollisionOBBObject *obb, HFVECTOR3 * collisionPosition, HFVECTOR3 * pushBack)
 *
 * @brief	1枚の平面とOBB.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param [in,out]	plane			 	If non-null, the plane.
 * @param [in,out]	obb				 	If non-null, the obb.
 * @param [in,out]	collisionPosition	If non-null, the collision position.
 * @param [in,out]	pushBack		 	If non-null, the push back.
 *
 * @return	true if collision of plane and obb, false if not.
 **************************************************************************************************/

bool isCollisionOfPlaneAndOBB(CollisionPlanesObject::PLANE_INFO *plane, CollisionOBBObject *obb, HFVECTOR3 * collisionPosition, HFVECTOR3 * pushBack)
{
	// 平面の法線に対するOBBの射影線の長さを算出
	FLOAT r = 0.0f;          // 近接距離
	HFVECTOR3 PlaneNormal = plane->normal; // 平面の法線ベクトル
	float length = 0;
	int i;
	for (i = 0; i < 3; i++) {
		HFVECTOR3 Direct = obb->GetDirection(i); // OBBの1つの軸ベクトル
		r += fabs(HFVec3Dot(&(Direct * obb->GetLength(i)), &PlaneNormal));
	}

	// 平面とOBBの距離を算出
	HFVECTOR3 ObbPos = obb->UpdateCenterPosition();
	HFVECTOR3 PlanePos = plane->GetCenter();
	FLOAT s = HFVec3Dot(&(ObbPos - PlanePos), &PlaneNormal);

	// 戻し距離を算出
	if (pushBack != NULL) {
		if (s > 0)
			length = r - fabs(s);
		else
			length = r + fabs(s);
	}

	// 衝突判定
	if (fabs(s) - r < 0.0f)
	{
		*pushBack = plane->normal * length;
		return true; // 衝突している
	}
	return false; // 衝突していない
}

//---------------------------------------------------------------------------------------
//	３角形の内部にあるかどうかを判定
//---------------------------------------------------------------------------------------
BOOL CheckInTriangle(const HFVECTOR3	*a,
	const HFVECTOR3	*b,
	const HFVECTOR3	*c,
	const HFVECTOR3	*p) {
	HFVECTOR3  ab, bc, ca;			// ３辺のベクトル
	HFVECTOR3  ap, bp, cp;			// 内部の点とのベクトル
	HFVECTOR3	 normal;			// ３角形の法線ベクトル
	HFVECTOR3	 n1, n2, n3;			// ３辺と内部の点との法線ベクトル

	ab = *b - *a;
	bc = *c - *b;
	ca = *a - *c;

	ap = *p - *a;
	bp = *p - *b;
	cp = *p - *c;

	normal = HFVec3Cross(ab, bc);

	n1 = HFVec3Cross(ab, ap);
	n2 = HFVec3Cross(bc, bp);
	n3 = HFVec3Cross(ca, cp);

	if (HFVec3Dot(&n1, &normal) < 0) return FALSE;
	if (HFVec3Dot(&n2, &normal) < 0) return FALSE;
	if (HFVec3Dot(&n3, &normal) < 0) return FALSE;
	return TRUE;
}

/**********************************************************************************************//**
 * @fn	bool isCollisionOfPlaneAndRay(CCollisionPlanesObject::PLANE_INFO plane, CBaseCollisionObject::COLLISION_RAY_INFO ray , HFVECTOR3* collisionPoint)
 *
 * @brief	Query if 'plane' is collision of plane and ray.
 *
 * @author	Kazuyuki Honda
 * @date	2015/11/04
 *
 * @param	plane				  	The plane.
 * @param	ray					  	The ray.
 * @param [in,out]	collisionPoint	If non-null, the collision point.
 *
 * @return	true if collision of plane and ray, false if not.
 **************************************************************************************************/

bool isCollisionOfPlaneAndRay(CollisionPlanesObject::PLANE_INFO plane, BaseCollisionObject::COLLISION_RAY_INFO ray, HFVECTOR3* collisionPoint)
{
	/*
	float dot_work = plane.plane.a * ray.startPoint.x + plane.plane.b*ray.startPoint.y + plane.plane.c* ray.startPoint.z + plane.plane.d;
	float normal_len = plane.plane.a*plane.plane.a + plane.plane.b*plane.plane.b + plane.plane.c*plane.plane.c;

	// 交点を求める
	float t = -1.0f * dot_work / normal_len;

	collisionPoint->x = ray.startPoint.x + plane.plane.a * t;
	collisionPoint->y = ray.startPoint.y + plane.plane.b * t;
	collisionPoint->z = ray.startPoint.z + plane.plane.c * t;

	float length = fabs(dot_work); // ÷ sqrtf(normal_len);	// 平面の法線を正規化しているのでsqrtは省きました

	if(HFVec3Length(&ray.direction) < length)
	{
		return false;
	}
	else
	{
		return true;
	}
	*/

	HFVECTOR3 p = HFVECTOR3(plane.plane.x * plane.plane.w, plane.plane.y * plane.plane.w, plane.plane.z * plane.plane.w);
	HFVECTOR3 normal = HFVECTOR3(plane.plane.x, plane.plane.y, plane.plane.z);
	float c = HFVec3Dot(&p, &plane.normal);
	float dot = HFVec3Dot(&normal, &ray.direction);
	if (dot == 0)
	{
		return false;
	}

	float t = -((HFVec3Dot(&normal, &ray.startPoint) + plane.plane.w) / HFVec3Dot(&normal, &ray.direction));
	*collisionPoint = ray.startPoint + ray.direction * t;

	//LengthPointToPlane(line_o, plane, ans);

	return true;
}

// 平面と 球体
bool isCollisionPlaneAndSphere
(
	CollisionPlanesObject::PLANE_INFO  plane,
	CollisionSphereObject* sphere,
	HFVECTOR3* point,
	HFVECTOR3* pushDistance,
	float* time
	)
{
	HFVECTOR3 pos, prePos, planeCenter;
	pos = sphere->GetCenter();
	prePos = sphere->GetOldPosition();
	planeCenter = plane.GetCenter();
	HFVECTOR3 move = prePos - planeCenter; // 平面上の一点から現在位置へのベクトル
	HFVECTOR3 distance = pos - prePos; // 現在位置から予定位置までのベクトル
	HFVECTOR3 normal; // 法線

	normal = HFVec3Normalize(HFVECTOR3(plane.normal)); // 法線を標準化

	// 平面と中心点の距離を算出
	FLOAT Dot_C0 = HFVec3Dot(&move, &normal);
	FLOAT dist_plane_to_point = fabs(Dot_C0);

	// 進行方向と法線の関係をチェック
	FLOAT Dot = HFVec3Dot(&distance, &normal);

	// 平面と平行に移動してめり込んでいるスペシャルケース
	if ((0.00001f - fabs(Dot) > 0.0f) && (dist_plane_to_point < sphere->GetSize()))
	{
		// 一生抜け出せないので最大時刻を返す
		*time = FLT_MAX;

		// 衝突位置は仕方ないので今の位置を指定
		*point = prePos;
		*pushDistance = normal * (sphere)->GetSize();
		return true;
	}

	// 交差時間の算出
	*time = (sphere->GetSize() - Dot_C0) / Dot;

	// 衝突位置の算出
	*point = prePos + (*time) * distance;

	// めり込んでいたら衝突として処理終了
	if (dist_plane_to_point < sphere->GetSize())
	{
		*pushDistance = normal * sphere->GetSize();
		return true;
	}

	// 壁に対して移動が逆向きなら衝突していない
	if (Dot >= 0)
	{
		return false;
	}

	// 時間が0～1の間にあれば衝突
	if ((0 <= *time) && (*time <= 1))
	{
		HFVECTOR3 vec = HFVECTOR3(HFVECTOR3(1, 1, 1));
		HFVECTOR3 move = HFVECTOR3(distance.x * vec.x, distance.y * vec.y, distance.z * vec.z) + normal * sphere->GetSize();
		*point += move;
		*pushDistance = normal * (sphere)->GetSize();
		return true;
	}
	return false;
}

// 複数の平面と球体
bool isCollisionPlanesAndSphere
(
	CollisionPlanesObject* plane,
	CollisionSphereObject* sphere,
	HFVECTOR3* point,
	HFVECTOR3* pushDistance,
	float* time
	)
{
	float t;
	HFVECTOR3 position;
	BaseCollisionObject::COLLISION_RAY_INFO ray;
	ray.startPoint = sphere->GetCenter();
	ray.direction = sphere->GetOldPosition() - sphere->GetCenter();
	ray.direction = HFVec3Normalize(ray.direction);
	for (int i = 0; i < plane->GetPlaneInfoArray().size(); i++)
	{
		if (CheckInTriangle(&plane->GetPlaneInfoArray().at(i)->p0,
			&plane->GetPlaneInfoArray().at(i)->p1,
			&plane->GetPlaneInfoArray().at(i)->p2,
			&sphere->GetCenter()
			))
		{
			if (isCollisionPlaneAndSphere(*plane->GetPlaneInfoArray()[i], sphere, point, pushDistance, time))
			{
				//*point += plane->GetPlaneInfoArray().at(i)->normal * sphere->GetSize();
				return true;
			}
		}
	}
	return false;
}