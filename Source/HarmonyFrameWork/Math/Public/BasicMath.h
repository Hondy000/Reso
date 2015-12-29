#pragma once

#ifdef BASIC_MATH
typedef struct HFVECTOR2
{
	float x;
	float y;
}HFVECTOR2;

typedef struct HFVECTOR3
{
	float x;
	float y;
	float z;
}HFVECTOR3;

typedef struct HFVECTOR4
{
	float x;
	float y;
	float z;
	float w;
}HFVECTOR4;

typedef struct HFMATRIXF44
{
	union
	{
		// çsóDêÊê›íË
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};
#endif