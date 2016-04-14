#pragma once
#include "../../../Core/Task/Public/TaskInterface.h"
#include "../../Buffer/Public/ConstantBuffer.h"
#include "../../Texture/Public/BaseTexture2D.h"
#include "../../RenderObject/Public/BaseRenderObject.h"
#include "BaseParticle.h"

class BaseEmitter
	:
	public BaseRenderObject
{
public:


	// 頂点定義
	typedef struct PARTICLE_VERTEX
	{
		HFVECTOR3 Vertex;
		HFVECTOR2 UV;
	}ParticleVertex;
	// 入力アセンブラ用定数バッファ０
	typedef struct IBUFFER0
	{
		// ワールド × ビュー × 射影 行列
		HFMATRIX  matWVP;
		// 頂点カラー
		HFVECTOR4 color;
	}InBuffer0;

	BaseEmitter() {};
	virtual~BaseEmitter() {};

protected:
	// デカールマップ
	std::shared_ptr<BaseTexture2D> m_pSRVDecalMap;

	std::shared_ptr<BaseBuffer> m_spVertexBuffer;

	std::shared_ptr<ConstantBuffer> m_pInputBuffer;

	// パーティクルのパラメータ
	std::list<std::shared_ptr<BaseParticle>> m_pParticleList;

	// パーティクルの数
	UINT m_numMaxParticles;
	// パーティクルの数
	UINT m_numParticles;

	UINT m_emitParticle;
	UINT m_waitTime;
	UINT m_progressTime;

	// パーティクルの描画範囲
	FLOAT m_particleRenderRange;
	HFVECTOR3 m_windDirection;


	FLOAT m_variationAngle;
	HFVECTOR2 m_variationSize;
	HFVECTOR4 m_variationColor;
	HFVECTOR3 m_emitRange;
	HFVECTOR3 m_emitDirction;
	FLOAT m_variationLife;
	FLOAT m_velocity;
	FLOAT m_gravity;
	BOOL isSquare;
	// パーティクルの初期化
	BOOL Init();
	void Reset();
	void ResetParticle(std::shared_ptr<BaseParticle> particle);
	BOOL isEmit;
	BOOL isLoop;
public:

	BOOL Update();

	// 初期化

	BOOL Setup(UINT NumParticles, UINT time, HFVECTOR2 ParticleSize, FLOAT ParticleRenderRange, TCHAR pTextureFileNames[]);

	void SetStartMAXPosition(HFVECTOR3 pos);
	void SetStartMAXSize(HFVECTOR2 size);
	void SetStartMAXColor(HFVECTOR4 color);
	void SetStartMAXLife(FLOAT life);
	void SetStartMAXAngle(FLOAT angle);

	void SetStartMINPosition(HFVECTOR3 pos);
	void SetStartMINSize(HFVECTOR2 size);
	void SetStartMINColor(HFVECTOR4 color);
	void SetStartMINLife(FLOAT life);
	void SetStartMINAngle(FLOAT angle);

	void SetVelocity(FLOAT pos);
	void SetEmitDirection(HFVECTOR3 pos);
	void SetEmitRange(HFVECTOR3 range);
	void SetMaxParticle(UINT num);
	void SetVariationSize(HFVECTOR2 size);
	void SetVariationColor(HFVECTOR4 color);
	void SetVariationLife(FLOAT size);
	void SetVariationAngle(FLOAT angle);

	void SetGravity(FLOAT g);
	void SetIsEmit(BOOL emit);
	void SetIsLoopt(BOOL emit);
	void SetWindDirection(HFVECTOR3 emit);


};
