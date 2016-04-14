/**********************************************************************************************//**
 * @file	Source\HarmonyFrame\Graphics\GraphicsObject\Basic\CBaseEmitter.cpp
 *
 * @brief	Implements the base emitter class.
 **************************************************************************************************/


#include <random>
#include "../../Buffer/Public/BaseBuffer.h"
#include "../Public/BaseEmitter.h"
#include "../../RenderDevice/Basic/Public/RendererManager.h"
#include "../../../Utility/Public/InlineUtility.h"
#include "../../../ResorceManager/Public/Texture2DManager.h"

using namespace std;

BOOL BaseEmitter::Update()
{
	// アルファ値の更新
	for (auto it = m_pParticleList.begin(); it != m_pParticleList.end(); )
	{
		if (*(*it)->GetVariable<FLOAT>("life")->GetValue() == 0)
		{
			*(*it)->GetVariable<FLOAT>("life")->GetValue() -= *(*it)->GetVariable<FLOAT>("decreaseLife")->GetValue();
			*(*it)->GetVariable<HFVECTOR3>("position")->GetValue() += *(*it)->GetVariable<HFVECTOR3>("velocity")->GetValue();
			*(*it)->GetVariable<HFVECTOR3>("rotation")->GetValue() += *(*it)->GetVariable<HFVECTOR3>("variableRotation")->GetValue();
			(*it)->GetVariable<HFVECTOR3>("position")->GetValue()->y -= m_gravity;
		}
		else
		{
			it = m_pParticleList.erase(it);
			continue;
		}
		it++;
	}

	// パーティクルの初期化
	// 	 if

	if (isEmit)
	{
		if (m_waitTime < ++m_progressTime)
		{
			for (auto i = 0; i < m_emitParticle; i++)
			{
			//	auto sp = std::shared_ptr<BaseParticle>(new BaseParticle);
			//	ResetParticle(sp);
			//	m_pParticleList.push_back(sp);
			}
			D3D11_BUFFER_DESC BufferDesc;
			::ZeroMemory(&BufferDesc, sizeof(BufferDesc));
			BufferDesc.ByteWidth = m_pParticleList.size() * sizeof(IBUFFER0);   // バッファサイズ
			BufferDesc.Usage = D3D11_USAGE_DYNAMIC;                 // リソース使用法を特定する
			BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;            // バッファの種類
			BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;              // CPU アクセスする
			BufferDesc.MiscFlags = 0;                                   // その他のフラグも設定しない
			HRESULT hr;
			hr = sRENDER_DEVICE->CreateBuffer(&BufferDesc, NULL, m_pInputBuffer->GetBuffer().GetAddressOf());
			if (FAILED(hr))
			{
			}

			if (!isLoop)
			{
				isEmit = false;
			}
			m_progressTime = 0;
		}
	}
	// ソート
	HFMATRIX view;
	sRENDER_DEVICE_MANAGER->GetTransform(&view, HFTS_VIEW);
	

	return true;
}

/**********************************************************************************************//**
  * @fn	BOOL CBaseEmitter::Setup( UINT NumParticles, UINT time , HFVECTOR2 ParticleSize , FLOAT ParticleRenderRange , TCHAR pTextureFileNames[] )
  *
  * @brief	初期化.
  *
  * @author	Kazuyuki Honda
  * @date	2015/11/04
  *
  * @param	NumParticles	   	Number of particles.
  * @param	time			   	The time.
  * @param	ParticleSize	   	Size of the particle.
  * @param	ParticleRenderRange	The particle render range.
  * @param	pTextureFileNames  	List of names of the texture files.
  *
  * @return	A BOOL.
  **************************************************************************************************/

// BOOL BaseEmitter::Setup(
// 	UINT NumParticles,
// 	UINT time
// 	, HFVECTOR2 ParticleSize
// 	, FLOAT ParticleRenderRange
// 	, TCHAR pTextureFileNames[]
// 	)
// {
// 	m_waitTime = time;
// 	HRESULT hr = E_FAIL;
// 	D3D11_BUFFER_DESC BufferDesc;
// 	D3DX11_IMAGE_LOAD_INFO info;
// 
// 	// パーティクル数
// 	m_emitParticle = NumParticles;
// 
// 	// パーティクルのサイズ
// 	m_startParamMAX.size = m_startParamMIN.size = ParticleSize;
// 
// 	// パーティクルを描画範囲
// 	m_particleRenderRange = ParticleRenderRange;
// 
// 	// 座標とアルファ値を初期化
// 	//InitParticleParam();
// 	isEmit = true;
// 	isLoop = true;
// 	// *****************************************************************************************************************
// 	// パーティクルの頂点座標の初期化
// 	// *****************************************************************************************************************
// 
// 	PARTICLE_VERTEX VertexArray[4] = {
// 		D3DXVECTOR3(-1.0f, 1.0f, 0.0f),   D3DXVECTOR2(0.0f, 0.0f)
// 		, D3DXVECTOR3(1.0f, 1.0f, 0.0f),  D3DXVECTOR2(1.0f, 0.0f)
// 		, D3DXVECTOR3(-1.0f, -1.0f, 0.0f),  D3DXVECTOR2(0.0f, 1.0f)
// 		, D3DXVECTOR3(1.0f, -1.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f)
// 	};
// 
// 	// バッファー リソース
// 	::ZeroMemory(&BufferDesc, sizeof(BufferDesc));
// 	BufferDesc.ByteWidth = sizeof(PARTICLE_VERTEX) * _countof(VertexArray); // バッファサイズ
// 	BufferDesc.Usage = D3D11_USAGE_DEFAULT;       // リソース使用法を特定する
// 	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;  // バッファの種類
// 	BufferDesc.CPUAccessFlags = 0;                         // CPU アクセスしない
// 	BufferDesc.MiscFlags = 0;                         // その他のフラグも設定しない
// 													  // サブリソース( 初期値 )
// 	D3D11_SUBRESOURCE_DATA resource;
// 	resource.pSysMem = (void*)VertexArray;
// 	resource.SysMemPitch = 0;
// 	resource.SysMemSlicePitch = 0;
// 	// バッファを作成する
// 	hr = sRENDER_DEVICE->CreateBuffer(&BufferDesc, &resource, m_spVertexBuffer->GetBuffer().GetAddressOf());
// 	if (FAILED(hr))
// 		return false;
// 
// 	// *****************************************************************************************************************
// 	// 入力アセンブラ用のバッファを作成
// 	// *****************************************************************************************************************
// 
// 	::ZeroMemory(&BufferDesc, sizeof(BufferDesc));
// 	BufferDesc.ByteWidth = NumParticles * sizeof(IBUFFER0);   // バッファサイズ
// 	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;                 // リソース使用法を特定する
// 	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;            // バッファの種類
// 	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;              // CPU アクセスする
// 	BufferDesc.MiscFlags = 0;                                   // その他のフラグも設定しない
// 	hr = sRENDER_DEVICE->CreateBuffer(&BufferDesc, NULL, m_pInputBuffer->GetBuffer().GetAddressOf());
// 	if (FAILED(hr))
// 		return false;
// 
// 	// *****************************************************************************************************************
// 	// デカールマップの初期化
// 	// *****************************************************************************************************************
// 
// 	// ファイルからシェーダーリソースビューを作成する
// 	::ZeroMemory(&info, sizeof(D3DX11_IMAGE_LOAD_INFO));
// 	info.Width = D3DX11_DEFAULT;
// 	info.Height = D3DX11_DEFAULT;
// 	info.Depth = D3DX11_DEFAULT;
// 	info.FirstMipLevel = D3DX11_DEFAULT;          // テクスチャーの最高解像度のミップマップ レベル。
// 	info.MipLevels = 0;                           // ミップマップ数。0 または D3DX11_DEFAULT を使用するとすべてのミップマップ チェーンを作成する。
// 	info.Usage = D3D11_USAGE_DEFAULT;
// 	info.BindFlags = D3D11_BIND_SHADER_RESOURCE;
// 	info.CpuAccessFlags = 0;
// 	info.MiscFlags = 0;
// 	info.Format = DXGI_FORMAT_FROM_FILE;
// 	info.Filter = D3DX11_FILTER_POINT;            // テクスチャー読み込み時に使用するフィルター
// 	info.MipFilter = D3DX11_FILTER_POINT;         // ミップマップ作成時に使用するフィルター
// 	info.pSrcInfo = NULL;
// 	
// 	Texture2DManager::GetInstance()->Get(pTextureFileNames, m_pSRVDecalMap);
// 
// 	if (FAILED(hr))
// 		return false;
// 
// 	hr = S_OK;
// 
// EXIT:
// 
// 	return true;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetStartMAXPosition(HFVECTOR3 pos)
//  *
//  * @brief	Sets start maximum position.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	pos	The position.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetStartMAXPosition(HFVECTOR3 pos)
// {
// 	m_startParamMAX.position = pos;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetStartMAXSize(HFVECTOR2 size)
//  *
//  * @brief	Sets start maximum size.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	size	The size.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetStartMAXSize(HFVECTOR2 size)
// {
// 	m_startParamMAX.size = size;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetStartMAXColor(HFVECTOR4 color)
//  *
//  * @brief	Sets start maximum color.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	color	The color.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetStartMAXColor(HFVECTOR4 color)
// {
// 	m_startParamMAX.color = color;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetStartMAXLife(FLOAT life)
//  *
//  * @brief	Sets start maximum life.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	life	The life.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetStartMAXLife(FLOAT life)
// {
// 	m_startParamMAX.life = life;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetStartMAXAngle(FLOAT angle)
//  *
//  * @brief	Sets start maximum angle.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	angle	The angle.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetStartMAXAngle(FLOAT angle)
// {
// 	m_startParamMAX.angle = angle;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetStartMINPosition(HFVECTOR3 pos)
//  *
//  * @brief	Sets start minimum position.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	pos	The position.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetStartMINPosition(HFVECTOR3 pos)
// {
// 	m_startParamMIN.position = pos;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetStartMINSize(HFVECTOR2 size)
//  *
//  * @brief	Sets start minimum size.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	size	The size.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetStartMINSize(HFVECTOR2 size)
// {
// 	m_startParamMIN.size = size;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetStartMINColor(HFVECTOR4 color)
//  *
//  * @brief	Sets start minimum color.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	color	The color.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetStartMINColor(HFVECTOR4 color)
// {
// 	m_startParamMIN.color = color;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetStartMINLife(FLOAT life)
//  *
//  * @brief	Sets start minimum life.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	life	The life.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetStartMINLife(FLOAT life)
// {
// 	m_startParamMIN.life = life;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetStartMINAngle(FLOAT angle)
//  *
//  * @brief	Sets start minimum angle.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	angle	The angle.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetStartMINAngle(FLOAT angle)
// {
// 	m_startParamMIN.angle = angle;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetVelocity(FLOAT pos)
//  *
//  * @brief	Sets a velocity.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	pos	The position.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetVelocity(FLOAT pos)
// {
// 	m_velocity = pos;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetEmitDirection(HFVECTOR3 range)
//  *
//  * @brief	Sets emit direction.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	range	The range.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetEmitDirection(HFVECTOR3 range)
// {
// 	m_emitDirction = range;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetEmitRange(HFVECTOR3 range)
//  *
//  * @brief	Sets emit range.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	range	The range.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetEmitRange(HFVECTOR3 range)
// {
// 	m_emitRange = range;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetMaxParticle(UINT num)
//  *
//  * @brief	Sets maximum particle.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	num	Number of.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetMaxParticle(UINT num)
// {
// 	m_numMaxParticles = num;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetVariationSize(HFVECTOR2 size)
//  *
//  * @brief	Sets variation size.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	size	The size.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetVariationSize(HFVECTOR2 size)
// {
// 	m_variationSize = size;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetVariationColor(HFVECTOR4 color)
//  *
//  * @brief	Sets variation color.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	color	The color.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetVariationColor(HFVECTOR4 color)
// {
// 	m_variationColor = color;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetVariationLife(FLOAT size)
//  *
//  * @brief	Sets variation life.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	size	The size.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetVariationLife(FLOAT size)
// {
// 	m_variationLife = size;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetVariationAngle(FLOAT angle)
//  *
//  * @brief	Sets variation angle.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	angle	The angle.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetVariationAngle(FLOAT angle)
// {
// 	m_variationAngle = angle;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::InitParticleParam()
//  *
//  * @brief	パーティクルの初期化.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  **************************************************************************************************/
// 
// BOOL BaseEmitter::Init()
// {
// 	int count = 0;
// 	for (auto i = m_pParticleList.begin(); i != m_pParticleList.end(); i++)
// 	{
// 	}
// 	return true;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::ResetParticleParam(std::shared_ptr<PARTICLE> i)
//  *
//  * @brief	パーティクルの初期化.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	i	Zero-based index of the.
//  **************************************************************************************************/
// 
 void BaseEmitter::Reset()
 {
 }
 
// void BaseEmitter::ResetParticle(std::shared_ptr<PARTICLE> particle)
// {
// 	if (particle)
// 	{
// 		if (particle->life <= 0.0f)
// 		{
// 			particle->position = D3DXVECTOR3(
// 				UTILITY::Rand(m_startParamMIN.position.x, m_startParamMAX.position.x)
// 				, UTILITY::Rand(m_startParamMIN.position.y, m_startParamMAX.position.y)
// 				, UTILITY::Rand(m_startParamMIN.position.z, m_startParamMAX.position.z)
// 				);
// 
// 			particle->life = UTILITY::Rand(m_startParamMIN.life, m_startParamMAX.life);
// 
// 			if (isSquare)
// 
// 			{
// 				FLOAT size = UTILITY::Rand(m_startParamMIN.size.x, m_startParamMAX.size.x);
// 				particle->size = HFVECTOR2(size, size);
// 			}
// 			else
// 			{
// 				particle->size = HFVECTOR2(
// 					UTILITY::Rand(m_startParamMIN.size.x, m_startParamMAX.size.x),
// 					UTILITY::Rand(m_startParamMIN.size.y, m_startParamMAX.size.y)
// 					);
// 			}
// 			particle->angle = UTILITY::Rand(m_startParamMIN.angle, m_startParamMAX.angle);
// 
// 			particle->color = HFVECTOR4(
// 				UTILITY::Rand(m_startParamMIN.color.x, m_startParamMAX.color.x),
// 				UTILITY::Rand(m_startParamMIN.color.y, (m_startParamMAX.color.y)),
// 				UTILITY::Rand(m_startParamMIN.color.z, (m_startParamMAX.color.z)),
// 				UTILITY::Rand(m_startParamMIN.color.w, (m_startParamMAX.color.w))
// 				);
// 
// 			// 発生後の個別変動量
// 			particle->decreaseLife = m_variationLife;
// 
// 			HFVECTOR3 normal;
// 
// 			HFQUATERNION quaRot;
// 			HFMATRIX matTrans, matRot;
// 			HFQuaternionRotationYawPitchRoll(&quaRot, UTILITY::Rand(-m_emitRange.x, m_emitRange.x), UTILITY::Rand(-m_emitRange.y, m_emitRange.y), UTILITY::Rand(-m_emitRange.z, m_emitRange.z));
// 			HFMatrixRotationQuaternion(&matRot, &quaRot);
// 			HFMatrixTranslation(&matTrans, m_emitDirction.x, m_emitDirction.y, m_emitDirction.z);
// 			matTrans *= matRot;
// 
// 			HFVec3Normalize(&normal, &HFVECTOR3(
// 				matTrans._41, matTrans._42, matTrans._43
// 				));
// 			particle->velocity = normal
// 				* m_velocity;
// 
// 			particle->variationSize = m_variationSize;
// 			particle->variationAngle = m_variationAngle;
// 			particle->variationColor = m_variationColor;
// 		}
// 	}
// 
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::BubbleSortParticles(D3DXMATRIX* pMatView)
//  *
//  * @brief	深度値によりパーティクルをバブルソート.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param [in,out]	pMatView	If non-null, the matrix view.
//  **************************************************************************************************/
// 
// void BaseEmitter::BubbleSortParticles(const HFMATRIX& pMatView)
// {
// 	D3DXVECTOR4 v1, v2;
// 	for (auto it1 = m_pParticleList.begin(); it1 != m_pParticleList.end(); it1++)
// 	{
// 		if ((*it1)->life == 0.0f)
// 			continue;
// 
// 		HFVec3Transform(&v1, &(*it1)->position, &pMatView);
// 
// 		for (auto it2 = it1; it2 != m_pParticleList.end(); it2++)
// 		{
// 			if ((*it1)->life == 0.0f)
// 				continue;
// 
// 			HFVec3Transform(&v2, &(*it2)->position, &pMatView);
// 
// 			// 深度値で奥から手前にむかってソート
// 			if (v1.z < v2.z)
// 			{
// 				std::shared_ptr< PARTICLE> temp;
// 				temp =  *it1;
// 				*it1 = *it2;
// 				*it2 = temp;
// 
// 				D3DXVec3Transform(&v1, &(*it1)->position, &pMatView);
// 			}
// 		}
// 	}
// }
// 
// 
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetGravity(FLOAT g)
//  *
//  * @brief	Sets a gravity.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	g	The FLOAT to process.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetGravity(FLOAT g)
// {
// 	m_gravity = g;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetIsEmit(BOOL emit)
//  *
//  * @brief	Sets is emit.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	emit	true to emit.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetIsEmit(BOOL emit)
// {
// 	isEmit = emit;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetIsLoopt(BOOL emit)
//  *
//  * @brief	Sets is loopt.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	emit	true to emit.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetIsLoopt(BOOL emit)
// {
// 	isLoop = emit;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetWindDirection(HFVECTOR3 emit)
//  *
//  * @brief	Sets wind direction.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	emit	The emit.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetWindDirection(HFVECTOR3 emit)
// {
// 	m_windDirection = emit;
// }