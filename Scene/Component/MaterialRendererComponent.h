#pragma once
#include "IComponent.h"
class MaterialRendererComponent : public IComponent
{
public:
	using IComponent::IComponent;
	~MaterialRendererComponent() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	std::weak_ptr<Texture2D> GetTexture2D() const { return texture; }
	void SetTexture2D(const std::string& path);

	std::shared_ptr<D3D11_Shader> GetVertexShader() const { return vertex_shader; }
	std::shared_ptr<D3D11_Shader> GetPixelShader() const { return pixel_shader; }
	std::shared_ptr<D3D11_InputLayout> GetInputLayout() const { return input_layout; }

private:
	void SetStandardMaterial();

private:
	ResourceManager* resource_manager = nullptr;

	std::weak_ptr<Texture2D> texture;
	std::shared_ptr<D3D11_Shader> vertex_shader;
	std::shared_ptr<D3D11_Shader> pixel_shader;
	std::shared_ptr<D3D11_InputLayout> input_layout;
};

