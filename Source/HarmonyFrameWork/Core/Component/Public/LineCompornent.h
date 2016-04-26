#pragma once
#include "..\..\..\Graphics\RenderObject\Public\LineObject.h"
#include "CompornentInterface.h"

class LineCompornent
	:
	public LineObject,
	public ICompornent
{
public:
	LineCompornent();
	~LineCompornent();

	bool Init();
	void Reset();
	bool Update();

	void Destroy();
private:

};
