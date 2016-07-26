#pragma once
#include "../../../Core/Task/Public/TaskInterface.h"
#include "../../Buffer/Public/ConstantBuffer.h"
#include "../../Texture/Public/BaseTexture2D.h"
#include "../../RenderObject/Public/BaseRenderObject.h"
#include "BaseParticle.h"

class BaseEmitter
	:
	virtual public BaseRenderObject
{
public:

	BaseEmitter();
	virtual~BaseEmitter();


	std::vector<std::shared_ptr<IBaseParticle>> GetParticleArray() const
	{
		return m_particleArray;
	}
	void SetMaxParticle(UINT num);

protected:
	/** @brief パーティクルのパラメータ. */
	std::vector<std::shared_ptr<IBaseParticle>> m_particleArray;

	/** @brief パーティクルの数. */
	UINT m_numParticles;
	/** @brief The wait time. */
	UINT m_waitTime;
	/** @brief The progress time. */
	UINT m_emittTime;
	/** @brief Number of particle of out at the times. */
	UINT m_numParticleOfOutAtATime;
	/** @brief パーティクルの描画範囲. */
	FLOAT m_particleRenderRange;

	/** @brief 1秒間のの放出量. */
	UINT m_emitParticlePerSecond;

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
	void EmittParticle();
	void SphereEmitt();
	void ConeEmitt();
	void MeshEmitt();
public:

	bool Update();



};
