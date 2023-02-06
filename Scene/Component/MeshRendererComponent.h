#pragma once
#include "IComponent.h"

enum class MeshType : uint
{
	Quad, 
	ScreenQuad
};

class MeshRendererComponent final : public IComponent
{
public:
	using IComponent::IComponent;
	~MeshRendererComponent() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	//====================================
	// [Mesh]
	//====================================
	std::shared_ptr<D3D11_VertexBuffer> GetVertexBuffer() const { return vertex_buffer; }
	std::shared_ptr<D3D11_IndexBuffer> GetIndexBuffer() const { return index_buffer; }
	void SetStandardMesh();

private:
	MeshType mesh_type = MeshType::Quad;

	std::shared_ptr<D3D11_VertexBuffer> vertex_buffer;
	std::shared_ptr<D3D11_IndexBuffer> index_buffer;
};

