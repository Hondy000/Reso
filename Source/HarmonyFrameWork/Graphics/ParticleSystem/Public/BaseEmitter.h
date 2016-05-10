#pragma once
#include "../../../Core/Task/Public/TaskInterface.h"
#include "../../Buffer/Public/ConstantBuffer.h"
#include "../../Texture/Public/BaseTexture2D.h"
#include "../../RenderObject/Public/BaseRenderObject.h"
#include "BaseParticle.h"

class BaseEmitter
	:
	public BaseRenderObject,
	public inheritable_enable_shared_from_this<BaseEmitter>
{
public:

	BaseEmitter();
	virtual~BaseEmitter();


	std::vector<std::shared_ptr<IBaseParticle>> GetParticleArray() const
	{
		return m_particleArray;
	}

	void SetParticleArray(std::vector<std::shared_ptr<IBaseParticle>> _val)
	{
		m_particleArray = _val;
	}

protected:
	/** @brief パーティクルのパラメータ. */
	std::vector<std::shared_ptr<IBaseParticle>> m_particleArray;

	/** @brief パーティクルの数. */
	UINT m_numParticles;
	/** @brief The wait time. */
	UINT m_waitTime;
	/** @brief The progress time. */
	UINT m_progressTime;
	/** @brief Number of particle of out at the times. */
	UINT m_numParticleOfOutAtATime;
	/** @brief パーティクルの描画範囲. */
	FLOAT m_particleRenderRange;
	/** @brief The emit range. */
	HFVECTOR3 m_emitRange;
	/** @brief The emit dirction. */
	HFVECTOR3 m_emitDirction;
	/** @brief The velocity. */
	FLOAT m_velocity;
	// パーティクルの初期化
	bool Init();
	void Reset();
	void ResetParticle(std::shared_ptr<IBaseParticle> particle);
	bool isEmit;
	bool isLoop;
public:

	bool Update();



};
