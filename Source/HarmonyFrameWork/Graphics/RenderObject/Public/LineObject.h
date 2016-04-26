#pragma once
#include "..\..\..\Core\Public\Common.h"
#include "BaseRenderObject.h"
#include "..\..\Public\GraphicsTypes.h"

struct LineData;

class LineObject
	:
	public BaseRenderObject,
	public inheritable_enable_shared_from_this<LineObject>
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
