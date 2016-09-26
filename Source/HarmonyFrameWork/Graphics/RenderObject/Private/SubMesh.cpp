#include "../Public/SubMesh.h"
#include "../../Buffer/Public/VertexBuffer.h"
#include "../../Buffer/Public/IndexBuffer.h"
#include "../../RenderDevice/Basic/Public/RendererManager.h"
#include "../../Shader/Basic/Public/BaseGraphicsShader.h"
#include "..\..\..\ResorceManager\Public\Texture2DManager.h"
#include "../../Public/GraphicsTypes.h"

bool SubMesh::LoadDiffuseTexture2D(HFString teturePath)
{
	if (m_material)
	{
		return m_material->LoadDiffuseTexture2D(teturePath);
	}
	return false;
}

void SubMesh::GetVertexBuffers(const int bufferNum, const HFGraphics::BufferLayout* layouts, std::vector<std::shared_ptr<VertexBuffer>>& bufferArray, std::vector<bool>& boolenArray)
{
	if (bufferArray.size() < bufferNum)
	{
		bufferArray.resize(bufferNum);
	}

	for (int i = 0; i < bufferNum; i++)
	{

		for (int j = 0; j < m_spVertexBuffers.size(); j++)
		{
			if (m_spVertexBuffers[j]->GetSementicsLayout() == layouts[i] )
			{

				bufferArray[i] = m_spVertexBuffers[j];
				break;
			}
		}

	}
}


void SubMesh::GetVertexBuffers(HFGraphics::MeshShaderBufferLayout meshShaderBufferLaout, std::vector<std::shared_ptr<VertexBuffer>>& bufferArray, std::vector<bool>& boolenArray)
{
	for (int i = 0; i < meshShaderBufferLaout.m_bufferLayoutArray.size(); i++)
	{
		for (int j = 0; j < m_spVertexBuffers.size(); j++)
		{
			if (m_spVertexBuffers[j]->GetSementicsLayout() == meshShaderBufferLaout.m_bufferLayoutArray[i])
			{
				if (bufferArray.size() <= i)
				{
					bufferArray.resize(i+1);
				}
				bufferArray[i] = m_spVertexBuffers[j];
				break;
			}
		}
	}
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
	HFGraphics::BufferLayout layout[1];
	std::vector<bool> boolenArray;
	GetVertexBuffers(1, layout, buffer,boolenArray);
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
