#pragma once
#include "../../../Core/Public/IBaseObject.h"		 
#include "../../Public/GraphicsTypes.h"
#include "../../Matetial/Public/Material.h"

namespace HFGraphics {
	struct MeshData;
}

class VertexBuffer;
class IndexBuffer;


class SubMesh 
	:
	public IBaseObject,
	public inheritable_enable_shared_from_this<SubMesh>
{
public:
	SubMesh() {};
	~SubMesh() {};
	HFGraphics::MeshData& GetMeshData(void)
	{
		return(m_meshData);
	};
	void SetSpMeshData(const HFGraphics::MeshData& spMeshData)
	{
		m_meshData = spMeshData;
	};

	bool LoadDiffuseTexture2D(HFString teturePath);

	std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers()
	{
		return m_spVertexBuffers;
	}

	// セマンティクスを指定してバッファを取得する
	bool GetVertexBuffers(const int bufferNum, const DWORD* semantics, std::vector<std::shared_ptr<VertexBuffer>>& bufferArray);

	void SetVertexBuffers(std::vector<std::shared_ptr<VertexBuffer>>& val)
	{
		m_spVertexBuffers = val;
	}

	std::shared_ptr<IndexBuffer> GetIndexBuffer();

	void SetIndexBuffer(std::shared_ptr<IndexBuffer>& val);

	virtual bool Setup()
	{
		return S_OK;
	};


	// Access the IndexCount
	UINT GetIndexCount(void);

	bool Render();


	// Access the Material
	const std::shared_ptr<Material>& GetMaterial(void) const
	{
		return(m_material);
	};
	void SetMaterial(const std::shared_ptr<Material>& material)
	{
		m_material = material;
	};

protected:
	/** @brief	頂点バッファ. */
	std::vector<std::shared_ptr<VertexBuffer>> m_spVertexBuffers;
	std::shared_ptr<Material>  m_material;

	/** @brief	インデックスバッファ. */
	std::shared_ptr<IndexBuffer> m_spIndexBuffer;
	UINT m_stride;	// 頂点ストライド
	UINT m_indexCount;
	HFGraphics::MeshData m_meshData;
	// Access the RenderPriority
	const DWORD& GetRenderPriority(void) const
	{
		return(m_renderPriority);
	};
	void SetRenderPriority(const DWORD& renderPriority)
	{
		m_renderPriority = renderPriority;
	};

public:

	const UINT& GetStride() const
	{
		return m_stride;
	}
	DWORD m_renderPriority;
};


