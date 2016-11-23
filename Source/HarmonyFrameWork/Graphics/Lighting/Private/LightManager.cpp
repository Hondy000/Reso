/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Graphics\Lighting\Private\LightManager.cpp
 *
 * @brief	Implements the light manager class.
 **************************************************************************************************/

#include <algorithm>
#include "../Public/LightManager.h"
#include "..\..\Shadow\Public\ShadowMapActor.h"
#include "..\..\..\Core\Task\Public\TaskSystem.h"

using namespace std;
namespace HFGraphics
{

	void LightManager::Register(std::shared_ptr<BaseLight> spLight)
	{

	//	std::shared_ptr<RenderShadowMapCommand> rsmCommand = std::make_shared<RenderShadowMapCommand>();
	//	sTASK_SYSTEM->RegisterGraphicsCommand(rsmCommand);
	//	spLight->GetCommmandArray().push_back(rsmCommand);
		if (spLight->GetLightType() == LightType::Directional)
		{
			// 既に平行光源セット済み
			if(m_spDirectionalLight)
			{
				// コマンドリスト内からシャドウマップ生成コマンドを探す
		//		for (auto it = m_spDirectionalLight->GetCommmandArray().begin(); it != m_spDirectionalLight->GetCommmandArray().end();)
		//		{
		//			if (std::dynamic_pointer_cast<RenderShadowMapCommand>(*it))
		//			{
						// システム内のコマンドリストからリムーブ
		//				sTASK_SYSTEM->RemoveGraphicsCommand(*it);
		//			}

		//			it++;
		//		}
			}
			m_spDirectionalLight = spLight;
			ShadowManager::GetInstance()->RegisterLight(spLight);
			return;
		}

		m_lightList.push_back(spLight);
	}

	void LightManager::Remove(std::shared_ptr<BaseLight> spLight)
	{
		for (auto it = m_lightList.begin(); it != m_lightList.end();)
		{
			if (*it == spLight)
			{
				it = m_lightList.erase(it);
				continue;
			}
			else
			{
				it++;
			}
		}
	}

	/**********************************************************************************************//**
	 * @fn	void LightManager::CheckUseCount()
	 *
	 * @brief	参照数チェック.
	 *
	 * @author	Kazuyuki Honda
	 * @date	2015/11/12
	 **************************************************************************************************/

	void LightManager::CheckUseCount()
	{
		for (auto it = m_lightList.begin(); it != m_lightList.end();)
		{
			if (it->use_count() == 0)
			{
				it = m_lightList.erase(it);
				continue;
			}
			else
			{
				it++;
			}
		}
	}

	void LightManager::GetPointLight(std::vector<std::shared_ptr<HFGraphics::PointLight>>& lightArray, const HFVECTOR3 & position, UINT lightCount)
	{
		lightArray.resize(lightCount);
		m_lightList.sort([position](const std::shared_ptr<HFGraphics::BaseLight>& x, const shared_ptr<HFGraphics::BaseLight>& y) -> FLOAT
		{
			FLOAT lengthX, lengthY;
			HFVECTOR4 positionX, positionY;
			lengthX = x->GetDistance(position);
			lengthY = y->GetDistance(position);
			return(lengthX < lengthY);
		});
		int i = 0;
		auto it = m_lightList.begin();
		for (it; it != m_lightList.end(); it++)
		{
			if (i < lightCount)
			{
				shared_ptr<PointLight> point = dynamic_pointer_cast<PointLight>(*it);
				
				if(point)
				{
					lightArray[i] = point;
					i++;
				}
			}
			else
			{
				break;
			}

		}
	}


	void LightManager::GetSpotLight(std::vector<std::shared_ptr<HFGraphics::SpotLight>>& lightArray, const HFVECTOR3 & position, UINT lightCount)
	{
		lightArray.resize(lightCount);
		m_lightList.sort([position](const std::shared_ptr<HFGraphics::BaseLight>& x, const shared_ptr<HFGraphics::BaseLight>& y) -> FLOAT
		{
			FLOAT lengthX, lengthY;
			HFVECTOR4 positionX, positionY;
			lengthX = x->GetDistance(position);
			lengthY = y->GetDistance(position);
			return(lengthX < lengthY);
		});
		int i = 0;
		auto it = m_lightList.begin();
		for (it; it != m_lightList.end(); it++)
		{
			if (i < lightCount)
			{
				shared_ptr<SpotLight> spot = dynamic_pointer_cast<SpotLight>(*it);

				if (spot)
				{
					lightArray[i] = spot;
					i++;
				}
			}
			else
			{
				break;
			}

		}
	}

	void LightManager::GetDirectionalLight(std::shared_ptr<HFGraphics::DirectinalLight>& lightArray)
	{
		lightArray = std::dynamic_pointer_cast<HFGraphics::DirectinalLight>( m_spDirectionalLight);
	}
}