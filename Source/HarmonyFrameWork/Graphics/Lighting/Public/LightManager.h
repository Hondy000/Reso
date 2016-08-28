#pragma once

#include "LightTypes.h"
#define sLIGHT_MANAGER (HFGraphics::LightManager::GetInstance())

namespace HFGraphics
{
	class LightManager
	{
	private:
		// singleton
		LightManager() {};
		LightManager(LightManager&);

	public:
		void Register(std::shared_ptr<BaseLight> spLight);
		void Remove(std::shared_ptr<BaseLight> spLight);

		static LightManager* GetInstance()
		{
			static LightManager singleton;
			return &singleton;
		}

		/**********************************************************************************************//**
		 * @fn	void LightManager::CheckUseCount();
		 *
		 * @brief	参照数チェック.
		 *
		 * @author	Kazuyuki Honda
		 * @date	2015/11/12
		 **************************************************************************************************/

		void CheckUseCount();
		void GetPointLight(std::vector<std::shared_ptr<HFGraphics::PointLight>>& lightArray, const HFVECTOR3& position, UINT lightCount);
		void GetSpotLight(std::vector<std::shared_ptr<HFGraphics::SpotLight>>& lightArray, const HFVECTOR3& position, UINT lightCount);
		void GetDirectionalLight(std::shared_ptr<HFGraphics::DirectinalLight>& light);
		void GetLight(std::vector<std::shared_ptr<BaseLight>>& lightArray, const HFVECTOR3& postion, UINT lightCount);
	private:
		std::list<std::shared_ptr<BaseLight>> m_lightList;
		std::shared_ptr<BaseLight> m_spDirectionalLight;
	};
}