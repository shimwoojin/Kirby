#include "stdafx.h"
#include "Shader.h"

Shader::Shader(Context* const context)
    : IResource(context, ResourceType::Shader)
{
}

bool Shader::SaveToFile(const std::string& path)
{
    return true;
}

bool Shader::LoadFromFile(const std::string& path)
{
	vertex_shader = std::make_shared<D3D11_Shader>(context->GetSubSystem<Graphics>());
	vertex_shader->Create(ShaderScope_VS, path);

	pixel_shader = std::make_shared<D3D11_Shader>(context->GetSubSystem<Graphics>());
	pixel_shader->Create(ShaderScope_PS, path);

    return true;
}
