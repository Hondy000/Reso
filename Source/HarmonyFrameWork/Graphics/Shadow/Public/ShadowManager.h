#pragma once
#include "..\..\..\Core\Public\ManagerInterface.h"
#include "..\..\RenderObject\Public\BaseRenderObject.h"
#include "..\..\..\Core\Actor\Public\ActorInterface.h"
#include "ShadowRenderObject.h"
#include "..\..\Lighting\Public\LightTypes.h"
#include "..\..\Camera\Public\BaseCamera.h"

class ShadowManager
	:
	public IActor
{
public:

	ShadowManager();
	~ShadowManager();

	bool Register(std::shared_ptr<BaseRenderObject> _renderringObject,std::shared_ptr<Transform> transform);

	std::list<std::shared_ptr<ShadowRenderObject>> GetShadowMapList()
	{
		return m_shadowMapList;
	}

	bool Update();

	void Reset() {};


	std::shared_ptr<HFGraphics::BaseLight> GetLight() const
	{
		return m_spLight;
	}

	void SetLight(std::shared_ptr<HFGraphics::BaseLight> _val)
	{
		m_spLight = _val;
	}

	std::shared_ptr<BaseShader> GetShadowMapShader() const
	{
		return m_shadowMapShader;
	}

	void SetShadowMapShader(std::shared_ptr<BaseShader> _val)
	{
		m_shadowMapShader = _val;
	}

protected:
private:
	std::list<std::shared_ptr<ShadowRenderObject>> m_shadowMapList;
	std::shared_ptr<HFGraphics::BaseLight> m_spLight;
	std::shared_ptr<BaseShader> m_shadowMapShader;
};
