#include "../Public/BasicMeshFactory.h"
#include "../../Graphics/RenderObject/Public/StaticMeshObject.h"   
#include "../../Graphics/RenderObject/Public/Mesh.h"
#include "../../Graphics/Buffer/Public/VertexBuffer.h" 
#include "../../Graphics/Buffer/Public/IndexBuffer.h"
#include "../Public/BasicMeshManager.h"
#include "../../Graphics/RenderObject/Public/Sprite2DObject.h"
#include "..\..\Graphics\Shader\DirectX\ver.11\Public\DefaultSpriteShader.h"
#include "..\..\Graphics\Shader\DirectX\ver.11\Public\ColorVertexSpriteShader.h"
#include "..\..\Graphics\Shader\DirectX\ver.11\Public\SimplePolygon3DShader.h"

using namespace std;

#define CREATE_ELEMENT (0)

shared_ptr<Mesh> BasicMeshFactory::Create(BASIC_MESH_TYPE meshType,UINT partition1, UINT partition2, UINT partition3)
{
	switch(meshType)
	{
	case HF_BM_SPRITE:
		return CreateSprite();
		break;
	case HF_BM_RECTANGLE_SPRITE:
		return CreateRectangleSprite(partition1);
		break;
	case HF_BM_QUAD:
		return CreateQuad(partition1, partition2);
		break;
	case HF_BM_BOX:
		return nullptr;
		break;
	case HF_BM_SPHERE:
		return nullptr;
		break;
	default:
		return nullptr;
		break;
		
	}
}

shared_ptr<Mesh> BasicMeshFactory::CreateSprite()
{
	shared_ptr<Mesh> renderobject = make_shared<Mesh>();
	if(renderobject)
	{
		renderobject->GetSubMeshArray().resize(1);
		renderobject->GetSubMeshArray()[CREATE_ELEMENT] = make_shared<SubMesh>();

		renderobject->GetSubMeshArray()[CREATE_ELEMENT]->SetMaterial(make_shared<Material>());
		vector<HFVECTOR3> positionArray;
		vector<HFVECTOR2> uvArray;

		renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers().resize(2);
		for (int i = 0; i < renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers().size(); i++)
		{
			renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[i] = make_shared<VertexBuffer>();
		}

		renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[0]->SetSemantics(0,HFGraphics::BufferSemantics("POSITION",0,sizeof(HFVECTOR3),HFGraphics::INPUT_PER_VERTEX_DATA,0));
		renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[1]->SetSemantics(0, HFGraphics::BufferSemantics("TEXCOORD", 0, sizeof(HFVECTOR2), HFGraphics::INPUT_PER_VERTEX_DATA, 0));

		positionArray.resize(4);
		positionArray[0] = HFVECTOR3(-1, 1, 0);
		positionArray[1] = HFVECTOR3(1, 1, 0);
		positionArray[2] = HFVECTOR3(-1, -1, 0);
		positionArray[3] = HFVECTOR3(1, -1, 0);

		if (
			FAILED(
				renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[0]->SetData(
					positionArray.data(),
					sizeof(HFVECTOR3),
					positionArray.size(),
					VertexBuffer::ACCESS_FLAG::WRITEONLY
					)
				)
			)
		{
		}

		uvArray.resize(4);

		uvArray[0] = HFVECTOR2(1, 1);
		uvArray[1] = HFVECTOR2(0, 1);
		uvArray[2] = HFVECTOR2(1, 0);
		uvArray[3] = HFVECTOR2(0, 0);
		if (
			FAILED(
				renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[1]->SetData(
					uvArray.data(),
					sizeof(HFVECTOR2),
					uvArray.size(),
					VertexBuffer::ACCESS_FLAG::WRITEONLY
					)
				)
			)
		{
			return nullptr;
		}
		renderobject->GetSubMeshArray()[CREATE_ELEMENT]->SetIndexBuffer(std::make_shared<IndexBuffer>());
		renderobject->GetSubMeshArray()[CREATE_ELEMENT]->SetParentMesh(renderobject);
		UINT index[6] =
		{
			0,1,2,2,1,3
		};

		if (FAILED(renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetIndexBuffer()->SetData(index, sizeof(UINT), 6, IndexBuffer::ACCESS_FLAG::WRITEONLY)))
		{
			return nullptr;
		}

	}
	

	return renderobject;
}



shared_ptr<Mesh> BasicMeshFactory::CreateQuad(UINT partition1, UINT partition2)
{
	shared_ptr<Mesh> staticMesh = make_shared<Mesh>();
	staticMesh->GetSubMeshArray().resize(1);
	staticMesh->GetSubMeshArray()[CREATE_ELEMENT] = make_shared<SubMesh>();

	vector<HFVECTOR3> positionArray;
	vector<HFVECTOR2> uvArray;

	staticMesh->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers().resize(2);
	for (int i = 0; i < staticMesh->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers().size();i++)
	{
		staticMesh->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[i] = make_shared<VertexBuffer>();
	}
	staticMesh->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[0]->SetSemantics(0, HFGraphics::BufferSemantics("POSITION", 0, sizeof(HFVECTOR3), HFGraphics::INPUT_PER_VERTEX_DATA, 0));
	staticMesh->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[1]->SetSemantics(0, HFGraphics::BufferSemantics("TEXCOORD", 0, sizeof(HFVECTOR2), HFGraphics::INPUT_PER_VERTEX_DATA, 0));

	positionArray.resize(4);
	positionArray[0] = HFVECTOR3(-1,  1, 0);
	positionArray[1] = HFVECTOR3( 1,  1, 0);
	positionArray[2] = HFVECTOR3(-1, -1, 0);
	positionArray[3] = HFVECTOR3( 1, -1, 0);

	if((!staticMesh->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[0]->SetData(positionArray.data(), sizeof(HFVECTOR3), positionArray.size(), VertexBuffer::ACCESS_FLAG::WRITEONLY)))
	{
		return nullptr;
	}

	uvArray.resize(4);

	uvArray[0] = HFVECTOR2(-1,  1);
	uvArray[1] = HFVECTOR2( 1,  1);
	uvArray[2] = HFVECTOR2(-1, -1);
	uvArray[3] = HFVECTOR2( 1, -1);

	if((!staticMesh->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[0]->SetData(uvArray.data(), sizeof(HFVECTOR2), uvArray.size(), VertexBuffer::ACCESS_FLAG::WRITEONLY)))
	{
		return nullptr;
	}
	shared_ptr<Material> spMaterial = make_shared<Material>();
	spMaterial->SetMaterialShader(std::make_shared<SimplePolygon3DShader>());
	spMaterial->GetMaterialShader()->Setup();
	staticMesh->GetSubMeshArray()[CREATE_ELEMENT]->SetMaterial(spMaterial);

	staticMesh->GetSubMeshArray()[CREATE_ELEMENT]->SetIndexBuffer(std::make_shared<IndexBuffer>());
	staticMesh->GetSubMeshArray()[CREATE_ELEMENT]->SetParentMesh(staticMesh);

	UINT index[6] =
	{
		0,1,2,2,1,3
	};

	if (!(staticMesh->GetSubMeshArray()[CREATE_ELEMENT]->GetIndexBuffer()->SetData(index, sizeof(UINT), 6, IndexBuffer::ACCESS_FLAG::WRITEONLY)))
	{
		return nullptr;
	}
	return staticMesh;
}



std::shared_ptr<Mesh> BasicMeshFactory::CreateRectangleSprite(int rectCount)
{
	shared_ptr<Mesh> renderobject = make_shared<Mesh>();
	if (renderobject)
	{
		renderobject->GetSubMeshArray().resize(1);
		renderobject->GetSubMeshArray()[CREATE_ELEMENT] = make_shared<SubMesh>();

		renderobject->GetSubMeshArray()[CREATE_ELEMENT]->SetMaterial(make_shared<Material>());
		vector<HFVECTOR3> positionArray;
		vector<HFVECTOR2> uvArray;
		vector<HFVECTOR4> colorVector;

		renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers().resize(3);
		for (int i = 0; i < renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers().size(); i++)
		{
			renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[i] = make_shared<VertexBuffer>();
		}
		renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[0]->SetSemantics(0, HFGraphics::BufferSemantics("POSITION", 0, sizeof(HFVECTOR3), HFGraphics::INPUT_PER_VERTEX_DATA, 0));
		renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[1]->SetSemantics(0, HFGraphics::BufferSemantics("TEXCOORD", 0, sizeof(HFVECTOR2), HFGraphics::INPUT_PER_VERTEX_DATA, 0));
		renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[1]->SetSemantics(0, HFGraphics::BufferSemantics("DIFFUSE", 0, sizeof(HFVECTOR4), HFGraphics::INPUT_PER_VERTEX_DATA, 0));


		for (int i = 0;i < rectCount;i++)
		{
			
			positionArray.push_back(HFVECTOR3(sin(HFToRadian(360 / rectCount*i)), cos(HFToRadian(360 / rectCount*i)),0));
		}

		if (
			FAILED(
				renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[0]->SetData(
					positionArray.data(),
					sizeof(HFVECTOR3),
					positionArray.size(),
					VertexBuffer::ACCESS_FLAG::WRITEONLY
				)
			)
			)
		{
		}

		colorVector.push_back(HFVECTOR4(1, 0, 0, 1));
		colorVector.push_back(HFVECTOR4(0, 1, 0, 1));
		colorVector.push_back(HFVECTOR4(0, 0, 1, 1));

		renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[2]->SetData(
			colorVector.data(),
			sizeof(HFVECTOR4),
			colorVector.size(),
			VertexBuffer::ACCESS_FLAG::WRITEONLY);

		for (int i = 0; i < rectCount; i++)
		{

			uvArray.push_back(HFVECTOR2(sin(HFToRadian(360 / rectCount*i)), cos(HFToRadian(360 / rectCount*i))));
		}
		if (
			FAILED(
				renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetVertexBuffers()[1]->SetData(
					uvArray.data(),
					sizeof(HFVECTOR2),
					uvArray.size(),
					VertexBuffer::ACCESS_FLAG::WRITEONLY
				)
			)
			)
		{
			return nullptr;
		}
		renderobject->GetSubMeshArray()[CREATE_ELEMENT]->SetIndexBuffer(std::make_shared<IndexBuffer>());

		vector<UINT> indexVector;
		indexVector.resize((rectCount-2)*3);
		for (int i = 0;i < rectCount-2;i++)
		{
			indexVector[i * 3] = 0;
			indexVector[i * 3+1] = i  + 1;
			indexVector[i * 3+2] = i  + 2;
		}

		if (FAILED(renderobject->GetSubMeshArray()[CREATE_ELEMENT]->GetIndexBuffer()->SetData(indexVector.data(), sizeof(UINT), indexVector.size(), IndexBuffer::ACCESS_FLAG::WRITEONLY)))
		{
			return nullptr;
		}
		renderobject->GetSubMeshArray()[CREATE_ELEMENT]->SetParentMesh(renderobject);
		shared_ptr<Material> spMaterial = make_shared<Material>();
		spMaterial->SetMaterialShader(std::make_shared<ColorVertexShader>());
		spMaterial->GetMaterialShader()->Setup();
		renderobject->GetSubMeshArray()[CREATE_ELEMENT]->SetMaterial(spMaterial);
	}

	return renderobject;
}
