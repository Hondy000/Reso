#include "../Public/SubMesh.h"
#include "../../Buffer/Public/VertexBuffer.h"
#include "../../Buffer/Public/IndexBuffer.h"
#include "../../RenderDevice/Basic/Public/RendererManager.h"
#include "../../Shader/Basic/Public/BaseShader.h"
#include "..\..\..\ResorceManager\Public\Texture2DManager.h"

bool SubMesh::LoadDiffuseTexture2D(HFString teturePath)
{
	if (m_material)
	{
		return m_material->LoadDiffuseTexture2D(teturePath);
	}
	return false;
}

bool SubMesh::GetVertexBuffers(const int bufferNum, const DWORD* semantics, std::vector<std::shared_ptr<VertexBuffer>>& bufferArray)
{
	if (bufferArray.size() < bufferNum)
	{
		bufferArray.resize(bufferNum);
	}
	for (int i = 0; i < bufferNum; i++)
	{

		for (int j = 0; j < m_spVertexBuffers.size(); j++)
		{
			if (semantics[i] == m_spVertexBuffers[j]->GetSemantics())
			{

				bufferArray[i] = m_spVertexBuffers[j];
				break;
			}
		}

	}
	return S_OK;
}

std::shared_ptr<IndexBuffer>SubMesh::GetIndexBuffer()
{
	return m_spIndexBuffer;
}

void SubMesh::SetIndexBuffer(std::shared_ptr<IndexBuffer>& val)
{
	m_spIndexBuffer = val;
}

UINT SubMesh::GetIndexCount(void)
{
	return m_spIndexBuffer->GetDataCount();
}

bool SubMesh::Render()
{
	m_material->GetMaterialShader()->PreProcessOfRender(shared_from_this(),m_material);
	m_material->GetMaterialShader()->Render();
	m_material->GetMaterialShader()->PostProcessOfRender();
	return true;
}

bool SubMesh::GetPositions(std::vector<HFVECTOR3>& array)
{
	std::vector<std::shared_ptr<VertexBuffer>> buffer;
	DWORD semantics = HF_SEMANTICS_POSITION;
	GetVertexBuffers(1, &semantics, buffer);
	array.resize( buffer[0]->GetDataCount());
	buffer[0]->GetData(array.data(),sizeof(HFVECTOR3));
	return true;
}

std::weak_ptr<Mesh> SubMesh::GetParentMesh() const
{
	return m_parentMesh;
}

void SubMesh::SetParentMesh(std::shared_ptr<Mesh>& _val)
{
	m_parentMesh = _val;
}
