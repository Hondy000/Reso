#pragma once
#include "../../Core/Public/Common.h"
#include "../../Core/Public/IBaseObject.h"
#include "..\..\Core\Task\Public\TaskInterface.h"
class BaseRenderObject;

class RenderCommand
	:
	public IBaseTask
{
public:
	RenderCommand() {};
	~RenderCommand() {};

	// Access the RenderObject
	const std::shared_ptr<BaseRenderObject>& GetRenderObject(void) const
	{
		return(m_renderObject);
	};
	bool Update();
	void Reset();
	void SetRenderObject(const std::shared_ptr<BaseRenderObject> renderObject);

	// Access the RenderMeshElement
	UINT GetRenderMeshElement(void) const
	{
		return(m_renderMeshElement);
	};
	void SetRenderMeshElement(UINT renderMeshElement)
	{
		m_renderMeshElement = renderMeshElement;
	};

	// Access the RenderPriority
	const DWORD& GetRenderPriority(void) const
	{
		return(m_renderPriority);
	};
	void SetRenderPriority(const DWORD& renderPriority)
	{
		m_renderPriority = renderPriority;
	};

protected:
	std::shared_ptr<BaseRenderObject> m_renderObject;
	UINT m_renderMeshElement;
	DWORD m_renderPriority;
};
