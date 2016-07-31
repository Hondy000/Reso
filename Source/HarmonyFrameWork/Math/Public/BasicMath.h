#pragma once

#ifdef BASIC_MATH
typedef struct HFVECTOR2
{
	FLOAT x;
	FLOAT y;
}HFVECTOR2;

typedef struct HFVECTOR3
{
	FLOAT x;
	FLOAT y;
	FLOAT z;
}HFVECTOR3;

typedef struct HFVECTOR4
{
	FLOAT x;
	FLOAT y;
	FLOAT z;
	FLOAT w;
}HFVECTOR4;

typedef struct HFMATRIXF44
{
	union
	{
		// çsóDêÊê›íË
		struct
		{
			FLOAT _11, _12, _13, _14;
			FLOAT _21, _22, _23, _24;
			FLOAT _31, _32, _33, _34;
			FLOAT _41, _42, _43, _44;
		};
		FLOAT m[4][4];
	};
};
#endif