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
#include "../../../Core/Task/Public/TaskInterface.h"
#include "..\..\Public\BaseGraphicsCommand.h"
#include "..\..\RenderObject\Public\Mesh.h"
#include "..\..\..\Core\Task\Public\TaskSystem.h"
#include "..\..\..\ResorceManager\Public\BasicMeshManager.h"
#include "..\..\Shader\DirectX\ver.11\Public\ParticleShader.h"
#include "..\..\..\ResorceManager\Public\ParticleFactory.h"
#include "../../../Utility/Public/HFSyatemTime.h"
#include "../../Shader/DirectX/ver.11/Public/GPUParticleShader.h"

using namespace std;

BaseEmitter::BaseEmitter()
{
	m_waitTime = 0;
	m_emittTime = 0;
}

void BaseEmitter::SetMaxParticle(UINT num)
{
	SetMesh(ParticleFactory::GetInstance()->GetQuadParticle(num));
	SetMaterialShader(0, std::make_shared<GPUParticleShader>());
	m_particleArray.resize(num);
	for (int i = 0; i < num; i++)
	{
		m_particleArray[i] = std::make_shared<IBaseParticle>();
	}
}

BaseEmitter::~BaseEmitter()
{

}

bool BaseEmitter::Init()
{
	RegisterVariable("m_numParticles", m_numMaxParticles);
	RegisterVariable("m_waitTime", m_waitTime);
	RegisterVariable("m_progressTime", m_emittTime);
	RegisterVariable("m_emitRange", m_emitRange);
	RegisterVariable("m_emitDirction", m_emitDirction);
	RegisterVariable("m_velocity", m_velocity);
	SetMesh( ParticleFactory::GetInstance()->GetQuadParticle(5000));
	SetMaterialShader(0, std::make_shared<GPUParticleShader>());
	m_particleArray.resize(5000);
	for (int i = 0;i<m_particleArray.size();i++)
	{
		m_particleArray[i] = std::make_shared<IBaseParticle>();
	}
	m_emitParticlePerSecond = 50;
	m_particleLife = 5.0f;
	m_emitRange = HFVECTOR3(10, 10, 10);
	m_emitDirction = HFVECTOR3(0, 1, 0);
	m_color = HFColor(1, 0.5, 1, 1.0f);
	LoadDiffuseTexture2D(0, "Resource/Textire/DefaultWhite.png");
	return true;
}

void BaseEmitter::Reset()
{

}



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
	m_waitTime += HFSyatemTime::GetInstance()->GetGameDeltaSeconds();
	if(1.0f / (float)m_emitParticlePerSecond <= m_waitTime)
	{
		m_waitTime = m_waitTime - 1.0f / (float)m_emitParticlePerSecond;
		// 時間経過でパーティクルを放出
		EmittParticle();
	}
	for (int i = 0; i < m_particleArray.size(); i++)
	{
		m_particleArray[i]->Update();
	}

	return true;
}


 
void BaseEmitter::ResetParticle(std::shared_ptr<IBaseParticle> particle)
{
	particle->SetDirection(
		HFVECTOR3(
			UTILITY::Rand(m_emitRange.x*-0.5f, m_emitRange.x*0.5f) + m_emitDirction.x,
			UTILITY::Rand(m_emitRange.y*-0.5f, m_emitRange.y*0.5f) + m_emitDirction.y,
			UTILITY::Rand(m_emitRange.z*-0.5f, m_emitRange.z*0.5f) + m_emitDirction.z));

}
 
void BaseEmitter::EmittParticle()
{
	for (int i = 0; i < m_particleArray.size();i++)
	{
		if (m_particleArray[i]->GetLife() <= 0)
		{
			// ライブが0以下
			// 寿命設定
			m_particleArray[i]->SetLife(m_particleLife);
			// 位置をエミッタの位置に
			m_particleArray[i]->GetTransform()->SetPosition(m_transform->GetPosition());
			m_particleArray[i]->SetColor(m_color);
			// 放出方向設定
			HFVECTOR3 direction;
			direction = HFVECTOR3(
				UTILITY::Rand(m_emitRange.x*-0.5f, m_emitRange.x*0.5f) + m_emitDirction.x,
				UTILITY::Rand(m_emitRange.y*-0.5f, m_emitRange.y*0.5f) + m_emitDirction.y,
				UTILITY::Rand(m_emitRange.z*-0.5f, m_emitRange.z*0.5f) + m_emitDirction.z);
			direction.Normalize();
			m_particleArray[i]->SetVelocity(0.1);

			m_particleArray[i]->SetDirection(direction);
			break;
		}
	}
	

}

void BaseEmitter::SphereEmitt()
{

}

void BaseEmitter::ConeEmitt()
{

}

void BaseEmitter::MeshEmitt()
{

}
