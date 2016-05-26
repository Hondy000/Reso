/**********************************************************************************************//**
 * @file	Source\HarmonyFrameWork\Graphics\Lighting\Private\LightManager.cpp
 *
 * @brief	Implements the light manager class.
 **************************************************************************************************/

#include <algorithm>
#include "../Public/LightManager.h"

using namespace std;
namespace HFGraphics
{

	void LightManager::Register(std::shared_ptr<BaseLight> spLight)
	{
		if (spLight->GetLightType() == LightType::Directional)
		{
			m_spDirectionalLight = spLight;
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
				shared_ptr<PointLight> point = static_pointer_cast<PointLight>(*it);
				
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
				shared_ptr<SpotLight> spot = static_pointer_cast<SpotLight>(*it);

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