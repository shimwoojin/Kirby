#include "stdafx.h"
#include "MaterialRendererComponent.h"

void MaterialRendererComponent::Initialize()
{
	resource_manager = context->GetSubSystem<ResourceManager>();
	SetStandardMaterial();
}

void MaterialRendererComponent::Update()
{
}

void MaterialRendererComponent::Destroy()
{
}

void MaterialRendererComponent::SetTexture2D(const std::string& path)
{
	texture = resource_manager->Load<Texture2D>(path);
}

void MaterialRendererComponent::SetStandardMaterial()
{
	texture = resource_manager->Load<Texture2D>("./Assets/Texture/Maps/MapTile_Dessert.png");
	vertex_shader = resource_manager->Load<Shader>("./Assets/Shader/Texture.hlsl").get()->GetVertexShader();
	pixel_shader = resource_manager->Load<Shader>("./Assets/Shader/Texture.hlsl").get()->GetPixelShader();

	//==========================================================================================
	// [Input Layout]
	//==========================================================================================
	input_layout = std::make_shared<D3D11_InputLayout>(context->GetSubSystem<Graphics>());
	input_layout->Create(D3D11_VertexTexture::descs, D3D11_VertexTexture::count, vertex_shader->GetShaderBlob());
}
