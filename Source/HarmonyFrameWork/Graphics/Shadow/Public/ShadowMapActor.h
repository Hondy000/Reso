#pragma once
#include "..\..\..\Core\Public\ManagerInterface.h"
#include "..\..\RenderObject\Public\BaseRenderMeshObject.h"
#include "..\..\..\Core\Actor\Public\ActorInterface.h"
#include "ShadowRenderObject.h"
#include "..\..\Lighting\Public\LightTypes.h"
#include "..\..\Camera\Public\BaseCamera.h"
#include "..\..\Public\BaseGraphicsCommand.h"
#include "..\..\Texture\Public\BaseTexture2D.h"
#include "..\..\RenderDevice\Basic\Public\BaseDepthStencilBuffer.h"


class RenderShadowMapCommand
	:
	public BaseGraphicsCommand
{
public:

	RenderShadowMapCommand();
	~RenderShadowMapCommand();


	bool Update();

	void Reset() {};



	std::shared_ptr<HFGraphics::BaseLight> GetLight() const
	{
		return m_light;
	}

	void SetLight(std::shared_ptr<HFGraphics::BaseLight> _val)
	{
		m_light = _val;
	}


	std::shared_ptr<BaseTexture2D> GetShadowMapTexture() const
	{
		return m_shadowMapTexture;
	}

	void SetShadowMapTexture(std::shared_ptr<BaseTexture2D>& _val)
	{
		m_shadowMapTexture = _val;
	}

protected:
private:
	std::shared_ptr<HFGraphics::BaseLight> m_light;
	std::shared_ptr<BaseTexture2D> m_shadowMapTexture;
	std::shared_ptr<BaseDepthStencilBuffer> m_depthBuffer;
};


class ShadowManager
{
public:
	~ShadowManager();

	static ShadowManager * GetInstance()
	{
		static ShadowManager instance;
		return &instance;
	}

	bool RegisterMesh(std::shared_ptr<BaseRenderMeshObject> _renderringObject, std::shared_ptr<Transform> transform);

	bool RegisterLight(std::shared_ptr<HFGraphics::BaseLight> spLight);

	void GetShadowMapTextures(std::vector<std::shared_ptr<BaseTexture2D>>& _shadowMapArray);

	std::list<std::shared_ptr<ShadowRenderObject>>& GetShadowMapList()
	{
		return m_shadowRenderObjectList;
	}
	std::shared_ptr<HFGraphics::BaseLight> GetLight() const
	{
		return m_spLight;
	}

	void SetLight(std::shared_ptr<HFGraphics::BaseLight> _val)
	{
		m_spLight = _val;
	}

	std::shared_ptr<BaseGraphicsShader> GetShadowMapShader() const
	{
		return m_shadowMapShader;
	}

	void SetShadowMapShader(std::shared_ptr<BaseGraphicsShader> _val)
	{
		m_shadowMapShader = _val;
	}


private:

	ShadowManager();
	std::unordered_map<std::shared_ptr<HFGraphics::BaseLight>, std::shared_ptr<RenderShadowMapCommand>> m_shadowMapSet;
	std::list<std::shared_ptr<ShadowRenderObject>> m_shadowRenderObjectList;
	std::shared_ptr<HFGraphics::BaseLight> m_spLight;
	std::shared_ptr<BaseGraphicsShader> m_shadowMapShader;
};
