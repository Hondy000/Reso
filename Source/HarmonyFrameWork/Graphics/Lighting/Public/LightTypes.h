#pragma once
#include "../../../Core/Public/Common.h"

namespace HFGraphics
{
	enum class LightType : uint8_t
	{
		Directional,
		Point,
		Spot,
		Max

	};


	struct DIRECTIONAL_LIGHT_PRAM
	{
		HFVECTOR4 color;
		HFVECTOR4 direction;
	};

	struct POINT_LIGHT_PRAM
	{
		HFVECTOR4 position;
		HFVECTOR4 color;
		FLOAT range;
		FLOAT attenuation;
		FLOAT falloff;
		FLOAT dummy;  // 16バイトにするためのダミー
	};

	struct SPOT_LIGHT_PRAM
	{
		HFVECTOR4 position;
		HFVECTOR4 color;
		HFVECTOR4 direction;
		FLOAT range;
		FLOAT attenuation;
		FLOAT falloff;
		FLOAT phi;
	};



	class BaseLight
	{
	public:
		BaseLight(): m_type(LightType::Max)
		{};
		~BaseLight() {};
		virtual FLOAT GetDistance(HFVECTOR3 pos);		

		// Access the Type
		const LightType& GetLightType(void) const
		{
			return(m_type);
		};
		void SetType(const LightType& type)
		{
			m_type = type;
		};
		// Access the ID
		const std::string& GetID(void) const
		{
			return(m_ID);
		};
		void SetID(const std::string& iD)
		{
			m_ID = iD;
		};

	protected:
		BaseLight(const LightType& type,std::string id)
			:
			m_type(type), 
			m_ID(id)
		{}

		BaseLight(const LightType& type)
			:
			m_type(type)
		{}
		LightType m_type;
		std::string m_ID;
	private:
	};


	class DirectinalLight
		:
		public BaseLight
	{
	public:
		DirectinalLight()  
			:
			BaseLight(LightType::Directional)
		{
			
		};

		virtual ~DirectinalLight() {};
		virtual FLOAT GetDistance(HFVECTOR3 pos);


		// Access the Pram
		const DIRECTIONAL_LIGHT_PRAM& GetPram(void) const	{ return(pram);	};
		void SetPram(const DIRECTIONAL_LIGHT_PRAM& _pram)	{ pram = _pram;	};

	private:
		DIRECTIONAL_LIGHT_PRAM pram;
	};




	class PointLight
		:
		public BaseLight
	{
	public:
		PointLight()
			:
			BaseLight(LightType::Directional)
		{

		};

		virtual ~PointLight() {};
		virtual FLOAT GetDistance(HFVECTOR3 pos);


		// Access the Pram
		const POINT_LIGHT_PRAM& GetPram(void) const
		{
			return(pram);
		};
		void SetPram(const POINT_LIGHT_PRAM& _pram)
		{
			pram = _pram;
		};

		void SetPosition(const HFVECTOR4& position)
		{
			pram.position = position;
		}

		void SetColor(const HFVECTOR4& color)
		{
			pram.color = color;
		}
		void SetFalloff(const FLOAT falloff)
		{
			pram.falloff = falloff;
		}
		void SetAtttention(const FLOAT attention)
		{
			pram.attenuation = attention;
		}
		void SetRange(const FLOAT range)
		{
			pram.range = range;
		}
		

	private:
		/** @brief	The pram. */
		POINT_LIGHT_PRAM pram;
	};

	class SpotLight
		:
		public BaseLight
	{
	public:
		SpotLight()
			:
			BaseLight(LightType::Directional)
		{

		};

		virtual ~SpotLight() {};
		virtual FLOAT GetDistance(HFVECTOR3 pos);


		// Access the Pram
		const SPOT_LIGHT_PRAM& GetPram(void) const	{ return(pram);	};
		void SetPram(const SPOT_LIGHT_PRAM& _pram)	{ pram = _pram;	};

	private:
		SPOT_LIGHT_PRAM pram;
	};
}