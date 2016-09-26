#pragma once
#include "../../../Core/Task/Public/TaskInterface.h"
#include "../../Buffer/Public/ConstantBuffer.h"
#include "../../Texture/Public/BaseTexture2D.h"
#include "../../RenderObject/Public/BaseRenderMeshObject.h"
#include "BaseParticle.h"

class BaseEmitter
	:
	virtual public BaseRenderMeshObject,
	public TransformHolder
{
public:

	BaseEmitter();
	virtual~BaseEmitter();


	std::vector<std::shared_ptr<IBaseParticle>> GetParticleArray() const
	{
		return m_particleArray;
	}
	void SetMaxParticle(UINT num);


	HFColor GetColor() const
	{
		return m_color;
	}

	void SetColor(HFColor _val)
	{
		m_color = _val;
	}

protected:
	/** @brief �p�[�e�B�N���̃p�����[�^. */
	std::vector<std::shared_ptr<IBaseParticle>> m_particleArray;

	/** @brief �p�[�e�B�N���̐�. */
	UINT m_numMaxParticles;
	/** @brief The wait time. */
	float m_waitTime;
	/** @brief The progress time. */
	float m_emittTime;

	/** @brief 1�b�Ԃ̂̕��o��. */
	UINT m_emitParticlePerSecond;

	/** @brief The emit range. */
	HFVECTOR3 m_emitRange;
	/** @brief The emit dirction. */
	HFVECTOR3 m_emitDirction;
	HFColor m_color;
	/** @brief The velocity. */
	FLOAT m_velocity;
	// �p�[�e�B�N���̎���
	float m_particleLife;
	
	// �p�[�e�B�N���̏�����
	bool Init();
	void Reset();
	void ResetParticle(std::shared_ptr<IBaseParticle> particle);
	bool isEmit;
	bool isLoop;
	void EmittParticle();
	void SphereEmitt();
	void ConeEmitt();
	void MeshEmitt();
public:

	bool Update();



};
