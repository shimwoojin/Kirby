#include "stdafx.h"
#include "MeshRendererComponent.h"

void MeshRendererComponent::Initialize()
{
	SetStandardMesh();
}

void MeshRendererComponent::Update()
{
}

void MeshRendererComponent::Destroy()
{
}

void MeshRendererComponent::SetStandardMesh()
{
	//==========================================================================================
	// [Geometry]
	//==========================================================================================
	D3D11_Geometry<D3D11_VertexTexture> geometry;
	Geometry_Generator::CreateQuad(geometry);

	//==========================================================================================
	// [Vertex Buffer]
	//==========================================================================================
	vertex_buffer = std::make_shared<D3D11_VertexBuffer>(context->GetSubSystem<Graphics>());
	vertex_buffer->Create(geometry.GetVertices());

	//==========================================================================================
	// [Index Buffer]
	//==========================================================================================
	index_buffer = std::make_shared<D3D11_IndexBuffer>(context->GetSubSystem<Graphics>());
	index_buffer->Create(geometry.GetIndices());
}
