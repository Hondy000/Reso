#include "../Public/MeshFactory.h"
#include "../Reader/Public/HFMReader.h"
#include "../../Utility/Public/StringUtility.h"
#include "../../Graphics/RenderObject/Public/StaticMeshObject.h"
#include "../../Graphics/Buffer/Public/VertexBuffer.h"
#include "../../Graphics/Buffer/Public/IndexBuffer.h"
#include "../../Graphics/RenderObject/Public/Mesh.h"
#include "../../Graphics/Shader/DirectX/ver.11/Public/DefaultMeshShader.h"
#include "../Public/Texture2DManager.h"
#include "../../Graphics/Shader/DirectX/ver.11/Public/DeferredShader.h"

using namespace std;


std::shared_ptr<Mesh> MeshFactory::Create(const std::string & path)
{
	HRESULT hr = E_FAIL;

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();


	// まだ読み込んでないのでパスから読み込みパーサー/ローダーに解析してもらう

	std::shared_ptr<HFGraphics::MeshData> data = std::shared_ptr<HFGraphics::MeshData>(new HFGraphics::MeshData);

	// 拡張子 解析
	std::string format = UTILITY::AnalysisFormat(path);


	if ("hfm" == format)
	{
		std::shared_ptr<HFMReader> spLoader = std::shared_ptr<HFMReader>(new HFMReader);
		///	hr = CheckFilePath(filePath);
		hr = spLoader->Read(path, data);
	}
	else
	{
		// 失敗
		hr = E_FAIL;
		return nullptr;
	}

	std::vector<HFVECTOR3> postiionVector;
	std::vector<HFVECTOR3> normalVector;
	std::vector<HFVECTOR2> texVector;
	std::vector<HFVECTOR4> ambientVector;
	std::vector<HFVECTOR4> diffuseVector;
	std::vector<HFVECTOR4> emissiveVector;
	std::vector<HFVECTOR4> specularVector;

	std::vector<UINT> indexVector;
	mesh->GetSubMeshArray().resize(data->submeshArray.size());
	for (int i = 0; i < data->submeshArray.size(); i++)
	{
		data->submeshArray[i]->CreatePolygonIndex(indexVector);
		data->submeshArray[i]->CreatePositionElement(postiionVector);
		data->submeshArray[i]->CreateNormalElement(normalVector);
		data->submeshArray[i]->CreateTexElement(texVector);
		data->submeshArray[i]->CreateMaterialVec4Element(ambientVector, HFGraphics::MATERIAL_ELEMENT::AMBIENT);
		data->submeshArray[i]->CreateMaterialVec4Element(diffuseVector, HFGraphics::MATERIAL_ELEMENT::DIFFUSE);
		data->submeshArray[i]->CreateMaterialVec4Element(emissiveVector, HFGraphics::MATERIAL_ELEMENT::EMISSIVE);
		data->submeshArray[i]->CreateMaterialVec4Element(specularVector, HFGraphics::MATERIAL_ELEMENT::SPECULAR);
		mesh->GetSubMeshArray()[i] = std::shared_ptr<SubMesh>(new SubMesh);
		mesh->GetSubMeshArray()[i]->GetVertexBuffers().resize(7);
		for (int j = 0; j < mesh->GetSubMeshArray()[i]->GetVertexBuffers().size(); j++)
		{
			mesh->GetSubMeshArray()[i]->GetVertexBuffers()[j] = std::shared_ptr<VertexBuffer>(new VertexBuffer);
		}
		mesh->GetSubMeshArray()[i]->GetVertexBuffers()[0]->SetSemantics(HF_SEMANTICS_POSITION);
		mesh->GetSubMeshArray()[i]->GetVertexBuffers()[1]->SetSemantics(HF_SEMANTICS_NORMAL);
		mesh->GetSubMeshArray()[i]->GetVertexBuffers()[2]->SetSemantics(HF_SEMANTICS_TEXCOORD0);
		mesh->GetSubMeshArray()[i]->GetVertexBuffers()[3]->SetSemantics(HF_SEMANTICS_DIFFUSE);
		mesh->GetSubMeshArray()[i]->GetVertexBuffers()[4]->SetSemantics(HF_SEMANTICS_AMBIENT);
		mesh->GetSubMeshArray()[i]->GetVertexBuffers()[5]->SetSemantics(HF_SEMANTICS_SPECULAR);
		mesh->GetSubMeshArray()[i]->GetVertexBuffers()[6]->SetSemantics(HF_SEMANTICS_EMISSIVE);

		hr = mesh->GetSubMeshArray()[i]->GetVertexBuffers()[0]->SetData(postiionVector.data(), sizeof(HFVECTOR3), postiionVector.size(), BaseBuffer::ACCESS_FLAG::WRITEONLY);
		hr = mesh->GetSubMeshArray()[i]->GetVertexBuffers()[1]->SetData(normalVector.data(), sizeof(HFVECTOR3), normalVector.size(), BaseBuffer::ACCESS_FLAG::WRITEONLY);
		hr = mesh->GetSubMeshArray()[i]->GetVertexBuffers()[2]->SetData(texVector.data(), sizeof(HFVECTOR2), texVector.size(), BaseBuffer::ACCESS_FLAG::WRITEONLY);
		hr = mesh->GetSubMeshArray()[i]->GetVertexBuffers()[3]->SetData(diffuseVector.data(), sizeof(HFVECTOR4), diffuseVector.size(), BaseBuffer::ACCESS_FLAG::WRITEONLY);
		hr = mesh->GetSubMeshArray()[i]->GetVertexBuffers()[4]->SetData(ambientVector.data(), sizeof(HFVECTOR4), ambientVector.size(), BaseBuffer::ACCESS_FLAG::WRITEONLY);
		hr = mesh->GetSubMeshArray()[i]->GetVertexBuffers()[5]->SetData(specularVector.data(), sizeof(HFVECTOR4), specularVector.size(), BaseBuffer::ACCESS_FLAG::WRITEONLY);
		hr = mesh->GetSubMeshArray()[i]->GetVertexBuffers()[6]->SetData(emissiveVector.data(), sizeof(HFVECTOR4), emissiveVector.size(), BaseBuffer::ACCESS_FLAG::WRITEONLY);

		mesh->GetSubMeshArray()[i]->SetIndexBuffer(std::shared_ptr<IndexBuffer>(new IndexBuffer));

		hr = mesh->GetSubMeshArray()[i]->GetIndexBuffer()->SetData(indexVector.data(), sizeof(UINT), indexVector.size(), BaseBuffer::ACCESS_FLAG::WRITEONLY);

		mesh->GetSubMeshArray()[i]->SetMaterial(std::make_shared<Material>());
		mesh->GetSubMeshArray()[i]->GetMaterial()->SetMaterialShader(std::make_shared<DeferredShader>());
		mesh->GetSubMeshArray()[i]->GetMaterial()->GetMaterialShader()->Setup();

		mesh->GetSubMeshArray()[i]->GetMaterial()->SetAmbient(HFVECTOR4(1.0f, 0.5f, 0.5f, 10));
		mesh->GetSubMeshArray()[i]->GetMaterial()->SetDiffuse(HFVECTOR4(1.0f, 0.5f, 0.5f, 1));
		mesh->GetSubMeshArray()[i]->GetMaterial()->SetEmissive(HFVECTOR4(1.0f, 0.5f, 0.5f, 10));
		mesh->GetSubMeshArray()[i]->GetMaterial()->SetSpecular(HFVECTOR4(1.0f, 0.1f, 1.0f, 1));

		std::shared_ptr<BaseTexture2D> diffuseTexture;
		diffuseTexture = Texture2DManager::GetInstance()->Get(data->submeshArray[i]->materialArray[0].diffuseFileName);
	
		mesh->GetSubMeshArray()[i]->GetMaterial()->SetDiffuseTexture(diffuseTexture);


	}

	return mesh;
}

void  MeshFactory::PartitionSubMesh(std::shared_ptr<HFGraphics::MeshData> mesh)
{
	
}