#pragma once
#include "IResource.h"

class Shader : public IResource
{
public:
	Shader(class Context* const context);
	~Shader() = default;

	virtual bool SaveToFile(const std::string& path) override;
	virtual bool LoadFromFile(const std::string& path) override;

	std::shared_ptr<D3D11_Shader> GetVertexShader() const { return vertex_shader; }
	std::shared_ptr<D3D11_Shader> GetPixelShader() const { return pixel_shader; }

private:
	std::shared_ptr<D3D11_Shader> vertex_shader;
	std::shared_ptr<D3D11_Shader> pixel_shader;
};

