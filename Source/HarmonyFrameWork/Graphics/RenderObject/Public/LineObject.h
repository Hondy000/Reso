#pragma once
#include "..\..\..\Core\Public\Common.h"
#include "BaseRenderMeshObject.h"
#include "..\..\Public\GraphicsTypes.h"

struct LineData;

class LineObject
	:
	public BaseRenderMeshObject
{
public:
	LineObject();
	virtual~LineObject();
	bool Init();

	bool Update();

	void Reset();
	bool AddLine(HFGraphics::LineData& addLine);

private:
};
