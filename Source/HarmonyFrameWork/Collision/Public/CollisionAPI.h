
#include "../../Core/Public/Common.h"
#include "..\CollisionObject\Public\CollisionPlanesObject.h"
#include "..\CollisionObject\Public\CollisionSphereObject.h"
class BaseCollisionObject;
class CollisionOBBObject;

bool isCollisionOfOBBandOBB(CollisionOBBObject* a, CollisionOBBObject* b);
bool isCollisionOfPlanesAndOBB(CollisionPlanesObject*, CollisionOBBObject*);
bool isCollisionOfPlaneAndOBB(CollisionPlanesObject::PLANE_INFO *plane, CollisionOBBObject *obb, HFVECTOR3 * collisionPosition, HFVECTOR3 * pushBack);

bool isCollisionPlaneAndSphere
(
	CollisionPlanesObject::PLANE_INFO  plane,
	CollisionSphereObject* sphere,
	HFVECTOR3* point,
	HFVECTOR3* pushBackDistance,
	float* time
	);

// ï°êîÇÃïΩñ Ç∆ãÖëÃ
bool isCollisionPlanesAndSphere
(
	CollisionPlanesObject* plane,
	CollisionSphereObject* sphere,
	HFVECTOR3* point,
	HFVECTOR3* pushBackDistance,
	float* time
	);