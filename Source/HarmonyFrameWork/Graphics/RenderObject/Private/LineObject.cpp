/**=================================================================================================
 * @file Source\HarmonyFrameWork\Graphics\RenderObject\Private\LineObject.cpp
 *
 * @brief Implements the line object class.
 *===============================================================================================**/

#include "..\Public\LineObject.h"
#include "..\..\Public\RenderCommand.h"
#include "..\Public\Mesh.h"
#include "..\..\..\Core\Task\Public\TaskSystem.h"
#include "..\..\Shader\Basic\Public\BaseShader.h"
#include "..\..\Public\GraphicsTypes.h"
#include "..\..\Buffer\Public\VertexBuffer.h"
#include "..\..\Shader\DirectX\ver.11\Public\LineShader.h"

using namespace std;

/**=================================================================================================
 * @struct Vertex LineObject.cpp
 * Source\HarmonyFrameWork\Graphics\RenderObject\Private\LineObject.cpp
 *
 * @brief A vertex.
 *
 * @author Kazuyuki
 *===============================================================================================**/

struct Vertex
{

};

/**=================================================================================================
 * @fn LineObject::LineObject()
 *
 * @brief Initializes a new instance of the LineObject class.
 *
 * @author Kazuyuki
 *===============================================================================================**/

LineObject::LineObject()
{
	Init();
}

/**=================================================================================================
 * @fn LineObject::~LineObject()
 *
 * @brief Finalizes an instance of the LineObject class.
 *
 * @author Kazuyuki
 *===============================================================================================**/

LineObject::~LineObject()
{
}

/**=================================================================================================
 * @fn bool LineObject::Init()
 *
 * @brief Initialises this object.
 *
 * @author Kazuyuki
 *
 * @return true if it succeeds, false if it fails.
 *===============================================================================================**/

bool LineObject::Init()
{
	m_mesh = std::make_shared<Mesh>();
	
	return true;
}

/**=================================================================================================
 * @fn bool LineObject::Update()
 *
 * @brief Updates this object.
 *
 * @author Kazuyuki
 *
 * @return true if it succeeds, false if it fails.
 *===============================================================================================**/

bool LineObject::Update()
{
	for (int i = 0; i < m_mesh->GetSubMeshArray().size(); i++)
	{
		std::shared_ptr<RenderCommand> command;
		command = std::shared_ptr<RenderCommand>(new RenderCommand);
		command->SetRenderObject(shared_from_this());
		command->SetRenderMeshElement(i);
		command->SetRenderPriority(m_mesh->GetSubMeshArray()[i]->GetMaterial()->GetMaterialShader()->GetPathPriority());
		sTASK_SYSTEM->RegisterRenderCommand(command);
	}
	return true;
}

/**=================================================================================================
 * @fn void LineObject::Reset()
 *
 * @brief Resets this object.
 *
 * @author Kazuyuki
 *===============================================================================================**/

void LineObject::Reset()
{

}

/**=================================================================================================
 * @fn bool LineObject::AddLine(HFGraphics::LineData addLine)
 *
 * @brief Adds a line.
 *
 * @author Kazuyuki
 *
 * @param addLine The add line.
 *
 * @return true if it succeeds, false if it fails.
 *===============================================================================================**/

bool LineObject::AddLine(HFGraphics::LineData& addLine)
{
	int i = m_mesh->GetSubMeshArray().size();
	shared_ptr<SubMesh>	 addSubmesh = make_shared<SubMesh>();
	vector<shared_ptr<VertexBuffer>> vertexVector;
	shared_ptr<VertexBuffer> positionBuffer = make_shared<VertexBuffer>();
	positionBuffer->SetSemantics(HF_SEMANTICS_POSITION);
	if(positionBuffer->SetData(addLine.positions.data(),sizeof(HFVECTOR3),addLine.positions.size(), BaseBuffer::ACCESS_FLAG::WRITEONLY))
	{
		addSubmesh->SetVertexBuffers(vertexVector);
		m_mesh->GetSubMeshArray().push_back(addSubmesh);
		int addElem = m_mesh->GetSubMeshArray().size()-1;
		shared_ptr<Material>  material = make_shared<Material>();
		material->SetMaterialShader(make_shared<LineShader>());
		material->GetMaterialShader()->Setup();
		m_mesh->GetSubMeshArray()[addElem]->SetMaterial(material);
		return true;
	}
	return false;
}

