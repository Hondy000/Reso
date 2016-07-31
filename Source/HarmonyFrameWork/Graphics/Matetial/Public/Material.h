#pragma once
#include "../../../Core/Public/Common.h"
#include "../../../Core/Public/IBaseObject.h"
class BaseShader;

class IBaseTexture;

class Material
	:
	public IBaseObject
{
public:
	Material() {}

	bool LoadDiffuseTexture2D(HFString texturePath);
	virtual ~Material() {};
	// Access the MaterialShader
	const std::shared_ptr<BaseShader>& GetMaterialShader(void) const
	{
		return(m_materialShader);
	};
	void SetMaterialShader(std::shared_ptr<BaseShader> materialShader)
	{
		m_materialShader = materialShader;
	};

	// Access the DiffuseTexture
	const std::shared_ptr<IBaseTexture>& GetDiffuseTexture(void) const			{ return(m_diffuseTexture);				};
	void SetDiffuseTexture(const std::shared_ptr<IBaseTexture>& diffuseTexture)	{ m_diffuseTexture = diffuseTexture;	};

	// Access the Ambient
	const HFVECTOR4& GetAmbient(void) const		{ return(ambient);		};
	void SetAmbient(const HFVECTOR4& _ambient)	{ ambient = _ambient;	};

	// Access the Diffuse
	const HFVECTOR4& GetDiffuse(void) const		{ return(diffuse);		};
	void SetDiffuse(const HFVECTOR4& _diffuse)	{ diffuse = _diffuse;	};

	// Access the Emissive
	const HFVECTOR4& GetEmissive(void) const		{ return(emissive);		};
	void SetEmissive(const HFVECTOR4& _emissive)	{ emissive = _emissive;	};

	// Access the Specular
	const HFVECTOR4& GetSpecular(void) const		{ return(specular);		};
	void SetSpecular(const HFVECTOR4& _specular)	{ specular = _specular;	};

protected:
	std::shared_ptr<BaseShader>	m_materialShader;

	std::shared_ptr<IBaseTexture> m_diffuseTexture;

	HFVECTOR4 ambient;
	HFVECTOR4 diffuse;
	HFVECTOR4 emissive;
	HFVECTOR4 specular;

};

