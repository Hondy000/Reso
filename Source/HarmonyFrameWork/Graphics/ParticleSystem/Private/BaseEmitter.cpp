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
#include "..\..\Public\RenderCommand.h"
#include "..\..\RenderObject\Public\Mesh.h"
#include "..\..\..\Core\Task\Public\TaskSystem.h"
#include "..\..\..\ResorceManager\Public\BasicMeshManager.h"
#include "..\..\Shader\DirectX\ver.11\Public\ParticleShader.h"
#include "..\..\..\ResorceManager\Public\ParticleFactory.h"
#include "../../../Utility/Public/Time.h"

using namespace std;

BaseEmitter::BaseEmitter()
{
}

void BaseEmitter::SetMaxParticle(UINT num)
{
	SetMesh(ParticleFactory::GetInstance()->GetQuadParticle(num));
	SetMaterialShader(0, std::make_shared<ParticleShader>());
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
	RegisterVariable("m_numParticles", m_numParticles);
	RegisterVariable("m_waitTime", m_waitTime);
	RegisterVariable("m_progressTime", m_emittTime);
	RegisterVariable("m_numParticleOfOutAtATime", m_numParticleOfOutAtATime);
	RegisterVariable("m_particleRenderRange", m_particleRenderRange);
	RegisterVariable("m_emitRange", m_emitRange);
	RegisterVariable("m_emitDirction", m_emitDirction);
	RegisterVariable("m_velocity", m_velocity);
	SetMesh( ParticleFactory::GetInstance()->GetQuadParticle(100));
	SetMaterialShader(0, std::make_shared<ParticleShader>());
	m_particleArray.resize(100);
	for (int i = 0;i<100;i++)
	{
		m_particleArray[i] = std::make_shared<IBaseParticle>();
	}
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
	m_waitTime += HFTime::GetInstance()->GetGameDeltaSeconds();
	if(m_emittTime <= m_waitTime)
	{
		// 時間経過でパーティクルを放出
		EmittParticle();
	}
	for (int i = 0; i < m_particleArray.size(); i++)
	{
		m_particleArray[i]->Update();
	}

	for (int i = 0; i < GetMesh()->GetSubMeshArray().size(); i++)
	{
		std::shared_ptr<RenderCommand> command;
		command = std::shared_ptr<RenderCommand>(new RenderCommand);
		command->SetRenderObject(shared_from_this());
		command->SetRenderMeshElement(i);
		command->SetRenderPriority(GetMesh()->GetSubMeshArray()[i]->GetMaterial()->GetMaterialShader()->GetPathPriority());
		///m_mesh->GetSubMeshArray()[i]->GetMaterial()->GetMaterialShader()->WriteInstanceData(m_mesh->GetSubMeshArray()[i], matArray.data(), sizeof(HFMATRIX));
		TaskSystem::GetInstance()->RegisterRenderCommand(command);
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
