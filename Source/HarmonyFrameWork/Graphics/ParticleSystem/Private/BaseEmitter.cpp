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

/**********************************************************************************************//**
 * @fn	bool BaseEmitter::Update()
 *
 * @brief	Updates this object.
 *
 * @author	Kazuyuki Honda
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool BaseEmitter::Update()
{
	// �A���t�@�l�̍X�V
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

	// �p�[�e�B�N���̏�����
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
			BufferDesc.ByteWidth = m_pParticleList.size() * sizeof(IBUFFER0);   // �o�b�t�@�T�C�Y
			BufferDesc.Usage = D3D11_USAGE_DYNAMIC;                 // ���\�[�X�g�p�@����肷��
			BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;            // �o�b�t�@�̎��
			BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;              // CPU �A�N�Z�X����
			BufferDesc.MiscFlags = 0;                                   // ���̑��̃t���O���ݒ肵�Ȃ�
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
	// �\�[�g
	HFMATRIX view;
	sRENDER_DEVICE_MANAGER->GetTransform(&view, HFTS_VIEW);
	

	return true;
}


  // 		
  // 		void BaseEmitter::SetStartMAXPosition(HFVECTOR3 pos)
  // 		{
  // 			m_startParamMAX.position = pos;
  // 		}
  // 		
  // 		
  // 		void BaseEmitter::SetStartMAXSize(HFVECTOR2 size)
  // 		{
  // 			m_startParamMAX.size = size;
  // 		}
  // 		

  // 		void BaseEmitter::SetStartMAXColor(HFVECTOR4 color)
  // 		{
  // 			m_startParamMAX.color = color;
  // 		}
  // 		
  // 		
  // 		void BaseEmitter::SetStartMAXLife(FLOAT life)
  // 		{
  // 			m_startParamMAX.life = life;
  // 		}
  // 		

  // 		void BaseEmitter::SetStartMAXAngle(FLOAT angle)
  // 		{
  // 			m_startParamMAX.angle = angle;
  // 		}
  // 		

  // 		void BaseEmitter::SetStartMINPosition(HFVECTOR3 pos)
  // 		{
  // 			m_startParamMIN.position = pos;
  // 		}
  // 		

  // 		void BaseEmitter::SetStartMINSize(HFVECTOR2 size)
  // 		{
  // 			m_startParamMIN.size = size;
  // 		}

  // 		void BaseEmitter::SetStartMINColor(HFVECTOR4 color)
  // 		{
  // 			m_startParamMIN.color = color;
  // 		}
  // 		

  // 		void BaseEmitter::SetStartMINLife(FLOAT life)
  // 		{
  // 			m_startParamMIN.life = life;
  // 		}
  // 		

  // 		void BaseEmitter::SetStartMINAngle(FLOAT angle)
  // 		{
  // 			m_startParamMIN.angle = angle;
  // 		}
  // 		

  // 		void BaseEmitter::SetVelocity(FLOAT pos)
  // 		{
  // 			m_velocity = pos;
  // 		}
  // 		

// 		void BaseEmitter::SetEmitDirection(HFVECTOR3 range)
// 		{
// 			m_emitDirction = range;
// 		}
// 		
// 		
// 		void BaseEmitter::SetEmitRange(HFVECTOR3 range)
// 		{
// 			m_emitRange = range;
// 		}
// 		
// 		
// 		void BaseEmitter::SetMaxParticle(UINT num)
// 		{
// 			m_numMaxParticles = num;
// 		}
// 		
//		
//		void BaseEmitter::SetVariationSize(HFVECTOR2 size)
//		{
//			m_variationSize = size;
//		}
//		
 // 		
 // 		void BaseEmitter::SetVariationColor(HFVECTOR4 color)
 // 		{
 // 			m_variationColor = color;
 // 		}
 // 		
		
	//void BaseEmitter::SetVariationLife(FLOAT size)
	//{
	//	m_variationLife = size;
	//}

// 		
// 		void BaseEmitter::SetVariationAngle(FLOAT angle)
// 		{
// 			m_variationAngle = angle;
// 		}
// 		
// 		
// 		bool BaseEmitter::Init()
// 		{
// 			int count = 0;
// 			for (auto i = m_pParticleList.begin(); i != m_pParticleList.end(); i++)
// 			{
// 			}
// 			return true;
// 		}
// 		

//void BaseEmitter::Reset()
//{
//}
 
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
// 			// ������̌ʕϓ���
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
//  * @brief	�[�x�l�ɂ��p�[�e�B�N�����o�u���\�[�g.
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
// 			// �[�x�l�ŉ������O�ɂނ����ă\�[�g
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
//  * @fn	void CBaseEmitter::SetIsEmit(bool emit)
//  *
//  * @brief	Sets is emit.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	emit	true to emit.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetIsEmit(bool emit)
// {
// 	isEmit = emit;
// }
// 
// /**********************************************************************************************//**
//  * @fn	void CBaseEmitter::SetIsLoopt(bool emit)
//  *
//  * @brief	Sets is loopt.
//  *
//  * @author	Kazuyuki Honda
//  * @date	2015/11/04
//  *
//  * @param	emit	true to emit.
//  **************************************************************************************************/
// 
// void BaseEmitter::SetIsLoopt(bool emit)
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