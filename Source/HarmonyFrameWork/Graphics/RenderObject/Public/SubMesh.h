#pragma once
#include "../../../Core/Public/IBaseObject.h"		 
#include "../../Public/GraphicsTypes.h"
#include "../../Matetial/Public/Material.h"

namespace HFGraphics {
	struct MeshData;
}

class VertexBuffer;
class IndexBuffer;
class Mesh;


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

	// �~�����o�b�t�@���ƃo�b�t�@���̃Z�}���e�B�N�X���C�A�E�g���w�肵�ăo�b�t�@���擾����
	void GetVertexBuffers(const int bufferNum, const HFGraphics::BufferLayout* layouts, std::vector<std::shared_ptr<VertexBuffer>>& bufferArray, std::vector<bool>& boolenArray);

	/***********************************************************************************************
	 * �~�����o�b�t�@�̃Z�}���e�B�N�X���C�A�E�g���w�肵�ēK��������̂��擾.
	 *
	 * @author Kazuyuki
	 *
	 * @param meshShaderBufferLaout The mesh shader buffer laout.
	 * @param bufferArray		    Array of buffers.
	 * @param boolenArray		    Array of boolens.
	 *************************************************************************************************/

	void GetVertexBuffers(HFGraphics::MeshShaderBufferLayout meshShaderBufferLaout, std::vector<std::shared_ptr<VertexBuffer>>& bufferArray ,std::vector<bool>& boolenArray);

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

	bool GetPositions(std::vector<HFVECTOR3>& array);

	std::weak_ptr<Mesh> GetParentMesh() const;

	void SetParentMesh(std::shared_ptr<Mesh>& _val);

	UINT GetIndexCount() const
	{
		return m_indexCount;
	}

	void SetIndexCount(UINT _val)
	{
		m_indexCount = _val;
	}


protected:
	/** @brief	���_�o�b�t�@. */
	std::vector<std::shared_ptr<VertexBuffer>> m_spVertexBuffers;
	std::shared_ptr<Material>  m_material;

	/** @brief	�C���f�b�N�X�o�b�t�@. */
	std::shared_ptr<IndexBuffer> m_spIndexBuffer;
	UINT m_stride;	// ���_�X�g���C�h
	UINT m_indexCount;
	HFGraphics::MeshData m_meshData;
	std::weak_ptr<Mesh> m_parentMesh;
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


