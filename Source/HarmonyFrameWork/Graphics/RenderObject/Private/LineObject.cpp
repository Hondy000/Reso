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
#include "..\..\Buffer\Public\IndexBuffer.h"

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
	SetMesh( std::make_shared<Mesh>());
	
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
	if (GetMesh() == nullptr)
	{

		SetMesh(std::make_shared<Mesh>());
	}

	int i = GetMesh()->GetSubMeshArray().size();
	shared_ptr<SubMesh>	 addSubmesh = make_shared<SubMesh>();
	vector<shared_ptr<VertexBuffer>> vertexVector;
	shared_ptr<VertexBuffer> positionBuffer = make_shared<VertexBuffer>();
	positionBuffer->SetSemantics(0,HFGraphics::BufferSemantics("POSITION",0,sizeof(HFVECTOR3),HFGraphics::INPUT_PER_VERTEX_DATA,0));
	if(positionBuffer->SetData(addLine.positions.data(),sizeof(HFVECTOR3),addLine.positions.size(), BaseBuffer::ACCESS_FLAG::WRITEONLY))
	{
		addSubmesh->SetVertexBuffers(vertexVector);
		GetMesh()->GetSubMeshArray().push_back(addSubmesh);
		int addElem = GetMesh()->GetSubMeshArray().size()-1;
		shared_ptr<Material>  material = make_shared<Material>();
		material->SetMaterialShader(make_shared<LineShader>());
		material->GetMaterialShader()->Setup();
		GetMesh()->GetSubMeshArray()[addElem]->SetMaterial(material);
		GetMesh()->GetSubMeshArray()[addElem]->GetVertexBuffers().push_back(positionBuffer);
		// index
		std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>();
		std::vector<UINT> indexVector;
		for (int i = 0;i < addLine.positions.size()*0.5;i++)
		{
			indexVector.push_back(i*2);
			indexVector.push_back(i*2+1);
		}
		if(indexBuffer->SetData(indexVector.data(), sizeof(UINT), indexVector.size(), BaseBuffer::ACCESS_FLAG::WRITEONLY))
		{
			GetMesh()->GetSubMeshArray()[addElem]->SetIndexBuffer(indexBuffer);
			return true;
		}
	}
	return false;
}

