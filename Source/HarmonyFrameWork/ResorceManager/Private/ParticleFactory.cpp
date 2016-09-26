#include "..\Public\ParticleFactory.h"
#include "..\..\Graphics\RenderObject\Public\Mesh.h"
#include "..\..\Graphics\Buffer\Public\VertexBuffer.h"
#include "..\..\Graphics\Shader\Basic\Public\BaseGraphicsShader.h"
#include "..\..\Graphics\Buffer\Public\IndexBuffer.h"
#include "..\..\Graphics\Shader\DirectX\ver.11\Public\ParticleShader.h"
using namespace std;
ParticleFactory::ParticleFactory()
{
}

ParticleFactory::~ParticleFactory()
{
}

std::shared_ptr<Mesh> ParticleFactory::GetQuadParticle(UINT particleNum)
{
	shared_ptr<Mesh> staticMesh = make_shared<Mesh>();
	staticMesh->GetSubMeshArray().resize(1);
	staticMesh->GetSubMeshArray()[0] = make_shared<SubMesh>();
	staticMesh->GetSubMeshArray()[0]->SetParentMesh(staticMesh);
	vector<HFVECTOR3> positionArray;
	vector<HFVECTOR2> uvArray;

	staticMesh->GetSubMeshArray()[0]->GetVertexBuffers().resize(4);
	for (int i = 0; i < staticMesh->GetSubMeshArray()[0]->GetVertexBuffers().size(); i++)
	{
		staticMesh->GetSubMeshArray()[0]->GetVertexBuffers()[i] = make_shared<VertexBuffer>();
	}
	staticMesh->GetSubMeshArray()[0]->GetVertexBuffers()[0]->SetSemantics(0, "POSITION", 0, sizeof(HFVECTOR3), HFGraphics::INPUT_PER_VERTEX_DATA, 0);
	staticMesh->GetSubMeshArray()[0]->GetVertexBuffers()[1]->SetSemantics(0, "TEXCOORD", 0, sizeof(HFVECTOR2), HFGraphics::INPUT_PER_VERTEX_DATA, 0);

	positionArray.resize(4);
	positionArray[0] = HFVECTOR3(-1, 1, 0);
	positionArray[1] = HFVECTOR3(1, 1, 0);
	positionArray[2] = HFVECTOR3(-1, -1, 0);
	positionArray[3] = HFVECTOR3(1, -1, 0);

	if ((!staticMesh->GetSubMeshArray()[0]->GetVertexBuffers()[0]->SetData(positionArray.data(), sizeof(HFVECTOR3), positionArray.size(), VertexBuffer::ACCESS_FLAG::WRITEONLY)))
	{
		return nullptr;
	}

	uvArray.resize(4);

	uvArray[0] = HFVECTOR2(0, 1);
	uvArray[1] = HFVECTOR2(1, 1);
	uvArray[2] = HFVECTOR2(0, 0);
	uvArray[3] = HFVECTOR2(1, 0);

	staticMesh->GetSubMeshArray()[0]->GetVertexBuffers()[1]->SetSemantics(0,"TEXCOORD",0,sizeof(HFVECTOR2),HFGraphics::INPUT_PER_VERTEX_DATA,0);
	if ((!staticMesh->GetSubMeshArray()[0]->GetVertexBuffers()[1]->SetData(uvArray.data(), sizeof(HFVECTOR2), uvArray.size(), VertexBuffer::ACCESS_FLAG::WRITEONLY)))
	{
		return nullptr;
	}

	// インスタンスの行列パラメータ用のバッファ
	staticMesh->GetSubMeshArray()[0]->GetVertexBuffers()[2]->SetSemantics(0, "MATRIX", 0, sizeof(HFVECTOR4), HFGraphics::INPUT_PER_INSTANCE_DATA, 1);
	staticMesh->GetSubMeshArray()[0]->GetVertexBuffers()[2]->SetSemantics(1, "MATRIX", 1, sizeof(HFVECTOR4), HFGraphics::INPUT_PER_INSTANCE_DATA, 1);
	staticMesh->GetSubMeshArray()[0]->GetVertexBuffers()[2]->SetSemantics(2, "MATRIX", 2, sizeof(HFVECTOR4), HFGraphics::INPUT_PER_INSTANCE_DATA, 1);
	staticMesh->GetSubMeshArray()[0]->GetVertexBuffers()[2]->SetSemantics(3, "MATRIX", 3, sizeof(HFVECTOR4), HFGraphics::INPUT_PER_INSTANCE_DATA, 1);
	if ((!staticMesh->GetSubMeshArray()[0]->GetVertexBuffers()[2]->SetData(NULL, sizeof(HFMATRIX), particleNum, VertexBuffer::ACCESS_FLAG::WRITEONLY)))
	{
		return nullptr;
	}

	// インスタンスのカラーパラメータ用のバッファ
	staticMesh->GetSubMeshArray()[0]->GetVertexBuffers()[3]->SetSemantics(0, "COLOR", 0, sizeof(HFColor), HFGraphics::INPUT_PER_INSTANCE_DATA, 1);
	if ((!staticMesh->GetSubMeshArray()[0]->GetVertexBuffers()[3]->SetData(NULL, sizeof(HFColor), particleNum, VertexBuffer::ACCESS_FLAG::WRITEONLY)))
	{
		return nullptr;
	}

	shared_ptr<Material> spMaterial = make_shared<Material>();
	spMaterial->SetMaterialShader(std::make_shared<ParticleShader>());
	staticMesh->GetSubMeshArray()[0]->SetMaterial(spMaterial);

	staticMesh->GetSubMeshArray()[0]->SetIndexBuffer(std::make_shared<IndexBuffer>());

	UINT index[6] =
	{
		0,1,2,2,1,3
	};

	if (!(staticMesh->GetSubMeshArray()[0]->GetIndexBuffer()->SetData(index, sizeof(UINT), 6, IndexBuffer::ACCESS_FLAG::WRITEONLY)))
	{
		return nullptr;
	}
	return staticMesh;
}
