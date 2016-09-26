#pragma once
#include "../../Core/Public/Common.h"
#include "../../Core/Public/IBaseObject.h"
#include "..\..\Core\Task\Public\TaskInterface.h"
class BaseRenderMeshObject;

class BaseGraphicsCommand
	:
	public IBaseTask
{
public:
	BaseGraphicsCommand() {};
	virtual~BaseGraphicsCommand() {};

	// Access the RenderObject
	const std::shared_ptr<BaseRenderMeshObject>& GetRenderObject(void) const
	{
		return(m_graphicsObject);
	};
	virtual bool Update();
	virtual void Reset();


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
	std::shared_ptr<BaseRenderMeshObject> m_graphicsObject;
	DWORD m_renderPriority;
};

class ClearRenderTargetViewComand
	:
	public BaseGraphicsCommand
{
public:
	ClearRenderTargetViewComand();
	~ClearRenderTargetViewComand();
	bool Update();
};


class RenderMeshCommmand
	:
	public BaseGraphicsCommand
{
public:
	RenderMeshCommmand() {};
	~RenderMeshCommmand() {};


	bool Update();
	void Reset();
	void SetRenderObject(const std::shared_ptr<BaseRenderMeshObject> renderObject);

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
	const DWORD& GetGraphicsPriority(void) const
	{
		return(m_renderPriority);
	};
	void SetGraphicsPriority(const DWORD& renderPriority)
	{
		m_renderPriority = renderPriority;
	};

protected:
	UINT m_renderMeshElement;
};
